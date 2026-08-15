#pragma once

#ifndef STK_BUFFER_WRITER_HPP
#define STK_BUFFER_WRITER_HPP

#include <cstddef>

namespace stk {
class FileWvOut;
class Instrmnt;
} // namespace stk

namespace hautbois {
class Duration;
class Pitch;

namespace synth {
namespace stk_buffer {

/* Calculate buffer size based on the Duration.
 * Optional : it is possible to reshape the Duration
 */

void calculateBufferSize(size_t& obufferSize,
                         const unsigned int __tempo, const Duration * __duration,
                         const unsigned int __divide_ratio, const unsigned  int __multiply_ratio);

void calculateBufferSize(size_t& obufferSize, const unsigned int __tempo, const Duration * __duration);

/* Initialize the buffer with 0. value */
void clearBuffer(double * oBuffer, const size_t __bufferSize);

/* Write single note to sound buffer accumulatively (array of double).
 * If either __instr or __pitch is NULL, write zero to buffer
 */
void writeToBuffer(double * oBuffer, const size_t __bufferSize,
                   stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude);

/* Possibility to call stk::Instrmnt methods before and after noteOn/noteOff
 */
void writeToBuffer(double * oBuffer, const size_t __bufferSize,
                   stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude,
                   void (*Method1)(stk::Instrmnt*,double,double), void (*Method2)(stk::Instrmnt*,double),
                   void (*Method3)(stk::Instrmnt*,double,double), void (*Method4)(stk::Instrmnt*,double));


} // namespace stk_wv
} // namespace synth
} // namespace hautbois

#endif