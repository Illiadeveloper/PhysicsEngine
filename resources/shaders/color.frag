#version 420 core
out vec4 FragColor;

in vec3 outPos;
in vec3 outNormal;
in vec3 outCameraPos;

uniform vec3 uObjectColor;

void main() {
  FragColor = vec4(uObjectColor, 1.0);
}
