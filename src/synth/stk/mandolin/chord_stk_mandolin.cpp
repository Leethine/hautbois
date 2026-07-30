#include "chord_stk_mandolin.hpp"

#include "../../../note/pitch.hpp"
#include "../../../note/duration.hpp"
#include "../../../utility/hbexcept.hpp"
#include "../hb_stk_defs.hpp"

#include "stk/FileWvOut.h"
#include <stdexcept>
#include <stk/Instrmnt.h>
#include <stk/Mandolin.h>
#include <stk/Stk.h>
#include <stk/Voicer.h>
#include <cmath>

namespace hautbois {
namespace synth {

namespace mandolin_stk {
static stk::Mandolin MandolinContraBass(20.);
static stk::Mandolin MandolinBass(110.);
static stk::Mandolin MandolinTenor(220.);
static stk::Mandolin MandolinAlto(440.);
static stk::Mandolin MandolinSopran(880.);
static stk::Mandolin MandolinSopranissimo(1760.);

static stk::Mandolin * selectInstrument(double __frequency) {
  stk::Mandolin * ptr;
  if (__frequency < 110.) {
    ptr = &MandolinContraBass;
  }
  else if (__frequency > 110. && __frequency < 220.) {
    ptr = &MandolinBass;
  }
  else if (__frequency > 220. && __frequency < 440.) {
    ptr = &MandolinTenor;
  }
  else if (__frequency > 440. && __frequency < 880.) {
    ptr = &MandolinAlto;
  }
  else if (__frequency > 880. && __frequency < 1760.) {
    ptr = &MandolinSopran;
  }
  else if (__frequency > 1760.) {
    ptr = &MandolinSopranissimo;
  }
  else {
    ptr = &MandolinContraBass;
  }
  return ptr;
}
} // namespace mandolin_stk

ChordStkMandolin::ChordStkMandolin(const std::vector<std::string>& __pitch, const std::string& __value) :
  Chord(__pitch, __value) {
}

ChordStkMandolin::ChordStkMandolin(const Chord& __other) :
  Chord(__other) {
}

ChordStkMandolin::ChordStkMandolin(const Chord&& __other) :
  Chord(__other) {
}
    
ChordStkMandolin::~ChordStkMandolin() {
}

void ChordStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __param1;
  if (!(__out && tempo_ptr)) {
    HB_THROW_MSG(std::runtime_error, std::string("Runtime error, please check the params."));
  }

  stk::Mandolin * __instr = nullptr;
  int tempo = * tempo_ptr;
  double seconds = 0. ;
  double freq = 0. ;

  if (Chord::getDuration()) {
    seconds = (double) Chord::getDuration()->getNum() / (double) Chord::getDuration()->getDenom();
    seconds *= tempo / 60.;
    seconds *= 4.;
  }

  int sample_count = int(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
  int chord_size = Chord::getSize();
  // init sample buffer
  stk::StkFloat samples[sample_count+10];
  for (int i = 0; i < sample_count; i++) {
    samples[i] = 0. ;
  }

  // write all pitches to buffer
  for (int n = 0; n < chord_size; n++) {
    if (Chord::getPitch(n)) {
      freq = Chord::getPitch(n)->toFrequency();
      __instr = mandolin_stk::selectInstrument(freq);
      __instr->noteOn(freq, 0.8);
      for (int i = 0; i < sample_count; i++) {
        try {
          samples[i] += __instr->tick();
        }
        catch (stk::StkError& e) {
          HB_THROW_MSG(std::runtime_error, e.getMessage());
        }
      }
      __instr->noteOff(0.8);
    }
  }

  // write buffer to output
  for (int i = 0; i < sample_count; i++) {
    try {
      __out->tick(samples[i]);
    }
    catch (stk::StkError& e) {
      HB_THROW_MSG(std::runtime_error, e.getMessage());
    }
  }
}


} // namespace synth
} // namespace hautbois