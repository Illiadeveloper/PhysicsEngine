#version 420 core
out vec4 FragColor;

in vec3 outPos;
in vec3 outNormal;
in vec3 outCameraPos;

layout(std140, binding = 1) uniform DirectionalLightUBO {
  vec3 direction;

  vec3 lightColor;
  float intensity;
} DirectionalLight;

layout(std140, binding = 2) uniform PointLightUBO {
  vec3 position;
  float linear;

  vec3 lightColor;
  float intensity;

  float constant;
  float quadratic;
} PointLight;

layout(std140, binding = 3) uniform SpotLightUBO {
  vec3 position;
  float cutOff;

  vec3 direction;
  float outerCutOff;

  float linear;
  float constant;
  float quadratic;

  vec3 lightColor;
  float intensity;
} SpotLight;

layout(std140, binding = 4) uniform MaterialUBO {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
} material;

uniform vec3 uObjectColor;

vec3 CalcDirectionalLight(vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-DirectionalLight.direction);
    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine
    vec3 ambient = material.ambient * DirectionalLight.lightColor * DirectionalLight.intensity;
    vec3 diffuse = material.diffuse * diff * DirectionalLight.lightColor * DirectionalLight.intensity;
    vec3 specular = material.specular * spec * DirectionalLight.lightColor * DirectionalLight.intensity;

    return (ambient + diffuse + specular) * uObjectColor;
}

vec3 CalcPointLight(vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(PointLight.position - outPos);
    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distanceToLight = length(PointLight.position - outPos);
    float attenuation = 1.0 / (PointLight.constant + PointLight.linear * distanceToLight + PointLight.quadratic * (distanceToLight * distanceToLight));
    // combine
    vec3 ambient = material.ambient * PointLight.lightColor * PointLight.intensity;
    vec3 diffuse = material.diffuse * diff * PointLight.lightColor * PointLight.intensity;
    vec3 specular = material.specular * spec * PointLight.lightColor * PointLight.intensity;
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular) * uObjectColor;
}

vec3 CalcSpotLight(vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(SpotLight.position - fragPos);
    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distanceToLight = length(SpotLight.position - outPos);
    float attenuation = 1.0 / (SpotLight.constant + SpotLight.linear * distanceToLight + SpotLight.quadratic * (distanceToLight * distanceToLight));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-SpotLight.direction));
    float epsilon = SpotLight.cutOff - SpotLight.outerCutOff;
    float intensity = clamp((theta - SpotLight.outerCutOff) / epsilon, 0.0, 1.0);
    // combine
    vec3 ambient = material.ambient * SpotLight.lightColor * SpotLight.intensity;
    vec3 diffuse = material.diffuse * diff * SpotLight.lightColor * SpotLight.intensity;
    vec3 specular = material.specular * spec * SpotLight.lightColor * SpotLight.intensity;
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular) * uObjectColor;
}

void main() {
  vec3 norm = normalize(outNormal);
  vec3 viewDir = normalize(outCameraPos - outPos);

  vec3 result = CalcDirectionalLight(norm, viewDir);
  result += CalcPointLight(norm, outPos, viewDir);
  result += CalcSpotLight(norm, outPos, viewDir);

  FragColor = vec4(result, 1.0);
}
