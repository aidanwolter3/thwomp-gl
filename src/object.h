#ifndef OBJECT_H_
#define OBJECT_H_

class Object {
 public:
  virtual ~Object() {}
  virtual int GetElementCount() = 0;
};

#endif  // OBJECT_H_
