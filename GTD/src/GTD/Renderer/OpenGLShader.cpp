#include "../PCH/PCH.h"
#include "OpenGLShader.h"
#include "../include/Logger.h"

#include "../../Vendor/glm/gtc/type_ptr.hpp"

#include <fstream>

namespace GTD
{
	// We cannnot call glGetUniformLocation from try_emplace (I think it tries to stash the function pointer rather than the result)
	// We must wrap it in a lambda (which is nice for the debug messages and error check) so that it will be executed
	// The uniform calls are much cleaner looking with this macro
#define CACHE_UNIFORM_LOCATION m_Locations.try_emplace(name, [&](uint32_t renderid, const char* name, const std::string& shaderName) \
	{ GLint loc = glGetUniformLocation(renderid, name); \
	if(-1 != loc) { LOG_DEBUG("Cached uniform: %s in location: %u for Shader: %s", name, loc, shaderName.c_str()); return loc; } \
	else { LOG_WARN("Invalid uniform name: %s\r\nEnsure that you intended on the uniform %s being in Shader %s", name, name, shaderName.c_str()); return -1;} } \
	(m_RendererID, name.c_str(), m_Name)).first->second

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if ("vertex" == type) // should be a macro or some sort of constexp
		{
			return GL_VERTEX_SHADER;
		}
		else if ("pixel" == type || "fragment" == type)
		{
			return GL_FRAGMENT_SHADER;
		}

		GTD_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filePath) // probably will be different per platform
		:m_RendererID(-1)
	{
		std::string shaderSource = ReadFile(filePath);
		auto shaderSources = PreProcess(shaderSource);

		// assets/shaders/Texture.glsl --> extract "Texture"
		auto lastSlash = filePath.find_last_of("/\\"); // could be back or forward slash (thanks Windows..)
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1; // check to make sure that we actually have a slash

		auto lastDot = filePath.rfind('.'); // find the place of the file ext
		auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filePath.substr(lastSlash, count);

		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
		: m_RendererID(-1), m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filePath)
	{
		std::string result;

		std::ifstream in(filePath, std::ios::in, std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			LOG_WARN("Could not open file %s!", filePath.c_str());
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		// Yeah clean this up using regex
		// end regex
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			GTD_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			GTD_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(
				nextLinePos,
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		GLuint program = glCreateProgram();

		// We have a maximum number of shaders we're holding the shader IDs on the stack -- I don't imagine being more than 2, but allow up to MAX_SHADER_SOURCES
		GTD_ASSERT(shaderSources.size() <= MAX_SHADER_SOURCES, std::to_string(shaderSources.size()) + " shaders found. Max number of shaders is: " + std::to_string(MAX_SHADER_SOURCES));
		std::array<GLenum, MAX_SHADER_SOURCES> glShaderIds;
		int glShaderIDIndex = 0;

		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* cSource = source.c_str();
			glShaderSource(shader, 1, &cSource, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (GL_FALSE == isCompiled)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.
				LOG_WARN("%s", std::string(infoLog.begin(), infoLog.end()).c_str());
				GTD_ASSERT(false, "Shader compilation failure!"); // check which type failed

				// In this simple program, we'll just leave
				break;
			}

			// Attach our shaders to our program
			glAttachShader(program, shader);
			glShaderIds[glShaderIDIndex++] = shader;

		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (GL_FALSE == isLinked)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.

			for (auto id : glShaderIds)
			{
				glDeleteShader(id);
			}

			// Use the infoLog as you see fit.
			LOG_WARN("%s", std::string(infoLog.begin(), infoLog.end()).c_str());
			GTD_ASSERT(false, "Shader shader link failure!");

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIds)
		{
			glDetachShader(program, id);
		}

		m_RendererID = program;
	}

	const std::string& OpenGLShader::GetFilename(const std::string& filePath) const
	{
		// assets/shaders/Texture.glsl
		auto lastSlash = filePath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1; // check to make sure that we actually have a slas

		auto lastDot = filePath.rfind('.'); // find the place of the file ext
		auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
		return filePath.substr(lastSlash, lastDot);
	}


	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniform(const std::string& name, int value) const
	{
		// checks to see if the name exists in the cache map -- otherwise get the location and put in into cache
		// then bind the value to the uniform
		if (m_Locations.find(name) != m_Locations.end())
		{
			glUniform1i(m_Locations.at(name), value);
		}
		else
		{
			glUniform1i(CACHE_UNIFORM_LOCATION, value);
		}
	}
	void OpenGLShader::UploadUniform(const std::string& name, int values[], uint32_t count) const
	{
		if (m_Locations.find(name) != m_Locations.end())
		{
			glUniform1iv(m_Locations.at(name), count, values);
		}
		else
		{
			glUniform1iv(CACHE_UNIFORM_LOCATION, count, values);
		}
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::mat3& mat, bool transpose) const
	{
		if (m_Locations.find(name) != m_Locations.end())
		{
			glUniformMatrix3fv(
				m_Locations.at(name),
				1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
		}
		else
		{
			glUniformMatrix3fv(
				CACHE_UNIFORM_LOCATION,
				1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
		}
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::mat4& mat, bool transpose) const
	{
		if (m_Locations.find(name) != m_Locations.end())
		{
			glUniformMatrix4fv(
				m_Locations.at(name),
				1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
		}
		else
		{
			glUniformMatrix4fv(
				CACHE_UNIFORM_LOCATION,
				1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(mat));
		}


	}
	void OpenGLShader::UploadUniform(const std::string& name, float value) const
	{
		if (m_Locations.find(name) != m_Locations.end())
		{
			glUniform1f(m_Locations.at(name), value);
		}
		else
		{
			glUniform1f(CACHE_UNIFORM_LOCATION, value);
		}
	}
	void OpenGLShader::UploadUniform(const std::string& name, const glm::vec2& values) const
	{
		if (m_Locations.find(name) != m_Locations.end())
		{
			glUniform2f(m_Locations.at(name), values.x, values.y);
		}
		else
		{
			glUniform2f(CACHE_UNIFORM_LOCATION, values.x, values.y);
		}
	}
	void OpenGLShader::UploadUniform(const std::string& name, const glm::vec3& values) const
	{
		if (m_Locations.find(name) != m_Locations.end())
		{
			glUniform3f(m_Locations.at(name), values.x, values.y, values.z);
		}
		else
		{
			glUniform3f(CACHE_UNIFORM_LOCATION, values.x, values.y, values.z);
		}
	}
	void OpenGLShader::UploadUniform(const std::string& name, const glm::vec4& values) const
	{
		if (m_Locations.find(name) != m_Locations.end())
		{
			glUniform4f(m_Locations.at(name), values.r, values.g, values.b, values.a);
		}
		else
		{
			glUniform4f(CACHE_UNIFORM_LOCATION, values.r, values.g, values.b, values.a);
		}
	}

	void OpenGLShader::Set(const std::string& name, const glm::vec3& value)
	{
		UploadUniform(name, value);
	}

	void OpenGLShader::Set(const std::string& name, const glm::vec4& value)
	{
		UploadUniform(name, value);
	}

	void OpenGLShader::Set(const std::string& name, const glm::mat4& mat)
	{
		UploadUniform(name, mat);
	}

	void OpenGLShader::Set(const std::string& name, int value)
	{
		UploadUniform(name, value);
	}

	void OpenGLShader::Set(const std::string& name, int values[], uint32_t size)
	{
		UploadUniform(name, values, size);
	}
}