#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include <map>
#include <memory>

#include "Shader.hpp"

enum class ShaderType
{
    Sprite,
};

class ShaderManager
{
public:
    ShaderManager();

    std::shared_ptr<Shader> getShader(ShaderType type);

    void useShader(ShaderType type);
    void unuseShader(ShaderType type);

private:
    void createShaders();

private:
    std::map<ShaderType, std::shared_ptr<Shader>> m_Shaders;
};

#endif // SHADER_MANAGER_HPP
