#pragma once

#ifndef STK_NOTE_STREAM
#define STK_NOTE_STREAM

#include <vector>

namespace stk {
class FileWvOut;
class Instrmnt;
} // namespace stk

namespace hautbois {
class Duration;
class Pitch;

namespace synth {

/* Write buffer to Wav file.
 * This function does not clean the buffer.
 */
void StkSaveBufferToWav(stk::FileWvOut * __output, double * __buffer, const size_t __bufferSize);

/* Return empty buffer (needs to be manually cleaned-up) */
double * StkBufferCreatorMutedNote(size_t& __oBufferSize,
                                   const unsigned int __tempo, const Duration * __duration,
                                   const unsigned int __divider, const unsigned  int __multiplier);

/* Return single note buffer (needs to be manually cleaned-up) */
double * StkBufferCreatorSingleNote(size_t& __oBufferSize,
                                    const unsigned int __tempo, const Duration * __duration,
                                    const unsigned int __divider, const unsigned  int __multiplier,
                                    stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude);

/* Return chord buffer (needs to be manually cleaned-up)
 * It is possible to only provide one instrument and one amplitude
 */
double * StkBufferCreatorChord(size_t& __oBufferSize,
                               const unsigned int __tempo, const Duration * __duration,
                               const unsigned int __divider, const unsigned int __multiplier,
                               const std::vector<const Pitch *>&   __pitch_list,
                               const std::vector<stk::Instrmnt *>& __instr_list,
                               const std::vector<double>&          __amplitude_list);

} // namespace synth
} // namespace hautbois

#endif