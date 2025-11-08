#version 420 core
out vec4 FragColor;

in vec3 outPos;
in vec3 outNormal;
in vec3 outCameraPos;

#define MAX_DIRECTIONALS 4
#define MAX_POINTS 16
#define MAX_SPOTS 16

struct DirectionalLightData {
  vec3 direction;

  vec3 lightColor;
  float intensity;
};

struct PointLightData {
  vec3 position;
  float linear;

  vec3 lightColor;
  float intensity;

  float constant;
  float quadratic;
};

struct SpotLightData {
  vec3 position;
  float cutOff;

  vec3 direction;
  float outerCutOff;

  float linear;
  float constant;
  float quadratic;

  vec3 lightColor;
  float intensity;
};

layout(std140, binding = 1) uniform DirectionalLightUBO {
  int size; 
  DirectionalLightData data[MAX_DIRECTIONALS];
} DirectionalLights;

layout(std140, binding = 2) uniform PointLightUBO {
  int size;
  PointLightData data[MAX_POINTS];
} PointLights;

layout(std140, binding = 3) uniform SpotLightUBO {
  int size;
  SpotLightData data[MAX_SPOTS];
} SpotLights;

layout(std140, binding = 4) uniform MaterialUBO {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
} material;

uniform vec3 uObjectColor;

vec3 CalcDirectionalLight(DirectionalLightData light, vec3 normal, vec3 viewDir) {
  vec3 lightDir = normalize(-light.direction);
  // diffuse
  float diff = max(dot(normal, lightDir), 0.0);
  // specular
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // combine
  vec3 ambient = material.ambient * light.lightColor * light.intensity;
  vec3 diffuse = material.diffuse * diff * light.lightColor * light.intensity;
  vec3 specular = material.specular * spec * light.lightColor * light.intensity;

  return (ambient + diffuse + specular) * uObjectColor;
}

vec3 CalcPointLight(PointLightData light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - outPos);
    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distanceToLight = length( light.position - outPos);
    float attenuation = 1.0 / ( light.constant + light.linear * distanceToLight + light.quadratic * (distanceToLight * distanceToLight));
    // combine
    vec3 ambient = material.ambient * light.lightColor * light.intensity;
    vec3 diffuse = material.diffuse * diff * light.lightColor * light.intensity;
    vec3 specular = material.specular * spec * light.lightColor * light.intensity;
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular) * uObjectColor;
}

vec3 CalcSpotLight(SpotLightData light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distanceToLight = length(light.position - outPos);
    float attenuation = 1.0 / (light.constant + light.linear * distanceToLight + light.quadratic * (distanceToLight * distanceToLight));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine
    vec3 ambient = material.ambient * light.lightColor * light.intensity;
    vec3 diffuse = material.diffuse * diff * light.lightColor * light.intensity;
    vec3 specular = material.specular * spec * light.lightColor * light.intensity;
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular) * uObjectColor;
}

void main() {
  vec3 norm = normalize(outNormal);
  vec3 viewDir = normalize(outCameraPos - outPos);

  vec3 result = vec3(0.0);
  for(int i = 0; i < DirectionalLights.size; ++i) {
    result += CalcDirectionalLight(DirectionalLights.data[i], norm, viewDir);
  }
  for(int = 0; i < PointLights.size; ++i) {
    result += CalcPointLight(PointLights.data[i], norm, outPos, viewDir);
  }
  for(int = 0; i < SpotLight.size; ++i) {
    result += CalcPointLight(SpotLights.data[i], norm, outPos, viewDir);
  }
  // result += CalcPointLight(norm, outPos, viewDir);
  // result += CalcSpotLight(norm, outPos, viewDir);

  FragColor = vec4(result, 1.0);
}
