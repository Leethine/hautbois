#include "../grace_note.hpp"
#include <cassert>
#include <iostream>

using namespace hautbois;

int main() {

  GraceNote n1({"An4","16","Bb4","16"}, "An4","4");
  n1.addProperty("pp", 2);
  n1.makeTie(2);
  assert(n1.toString() == "An4,16,Bb4,16,An4~,4,[,,pp]");
  n1.addProperty("", 2);
  assert(n1.toString() == "An4,16,Bb4,16,An4~,4");
  
  n1.addProperty("staccato", 0);
  n1.addProperty("staccato", 1);
  n1.addProperty("staccato", 2);

  GraceNote n2 (n1);
  assert(n2.toString() == "An4,16,Bb4,16,An4~,4,[staccato,staccato,staccato]");

  // TODO 
  // Test exception
  
  return 0;

}