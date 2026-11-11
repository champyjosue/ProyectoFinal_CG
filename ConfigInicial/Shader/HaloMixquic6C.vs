#version 330 core
layout(location=0) in vec3 centro;
layout(location=1) in vec2 esquina;
layout(location=2) in vec3 parametros;
uniform mat4 vista;
uniform mat4 proyeccion;
uniform float tiempo;
out vec2 posicion;
flat out float brillo;
flat out float calido;
flat out float veladora;

void main()
{
    vec4 punto = vista * vec4(centro,1.0);
    float radio = parametros.x;
    punto.xy += esquina * radio;
    veladora = parametros.z;
    punto.z += veladora > 0.5 ? min(radio * 0.47,0.105) : min(radio * 0.56, 0.18);
    brillo = parametros.y * (0.95 + 0.05 * sin(tiempo * 6.0 + centro.x * 8.0 + centro.z));
    calido = smoothstep(0.20,0.24,radio);
    posicion = esquina;
    gl_Position = proyeccion * punto;
}
