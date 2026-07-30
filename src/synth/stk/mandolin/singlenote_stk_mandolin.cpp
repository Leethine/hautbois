#include "singlenote_stk_mandolin.hpp"

#include "../../../note/pitch.hpp"
#include "../../../note/duration.hpp"
#include "../../../utility/hbexcept.hpp"
#include "../hb_stk_defs.hpp"

#include "stk/FileWvOut.h"
#include <stk/Instrmnt.h>
#include <stk/Mandolin.h>
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

SingleNoteStkMandolin::SingleNoteStkMandolin(const std::string& __pitch, const std::string& __value) :
  SingleNote(__pitch, __value) {
}

SingleNoteStkMandolin::SingleNoteStkMandolin(const SingleNote& __other) :
  SingleNote(__other) {
}

SingleNoteStkMandolin::SingleNoteStkMandolin(const SingleNote&& __other) :
  SingleNote(__other) {
}
    
SingleNoteStkMandolin::~SingleNoteStkMandolin() {
}

void SingleNoteStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __param1;
  if (!(__out && tempo_ptr)) {
    HB_THROW_MSG(std::runtime_error, std::string("Runtime error, please check the params."));
  }

  // process note value 
  int tempo = * ((int *)__param1);
  double seconds = 0. ;
  if (SingleNote::getDuration()) {
    seconds = (double) SingleNote::getDuration()->getNum() / (double) SingleNote::getDuration()->getDenom();
    seconds *= tempo / 60.;
    seconds *= 4.;
  }

  if (SingleNote::isMute()) {
    // write empty data to output
    for (int i = 0; i < int(std::round(STK_DEFAULT_SAMPLE_RATE * seconds)); i++) {
      try {
        __out->tick(0.);
      }
      catch (stk::StkError& e) {
        HB_THROW_MSG(std::runtime_error, e.getMessage());
      }
    }
  }
  else {
    double freq = 0. ;
    if (SingleNote::getPitch()) {
      freq = SingleNote::getPitch()->toFrequency();
    }
    stk::Mandolin *  __instr = mandolin_stk::selectInstrument(freq);
    // write sample to output
    __instr->noteOn(freq , 0.8);
    for (int i = 0; i < int(std::round(STK_DEFAULT_SAMPLE_RATE * seconds)); i++) {
      try {
        __out->tick( __instr->tick() );
      }
      catch (stk::StkError& e) {
        HB_THROW_MSG(std::runtime_error, e.getMessage());
      }
    }
    __instr->noteOff(0.8);
  }
}


} // namespace synth
} // namespace hautbois