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
//
void main() {
  // vec3 ambient = material.ambient * light.lightColor * light.intensity;
  // 
  // // Diffuse 
  // vec3 norm = normalize(outNormal);
  // vec3 lightDir = normalize(light.position - outPos);
  // float diff = max(dot(norm, lightDir), 0.0);
  // vec3 diffuse = (material.diffuse * diff) * light.lightColor * light.intensity;
  // 
  // // Specular
  // vec3 viewDir = normalize(outCameraPos - outPos);
  // vec3 reflectDir = reflect(-lightDir, norm);
  // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // vec3 specular = material.specular * spec * light.lightColor * light.intensity;
  //
  // vec3 result = (ambient + diffuse + specular) * uObjectColor;
  // result = clamp(result, 0.0, 1.0);
  // FragColor = vec4(result, 1.0);

  // vec3 ambient = material.ambient * light.lightColor * light.intensity;
  // 
  // // Diffuse 
  // vec3 norm = normalize(outNormal);
  // vec3 lightDir = normalize(light.direction);
  // float diff = max(dot(norm, lightDir), 0.0);
  // vec3 diffuse = (material.diffuse * diff) * light.lightColor * light.intensity;
  // 
  // // Specular
  // vec3 viewDir = normalize(outCameraPos - outPos);
  // vec3 reflectDir = reflect(-lightDir, norm);
  // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  // vec3 specular = material.specular * spec * light.lightColor * light.intensity;
  //
  // vec3 result = (ambient + diffuse + specular) * uObjectColor;
  FragColor = vec4(vec3(1.0), 1.0);
}
