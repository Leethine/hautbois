#include "stk/FileWvOut.h"
#include "../src/synth/stk/mandolin/singlenote_stk_mandolin.hpp"
#include "../src/synth/stk/mandolin/chord_stk_mandolin.hpp"

using namespace hautbois;
using namespace synth;

int main () {

  stk::Stk::setSampleRate(44100);
  stk::Stk::setRawwavePath("/usr/share/stk/rawwaves/");
  stk::FileWvOut output;
  output.openFile( "mandolin_bwv539.wav", 1, stk::FileWrite::FILE_WAV, stk::Stk::STK_SINT16 );

  std::vector <Note *> notes;
  notes.reserve(100);

  notes.push_back(new SingleNoteStkMandolin("R", "8"));
  notes.push_back(new SingleNoteStkMandolin("A5", "8"));
  notes.push_back(new SingleNoteStkMandolin("A5", "8"));
  notes.push_back(new SingleNoteStkMandolin("A5", "8"));

  notes.push_back(new SingleNoteStkMandolin("A5", "8"));
  notes.push_back(new SingleNoteStkMandolin("G5", "16"));
  notes.push_back(new SingleNoteStkMandolin("F5", "16"));
  notes.push_back(new SingleNoteStkMandolin("G5", "8"));
  notes.push_back(new SingleNoteStkMandolin("E5", "8"));

  notes.push_back(new SingleNoteStkMandolin("F5", "8"));
  notes.push_back(new SingleNoteStkMandolin("D5", "8"));
  notes.push_back(new ChordStkMandolin({"D5", "Bb5"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("D5", "8"));

  notes.push_back(new ChordStkMandolin({"D5", "E5"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("C5", "16"));
  notes.push_back(new SingleNoteStkMandolin("Bb4", "16"));
  notes.push_back(new ChordStkMandolin({"C5", "A5"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("A4", "8"));

  notes.push_back(new ChordStkMandolin({"A5", "Bb4"}, "8"));
  notes.push_back(new ChordStkMandolin({"D6", "G5"}, "8"));
  notes.push_back(new ChordStkMandolin({"D6", "G5", "Bb4"}, "8"));
  notes.push_back(new ChordStkMandolin({"D6", "E5"}, "8"));

  notes.push_back(new ChordStkMandolin({"D6", "F5", "A4"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("C6", "16"));
  notes.push_back(new SingleNoteStkMandolin("Bb5", "16"));
  notes.push_back(new ChordStkMandolin({"C6", "E5", "A4"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("A4", "8"));
  
  notes.push_back(new ChordStkMandolin({"Bb5", "D5", "A4"}, "8"));
  notes.push_back(new SingleNoteStkMandolin("D4", "8"));
  notes.push_back(new SingleNoteStkMandolin("G4", "16"));
  notes.push_back(new SingleNoteStkMandolin("F4", "16"));
  notes.push_back(new SingleNoteStkMandolin("E4", "16"));
  notes.push_back(new SingleNoteStkMandolin("F4", "32"));
  notes.push_back(new SingleNoteStkMandolin("G4", "32"));

  notes.push_back(new SingleNoteStkMandolin("C#5", "4"));

  int tempo = 60;

  for (Note * n : notes) {
    n->toStream(&output, &tempo, nullptr, nullptr);
  }

  return 0;
}