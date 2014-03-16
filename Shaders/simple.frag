#version 130

in vec4 color;
out vec4 out_Color;

in float distanceToPlayer;

flat in int lightingEnabled;

void main()
{
	if (lightingEnabled == 1)
	{
		out_Color = color * (1.0 / (distanceToPlayer / 30.0));
	}
	else
	{
		out_Color = color;
	}
}
