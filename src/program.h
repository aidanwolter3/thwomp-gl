#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <memory>
#include <vector>

class Object;
class Shader;

class Program {
 public:
  Program(std::vector<std::unique_ptr<Shader>> shaders);
  ~Program();

  // Delete copy and assign;
  Program(const Program&) = delete;
  Program operator=(const Program&) = delete;

  // Adds an object to get drawn in each Render().
  void AddObject(std::unique_ptr<Object> object);

  // Run a single render refresh.
  void Render();

  void SetAspectRatio(float aspect_ratio);

  const unsigned int vao() { return vao_; }

 private:
  void ApplyUniforms();

  unsigned int program_;
  unsigned int vao_;

  std::vector<std::unique_ptr<Object>> objects_;

  float aspect_ratio_ = 1.0f;
};

#endif  // PROGRAM_H_
