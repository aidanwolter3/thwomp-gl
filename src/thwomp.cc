#include "thwomp.h"

#include <iostream>

#include <glad/glad.h>
#include <stb_image.h>

Thwomp::Thwomp(unsigned int vao) {
  if (vao == 0) {
    // TODO: throw an error somehow.
    return;
  }

  // Instantiate the buffers for our vertices and elements.
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);

  glBindVertexArray(vao);

  PopulateVerticesAndElements();

  // Create the vertices.
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER,
               vertices_.size()*sizeof(float),
               vertices_.data(),
               GL_STATIC_DRAW);

  // Define the elements (triangles) from the vertex indeces.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               elements_.size()*sizeof(unsigned int),
               elements_.data(),
               GL_STATIC_DRAW);

  // Add the vertices and elements to the Vertex Array Object (VAO).
  // TODO: generate the index dynamically.
  glVertexAttribPointer(/*index=*/0,
                        /*size=*/3,
                        /*type=*/GL_FLOAT,
                        /*normalized=*/GL_FALSE,
                        /*stride=*/3 * sizeof(float),
                        /*offset=*/(void*)0);
  glEnableVertexAttribArray(0);

  // Unbind to clean up.
  // Note: The vertex array MUST be unbound first.
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Thwomp::~Thwomp() {
  if (vbo_) {
    glDeleteBuffers(1, &vbo_);
  }
}

int Thwomp::GetElementCount() {
  return elements_.size();
}

void Thwomp::AddTriangle(Coord c1, Coord c2, Coord c3) {
  for (auto c : {c1, c2, c3}) {
    elements_.push_back(vertices_.size() / 3);
    vertices_.push_back(c.x);
    vertices_.push_back(c.y);
    vertices_.push_back(c.z);
  }
}

