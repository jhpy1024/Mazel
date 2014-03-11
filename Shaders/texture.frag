#version 130

in vec2 texCoord;

uniform sampler2D in_Texture;

out vec2 out_Color;

void main()
{
    out_Color = texture(in_Texture, texCoord);
}
