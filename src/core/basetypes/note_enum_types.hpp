#pragma once

#ifndef NOTE_ENUM_TYPES_H
#define NOTE_ENUM_TYPES_H

namespace hautbois {
namespace core {

enum class NoteNameEnum {
  C, D, E, F, G, A, B, R, S, CHORD, XPLET
};

enum class LatinNoteNameEnum {
  Do, Re, Mi, Fa, Sol, La, Si
};

enum class OctaveEnum {
  zeroth,first,second,third,fourth,fifth,sixth,seventh,eighth,
  unknown
};

enum class AccidentalEnum {
  n, s, b, ss, x, bb
};

enum class RhythmicValuesEnum {
  Large,
  Long,
  Breve,
  Semibreve,
  Minim,
  Crotchet,
  Quaver,
  Semiquaver,
  Demisemiquaver,
  Hemidemisemiquaver,
  Semihemidemisemiquaver,
  Quasihemidemisemiquaver,
  Demisemihemidemisemiquaver
};

} // namespace notation
} // namespace hautbois

#endif