#include "Shader.hpp"

#include <fstream>
#include <iostream>

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
{
    auto vertexSrc = getFileContents(vertexFile);
    auto fragmentSrc = getFileContents(fragmentFile);

    createVertexShader(vertexSrc);
    createFragmentShader(fragmentSrc);
    createProgram();
}

GLint Shader::getAttribLocation(const std::string& name)
{
    return glGetAttribLocation(m_Program, name.c_str());
}

void Shader::use()
{
    glUseProgram(m_Program);
}

void Shader::unuse()
{
    glUseProgram(0);
}

void Shader::createVertexShader(const std::string& source)
{
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);

    auto sourceCStr = source.c_str();

    glShaderSource(m_VertexShader, 1, &sourceCStr, NULL);
    glCompileShader(m_VertexShader);
}

void Shader::createFragmentShader(const std::string& source)
{
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    auto sourceCStr = source.c_str();

    glShaderSource(m_FragmentShader, 1, &sourceCStr, NULL);
    glCompileShader(m_FragmentShader);
}

void Shader::createProgram()
{
    m_Program = glCreateProgram();

    glAttachShader(m_Program, m_VertexShader);
    glAttachShader(m_Program, m_FragmentShader);

    glLinkProgram(m_Program);
}

std::string Shader::getFileContents(const std::string& file) const
{
    std::ifstream fileStream(file);

    std::string currentLine;
    std::string fileContents;

    if (fileStream.is_open())
    {
        while (std::getline(fileStream, currentLine))
        {
            fileContents += currentLine;
        }
    }
    else
    {
        std::cerr << "Unable to open shader source file: " << file << std::endl;
    }

    return fileContents;
}
