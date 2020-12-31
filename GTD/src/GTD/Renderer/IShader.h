#pragma once
#include "../include/Core.h"
#include "../Util/Utils.h"

namespace GTD
{
	class GTD_API IShader
	{
	public:
		// load shader from file
		static Ref<IShader> Create(const std::string& filePath);

		virtual const std::string& GetName() const = 0;

		//load shader from text
		static Ref<IShader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

		virtual void Bind() const = 0; // Tell GPU that we are about to describe data for this shader
		virtual void Unbind() const = 0;


		/* Uniform type upload by type
		 * In shader program the uniform variable types will map to the names
		 * Such as 	uniform vec4 u_Color; is a uniform with a 4 dim vector with name u_Color
		 */
		virtual void UploadUniform(const std::string& name, int value) const = 0;
		virtual void UploadUniform(const std::string& name, int values[], uint32_t count) const = 0;

		virtual void UploadUniform(const std::string& name, const glm::mat4& mat, bool transpose = false) const = 0;
		virtual void UploadUniform(const std::string& name, const glm::mat3& mat, bool transpose = false) const = 0;

		virtual void UploadUniform(const std::string& name, float value) const = 0;
		virtual void UploadUniform(const std::string& name, const glm::vec2& value) const = 0;
		virtual void UploadUniform(const std::string& name, const glm::vec3& value) const = 0;
		virtual void UploadUniform(const std::string& name, const glm::vec4& value) const = 0;
		
		virtual void Set(const std::string& name, const glm::vec3& value) = 0;
		virtual void Set(const std::string& name, const glm::vec4& value) = 0;
		virtual void Set(const std::string& name, const glm::mat4& mat) = 0;
		virtual void Set(const std::string& name, int value) = 0;
		virtual void Set(const std::string& name, int value[], uint32_t size) = 0;


	};
}


