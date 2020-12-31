#include "../PCH/PCH.h"
#include "ShaderLibrary.h"

namespace GTD
{
    void GTD::ShaderLibrary::Add(const Ref<IShader>& shader)
    {
        auto& name = shader->GetName();
        auto ret = m_Shaders.try_emplace(name, shader);
        GTD_ASSERT(ret.second, "Shader " + name + "already exists!");
        LOG_DEBUG("Added %s shader to library", name.c_str());
    }

    void GTD::ShaderLibrary::Add(const std::string& name, const Ref<IShader>& shader)
    {
        auto ret = m_Shaders.try_emplace(name, shader);
        GTD_ASSERT(ret.second, "Shader " + name + "already exists!");
        LOG_DEBUG("Added %s shader to library", name);
    }

    Ref<IShader> GTD::ShaderLibrary::Load(const std::string& name, const std::string& filePath)
    {
        auto shader = IShader::Create(filePath);
        Add(name, shader);
        return shader;
    }

    Ref<IShader> GTD::ShaderLibrary::Load(const std::string& filePath)
    {
        auto shader = IShader::Create(filePath);
        Add(shader);
        return shader;
    }

    Ref<IShader> GTD::ShaderLibrary::Get(const std::string& name)
    {
        GTD_ASSERT((m_Shaders.find(name) != m_Shaders.end()), ("Shader: " + name+ " doesn't exist!").c_str());
        return m_Shaders[name];
    }
}

