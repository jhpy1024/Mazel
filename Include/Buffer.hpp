#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>

class Buffer
{
public:
    void setData(const std::vector<float>& data);

    void bind();

private:
    GLuint m_Buffer;
};

#endif // BUFFER_HPP
