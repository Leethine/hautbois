#include "../pitch.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>

#define EXCEPTION_CAUGHT() ( assert("Exception Caught" == nullptr) )

using namespace hautbois;

int main() {
  Pitch p1 ('C', 'n', 4);
  Pitch p2 ("A#5");

  assert(p1.toString() == "Cn4");
  assert(p2.toString() == "A#5");

  try {
    Pitch p ("Gk4");
    EXCEPTION_CAUGHT();
  }
  catch (std::invalid_argument& e) {
    assert(e.what());
    std::cout << e.what() << "\n";
  }

  try {
    Pitch p ("G9");
    EXCEPTION_CAUGHT();
  }
  catch (std::invalid_argument& e) {
    assert(e.what());
    std::cout << e.what() << "\n";
  }

  Pitch p ("G8");

  return 0;
}