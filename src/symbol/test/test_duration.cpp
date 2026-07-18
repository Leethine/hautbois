#include "../duration.hpp"
#include <cassert>
#include <stdexcept>
#include <iostream>

#define EXCEPTION_CAUGHT() ( assert("Exception Caught" == nullptr) )

using namespace hautbois;

int main() {

  // Basic usecase
  Duration d1 (4, 4);
  Duration d2 (4);
  Duration d3 (4, ".");
  Duration d4 ("8.");

  assert(d1.isMeter());
  assert(d2.isNoteValue());
  assert(d3.isNoteValue());
  assert(d4.isNoteValue());

  assert(d1.toString() == "4/4");
  assert(d2.toString() == "4");
  assert(d3.toString() == "4.");
  assert(d4.toString() == "8.");

  assert(d1.getNum() == 4);
  assert(d1.getDenom() == 4);
  assert(d2.getNum() == 1);
  assert(d2.getDenom() == 4);
  assert(d3.getNum() == 3);
  assert(d3.getDenom() == 8);
  assert(d4.getNum() == 3);
  assert(d4.getDenom() == 16);

  assert(d1.getValue() == 0);
  assert(d1.getDots().empty());
  assert(d2.getValue() == 4);
  assert(d2.getDots().empty());
  assert(d3.getValue() == 4);
  assert(d3.getDots() == ".");
  assert(d4.getValue() == 8);
  assert(d4.getDots() == ".");

  // Constructor throw exception
  try {
    Duration d(3);
    EXCEPTION_CAUGHT();
  }
  catch (std::invalid_argument& e) {
    assert(e.what());
    std::cout << e.what() << "\n";
  }
  
  try {
    Duration d(4, "....");
    EXCEPTION_CAUGHT();
  }
  catch (std::invalid_argument& e) {
    assert(e.what());
    std::cout << e.what() << "\n";
  }

  try {
    Duration d("SFZ");
    EXCEPTION_CAUGHT();
  }
  catch (std::invalid_argument& e) {
    assert(e.what());
    std::cout << e.what() << "\n";
  }

  try {
    Duration d("3.");
    EXCEPTION_CAUGHT();
  }
  catch (std::invalid_argument& e) {
    assert(e.what());
    std::cout << e.what() << "\n";
  }

  try {
    Duration d("123456453412342534253435654312345642534324253634232534231");
    EXCEPTION_CAUGHT();
  }
  catch (std::out_of_range& e) {
    assert(e.what());
    std::cout << e.what() << "\n";
  }

  return 0;
}