void Thwomp::PopulateVerticesAndElements() {
  const float box_height = 0.9f;
  const float box_width = 0.8f;
  const float spike_height = 0.15f;
  const float spike_width = 0.2f;
  const int num_spikes_on_each_side = 3;

  // Left spikes
  for (int i = 0; i < num_spikes_on_each_side; i++) {
    const float offset = i * spike_width;
    const float spike_direction = -1.0f;
    auto one = Coord{
      .x = (box_width / 2.0f) * spike_direction,
      .y = (spike_width * -1.5f) + offset,
      .z = 0.0f};
    auto two = Coord{
      .x = ((box_width / 2.0f) + spike_height) * spike_direction,
      .y = (spike_width * -1.0f) + offset,
      .z = 0.0f};
    auto three = Coord{
      .x = (box_width / 2.0f) * spike_direction,
      .y = (spike_width * -0.5f) + offset,
      .z = 0.0f};
    AddTriangle(one, two, three);
  }

  // Right spikes
  for (int i = 0; i < num_spikes_on_each_side; i++) {
    const float offset = i * spike_width;
    const float spike_direction = 1.0f;
    auto one = Coord{
      .x = (box_width / 2.0f) * spike_direction,
      .y = (spike_width * -1.5f) + offset,
      .z = 0.0f};
    auto two = Coord{
      .x = ((box_width / 2.0f) + spike_height) * spike_direction,
      .y = (spike_width * -1.0f) + offset,
      .z = 0.0f};
    auto three = Coord{
      .x = (box_width / 2.0f) * spike_direction,
      .y = (spike_width * -0.5f) + offset,
      .z = 0.0f};
    AddTriangle(one, two, three);
  }

  // Top spikes
  for (int i = 0; i < num_spikes_on_each_side; i++) {
    const float offset = i * spike_width;
    const float spike_direction = 1.0f;
    auto one = Coord{
      .x = (spike_width * -1.5f) + offset,
      .y = (box_height / 2.0f) * spike_direction,
      .z = 0.0f};
    auto two = Coord{
      .x = (spike_width * -1.0f) + offset,
      .y = ((box_height / 2.0f) + spike_height) * spike_direction,
      .z = 0.0f};
    auto three = Coord{
      .x = (spike_width * -0.5f) + offset,
      .y = (box_height / 2.0f) * spike_direction,
      .z = 0.0f};
    AddTriangle(one, two, three);
  }

  // Bottom spikes
  for (int i = 0; i < num_spikes_on_each_side; i++) {
    const float offset = i * spike_width;
    const float spike_direction = -1.0f;
    auto one = Coord{
      .x = (spike_width * -1.5f) + offset,
      .y = (box_height / 2.0f) * spike_direction,
      .z = 0.0f};
    auto two = Coord{
      .x = (spike_width * -1.0f) + offset,
      .y = ((box_height / 2.0f) + spike_height) * spike_direction,
      .z = 0.0f};
    auto three = Coord{
      .x = (spike_width * -0.5f) + offset,
      .y = (box_height / 2.0f) * spike_direction,
      .z = 0.0f};
    AddTriangle(one, two, three);
  }

  // Top-left corner spike
  {
    const float corner_height_offset = spike_height*1.1f;
    auto one = Coord{
      .x = -box_width / 2.0f,
      .y = spike_width * 1.5f,
      .z = 0.0f};
    auto two = Coord{
      .x = spike_width * -1.5f,
      .y = box_height / 2.0f,
      .z = 0.0f};
    auto three = Coord{
      .x = (spike_width * -1.5f) - corner_height_offset,
      .y = (spike_width * 1.5f) + corner_height_offset,
      .z = 0.0f};
    AddTriangle(one, two, three);
  }

  // Top-right corner spike
  {
    const float corner_height_offset = spike_height*1.1f;
    auto one = Coord{
      .x = box_width / 2.0f,
      .y = spike_width * 1.5f,
      .z = 0.0f};
    auto two = Coord{
      .x = spike_width * 1.5f,
      .y = box_height / 2.0f,
      .z = 0.0f};
    auto three = Coord{
      .x = (spike_width * 1.5f) + corner_height_offset,
      .y = (spike_width * 1.5f) + corner_height_offset,
      .z = 0.0f};
    AddTriangle(one, two, three);
  }

  // Bottom-left corner spike
  {
    const float corner_height_offset = spike_height*1.1f;
    auto one = Coord{
      .x = -box_width / 2.0f,
      .y = spike_width * -1.5f,
      .z = 0.0f};
    auto two = Coord{
      .x = spike_width * -1.5f,
      .y = -box_height / 2.0f,
      .z = 0.0f};
    auto three = Coord{
      .x = (spike_width * -1.5f) - corner_height_offset,
      .y = (spike_width * -1.5f) - corner_height_offset,
      .z = 0.0f};
    AddTriangle(one, two, three);
  }

  // Bottom-right corner spike
  {
    const float corner_height_offset = spike_height*1.1f;
    auto one = Coord{
      .x = box_width / 2.0f,
      .y = spike_width * -1.5f,
      .z = 0.0f};
    auto two = Coord{
      .x = spike_width * 1.5f,
      .y = -box_height / 2.0f,
      .z = 0.0f};
    auto three = Coord{
      .x = (spike_width * 1.5f) + corner_height_offset,
      .y = (spike_width * -1.5f) - corner_height_offset,
      .z = 0.0f};
    AddTriangle(one, two, three);
  }

  // Inside fill
  {
    auto one = Coord{
      .x = -box_width / 2.0f,
      .y = -box_height / 2.0f,
      .z = 0.0f};
    auto two = Coord{
      .x = -box_width / 2.0f,
      .y = box_height / 2.0f,
      .z = 0.0f};
    auto three = Coord{
      .x = box_width / 2.0f,
      .y = box_height / 2.0f,
      .z = 0.0f};
    auto four = Coord{
      .x = box_width / 2.0f,
      .y = -box_height / 2.0f,
      .z = 0.0f};
    AddTriangle(one, two, three);
    AddTriangle(three, four, one);
  }
}

