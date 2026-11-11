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
// Defaults conservan el comportamiento de otros ejemplos que usan este shader.
uniform vec2 textureTiling = vec2(1.0);
uniform vec3 emissionColor = vec3(0.0);
uniform vec3 objectGlow = vec3(0.0);
uniform float emissionPulse = 1.0;
uniform bool hasSpecularTexture = false;
uniform bool shadowEnabled = false;
uniform sampler2DShadow shadowMap;
uniform mat4 shadowClip;
uniform bool alumbradaEnabled = false;
uniform float alumbradaExposure = 1.0;
uniform float alumbradaEmission = 1.0;
uniform bool alumbrada6c = false;
uniform bool tierraMixquic = false;
uniform bool revision6c1 = false;
uniform bool tierraLigera6c1 = false;
uniform int fuenteDecorativa = 0;
uniform sampler2D mapaAlumbrada;
uniform sampler2D muestraTierra;
uniform vec2 extensionAlumbrada;

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

void TierraRevisada(float huella)
{
    const mat2 giro = mat2(0.82,-0.57,0.57,0.82);
    vec4 grano = texture(muestraTierra,FragPos.xz * 0.176);
    float macro = grano.g;
    if (!tierraLigera6c1)
        macro = texture(muestraTierra,(giro*FragPos.xz)*0.049+vec2(0.31,0.63)).g;

    float borde = smoothstep(0.15,0.84,huella+(macro-0.5)*0.72+(grano.g-0.5)*0.36);
    float irregularidad = mix(macro,grano.g,0.36);
    vec3 tierra = mix(vec3(0.164,0.126,0.090),vec3(0.275,0.227,0.171),irregularidad);
    vec3 sendero = mix(vec3(0.271,0.212,0.158),vec3(0.431,0.370,0.303),irregularidad);
    float polvo = smoothstep(0.37,0.70,grano.g)*borde;
    baseDiffuse = mix(tierra,sendero,borde) * mix(0.60,1.34,grano.r);
    baseDiffuse += vec3(0.033,0.026,0.018)*polvo;
    baseDiffuse = mix(baseDiffuse,vec3(0.329,0.296,0.245),grano.b*0.37);
    float margen = 1.0 - abs(borde*2.0-1.0);
    float musgo = smoothstep(0.54,0.79,irregularidad)*(1.0-borde);
    baseDiffuse = mix(baseDiffuse,vec3(0.174,0.192,0.106),musgo*0.33);
    baseDiffuse = mix(baseDiffuse,vec3(0.61,0.275,0.047),grano.a*max(margen,0.16*borde)*0.78);
    baseSpecular = vec3(0.013);
}

void main()
{
    safeShininess = max(material.shininess, 1.0);

    // 1. Determinar color base (Textura vs Material .mtl)
    if (hasTexture == 1)
    {
        vec4 t = texture(texture_diffuse1, TexCoords * textureTiling);
        baseDiffuse = t.rgb;

        // Si el PNG tiene canal alfa real (< 0.99), usamos t.a;
        // si no (ej. JPG con fondo negro como TumbaTransparente), usamos t.r
        maskAlpha = (t.a < 0.99) ? t.a : t.r;

        baseSpecular = hasSpecularTexture ? texture(texture_specular1, TexCoords * textureTiling).rgb : vec3(0.12);
    }
    else
    {
        baseDiffuse = materialColor;
        maskAlpha = 1.0;
        baseSpecular = vec3(0.2);
    }

    vec3 norm = normalize(Normal);
    float reboteCalido = 0.0;
    float reboteVeladora = 0.0;
    vec3 emisionVisible = emissionColor;
    if (alumbrada6c)
    {
        if (fuenteDecorativa != 0)
            baseDiffuse = min(baseDiffuse, vec3(0.88, 0.76, 0.64));
        if (fuenteDecorativa == 3)
        {
            if (emissionColor.r > 1.7)
                emisionVisible = vec3(2.75,1.53,0.39);
            else if (emissionColor.r > 0.3)
            {
                baseDiffuse = vec3(0.47,0.225,0.055);
                emisionVisible = vec3(0.16,0.058,0.012);
            }
        }
        vec2 mapaUV = FragPos.xz / extensionAlumbrada * 0.5 + 0.5;
        if (FragPos.y < 3.4 && all(greaterThanEqual(mapaUV,vec2(0))) && all(lessThanEqual(mapaUV,vec2(1))))
        {
            vec3 campo = texture(mapaAlumbrada,mapaUV).rgb;
            reboteCalido = campo.g * (1.0 - smoothstep(1.0,3.4,FragPos.y));
            if (revision6c1)
                reboteVeladora = campo.b * (1.0-smoothstep(0.58,1.7,FragPos.y));
            if (tierraMixquic && revision6c1)
                TierraRevisada(campo.r);
            else if (tierraMixquic)
            {
                vec3 suelo = texture(muestraTierra,FragPos.xz * 0.29).rgb;
                float borde = smoothstep(0.20,0.80,campo.r + (suelo.g - 0.5) * 0.32);
                vec3 tierra = mix(vec3(0.204,0.190,0.149),vec3(0.347,0.318,0.241),suelo.g);
                vec3 compacta = mix(vec3(0.31,0.267,0.216),vec3(0.438,0.386,0.316),suelo.g);
                baseDiffuse = mix(tierra,compacta,borde) * mix(0.76,1.25,suelo.r);
                float margen = 1.0 - abs(borde * 2.0 - 1.0);
                float hierba = smoothstep(0.56,0.78,suelo.g) * (1.0-borde);
                baseDiffuse = mix(baseDiffuse,vec3(0.205,0.239,0.124),hierba * 0.58);
                baseDiffuse = mix(baseDiffuse,vec3(0.68,0.29,0.035),margen * suelo.b * 0.72);
                baseSpecular = vec3(0.018);
            }
        }
    }
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
        vec4 t = texture(texture_diffuse1, TexCoords * textureTiling);
        if (t.a < 0.1)
            discard;
    }

    // Llamas/vidrios visibles en la noche sin ampliar las cinco luces puntuales.
    if (alumbradaEnabled)
    {
        // Rebote localizado precalculado. Las cinco fuentes directas conservan su pase original.
        float orientacion = 0.38 + 0.62 * max(norm.y,0.0);
        result += baseDiffuse * vec3(1.04,0.51,0.16) * (reboteCalido * orientacion);
        result += baseDiffuse * vec3(0.95,0.49,0.20) * (reboteVeladora * orientacion);
        result += emisionVisible * emissionPulse * alumbradaEmission + objectGlow;
        result *= alumbradaExposure;
    }
    else
    {
        result += emissionColor * emissionPulse + objectGlow;
    }
    vec3 mapped = vec3(1.0) - exp(-max(result, vec3(0.0)));
    color = vec4(pow(mapped, vec3(1.0 / 2.2)), finalAlpha);
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

    if (shadowEnabled)
    {
        vec4 proyectado = shadowClip * vec4(FragPos,1.0);
        vec3 uvz = proyectado.xyz / proyectado.w * 0.5 + 0.5;
        if (all(greaterThan(uvz,vec3(0.0))) && all(lessThan(uvz,vec3(1.0))))
        {
            float sesgo = mix(0.00115,0.00038,diff);
            float visible = texture(shadowMap,vec3(uvz.xy,uvz.z-sesgo));
            return ambient + (diffuse + specular) * mix(0.16,1.0,visible);
        }
    }
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
