#include "stk_note_stream.hpp"
#include "hb_stk_defs.hpp"
#include "../../note/duration.hpp"
#include "../../note/pitch.hpp"

#include <cstddef>
#include <stk/FileWvOut.h>
#include <stk/Instrmnt.h>
#include <cmath>

namespace hautbois {
namespace synth {

void StkSaveBufferToWav(stk::FileWvOut * __output, double * __buffer, const size_t __bufferSize) {
  if (__buffer) {
    for (size_t i = 0; i < __bufferSize; i++) {
      __output->tick(__buffer[i]);
    }
  }
}

double * StkBufferCreatorMutedNote(size_t& __oBufferSize,
  const unsigned int __tempo,   const Duration *   __duration,
  const unsigned int __divider, const unsigned int __multiplier) {

  double * outbuffer = nullptr;
  double seconds = 0. ;
  if (__duration) {
    seconds = ((double)__multiplier * __duration->getNum() / __duration->getDenom()) / __divider;
    seconds *= 4. * 60 / __tempo;
    __oBufferSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
    outbuffer = new double[__oBufferSize + 10];
    for (size_t i = 0; i < __oBufferSize; i++) {
      outbuffer[i] = 0.;
    }
  }

  return outbuffer;
}

double * StkBufferCreatorSingleNote(size_t& __oBufferSize,
  const unsigned int __tempo,   const Duration *    __duration,
  const unsigned int __divider, const unsigned  int __multiplier,
  stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude) {

  double * outbuffer = nullptr;
  double seconds = 0. ;
  double freq = 0. ;
  if (__duration && __pitch) {
    freq = __pitch->toFrequency();
    seconds = ((double)__multiplier * __duration->getNum() / __duration->getDenom()) / __divider;
    seconds *= 4. * 60 / __tempo;
    __oBufferSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
    outbuffer = new double[__oBufferSize + 10];
    __instr->noteOn(freq, __amplitude);
    for (size_t i = 0; i < __oBufferSize; i++) {
      outbuffer[i] = __instr->tick();
    }
    __instr->noteOff(__amplitude);
  }

  return outbuffer;
}

double * StkBufferCreatorChord(size_t& __oBufferSize,
  const unsigned int __tempo,   const Duration *   __duration,
  const unsigned int __divider, const unsigned int __multiplier,
  const std::vector<const Pitch *>&   __pitch_list,
  const std::vector<stk::Instrmnt *>& __instr_list,
  const std::vector<double>&          __amplitude_list) {

  // it is possible to only provide one instrument or one amplitude
  std::vector<double> amplitude_lst;
  if (__amplitude_list.size() == 1) {
    amplitude_lst.reserve(__pitch_list.size());
    for (size_t i = 0; i < __pitch_list.size(); i++) {
      amplitude_lst.push_back(__amplitude_list.front());
    }
  }
  else {
    amplitude_lst = __amplitude_list;
  }

  /*
  std::vector<stk::Instrmnt *> instr_lst;
  if (__instr_list.size() == 1) {
    instr_lst.reserve(__pitch_list.size());
    for (size_t i = 0; i < __pitch_list.size(); i++) {
      instr_lst.push_back(__instr_list.front());
    }
  }
  else {
    instr_lst = __instr_list;
  }
  */
  auto& instr_lst = __instr_list;

  double * outbuffer = nullptr;
  double seconds = 0. ;
  double freq = 0. ;
  if (__duration && __pitch_list.size() == instr_lst.size() &&
      __pitch_list.size() == amplitude_lst.size()) {
    seconds = ((double)__multiplier * __duration->getNum() / __duration->getDenom()) / __divider;
    seconds *= 4. * 60 / __tempo;
    __oBufferSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
    // create empty out buffer
    outbuffer = new double[__oBufferSize + 10];
    for (size_t i = 0; i < __oBufferSize; i++) {
      outbuffer[i] += 0.;
    }
    // write to buffer
    for (size_t n = 0; n < __pitch_list.size(); n++) {
      if (__pitch_list[n] && instr_lst[n]) {
        freq = __pitch_list[n]->toFrequency();
        instr_lst[n]->noteOn(freq, amplitude_lst[n]);
        for (size_t i = 0; i < __oBufferSize; i++) {
          outbuffer[i] += instr_lst[n]->tick();
        }
        instr_lst[n]->noteOff(amplitude_lst[n]);
      }
    }
  }

  return outbuffer;
}

} // namespace synth
} // namespace hautbois
