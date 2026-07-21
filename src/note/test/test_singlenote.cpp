#include "../single_note.hpp"
#include "../../hbtype/hbdefs.hpp"
#include <cassert>
#include <iostream>

using namespace hautbois;

int main() {

  SingleNote n1("Cn4", "4.");
  assert(n1.getType() == CHAR_NOTETYPE_SINGLE);
  assert(n1.isValid());
  assert(n1.toString() == "Cn4,4.");

  n1.addProperty("pp");
  assert(n1.getProperty()->toString() == "pp");
  assert(n1.toString() == "Cn4,4.,[pp]");

  SingleNote n2 (n1);
  assert(n2.getType() == CHAR_NOTETYPE_SINGLE);
  assert(n2.isValid());
  assert(n2.getProperty()->toString() == "pp");
  assert(n2.toString() == "Cn4,4.,[pp]");

  n1.makeTie();
  assert(n1.isTied());
  n1.addProperty("");
  SingleNote n3 (n1);
  assert(n3.isTied());
  assert(n3.toString() == "Cn4~,4.");

  // TODO 
  // Test exception

  return 0;

}