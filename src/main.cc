#include <iostream>
#include <memory>

#include <glad/glad.h>

#include "program.h"
#include "shader.h"
#include "window.h"

int main(int argc, char** argv) {
  Window window;

  std::vector<std::unique_ptr<Shader>> shaders;
  shaders.push_back(std::unique_ptr<Shader>(new Shader(
        GL_VERTEX_SHADER, "src/vertex.glsl")));
  shaders.push_back(std::unique_ptr<Shader>(new Shader(
        GL_FRAGMENT_SHADER, "src/fragment.glsl")));

  Program program(std::move(shaders));

  window.SetAspectRatioCallback([&program](float aspect_ratio){
    program.SetAspectRatio(aspect_ratio);
  });

  // Render loop.
  std::cout << "Rendering a thwomp" << std::endl;
  while (true) {
    program.Render();
    window.Update();
  }

  return 0;
}
