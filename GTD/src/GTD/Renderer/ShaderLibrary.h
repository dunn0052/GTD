#pragma once
#include <unordered_map>
#include "../Util/Utils.h"
#include "../include/Logger.h"
#include "IShader.h"

namespace GTD
{
	class ShaderLibrary
	{
	public:
		GTD_API void Add(const Ref<IShader>& shader);
		GTD_API void Add(const std::string& name, const Ref<IShader>& shader);
		GTD_API Ref<IShader> Load(const std::string& name, const std::string& filePath);
		GTD_API Ref<IShader> Load(const std::string& filePath);
		GTD_API Ref<IShader> Get(const std::string& filePath);

	private:
		std::unordered_map < std::string, Ref<IShader>> m_Shaders;
	};
}