#include "stk_buffer_writer.hpp"
#include "hb_stk_defs.hpp"
#include "../../note/duration.hpp"
#include "../../note/pitch.hpp"

#include <cstddef>
#include <stk/FileWvOut.h>
#include <stk/Instrmnt.h>
#include <cmath>
#include <stk/Stk.h>

namespace hautbois {
namespace synth {
namespace stk_wav_writer {


void writeMutedNote(stk::FileWvOut * __output,
  const unsigned int __tempo,   const Duration *   __duration,
  const unsigned int __divider, const unsigned int __multiplier) {

  double seconds = 0. ;
  size_t bufferSize = 0;
  if (__duration) {
    seconds = ((double)__multiplier * __duration->getNum() / __duration->getDenom()) / __divider;
    seconds *= 4. * 60 / __tempo;
    bufferSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
    if (__output) {
      for (size_t i = 0; i < bufferSize; i++) {
        __output->tick(0.);
      }
    }
  }
}

void writeSingleNote(stk::FileWvOut * __output,
  const unsigned int __tempo,   const Duration *    __duration,
  const unsigned int __divider, const unsigned  int __multiplier,
  stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude) {

  double seconds = 0. ;
  double freq = 0. ;
  size_t bufferSize = 1;

  if (__duration && __pitch) {
    freq = __pitch->toFrequency();
    seconds = ((double)__multiplier * __duration->getNum() / __duration->getDenom()) / __divider;
    seconds *= 4. * 60 / __tempo;
    bufferSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
    __instr->noteOn(freq, __amplitude);
    if (__output) {
      for (size_t i = 0; i < bufferSize; i++) {
        __output->tick(__instr->tick());
      }
    }
    __instr->noteOff(__amplitude);
  }
}

void writeChord(stk::FileWvOut * __output,
  const unsigned int __tempo,   const Duration *   __duration,
  const unsigned int __divider, const unsigned int __multiplier,
  const std::vector<const Pitch *>&   __pitch_list,
  const std::vector<stk::Instrmnt *>& __instr_list,
  const std::vector<double>&          __amplitude_list) {

  double seconds = 0. ;
  double freq = 0. ;
  size_t bufferSize = 0;
  if (__duration && __pitch_list.size() == __instr_list.size() &&
      __pitch_list.size() == __amplitude_list.size()) {
    seconds = ((double)__multiplier * __duration->getNum() / __duration->getDenom()) / __divider;
    seconds *= 4. * 60 / __tempo;
    bufferSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));

    // create empty out buffer
    stk::StkFloat buffer[bufferSize+1];
    for (size_t i = 0; i < bufferSize; i++) {
      buffer[i] = 0.;
    }
    // write to buffer
    for (size_t n = 0; n < __pitch_list.size(); n++) {
      if (__pitch_list[n] && __instr_list[n]) {
        freq = __pitch_list[n]->toFrequency();
        __instr_list[n]->noteOn(freq, __amplitude_list[n]);
        for (size_t i = 0; i < bufferSize; i++) {
          buffer[i] += __instr_list[n]->tick();
        }
        __instr_list[n]->noteOff(__amplitude_list[n]);
      }
    }
    // write to wav file output
    if (__output) {
      for (size_t i = 0; i < bufferSize; i++) {
        __output->tick(buffer[i]);
      }
    }
  }
}

} // namespace stk_wav_writer
} // namespace synth
} // namespace hautbois
