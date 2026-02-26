#include "duration.hpp"
#include "pitch.hpp"
#include "property.hpp"
#include "note.hpp"
#include "voice.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace hautbois;
using namespace core;

int main() {
  Voice piece(4,4);
  piece.newBar(2,4);
  piece.addNote(1,4, "C4");
  piece.addNote(1,4, "F4");

  piece.newTempVoice();
  piece.addNoteTV(1,4, "S4");
  piece.addNoteTV(1,8, "G4");
  piece.addNoteTV(1,8, "F4");

  piece.newBar();
  piece.addNote(1,8, "D4");
  piece.addNote(1,8, "D4");
  piece.addNote(1,4, "A4");
  piece.addNote(1,4, "B4");
  piece.addNote(1,4, "Bs4");

  Duration d (1,1);
  d += Duration(2,4);

  std::cout << "1/1 + 2/4 = " + d.toString() << "\n";

  // Print, check
  //std::cout << piece.getNote(0,0)->toString() << "\n";
  //std::cout << piece.getNote(0,1)->toString() << "\n";

  std::cout << piece.getNoteTV(0,0,0)->toString() << "\n";
  std::cout << piece.getNoteTV(0,1,0)->toString() << "\n";
  std::cout << piece.getNoteTV(0,2,0)->toString() << "\n";
  piece.barCheck();
  return 0;
}