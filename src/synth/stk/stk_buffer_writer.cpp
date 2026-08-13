#include "stk_buffer_writer.hpp"
#include "hb_stk_defs.hpp"
#include "../../note/duration.hpp"
#include "../../note/pitch.hpp"
#include "../../utility/hbexcept.hpp"

#include <stdexcept>
#include <cmath>
#include <stk/FileWvOut.h>
#include <stk/Instrmnt.h>
#include <stk/Stk.h>

namespace hautbois {
namespace synth {
namespace stk_wv {


void writeSingleNote(stk::FileWvOut * __output,
                     const unsigned int __tempo, const Duration * __duration,
                     stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude,
                     const unsigned int __divide_ratio, const unsigned  int __multiply_ratio,
                     const Duration * __left_shift, const Duration * __right_shift) {
  if (__output == nullptr) {
    HB_THROW_MSG(std::runtime_error, "stk::FileWvOut object ptr is NULL");
  }
 
  double seconds = 0. ;
  double freq = 0. ;
  size_t bufferSize = 0;
  size_t leftPatchSize = 0;
  size_t rightPatchSize = 0;

  if (__left_shift) {
    seconds = ((double)__multiply_ratio * __left_shift->getNum() / __left_shift->getDenom()) / __divide_ratio;
    seconds *= 4. * 60 / __tempo;
    leftPatchSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
  }
  if (__right_shift) {
    seconds = ((double)__multiply_ratio * __right_shift->getNum() / __right_shift->getDenom()) / __divide_ratio;
    seconds *= 4. * 60 / __tempo;
    rightPatchSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
  }

  if (__duration) {
    seconds = ((double)__multiply_ratio * __duration->getNum() / __duration->getDenom()) / __divide_ratio;
    seconds *= 4. * 60 / __tempo;
    bufferSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
    // patch the note on the left
    for (size_t i = 0; i < leftPatchSize; i++) {
      __output->tick(0.);
    }

    if (__instr && __pitch) { // non-mute
      freq = __pitch->toFrequency();
      __instr->noteOn(freq, __amplitude);
      for (size_t i = 0; i < bufferSize; i++) {
        __output->tick(__instr->tick());
      }
      __instr->noteOff(__amplitude);
    }
    else { // generate mute note
      for (size_t i = 0; i < bufferSize; i++) {
        __output->tick(0.);
      }
    }

    // patch the note on the right
    for (size_t i = 0; i < rightPatchSize; i++) {
      __output->tick(0.);
    }
  }
}


void writeChord(stk::FileWvOut * __output,
                const unsigned int __tempo, const Duration * __duration,
                const std::vector<const Pitch *>&   __pitch_list,
                const std::vector<stk::Instrmnt *>& __instr_list,
                const std::vector<double>&          __amplitude_list,
                const unsigned int __divide_ratio, const unsigned int __multiply_ratio,
                const Duration * __left_shift, const Duration * __right_shift) {
  if (__output == nullptr) {
    HB_THROW_MSG(std::runtime_error, "stk::FileWvOut object ptr is NULL");
  }

  double seconds = 0. ;
  double freq = 0. ;
  size_t bufferSize = 0;
  size_t leftPatchSize = 0;
  size_t rightPatchSize = 0;

  if (__left_shift) {
    seconds = ((double)__multiply_ratio * __left_shift->getNum() / __left_shift->getDenom()) / __divide_ratio;
    seconds *= 4. * 60 / __tempo;
    leftPatchSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
  }
  if (__right_shift) {
    seconds = ((double)__multiply_ratio * __right_shift->getNum() / __right_shift->getDenom()) / __divide_ratio;
    seconds *= 4. * 60 / __tempo;
    rightPatchSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
  }

  if (__duration && __pitch_list.size() == __instr_list.size() &&
      __pitch_list.size() == __amplitude_list.size()) {
    seconds = ((double)__multiply_ratio * __duration->getNum() / __duration->getDenom()) / __divide_ratio;
    seconds *= 4. * 60 / __tempo;
    bufferSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));

    // create empty out buffer
    stk::StkFloat buffer[bufferSize + leftPatchSize + rightPatchSize + 10];
    //for (size_t i = 0; i < bufferSize; i++) { buffer[i] = 0.; }

