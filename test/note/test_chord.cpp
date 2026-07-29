#include "../chord.hpp"
#include <cassert>
#include <iostream>

using namespace hautbois;

int main() {

  Chord n1({"Cn4","Eb4","Gn4"}, "8.");
  n1.addProperty("pp", 1);
  assert(n1.toString() == "Cn4+Eb4+Gn4,8.,[,pp,]");
  assert(n1.getDuration()->toString() == "8.");
  assert(n1.getSize() == 3);
  assert(n1.getPitch(1)->toString() == "Eb4");
  
  assert(n1.isTied(1) == false);
  n1.makeTie(1);
  assert(n1.isTied(1) == true);
  n1.makeUntie(1);
  assert(n1.isTied(1) == false);

  n1.makeTie(2);
  Chord n2 (n1);
  assert(n2.toString() == "Cn4+Eb4+Gn4~,8.,[,pp,]");
  assert(n2.isValid());

  // TODO 
  // Test exception
  
  return 0;

}