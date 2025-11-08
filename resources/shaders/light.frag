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

void main() {
  vec3 result = light.lightColor * clamp(light.intensity, 0.0 , 0.999);
  FragColor = vec4(result, 1.0);
}
