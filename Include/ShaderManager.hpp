#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include "Shader.hpp"

#include <string>
#include <memory>

class ShaderManager
{
public:
    void addShader(const std::string& shaderId, std::shared_ptr<Shader> shader);

    void useShader(const std::string& shaderId);
    void unuseShader(const std::string& shaderId);

    std::shared_ptr<Shader> getShader(const std::string& shaderId);

private:
    std::map<std::string, std::shared_ptr<Shader>> m_Shaders;
};

#endif // SHADER_MANAGER_HPP
