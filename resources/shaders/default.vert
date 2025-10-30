#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 outPos;

void main() {
  outPos = aPos;
  gl_Position = vec4(aPos, 1.0f);
}
