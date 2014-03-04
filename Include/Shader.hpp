#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <map>

#include <GL/glew.h>
#include <GL/gl.h>

class Shader
{
public:
    Shader(const std::string& vertShader, const std::string& fragShader);
    ~Shader();

    void use();
    void unuse();

    GLint getAttribLocation(const std::string& attribName);
    GLint getUniformLocation(const std::string& uniformName);

private:
    std::string getShaderSource(const std::string& file) const;

    void createVertexShader(const std::string& source);
    void createFragmentShader(const std::string& source);
    void createProgram();
    void freeResources();

    void checkLinkStatus();
    void checkCompileStatus(GLuint shader);

private:
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_Program;

    std::map<std::string, GLint> m_UniformLocations;
    std::map<std::string, GLint> m_AttribLocations;
};

#endif // SHADER_HPP
