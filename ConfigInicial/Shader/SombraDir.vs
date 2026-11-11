#version 330 core
layout(location=0) in vec3 position;
uniform mat4 luzClip;
void main() { gl_Position = luzClip * vec4(position,1.0); }
