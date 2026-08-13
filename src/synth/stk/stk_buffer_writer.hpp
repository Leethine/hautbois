#pragma once

#ifndef STK_BUFFER_WRITER_HPP
#define STK_BUFFER_WRITER_HPP

#include <vector>

namespace stk {
class FileWvOut;
class Instrmnt;
} // namespace stk

namespace hautbois {
class Duration;
class Pitch;

namespace synth {
namespace stk_wv {

/* Write single note buffer to WAV output.
 * If either __instr or __pitch is NULL, write empty buffer
 */
void writeSingleNote(stk::FileWvOut * __output,
                     const unsigned int __tempo, const Duration * __duration,
                     stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude,
                     const unsigned int __divide_ratio, const unsigned  int __multiply_ratio,
                     const Duration * __left_shift, const Duration * __right_shift);

/* Write chord buffer to WAV output. */
void writeChord(stk::FileWvOut * __output,
                const unsigned int __tempo, const Duration * __duration,
                const std::vector<const Pitch *>&   __pitch_list,
                const std::vector<stk::Instrmnt *>& __instr_list,
                const std::vector<double>&          __amplitude_list,
                const unsigned int __divide_ratio, const unsigned int __multiply_ratio,
                const Duration * __left_shift, const Duration * __right_shift);

void writeChordMonoInstrument(stk::FileWvOut * __output,
                              const unsigned int __tempo, const Duration * __duration,
                              const std::vector<const Pitch *>&  __pitch_list,
                              stk::Instrmnt * __instr, double __amplitude,
                              const unsigned int __divide_ratio, const unsigned int __multiply_ratio,
                              const Duration * __left_shift, const Duration * __right_shift);


/* Write chord buffer to WAV output, but each note has a left shift.
 * Useful when creating arpeggio. */
// Todo implement
/*
void writeChordDiff(stk::FileWvOut * __output,
                    const unsigned int __tempo, const Duration * __duration,
                    const std::vector<const Pitch *>&   __pitch_list,
                    const std::vector<stk::Instrmnt *>& __instr_list,
                    const std::vector<double>&          __amplitude_list,
                    const unsigned int __divide_ratio, const unsigned int __multiply_ratio,
                    std::vector<const Duration *> __left_shift_list);
*/


/* Dummy note wrappers */
void writeMuteNoteDummy(stk::FileWvOut * __output,
                        const unsigned int __tempo, const Duration * __duration);

void writeSingleNoteDummy(stk::FileWvOut * __output,
                          const unsigned int __tempo, const Duration * __duration,
                          stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude);

/* Write chord buffer to WAV output. */
void writeChordDummy(stk::FileWvOut * __output,
                     const unsigned int __tempo, const Duration * __duration,
                     const std::vector<const Pitch *>&  __pitch_list,
                     stk::Instrmnt * __instr, const double __amplitude);

} // namespace stk_wv
} // namespace synth
} // namespace hautbois

#endif