#include "stk/FileWvOut.h"
#include "../src/synth/stk/mandolin_note.hpp"
#include <stk/Stk.h>

using namespace hautbois;
using namespace synth;

int main () {

  stk::Stk::setSampleRate(44100);
  stk::Stk::setRawwavePath("/usr/share/stk/rawwaves/");
  stk::FileWvOut output;
  output.openFile( "mandolin_lascia.wav", 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16 );

  std::vector <Note *> notes;
  notes.reserve(100);

  notes.push_back(new SingleNoteStkMandolin("R", "4"));

  notes.push_back(new ChordStkMandolin({"D4","F#4"}, "2"));
  notes.push_back(new ChordStkMandolin({"D4","F#4"}, "2."));
  notes.push_back(new SingleNoteStkMandolin("F#4", "4"));
  
  notes.push_back(new ChordStkMandolin({"E4","G4"}, "2"));
  notes.push_back(new ChordStkMandolin({"E4","G4"}, "1"));
  
  notes.push_back(new ChordStkMandolin({"C#4","E4"}, "2"));
  notes.push_back(new ChordStkMandolin({"C#4","A4"}, "2."));
  notes.push_back(new SingleNoteStkMandolin("G4", "4"));

  notes.push_back(new ChordStkMandolin({"E4","G4"}, "4"));
  notes.push_back(new SingleNoteStkMandolin("F#4", "4"));
  notes.push_back(new ChordStkMandolin({"D4","F#4"}, "1"));

  notes.push_back(new ChordStkMandolin({"B4","G4"}, "2"));
  notes.push_back(new ChordStkMandolin({"B4","G4"}, "2."));

  notes.push_back(new SingleNoteStkMandolin("E5", "4")); // TODO use tuplet

  notes.push_back(new ChordStkMandolin({"A4","F#4"}, "2"));
  notes.push_back(new ChordStkMandolin({"A4","F#4"}, "2."));

  notes.push_back(new SingleNoteStkMandolin("D5", "4"));
  notes.push_back(new ChordStkMandolin({"D4","F#4"}, "4"));
  notes.push_back(new ChordStkMandolin({"E4","C#4"}, "4"));

  notes.push_back(new ChordStkMandolin({"D4","F#4"}, "2"));
  notes.push_back(new ChordStkMandolin({"E4","C#4"}, "4"));
  notes.push_back(new ChordStkMandolin({"D4","G3"}, "4."));
  notes.push_back(new ChordStkMandolin({"D4","F#3"}, "1"));


  int tempo = 120; // TODO fix tempo calculation 

  for (Note * n : notes) {
    n->toStream(&output, &tempo, nullptr, nullptr);
  }
  output.closeFile();

  for (Note * n : notes) {
    delete n;
  }

  return 0;
}