#version 130

in vec2 texCoord;

uniform sampler2D in_Texture;

out vec4 out_Color;

void main()
{
    out_Color = vec4(1.0, 0.0, 0.0, 1.0);
}
