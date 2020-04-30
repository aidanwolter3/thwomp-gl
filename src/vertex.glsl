#version 330 core

layout (location = 0) in vec3 aPos;

// Aspect ratio
uniform mat4 projection;

// Animation
uniform mat4 transform;

void main() {
  gl_Position = projection * transform * vec4(aPos.xyz, 1.0);
}
