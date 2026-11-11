#version 330 core
in vec2 posicion;
flat in float brillo;
flat in float calido;
flat in float veladora;
out vec4 color;

void main()
{
    float radio = dot(posicion,posicion);
    if (radio >= 1.0) discard;
    float borde = 1.0 - radio;
    float intensidad = brillo * borde * borde * exp(-2.3 * radio);
    vec3 ambar = mix(vec3(1.0,0.54,0.20),vec3(1.0,0.65,0.32),calido);
    if (veladora > 0.5)
    {
        // Un núcleo pequeño conserva presencia a distancia. El anillo exterior se desvanece suavemente.
        float nucleo = exp(-25.0 * radio) * 0.44;
        float entorno = borde * borde * exp(-1.9 * radio) * 0.56;
        vec3 luz = vec3(1.0,0.78,0.44)*nucleo + vec3(1.0,0.52,0.21)*entorno;
        color = vec4(luz*brillo,0.0);
    }
    else color = vec4(ambar * intensidad,0.0);
}
