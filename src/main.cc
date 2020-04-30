#include <iostream>

#include "window.h"

int main(int argc, char** argv) {
  Window window;

  // Render loop.
  std::cout << "Rendering a thwomp" << std::endl;
  while (true) {
    window.Update();
  }

  return 0;
}
