#include "tuplet_stk_mandolin.hpp"

#include "../../../note/pitch.hpp"
#include "../../../note/duration.hpp"
#include "../../../utility/hbexcept.hpp"
#include "../../../hbtype/hbdefs.hpp"
#include "../hb_stk_defs.hpp"

#include "stk/FileWvOut.h"
#include <cstddef>
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

TupletStkMandolin::TupletStkMandolin(const size_t __total, const size_t __value,
                                     const std::vector<std::string>& __notes) :
  Tuplet(__total, __value, __notes) {
}

TupletStkMandolin::TupletStkMandolin(const Tuplet& __other) :
  Tuplet(__other) {
}

TupletStkMandolin::TupletStkMandolin(const Tuplet&& __other) :
  Tuplet(__other) {
}
    
TupletStkMandolin::~TupletStkMandolin() {
}

void TupletStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  stk::Mandolin  * __instr = nullptr;
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __param1;
  if (!(__out && tempo_ptr)) {
    HB_THROW_MSG(std::runtime_error, std::string("Runtime error, please check the params."));
  }

  // process note value 
  int tempo = * ((int *)__param1);
  double seconds = 0. ;
  double freq = 0. ;
  
  // get the note count (divider)
  int divider = 1;
  if (Tuplet::getDuration(Tuplet::getSize())) {
    divider = Tuplet::getDuration(Tuplet::getSize())->getNum();
  }

  for (int n = 0; n < Tuplet::getSize(); n++) {
    const Note * note_ptr = Tuplet::getNote(n);
    if (note_ptr && note_ptr->getDuration(0)) {
      // calculate note length in seconds
      seconds = (double) note_ptr->getDuration(0)->getNum() / (double) note_ptr->getDuration(0)->getDenom();
      seconds *= tempo / 60.;
      seconds *= 4.;
      seconds /= divider; // tuplet is divided
      if (note_ptr->isType(CHAR_NOTETYPE_SINGLE) && note_ptr->getPitch(0)) {
        // write frequency data to output
        freq = note_ptr->getPitch(0)->toFrequency();
        __instr = mandolin_stk::selectInstrument(freq);
        __instr->noteOn(freq , 0.8);
        for (int i = 0; i < int(std::round(STK_DEFAULT_SAMPLE_RATE * seconds)); i++) {
          try {
            __out->tick(__instr->tick());
          }
          catch (stk::StkError& e) {
            HB_THROW_MSG(std::runtime_error, e.getMessage());
          }
        }
        __instr->noteOff(0.8);
      }
      else if (note_ptr->isType(CHAR_NOTETYPE_CHORD)) {
        int sample_count = int(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
        stk::StkFloat samples[sample_count+10];

        // first, write each chord pitch to sample buffer
        for (int j = 0; j < note_ptr->getSize(); j++) {
          if (note_ptr->getNote(j) && note_ptr->getPitch(j)) {
            freq = note_ptr->getPitch(j)->toFrequency();
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
          }
        }
        // then, write buffer to output
        for (int i = 0; i < sample_count; i++) {
          try {
            __out->tick(samples[i]);
          }
          catch (stk::StkError& e) {
            HB_THROW_MSG(std::runtime_error, e.getMessage());
          }
        }
      }
      
      else { // note is mute, write empty data to output
        for (int i = 0; i < int(std::round(STK_DEFAULT_SAMPLE_RATE * seconds)); i++) {
          try {
            __out->tick(0.);
          }
          catch (stk::StkError& e) {
            HB_THROW_MSG(std::runtime_error, e.getMessage());
          }
        }
      }
    }
  }
}


} // namespace synth
} // namespace hautbois