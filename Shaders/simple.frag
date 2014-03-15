#version 130

in vec4 color;
out vec4 out_Color;

in float distanceToPlayer;

void main()
{
    if (distanceToPlayer == 0.0)
    {
        out_Color = color;
    }
    else
    {
        out_Color = color * (1.0 / (distanceToPlayer / 100.0));
    }
}
