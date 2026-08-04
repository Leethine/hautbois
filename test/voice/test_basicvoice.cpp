#include "engine/basic_voice.hpp"
#include "note/single_note.hpp"
#include "note/chord.hpp"
#include "note/grace_note.hpp"
#include "note/tuplet.hpp"

#include <iostream>
#include <cassert>
#include <vector>

#define HB_NOTE_TYPE SingleNote,Chord,GraceNote,Tuplet

using namespace hautbois;

int main() {

  BasicVoice<HB_NOTE_TYPE> voice1;

  voice1.addBar();
  voice1.addNote("Cn4", "4");
  voice1.addNote("Cn4", "4");
  voice1.addNote("Cn4", "4");
  voice1.addNote("Cn4", "4");

  voice1.addBar();
  voice1.addNote(std::vector<std::string>({"Cn4", "En4"}), "4");
  voice1.addNote(std::vector<std::string>({"Cn4", "En4"}), "4");
  voice1.addNote(std::vector<std::string>({"Cn4", "En4"}), "4");
  voice1.addNote(std::vector<std::string>({"Cn4", "En4"}), "4");

  voice1.addBar();
  voice1.addNote(std::vector<std::string>({"Cn4","16","En4","16"}),"Gn4" ,"4");
  voice1.addNote(std::vector<std::string>({"Cn4","16","En4","16"}),"Gn4" ,"4");
  voice1.addNote(std::vector<std::string>({"Cn4","16","En4","16"}),"Gn4" ,"4");
  voice1.addNote(std::vector<std::string>({"Cn4","16","En4","16"}),"Gn4" ,"4");

  voice1.addBar();
  voice1.addNote(3, 4, std::vector<std::string>({"Cn4","8","En4","8","Gn4","8"}));
  voice1.addNote(3, 4, std::vector<std::string>({"Cn4","8","En4","8","Gn4","8"}));
  voice1.addNote(3, 4, std::vector<std::string>({"Cn4","8","En4","8","Gn4","8"}));
  voice1.addNote(3, 4, std::vector<std::string>({"Cn4","8","En4","8","Gn4","8"}));
  
  std::cout << voice1.toString() << std::endl;

  assert(voice1.barCheck(0));
  assert(voice1.barCheckReturnErr() == "");
  assert(voice1.getMeter(0)->getNum() == 4 && voice1.getMeter(0)->getDenom() == 4);

  voice1.addBar();
  voice1.addNote("Cn4","1.");
  assert(!voice1.barCheck(4));

  // TODO
  // add test cases for:
  // 1. note patching
  // 2. meter change
  // 3. counterpoint

  return 0;
}