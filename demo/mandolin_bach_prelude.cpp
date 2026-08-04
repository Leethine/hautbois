#include "stk/FileWvOut.h"
#include "../src/synth/stk/mandolin_note.hpp"
#include <stk/Stk.h>

using namespace hautbois;
using namespace synth;

int main () {

  stk::Stk::setSampleRate(44100);
  stk::Stk::setRawwavePath("/usr/share/stk/rawwaves/");
  stk::FileWvOut output;
  output.openFile( "mandolin_little_prelude.wav", 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16 );

  std::vector <Note *> notes;
  notes.reserve(100);

  notes.push_back(new TupletStkMandolin(3,4, {"F4","8","A4","8","C5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"F4","8","A4","8","C5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"F4","8","A4","8","C5","8"}));

  notes.push_back(new TupletStkMandolin(3,4, {"F4","8","Bb4","8","D5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"F4","8","Bb4","8","D5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"F4","8","Bb4","8","D5","8"}));

  notes.push_back(new TupletStkMandolin(3,4, {"G4","8","B4","8","D5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"G4","8","B4","8","D5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"G4","8","B4","8","D5","8"}));

  notes.push_back(new TupletStkMandolin(3,4, {"G4","8","C5","8","E5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"G4","8","C5","8","E5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"G4","8","C5","8","E5","8"}));

  notes.push_back(new TupletStkMandolin(3,4, {"A4","8","C#5","8","E5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"A4","8","C#5","8","E5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"A4","8","C#5","8","E5","8"}));

  notes.push_back(new TupletStkMandolin(3,4, {"A4","8","D5","8","F5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"A4","8","D5","8","F5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"A4","8","D5","8","F5","8"}));

  notes.push_back(new TupletStkMandolin(3,4, {"Bb4","8","D5","8","F5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"Bb4","8","D5","8","F5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"Bb4","8","D5","8","G5","8"}));

  notes.push_back(new SingleNoteStkMandolin("E5", "8"));
  notes.push_back(new SingleNoteStkMandolin("C5", "8"));
  notes.push_back(new SingleNoteStkMandolin("D5", "8"));
  notes.push_back(new SingleNoteStkMandolin("E5", "8"));
  notes.push_back(new SingleNoteStkMandolin("F5", "4"));

  notes.push_back(new SingleNoteStkMandolin("R", "8"));
  notes.push_back(new SingleNoteStkMandolin("Bb4", "8"));
  notes.push_back(new GraceNoteStkMandolin({"A4","16","G4","16","A4","16"} ,"G4", "4."));
  notes.push_back(new SingleNoteStkMandolin("F4", "8"));
  notes.push_back(new SingleNoteStkMandolin("F4", "4"));

  notes.push_back(new TupletStkMandolin(3,4, {"F4+A3","8","A4","8","C5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"F4+C4","8","A4","8","C5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"F4+A3","8","A4","8","C5","8"}));

  notes.push_back(new TupletStkMandolin(3,4, {"E4+G3","8","G4","8","C5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"E4+C4","8","G4","8","C5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"E4+G3","8","G4","8","C5","8"}));

  notes.push_back(new TupletStkMandolin(3,4, {"F4+A3","8","A4","8","C5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"F4+C4","8","A4","8","C5","8"}));
  notes.push_back(new TupletStkMandolin(3,4, {"F4+A3","8","A4","8","C5","8"}));

  notes.push_back(new ChordStkMandolin({"G5", "E4"}, "8"));
  notes.push_back(new ChordStkMandolin({"D5", "F4"}, "8"));
  notes.push_back(new ChordStkMandolin({"G5", "E4", "C4"}, "1"));

  //notes.push_back(new TupletStkMandolin(3,2, {"F#4+D4","4","E4+C#4","4","F#4+D4","4"}));
  int tempo = 90;

  for (Note * n : notes) {
    n->toStream(&output, &tempo, nullptr, nullptr);
  }
  output.closeFile();

  for (Note * n : notes) {
    delete n;
  }

  return 0;
}