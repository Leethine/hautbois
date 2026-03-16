#include "note.hpp"
#include "note_chord.hpp"
#include "note_tuplet.hpp"
#include "note_single.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <utility>

#define PRINTL(X) (std::cout << (X) << "\n")

using namespace hautbois;
using namespace core;


int main() {

  std::vector<Note *> notelist;
  Note * n = nullptr;
  n = new SingleNote("R",1,4);
  notelist.push_back(n);
  n = new SingleNote("S",1,4);
  notelist.push_back(n);
  n = new SingleNote("Eb3",1,4);
  notelist.push_back(n);
  n = new SingleNote("G3",1,4);
  notelist.push_back(n);
  n = new Chord({"C3", "E3", "G3"}, 1,4);
  notelist.push_back(n);
  n = new Tuplet(1,4,{"C3","8","E3","8","G3","8"},3);
  notelist.push_back(n);

  for (auto ptr : notelist) {
    PRINTL(ptr->getTypeStr());
    PRINTL(ptr->toString());
  }
  return 0;
}
