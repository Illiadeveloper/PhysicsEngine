#version 420 core
out vec4 FragColor;

in vec3 outPos;
in vec3 outNormal;
in vec3 outCameraPos;

layout(std140, binding = 1) uniform LightUBO {
  vec3 lightPos;
  float intensity;
  vec3 lightColor;
} light;

uniform vec3 uObjectColor;

void main() {
  float ambientStrength = 0.1;
  float specularStrength = 0.5;

  vec3 ambient = ambientStrength * light.lightColor * light.intensity;
  
  // Diffuse 
  vec3 norm = normalize(outNormal);
  vec3 lightDir = normalize(light.lightPos - outPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * light.lightColor * light.intensity;
  
  // Specular
  vec3 viewDir = normalize(outCameraPos - outPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * light.lightColor * light.intensity;

  vec3 result = (ambient + diffuse + specular) * uObjectColor;
  result = clamp(result, 0.0, 1.0);
  FragColor = vec4(result, 1.0);
}
