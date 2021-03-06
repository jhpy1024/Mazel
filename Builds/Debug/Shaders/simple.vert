#version 130

in vec2 in_Position;
in vec4 in_Color;
uniform mat4 in_MvpMatrix;

out vec4 color;

void main()
{
    gl_Position = in_MvpMatrix * vec4(in_Position, 0.0, 1.0);
    color = in_Color;
}
