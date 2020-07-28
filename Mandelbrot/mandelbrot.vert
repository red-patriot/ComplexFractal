#version 440 core
layout(location = 0) in vec3 apos;
layout(location = 1) in vec2 in_coords;

out vec2 c;

uniform mat4 trans;

void main() {
  gl_Position = trans * vec4(apos, 1.0);
  c = in_coords;
}
