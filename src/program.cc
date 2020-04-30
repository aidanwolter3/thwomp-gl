#include "program.h"

#include <iostream>
#include <math.h> // TODO: remove this

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "object.h"
#include "shader.h"

Program::Program(std::vector<std::unique_ptr<Shader>> shaders)
    : program_(glCreateProgram()) {
  if (!program_) {
    std::cout << "Failed to create the program" << std::endl;
    return;
  }

  // Assemble the program.
  for (auto& shader : shaders) {
    shader->AttachToProgram(program_);
  }
  glLinkProgram(program_);

  // Ensure the assembly succeeded.
  int success;
  glGetProgramiv(program_, GL_LINK_STATUS, &success);
  if (!success) {
    char info_log[512];
    glGetProgramInfoLog(program_, 512, NULL, info_log);
    std::cout << "Failed to compile program" << std::endl
              << info_log << std::endl;
    program_ = 0;
  }

  // Create the vertex arrays.
  // This must be prepared before any objects can be initialized.
  glGenVertexArrays(1, &vao_);
}

Program::~Program() {
  if (program_) {
    glDeleteProgram(program_);
  }
  if (vao_) {
    glDeleteVertexArrays(1, &vao_);
  }
}

void Program::AddObject(std::unique_ptr<Object> object) {
  objects_.push_back(std::move(object));
}

// TODO: Create a RenderInternal() so subclasses can do custom things.
void Program::Render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(program_);
  ApplyUniforms();  // Must be after glUseProgram.

  glBindVertexArray(vao_);
  int element_count = 0;
  for (auto& object : objects_) {
    element_count += object->GetElementCount();
  }
  glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Program::SetAspectRatio(float aspect_ratio) {
  aspect_ratio_ = aspect_ratio;
}

// TODO: move this to a subclass?
void Program::ApplyUniforms() {
  auto projection_location = glGetUniformLocation(program_, "projection");
  glm::mat4 projection = glm::scale(glm::vec3(aspect_ratio_, 1.0f, 1.0f));
  glUniformMatrix4fv(projection_location, 1, false, &projection[0][0]);

  const float max_height_offset = 0.4f;
  const double cycle_time = 4;
  const double split_time = 3.8;
  float height_offset = 0;
  double glfw_time = glfwGetTime();
  double time = glfw_time - (((int)glfw_time / (int)cycle_time) * (int)cycle_time);
  // Ascending.
  if (time < split_time) {
    height_offset = (time / split_time) * max_height_offset;
  }
  // Descending.
  else {
    height_offset = max_height_offset * ((cycle_time - time) / (cycle_time - split_time));
  }
  auto transform_location = glGetUniformLocation(program_, "transform");
  glm::mat4 transform = glm::mat4(1.0f);
  transform = glm::translate(transform, glm::vec3(0.0f, height_offset, 0.0f));
  glUniformMatrix4fv(transform_location, 1, false, &transform[0][0]);
}
