#version 330 core
layout(location=0) in vec4 centro;
layout(location=1) in vec2 apariencia;
uniform mat4 vista;
uniform mat4 proyeccion;
out vec2 uv;
flat out vec2 datos;
const vec2 vertices[6] = vec2[](
    vec2(-1,-1), vec2(1,-1), vec2(1,1),
    vec2(-1,-1), vec2(1,1), vec2(-1,1)
);
void main()
{
    uv = vertices[gl_VertexID];
    datos = apariencia;
    vec4 p = vista * vec4(centro.xyz,1);
    p.xy += uv * centro.w * vec2(1.0,1.37);
    gl_Position = proyeccion * p;
}
