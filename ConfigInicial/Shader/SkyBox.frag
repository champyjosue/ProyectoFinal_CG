#version 330 core
in vec3 TexCoords;
out vec4 color;

uniform samplerCube skybox;

// Reflect the neighboring face into the transition band so its edge can be
// blended without changing any of the original JPEGs.
vec3 sampleFace(vec3 direction, int axis)
{
    vec3 local = direction / abs(direction[axis]);
    vec3 magnitude = abs(local);
    local = sign(local) * min(1.0 - abs(1.0 - magnitude), vec3(0.999));
    local[axis] = sign(direction[axis]);
    return texture(skybox, local).rgb;
}

vec3 sampleSky(vec3 direction)
{
    vec3 axes = abs(direction);
    float major = max(axes.x, max(axes.y, axes.z));
    vec3 weights = smoothstep(vec3(0.90), vec3(1.0), axes / major);
    float total = weights.x + weights.y + weights.z;
    if (weights.x * weights.y + weights.y * weights.z + weights.z * weights.x > 0.0)
    {
        vec3 blended = vec3(0.0);
        if (weights.x > 0.0) blended += weights.x * sampleFace(direction, 0);
        if (weights.y > 0.0) blended += weights.y * sampleFace(direction, 1);
        if (weights.z > 0.0) blended += weights.z * sampleFace(direction, 2);
        return blended / total;
    }
    return texture(skybox, direction).rgb;
}

void main()
{
    vec3 sky = sampleSky(TexCoords);
    if (TexCoords.z < 0.0)
    {
        // front.jpg is the -Z face. Cover only its baked lunar disc with
        // adjacent sky. The scene's animated moon remains a separate object.
        vec2 uv = 0.5 * (TexCoords.xy / TexCoords.z + 1.0);
        float distanceToMoon = distance(uv, vec2(0.287, 0.256));
        if (distanceToMoon < 0.073)
        {
            vec2 donor = uv - vec2(0.130, 0.0);
            vec3 nearbySky = texture(skybox, vec3(1.0 - 2.0 * donor, -1.0)).rgb;
            nearbySky = clamp(nearbySky + vec3(9.0, 11.0, 14.0) / 255.0, 0.0, 1.0);
            sky = mix(nearbySky, sky, smoothstep(0.045, 0.073, distanceToMoon));
        }
    }
    color = vec4(sky, 1.0);
}
