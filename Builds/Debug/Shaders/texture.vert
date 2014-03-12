#version 130

in vec2 in_Position;
in vec2 in_TexCoord;

out vec2 texCoord;

uniform mat4 in_MvpMatrix;

void main()
{
    gl_Position = in_MvpMatrix * vec4(in_Position, 0.0, 1.0);
    texCoord = in_TexCoord;
}
