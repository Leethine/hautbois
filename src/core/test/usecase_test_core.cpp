#include "../base_duration.hpp"
#include "../base_note_property.hpp"
#include "../base_note.hpp"
#include "../base_voice.hpp"
#include "../base_bar.hpp"
#include <vector>
#include <string>
#include <iostream>

int main () {
  hautbois::core::BaseNote n1 ("C", "#", "4", 1, 2);
  std::cout << n1.getNoteNameAsString() << "\n";
  std::cout << n1.getAccidentalAsString() << "\n";
  std::cout << n1.getOctaveAsString() << "\n";
  std::cout << n1.getIndexAsString() << "\n";
  std::cout << n1.getFullNoteNameAsString() << "\n";
  std::cout << n1.getDurationAsString() << "\n";

  hautbois::core::BaseNote n2 ("D", "", "4", 4, "");
  std::cout << n2.getNoteNameAsString() << "\n";
  std::cout << n2.getAccidentalAsString() << "\n";
  std::cout << n2.getOctaveAsString() << "\n";
  std::cout << n2.getIndexAsString() << "\n";
  std::cout << n2.getFullNoteNameAsString() << "\n";
  std::cout << n2.getDurationAsString() << "\n";

  hautbois::core::BaseNote n3 ("E", "bb", "4", 4, ".");
  std::cout << n3.getNoteNameAsString() << "\n";
  std::cout << n3.getAccidentalAsString() << "\n";
  std::cout << n3.getOctaveAsString() << "\n";
  std::cout << n3.getIndexAsString() << "\n";
  std::cout << n3.getFullNoteNameAsString() << "\n";
  std::cout << n3.getDurationAsString() << "\n";

  hautbois::core::BaseNote n4 ("C", "x", "2", 16, "..");
  std::cout << n4.getNoteNameAsString() << "\n";
  std::cout << n4.getAccidentalAsString() << "\n";
  std::cout << n4.getOctaveAsString() << "\n";
  std::cout << n4.getIndexAsString() << "\n";
  std::cout << n4.getFullNoteNameAsString() << "\n";
  std::cout << n4.getDurationAsString() << "\n";

  hautbois::core::BaseNote n5 ({"C4","Eb4","G4"}, 4, ".");
  std::cout << n5.getFullNoteNameAsString() << "\n";
  std::cout << n5.getDurationAsString() << "\n";

  hautbois::core::BaseDuration d1 = n1.getDuration();
  hautbois::core::BaseDuration d4 = n4.getDuration();

  hautbois::core::BaseDuration d14_1 = d1 + d4;
  hautbois::core::BaseDuration d14_2 = d4 - d1;

  std::cout << d14_1.toString() << "\n";
  std::cout << d14_2.toString() << "\n";

  std::cout << "SILENCE_NOTE_INDEX " << int(hautbois::core::SILENCE_NOTE_INDEX) << "\n";

  try {
    n1.addProperty("pp");
    auto p = n1.getProperty();
    std::cout << p.getDynamics().first << "\n";
  }
  catch(std::exception& e) {
    std::cout << e.what() << "\n";
  }
  return 0;
}