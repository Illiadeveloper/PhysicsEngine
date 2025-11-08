#version 420 core
out vec4 FragColor;

in vec3 outPos;
in vec3 outNormal;
in vec3 outCameraPos;


layout(std140, binding = 2) uniform PointLightUBO {
  vec3 position;
  float linear;

  vec3 lightColor;
  float intensity;

  float constant;
  float quadratic;
} PointLight;


void main() {
  vec3 result = PointLight.lightColor * clamp(PointLight.intensity, 0.0 , 0.999);
  FragColor = vec4(result, 1.0);
}
