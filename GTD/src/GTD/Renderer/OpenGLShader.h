#pragma once
#include <string>
#include <unordered_map>
#include <regex>

#include "IShader.h"
#include "BufferElement.h"

namespace GTD
{
	/*regex stuff
	const static std::string POUND_TYPE = "#type";
	const static std::string SHADER_PIXEL = "pixel";
	const static std::string SHADER_VERTEX = "vertex";
	const static std::string SHADER_FRAGMENT = "fragment";
	const static std::regex finde_shader("#type \w+\n(.* ?)#type \w +\n");
	*/


	static constexpr uint16_t MAX_SHADER_SOURCES = 16; // hardcoded here because we are setting up a stack allocated array

	static GLenum ShaderDataTypeTOOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::FLOAT:
		case ShaderDataType::FLOAT2:
		case ShaderDataType::FLOAT3:
		case ShaderDataType::FLOAT4:
		case ShaderDataType::MAT3:
		case ShaderDataType::MAT4:
			return GL_FLOAT;
		case ShaderDataType::INT:
		case ShaderDataType::INT2:
		case ShaderDataType::INT3:
		case ShaderDataType::INT4:
			return GL_INT;
		case ShaderDataType::BOOL:
			return GL_BOOL;
		}
		GTD_ASSERT(false, "Uknown type!");
		return 0;
	}

	class OpenGLShader : public IShader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		const std::string& GetName() const override { return m_Name; }

		void Bind() const;
		void Unbind() const;

		void UploadUniform(const std::string& name, int value) const;
		void UploadUniform(const std::string& name, int values[], uint32_t count) const override;
		
		void UploadUniform(const std::string& name, const glm::mat4& mat, bool transpose = false) const;
		void UploadUniform(const std::string& name, const glm::mat3& mat, bool transpose = false) const;

		void UploadUniform(const std::string& name, float value) const;
		void UploadUniform(const std::string& name, const glm::vec2& value) const;
		void UploadUniform(const std::string& name, const glm::vec3& value) const;
		void UploadUniform(const std::string& name, const glm::vec4& value) const;

		void Set(const std::string& name, const glm::vec3& value) override;
		void Set(const std::string& name, const glm::vec4& value) override;
		void Set(const std::string& name, const glm::mat4& mat) override;
		void Set(const std::string& name, int value) override;
		void Set(const std::string& name, int value[], uint32_t size) override;

	private:
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		const std::string& GetFilename(const std::string& filePath) const;

	private:
		uint32_t m_RendererID;
		mutable std::unordered_map<std::string, GLint> m_Locations;
		std::string m_Name;
	};
}


