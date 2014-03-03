#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include <map>
#include <memory>

#include "Shader.hpp"

class ShaderManager
{
public:
    void addShader(const std::string& shaderId, std::shared_ptr<Shader> shader);

    std::shared_ptr<Shader> getShader(const std::string& shaderId);

    void useShader(const std::string& shaderId);
    void unuseShader(const std::string& shaderId);

private:
    std::map<std::string, std::shared_ptr<Shader>> m_Shaders;
};

#endif // SHADER_MANAGER_HPP
