#version 130

in vec4 color;
out vec4 out_Color;

in float distanceToPlayer;

void main()
{
    out_Color = color;

    if (distanceToPlayer >= 300.f)
    {
        out_Color *= 0.3f;
    }
}
