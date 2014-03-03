#include "ShaderManager.hpp"

ShaderManager::ShaderManager()
{
    createShaders();
}

std::shared_ptr<Shader> ShaderManager::getShader(ShaderType type)
{
    return m_Shaders[type];
}

void ShaderManager::createShaders()
{
    m_Shaders[ShaderType::Sprite] = std::make_shared<Shader>("Shaders/sprite.vert", "Shaders/sprite.frag");
}

void ShaderManager::useShader(ShaderType type)
{
    m_Shaders[type]->use();
}

void ShaderManager::unuseShader(ShaderType type)
{
    m_Shaders[type]->unuse();
}
