#include "note_enum_converter.hpp"

const std::map<std::string, hautbois::core::NoteNameEnum> hautbois::core::notename_str_enum_convert::SCINAME_STRING_TO_ENUM {
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

const std::map<hautbois::core::NoteNameEnum, std::string> hautbois::core::notename_str_enum_convert::SCINAME_ENUM_TO_STRING {
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

const std::map<std::string, hautbois::core::NoteNameEnum> hautbois::core::notename_str_enum_convert::LATINNAME_STRING_TO_ENUM {
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

const std::map<hautbois::core::NoteNameEnum, std::string> hautbois::core::notename_str_enum_convert::LATINNAME_ENUM_TO_STRING {
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

const std::map<std::string, hautbois::core::AccidentalEnum> hautbois::core::accidental_str_enum_convert::ACCIDENTAL_STRING_TO_ENUM {
  {"n", AccidentalEnum::n},
  {"", AccidentalEnum::n},
  {"s", AccidentalEnum::s},
  {"#", AccidentalEnum::s},
  {"x", AccidentalEnum::x},
  {"ss", AccidentalEnum::x},
  {"b", AccidentalEnum::b},
  {"bb", AccidentalEnum::bb}
};

const std::map<hautbois::core::AccidentalEnum, std::string> hautbois::core::accidental_str_enum_convert::ACCIDENTAL_ENUM_TO_STRING {
  {AccidentalEnum::n, ""},
  {AccidentalEnum::s, "#"},
  {AccidentalEnum::x, "x"},
  {AccidentalEnum::b, "b"},
  {AccidentalEnum::bb, "bb"}
};

const std::map<std::string, hautbois::core::OctaveEnum> hautbois::core::octave_str_enum_convert::OCTAVE_STRING_TO_ENUM {
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

const std::map<hautbois::core::OctaveEnum,std::string> hautbois::core::octave_str_enum_convert::OCTAVE_ENUM_TO_STRING {
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