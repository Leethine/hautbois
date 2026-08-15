#include "stk_buffer_writer.hpp"
#include "hb_stk_defs.hpp"
#include "../../note/duration.hpp"
#include "../../note/pitch.hpp"

#include <cmath>
#include <stk/FileWvOut.h>
#include <stk/Instrmnt.h>
#include <stk/Stk.h>

namespace hautbois {
namespace synth {
namespace stk_buffer {

void calculateBufferSize(size_t& obufferSize,
                         const unsigned int __tempo, const Duration * __duration,
                         const unsigned int __divide_ratio, const unsigned  int __multiply_ratio) {
  obufferSize = 0;
  if (__duration) {
    double seconds = (double) __multiply_ratio * __duration->getNum() /
                     __duration->getDenom() / __divide_ratio * 4. * 60 / __tempo;
    obufferSize = size_t(std::round(STK_DEFAULT_SAMPLE_RATE * seconds));
  }
}

void calculateBufferSize(size_t& obufferSize, const unsigned int __tempo, const Duration * __duration) {
  calculateBufferSize(obufferSize, __tempo, __duration, 1, 1);
}

void clearBuffer(double * oBuffer, const size_t __bufferSize) {
  for (size_t i = 0; i < __bufferSize; i++) {
    oBuffer[i] = 0.;
  }
}

void writeToBuffer(double * oBuffer, const size_t __bufferSize,
                   stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude) {
  if (__instr && __pitch) {
    double freq = __pitch->toFrequency();
    __instr->noteOn(freq, __amplitude);
    for (size_t i = 0; i < __bufferSize; i++) {
      oBuffer[i] += __instr->tick();
    }
    __instr->noteOff(__amplitude);
  }
  else {
    for (size_t i = 0; i < __bufferSize; i++) {
      oBuffer[i] += .0;
    }
  }
}


void writeToBuffer(double * oBuffer, const size_t __bufferSize,
                   stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude,
                   void (*Method1)(stk::Instrmnt*,double,double), void (*Method2)(stk::Instrmnt*,double),
                   void (*Method3)(stk::Instrmnt*,double,double), void (*Method4)(stk::Instrmnt*,double)) {
  // TODO
  // implementation not needed for now
}


} // namespace stk_wv
} // namespace synth
} // namespace hautbois
