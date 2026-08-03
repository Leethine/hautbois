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
namespace stk_wav_writer {

/* Write empty buffer to WAV output */
void writeMutedNote(stk::FileWvOut * __output,
                    const unsigned int __tempo, const Duration * __duration,
                    const unsigned int __divider, const unsigned  int __multiplier);

/* Write single note buffer to WAV output */
void writeSingleNote(stk::FileWvOut * __output,
                     const unsigned int __tempo, const Duration * __duration,
                     const unsigned int __divider, const unsigned  int __multiplier,
                     stk::Instrmnt * __instr, const Pitch * __pitch, const double __amplitude);

/* Write chord buffer to WAV output. */
void writeChord(stk::FileWvOut * __output,
                const unsigned int __tempo, const Duration * __duration,
                const unsigned int __divider, const unsigned int __multiplier,
                const std::vector<const Pitch *>&   __pitch_list,
                const std::vector<stk::Instrmnt *>& __instr_list,
                const std::vector<double>&          __amplitude_list);

} // namespace stk_wav_writer
} // namespace synth
} // namespace hautbois

#endif