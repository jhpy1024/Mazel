#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <GL/gl.h>

#include <string>

class Shader
{
public:
    Shader(const std::string& vertexFile, const std::string& fragmentFile);

    GLint getAttribLocation(const std::string& name);

    void use();
    void unuse();

private:
    std::string getFileContents(const std::string& file) const;

    void createVertexShader(const std::string& source);
    void createFragmentShader(const std::string& source);
    void createProgram();

    void checkShaderCompilation(GLuint shader);

private:
    GLuint m_VertexShader;
    GLuint m_FragmentShader;
    GLuint m_Program;
};

#endif // SHADER_HPP
