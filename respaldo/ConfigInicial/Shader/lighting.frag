#version 330 core

#define NUMBER_OF_POINT_LIGHTS 5

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Estructura para Sol y Luna (Practica 8)
struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NUMBER_OF_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;

// Uniforms de Sol y Luna
uniform Light sun;
uniform Light moon;
uniform bool sunEnabled;
uniform bool moonEnabled;

// Samplers enviados por Mesh.h
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

// 0 = objeto OPACO, 1 = objeto TRANSPARENTE
uniform int transparency;

// Color del .mtl y bandera de textura enviados por Mesh.h
uniform vec3 materialColor;
uniform int hasTexture;

// Valores base del fragmento
vec3 baseDiffuse;
vec3 baseSpecular;
float maskAlpha;
float safeShininess;

// Prototipos
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSimpleLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    safeShininess = max(material.shininess, 1.0);

    // 1. Determinar color base (Textura vs Material .mtl)
    if (hasTexture == 1)
    {
        vec4 t = texture(texture_diffuse1, TexCoords);
        baseDiffuse = t.rgb;

        // Si el PNG tiene canal alfa real (< 0.99), usamos t.a;
        // si no (ej. JPG con fondo negro como TumbaTransparente), usamos t.r
        maskAlpha = (t.a < 0.99) ? t.a : t.r;

        baseSpecular = texture(texture_specular1, TexCoords).rgb;
    }
    else
    {
        baseDiffuse = materialColor;
        maskAlpha = 1.0;
        baseSpecular = vec3(0.2);
    }

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // 2. Acumular iluminacion
    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    for (int i = 0; i < NUMBER_OF_POINT_LIGHTS; i++)
    {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }

    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    if (sunEnabled)
    {
        result += CalcSimpleLight(sun, norm, FragPos, viewDir);
    }

    if (moonEnabled)
    {
        result += CalcSimpleLight(moon, norm, FragPos, viewDir);
    }

    // 3. Manejo de transparencia con 0 y 1
    float finalAlpha = 1.0;
    if (transparency == 1)
    {
        finalAlpha = maskAlpha;
        if (finalAlpha < 0.1)
            discard;
    }
    else if (hasTexture == 1)
    {
        // Recorte basico para hojas de arboles/flores en PNG con fondo transparente
        vec4 t = texture(texture_diffuse1, TexCoords);
        if (t.a < 0.1)
            discard;
    }

    color = vec4(result, finalAlpha);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    if (length(light.direction) < 0.0001)
        return vec3(0.0);

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), safeShininess);

    vec3 ambient = light.ambient * baseDiffuse;
    vec3 diffuse = light.diffuse * diff * baseDiffuse;
    vec3 specular = light.specular * spec * baseSpecular;

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    float distance = length(light.position - fragPos);
    float denom = light.constant + light.linear * distance + light.quadratic * (distance * distance);
    if (denom <= 0.0001)
        return vec3(0.0); // Si la luz no fue configurada en main, se ignora sin causar error

    float attenuation = 1.0 / denom;

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), safeShininess);

    vec3 ambient = light.ambient * baseDiffuse * attenuation;
    vec3 diffuse = light.diffuse * diff * baseDiffuse * attenuation;
    vec3 specular = light.specular * spec * baseSpecular * attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    float distance = length(light.position - fragPos);
    float denom = light.constant + light.linear * distance + light.quadratic * (distance * distance);
    if (denom <= 0.0001 || length(light.direction) < 0.0001)
        return vec3(0.0);

    float attenuation = 1.0 / denom;

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), safeShininess);

    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / max(epsilon, 0.0001), 0.0, 1.0);

    vec3 ambient = light.ambient * baseDiffuse * attenuation * intensity;
    vec3 diffuse = light.diffuse * diff * baseDiffuse * attenuation * intensity;
    vec3 specular = light.specular * spec * baseSpecular * attenuation * intensity;

    return (ambient + diffuse + specular);
}

vec3 CalcSimpleLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), safeShininess);

    vec3 ambient = light.ambient * baseDiffuse;
    vec3 diffuse = light.diffuse * diff * baseDiffuse;
    vec3 specular = light.specular * spec * baseSpecular;

    return (ambient + diffuse + specular);
}