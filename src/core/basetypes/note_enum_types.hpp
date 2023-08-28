#pragma once

#ifndef NOTE_ENUM_TYPES_H
#define NOTE_ENUM_TYPES_H

#include <map>
#include <string>

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

namespace notename_str_enum_convert {
const std::map<std::string,NoteNameEnum> SCINAME_STRING_TO_ENUM {
  {"C", NoteNameEnum::C},
  {"D", NoteNameEnum::D},
  {"E", NoteNameEnum::E},
  {"F", NoteNameEnum::F},
  {"G", NoteNameEnum::G},
  {"A", NoteNameEnum::A},
  {"B", NoteNameEnum::B},

  {"R", NoteNameEnum::R},
  {"REST", NoteNameEnum::R},
  {"S", NoteNameEnum::S},
  {"SILENCE", NoteNameEnum::S}
};

const std::map<NoteNameEnum,std::string> SCINAME_ENUM_TO_STRING {
  {NoteNameEnum::C, "C"},
  {NoteNameEnum::D, "D"},
  {NoteNameEnum::E, "E"},
  {NoteNameEnum::F, "F"},
  {NoteNameEnum::G, "G"},
  {NoteNameEnum::A, "A"},
  {NoteNameEnum::B, "B"},

  {NoteNameEnum::R, "REST"},
  {NoteNameEnum::S, "SILENCE"}
};

const std::map<std::string,NoteNameEnum> LATINNAME_STRING_TO_ENUM {
  {"DO", NoteNameEnum::C},
  {"UT", NoteNameEnum::C},
  {"RE", NoteNameEnum::D},
  {"MI", NoteNameEnum::E},
  {"FA", NoteNameEnum::F},
  {"SOL", NoteNameEnum::G},
  {"LA", NoteNameEnum::A},
  {"SI", NoteNameEnum::B},

  {"R", NoteNameEnum::R},
  {"REST", NoteNameEnum::R},
  {"S", NoteNameEnum::S},
  {"SILENCE", NoteNameEnum::S}
};

const std::map<NoteNameEnum,std::string> LATINNAME_ENUM_TO_STRING {
  {NoteNameEnum::C, "DO"},
  {NoteNameEnum::D, "RE"},
  {NoteNameEnum::E, "MI"},
  {NoteNameEnum::F, "FA"},
  {NoteNameEnum::G, "SOL"},
  {NoteNameEnum::A, "LA"},
  {NoteNameEnum::B, "SI"},

  {NoteNameEnum::R, "REST"},
  {NoteNameEnum::S, "SILENCE"}
};

} // namespace notename_str_enum_convert

namespace accidental_str_enum_convert {

const std::map<std::string,AccidentalEnum> ACCIDENTAL_STRING_TO_ENUM {
  {"n", AccidentalEnum::n},
  {"", AccidentalEnum::n},
  {"s", AccidentalEnum::s},
  {"#", AccidentalEnum::s},
  {"x", AccidentalEnum::x},
  {"ss", AccidentalEnum::x},
  {"b", AccidentalEnum::b},
  {"bb", AccidentalEnum::bb}
};

const std::map<AccidentalEnum,std::string> ACCIDENTAL_ENUM_TO_STRING {
  {AccidentalEnum::n, ""},
  {AccidentalEnum::s, "#"},
  {AccidentalEnum::x, "x"},
  {AccidentalEnum::b, "b"},
  {AccidentalEnum::bb, "bb"}
};

} // namespace accidental_str_enum_convert

namespace octave_str_enum_convert {

const std::map<std::string,OctaveEnum> OCTAVE_STRING_TO_ENUM {
  {"", OctaveEnum::unknown},
  {"0", OctaveEnum::zeroth},
  {"1", OctaveEnum::first},
  {"2", OctaveEnum::second},
  {"3", OctaveEnum::third},
  {"4", OctaveEnum::fourth},
  {"5", OctaveEnum::fifth},
  {"6", OctaveEnum::sixth},
  {"7", OctaveEnum::seventh},
  {"8", OctaveEnum::eighth}
};

const std::map<OctaveEnum,std::string> OCTAVE_ENUM_TO_STRING {
  {OctaveEnum::zeroth, "0"},
  {OctaveEnum::first,  "1"},
  {OctaveEnum::second, "2"},
  {OctaveEnum::third,  "3"},
  {OctaveEnum::fourth, "4"},
  {OctaveEnum::fifth,  "5"},
  {OctaveEnum::sixth,  "6"},
  {OctaveEnum::seventh,"7"},
  {OctaveEnum::eighth, "8"}
};

} // namespace octave_str_enum_convert

} // namespace notation
} // namespace hautbois

#endif