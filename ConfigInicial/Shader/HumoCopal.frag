#version 330 core
in vec2 uv;
flat in vec2 datos;
out vec4 color;
void main()
{
    float offset = 0.14 * sin(uv.y * 4.0 + datos.y);
    vec2 p = vec2(uv.x - offset,uv.y);
    float velo = 1.0 - smoothstep(0.13,0.91,length(p));
    float forma = 0.80 + 0.10*sin(8.0*p.x+5.0*p.y+datos.y)
                      + 0.10*cos(7.0*p.y-4.0*p.x-datos.y);
    color = vec4(0.62,0.64,0.70,velo*velo*forma*datos.x);
}
