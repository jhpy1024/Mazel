#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <vector>

Shader::Shader(const std::string& vertShader, const std::string& fragShader)
{
    auto vertSrc = getShaderSource(vertShader);
    auto fragSrc = getShaderSource(fragShader);

    createVertexShader(vertSrc);
    createFragmentShader(fragSrc);
    createProgram();
    freeResources();
}

Shader::~Shader()
{
    glDeleteProgram(m_Program);
}

void Shader::use()
{
    glUseProgram(m_Program);
}

void Shader::unuse()
{
    glUseProgram(0);
}

GLint Shader::getAttribLocation(const std::string& attribName)
{
    if (m_AttribLocations.find(attribName) == m_AttribLocations.end())
        m_AttribLocations[attribName] = glGetAttribLocation(m_Program, attribName.c_str());

    return m_AttribLocations[attribName];
}

GLint Shader::getUniformLocation(const std::string& uniformName)
{
    if (m_UniformLocations.find(uniformName) == m_UniformLocations.end())
        m_UniformLocations[uniformName] = glGetUniformLocation(m_Program, uniformName.c_str());

    return m_UniformLocations[uniformName];
}

void Shader::createProgram()
{
    m_Program = glCreateProgram();

    glAttachShader(m_Program, m_VertexShader);
    glAttachShader(m_Program, m_FragmentShader);

    glLinkProgram(m_Program);

    checkLinkStatus();
}

void Shader::freeResources()
{
    glDetachShader(m_Program, m_VertexShader);
    glDetachShader(m_Program, m_FragmentShader);

    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
}

void Shader::createFragmentShader(const std::string& source)
{
    auto cStrSource = source.c_str();

    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(m_FragmentShader, 1, &cStrSource, NULL);
    glCompileShader(m_FragmentShader);

    checkCompileStatus(m_FragmentShader);
}

void Shader::createVertexShader(const std::string& source)
{
    auto cStrSource = source.c_str();

    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(m_VertexShader, 1, &cStrSource, NULL);
    glCompileShader(m_VertexShader);

    checkCompileStatus(m_VertexShader);
}

void Shader::checkCompileStatus(GLuint shader)
{
    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        std::cerr << "Error compiling shader\n"
                     "------------------------" << std::endl;
        for (auto& c : errorLog)
            std::cerr << c;
        std::cerr << "------------------------" << std::endl;

        glDeleteShader(shader);
    }
}

void Shader::checkLinkStatus()
{
    GLint isLinked = 0;
    glGetProgramiv(m_Program, GL_LINK_STATUS, &isLinked);

    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(m_Program, maxLength, &maxLength, &errorLog[0]);

        std::cerr << "Error compiling shader\n"
                     "------------------------" << std::endl;
        for (auto& c : errorLog)
            std::cerr << c;
        std::cerr << "------------------------" << std::endl;

        glDeleteProgram(m_Program);
    }
}

std::string Shader::getShaderSource(const std::string& file) const
{
    std::ifstream fileStream(file);

    std::string currentLine;
    std::string fileContents;

    if (fileStream.is_open())
    {
        while (std::getline(fileStream, currentLine))
        {
            fileContents += currentLine += "\n";
        }
    }
    else
    {
        std::cerr << "Unable to open shader source file: " << file << std::endl;
    }

    return fileContents;
}
