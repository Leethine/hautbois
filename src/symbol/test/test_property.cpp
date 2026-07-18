#include "../property.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>

#define EXCEPTION_CAUGHT() ( assert("Exception Caught" == nullptr) )

using namespace hautbois;

int main() {
  Property p1("pp staccato");
  assert(p1.toList().size() == 2);
  assert(p1.toString() == "pp staccato");
  assert(p1.getArticulation() == "staccato");
  assert(p1.getDynamic() == "pp");

  Property p2("ff pistachio");
  assert(p2.toList().size() == 1);
  assert(p2.toString() == "ff");
  assert(p2.getArticulation().empty());
  assert(p2.getDynamic() == "ff");

  return 0;
}