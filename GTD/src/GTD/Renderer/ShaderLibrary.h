#pragma once
#include <unordered_map>
#include "../Util/Utils.h"
#include "../include/Logger.h"
#include "IShader.h"

namespace GTD
{
	class GTD_API ShaderLibrary
	{
	public:
		void Add(const Ref<IShader>& shader);
		void Add(const std::string& name, const Ref<IShader>& shader);
		Ref<IShader> Load(const std::string& name, const std::string& filePath);
		Ref<IShader> Load(const std::string& filePath);
		Ref<IShader> Get(const std::string& filePath);

	private:
		std::unordered_map < std::string, Ref<IShader>> m_Shaders;
	};
}