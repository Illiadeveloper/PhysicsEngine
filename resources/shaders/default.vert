#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

layout(std140, binding = 0) uniform CameraUBO {
  mat4 view;
  mat4 projection;
  vec3 cameraPos;
} camera;

uniform mat4 uModel;

out vec3 outPos;
out vec3 outNormal;
out vec3 outCameraPos;

void main() {
  vec4 worldPos = uModel * vec4(aPos, 1.0);
  outPos = worldPos.xyz;

  mat3 normalMatrix = transpose(inverse(mat3(uModel)));
  outNormal = normalize(normalMatrix * aNormal);

  outCameraPos = camera.cameraPos;

  gl_Position = camera.projection * camera.view * worldPos;
}
