#include "stk/FileWvOut.h"
#include "../src/synth/stk/mandolin_note.hpp"
#include <stk/Stk.h>

using namespace hautbois;
using namespace synth;

int main () {

  stk::Stk::setSampleRate(44100);
  stk::Stk::setRawwavePath("/usr/share/stk/rawwaves/");
  stk::FileWvOut output;
  output.openFile( "mandolin_fugue.wav", 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16 );

  std::vector <Note *> notes;
  notes.reserve(100);

  notes.push_back(new SingleNoteStkMandolin("R", "8"));
  notes.push_back(new SingleNoteStkMandolin("A4", "8"));
  notes.push_back(new SingleNoteStkMandolin("A4", "8"));
  notes.push_back(new SingleNoteStkMandolin("A4", "8"));

  notes.push_back(new SingleNoteStkMandolin("A4", "8"));
  notes.push_back(new SingleNoteStkMandolin("G4", "16"));
  notes.push_back(new SingleNoteStkMandolin("F4", "16"));
  notes.push_back(new SingleNoteStkMandolin("G4", "8"));
  notes.push_back(new SingleNoteStkMandolin("E4", "8"));

  notes.push_back(new SingleNoteStkMandolin("F4", "8"));
  notes.push_back(new SingleNoteStkMandolin("D4", "8"));
  notes.push_back(new ChordStkMandolin({"D4", "Bb4"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("D4", "8"));

  notes.push_back(new ChordStkMandolin({"D4", "E4"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("C4", "16"));
  notes.push_back(new SingleNoteStkMandolin("Bb3", "16"));
  notes.push_back(new ChordStkMandolin({"C4", "A3"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("A3", "8"));

  notes.push_back(new ChordStkMandolin({"A4", "Bb3"}, "8"));
  notes.push_back(new ChordStkMandolin({"D5", "G4"}, "8"));
  notes.push_back(new ChordStkMandolin({"D5", "G4", "Bb4"}, "8"));
  notes.push_back(new ChordStkMandolin({"D5", "E4"}, "8"));

  notes.push_back(new ChordStkMandolin({"D5", "F4", "A3"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("C5", "16"));
  notes.push_back(new SingleNoteStkMandolin("Bb4", "16"));
  notes.push_back(new ChordStkMandolin({"C5", "E4", "A3"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("A4", "8"));
  
  notes.push_back(new ChordStkMandolin({"Bb4", "D4", "A3"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("D4", "8"));
  notes.push_back(new SingleNoteStkMandolin("G4", "16"));
  notes.push_back(new SingleNoteStkMandolin("F4", "16"));
  notes.push_back(new SingleNoteStkMandolin("E4", "16"));
  notes.push_back(new SingleNoteStkMandolin("F4", "32"));
  notes.push_back(new SingleNoteStkMandolin("G4", "32"));

  notes.push_back(new ChordStkMandolin({"A4", "C#4", "G3"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("A5", "8"));
  notes.push_back(new ChordStkMandolin({"A5", "A4", "D4", "F3"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("A5", "8"));

  notes.push_back(new ChordStkMandolin({"A5", "Bb4", "D4", "E3"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("G5", "16"));
  notes.push_back(new SingleNoteStkMandolin("F5", "16"));
  notes.push_back(new ChordStkMandolin({"G5", "A4", "C#4", "A3"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("E5", "8"));

  int tempo = 60; // TODO fix tempo calculation 

  for (Note * n : notes) {
    n->toStream(&output, &tempo, nullptr, nullptr);
  }
  output.closeFile();

  for (Note * n : notes) {
    delete n;
  }

  return 0;
}