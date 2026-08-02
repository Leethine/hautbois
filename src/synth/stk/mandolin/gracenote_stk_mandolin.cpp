#include "gracenote_stk_mandolin.hpp"

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

GraceNoteStkMandolin::GraceNoteStkMandolin(const std::vector<std::string>& __grace_notes,
                                           const std::string& __pitch, const std::string& __value) :
  GraceNote(__grace_notes, __pitch, __value) {
}

GraceNoteStkMandolin::GraceNoteStkMandolin(const GraceNote& __other) :
  GraceNote(__other) {
}

GraceNoteStkMandolin::GraceNoteStkMandolin(const GraceNote&& __other) :
  GraceNote(__other) {
}
    
GraceNoteStkMandolin::~GraceNoteStkMandolin() {
}

void GraceNoteStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  stk::Mandolin  * __instr = nullptr;
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __param1;
  if (!(__out && tempo_ptr)) {
    HB_THROW_MSG(std::runtime_error, std::string("Runtime error, please check the params."));
  }

  // process main note value 
  int tempo = * ((int *)__param1);
  double main_seconds = 0. ;
  const Duration * main_value = GraceNote::getDuration(GraceNote::getSize() - 1);
  if (main_value) {
    main_seconds = (double) main_value->getNum() / (double) main_value->getDenom();
    main_seconds *= tempo / 60.;
    main_seconds *= 4.;
  }
  double freq = 0. ;

  int grace_size = GraceNote::getSize() - 1;
  double grace_seconds ;
  if (grace_size > 0) {
    for (int i = 0; i < grace_size; i++) {
      if (GraceNote::getDuration(i) && GraceNote::getPitch(i)) {
        grace_seconds = (double) GraceNote::getDuration(i)->getNum() / (double) GraceNote::getDuration(i)->getDenom();
        grace_seconds *= tempo / 60. ;
        grace_seconds *= 4. ;
        grace_seconds /= 1.6 ; // grace notes are shorter
        main_seconds -= grace_seconds;
        // Generate grace note
        freq = GraceNote::getPitch(i)->toFrequency();
        __instr = mandolin_stk::selectInstrument(freq);
        __instr->noteOn(freq, 0.8);
        for (int j = 0; j < int(std::round(STK_DEFAULT_SAMPLE_RATE * grace_seconds)); j++) {
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
  }

  // generate main note
  const Pitch * main_pitch = GraceNote::getPitch(grace_size);
  if (main_pitch) {
    // Generate main note
    freq = main_pitch->toFrequency();
    __instr = mandolin_stk::selectInstrument(freq);
    __instr->noteOn(freq, 0.8);
    for (int i = 0; i < int(std::round(STK_DEFAULT_SAMPLE_RATE * main_seconds)); i++) {
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