#include "singlenote_stk_mandolin.hpp"

#include "../../../note/pitch.hpp"
#include "../../../note/duration.hpp"

#include "stk/FileWvOut.h"
#include <stk/Instrmnt.h>
#include <stk/Mandolin.h>

namespace hautbois {
namespace synth {

namespace mandolin_stk {
static stk::Mandolin MandolinContraBass(20.);
static stk::Mandolin MandolinBass(110.);
static stk::Mandolin MandolinTenor(220.);
static stk::Mandolin MandolinAlto(440.);
static stk::Mandolin MandolinSopran(880.);
static stk::Mandolin MandolinSopranissimo(1760.);

stk::Mandolin * selectInstrument(double __frequency) {
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
  stk::Mandolin * __instr = nullptr;
  int tempo = * ((int *)__param1);
  double seconds = 0. ;
  double freq = 0. ;
  if (SingleNote::getPitch()) {
    freq = SingleNote::getPitch()->toFrequency();
  }
  __instr = mandolin_stk::selectInstrument(freq);

  if (SingleNote::getDuration()) {
    seconds = (double) SingleNote::getDuration()->getNum() / (double) SingleNote::getDuration()->getDenom();
    seconds *= tempo / 60.;
    seconds *= 4.;
  }

  __instr->noteOn( freq , 0.8 );
  for ( int i=0; i< int(44100 * seconds); i++ ) {
    try {
      __out->tick( __instr->tick() );
    }
    catch ( stk::StkError & ) {
      exit( 1 );
    }
  }
  __instr->noteOff(0.5);
}


} // namespace synth
} // namespace hautbois