#include "../tuplet.hpp"
#include <cassert>
#include <iostream>

using namespace hautbois;

int main() {

  Tuplet n1 (3, 4, {"An4","8","Bb4","8", "Bn4","8"});

  assert(n1.toString() == "3/4,{ An4,8 Bb4,8 Bn4,8 }");

  n1.addProperty("pp", 0);
  n1.makeTie(2);

  Tuplet n2 (n1);
  assert(n2.toString() == "3/4,{ An4,8,[pp] Bb4,8 Bn4~,8 }");
  assert(n2.getSize() == 3);

  // TODO test exception
  // test reduce() enlarge() isValid()

  return 0;

}