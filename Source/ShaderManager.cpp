#include "ShaderManager.hpp"

void ShaderManager::addShader(const std::string& shaderId, std::shared_ptr<Shader> shader)
{
    m_Shaders[shaderId] = shader;
}

void ShaderManager::useShader(const std::string& shaderId)
{
    m_Shaders[shaderId]->use();
}

void ShaderManager::unuseShader(const std::string& shaderId)
{
    m_Shaders[shaderId]->unuse();
}

std::shared_ptr<Shader> ShaderManager::getShader(const std::string& shaderId)
{
    return m_Shaders[shaderId];
}
