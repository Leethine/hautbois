#include "mandolin_note.hpp"
#include "stk_buffer_writer.hpp"
#include "../../utility/hbexcept.hpp"

#include <stk/FileWvOut.h>
#include <stk/Instrmnt.h>
#include <stk/Mandolin.h>

#define DEFAULT_AMPLITUDE 0.8

namespace hautbois {
namespace synth {

namespace stk_mandolin {
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


void SingleNoteStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __param1;
  if (!(__out && tempo_ptr)) {
    HB_THROW_MSG(std::runtime_error, std::string("Runtime error, please check the params."));
  }

  if (SingleNote::isMute()) {
    stk_wav_writer::writeMutedNote(__out, *tempo_ptr, SingleNote::getDuration(0), 1, 1);
  }
  else if (SingleNote::getPitch(0)) {
    stk_wav_writer::writeSingleNote(__out, *tempo_ptr, SingleNote::getDuration(0), 1, 1,
    stk_mandolin::selectInstrument(SingleNote::getPitch(0)->toFrequency()),
    SingleNote::getPitch(0), DEFAULT_AMPLITUDE);
  }
}


void ChordStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __param1;
  if (!(__out && tempo_ptr)) {
    HB_THROW_MSG(std::runtime_error, std::string("Runtime error, please check the params."));
  }

  std::vector<const Pitch *> pitch_list;
  std::vector<double> amplitude_list;
  std::vector<stk::Instrmnt *> instrument_list;

  for (int i = 0; i < Chord::getSize(); i++) {
    if (Chord::getPitch(i)) {
      pitch_list.push_back(Chord::getPitch(i));
      instrument_list.push_back(stk_mandolin::selectInstrument(Chord::getPitch(i)->toFrequency()));
      amplitude_list.push_back(DEFAULT_AMPLITUDE);
    }
  }

  stk_wav_writer::writeChord(__out,
    *tempo_ptr, Chord::getDuration(0), 1, 1,
    pitch_list, instrument_list, amplitude_list);

}


void GraceNoteStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
}


void TupletStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
}

} // namespace synth
} // namespace hautbois
