#ifndef THWOMP_H_
#define THWOMP_H_

#include <vector>

#include "object.h"

class Thwomp : public Object {
 public:
  Thwomp(unsigned int vao);
  ~Thwomp() override;

  // Delete copy and assign.
  Thwomp(const Thwomp&) = delete;
  Thwomp operator=(const Thwomp&) = delete;

 private:
  struct Coord {
    float x, y, z;
  };

  // Object implementation:
  int GetElementCount() override;

  void AddTriangle(Coord c1, Coord c2, Coord c3);
  void PopulateVerticesAndElements();

  unsigned int vbo_;
  unsigned int ebo_;

  std::vector<float> vertices_;
  std::vector<unsigned int> elements_;
};

#endif  // THWOMP_H_