    // patch the buffer on the left
    for (size_t i = 0; i < leftPatchSize; i++) {
      buffer[i] = 0.;
    }
    // write to buffer
    for (size_t n = 0; n < __pitch_list.size(); n++) {
      if (__pitch_list[n] && __instr_list[n]) {
        freq = __pitch_list[n]->toFrequency();
        __instr_list[n]->noteOn(freq, __amplitude_list[n]);
        for (size_t i = leftPatchSize; i < bufferSize + leftPatchSize; i++) {
          buffer[i] += __instr_list[n]->tick();
        }
        __instr_list[n]->noteOff(__amplitude_list[n]);
      }
    }
    // patch the buffer on the right side
    for (size_t i = bufferSize + leftPatchSize; i < bufferSize + leftPatchSize + rightPatchSize; i++) {
      buffer[i] = 0.;
    }

    // write to wav file output
    for (size_t i = 0; i < bufferSize + leftPatchSize + rightPatchSize; i++) {
      __output->tick(buffer[i]);
    }
  }
}

void writeChordMonoInstrument(stk::FileWvOut * __output,
                              const unsigned int __tempo, const Duration * __duration,
                              const std::vector<const Pitch *>&  __pitch_list,
                              stk::Instrmnt * __instr, double __amplitude,
                              const unsigned int __divide_ratio, const unsigned int __multiply_ratio,
                              const Duration * __left_shift, const Duration * __right_shift) {
  if (__output == nullptr) {
    HB_THROW_MSG(std::runtime_error, "stk::FileWvOut object ptr is NULL");
  }

  double seconds = 0. ;
  double freq = 0. ;
  size_t bufferSize = 0;
  size_t leftPatchSize = 0;
  size_t rightPatchSize = 0;

  if (__left_shift) {
    seconds = ((double)__multiply_ratio * __left_shift->getNum() / __left_shift->getDenom()) / __divide_ratio;
    seconds *= 4. * 60 / __tempo;
    leftPatchSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
  }
  if (__right_shift) {
    seconds = ((double)__multiply_ratio * __right_shift->getNum() / __right_shift->getDenom()) / __divide_ratio;
    seconds *= 4. * 60 / __tempo;
    rightPatchSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
  }

  if (__duration && __instr && !__pitch_list.empty()) {
    seconds = ((double)__multiply_ratio * __duration->getNum() / __duration->getDenom()) / __divide_ratio;
    seconds *= 4. * 60 / __tempo;
    bufferSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));

    // create empty out buffer
    stk::StkFloat buffer[bufferSize + leftPatchSize + rightPatchSize + 10];
    //for (size_t i = 0; i < bufferSize; i++) { buffer[i] = 0.; }

    // patch the buffer on the left
    for (size_t i = 0; i < leftPatchSize; i++) {
      buffer[i] = 0.;
    }
    // write to buffer
    for (size_t n = 0; n < __pitch_list.size(); n++) {
      if (__pitch_list[n]) {
        freq = __pitch_list[n]->toFrequency();
        __instr->noteOn(freq, __amplitude);
        for (size_t i = leftPatchSize; i < bufferSize + leftPatchSize; i++) {
          buffer[i] += __instr->tick();
        }
        __instr->noteOff(__amplitude);
      }
    }
    // patch the buffer on the right side
    for (size_t i = bufferSize + leftPatchSize; i < bufferSize + leftPatchSize + rightPatchSize; i++) {
      buffer[i] = 0.;
    }

    // write to wav file output
    for (size_t i = 0; i < bufferSize + leftPatchSize + rightPatchSize; i++) {
      __output->tick(buffer[i]);
    }
  }
}


void writeMuteNoteDummy(stk::FileWvOut * __output,
                          const unsigned int __tempo, const Duration * __duration) {
  writeSingleNote(__output, __tempo, __duration,
                  nullptr, nullptr, 0.0, 
                  1, 1, nullptr, nullptr);
}


void writeSingleNoteDummy(stk::FileWvOut * __output,
                          const unsigned int __tempo, const Duration * __duration,
                          stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude) {
  writeSingleNote(__output, __tempo, __duration,
                  __instr, __pitch, __amplitude,
                  1, 1, nullptr, nullptr);
}


/* Write chord buffer to WAV output. */
void writeChordDummy(stk::FileWvOut * __output,
                     const unsigned int __tempo, const Duration * __duration,
                     const std::vector<const Pitch *>&  __pitch_list,
                     stk::Instrmnt * __instr, const double __amplitude) {

  writeChordMonoInstrument(__output, __tempo, __duration, 
                           __pitch_list, __instr, __amplitude,
                           1, 1, nullptr, nullptr);
}


} // namespace stk_wv
} // namespace synth
} // namespace hautbois
