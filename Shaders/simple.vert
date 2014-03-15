#version 130

in vec2 in_Position;
in vec4 in_Color;
uniform mat4 in_MvpMatrix;

out vec4 color;

uniform vec2 in_PlayerPosition;
out float distanceToPlayer;

void main()
{
    gl_Position = in_MvpMatrix * vec4(in_Position, 0.0, 1.0);
    color = in_Color;

    distanceToPlayer = distance(in_PlayerPosition, vec2(gl_Position.xy));
}
