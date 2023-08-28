#pragma once

#ifndef NOTE_ENUM_CONVERTER_H
#define NOTE_ENUM_CONVERTER_H

#include "note_enum_types.hpp"
#include <map>
#include <string>

namespace hautbois {
namespace core {

namespace notename_str_enum_convert {

extern const std::map<std::string,NoteNameEnum> SCINAME_STRING_TO_ENUM;
extern const std::map<NoteNameEnum,std::string> SCINAME_ENUM_TO_STRING;
extern const std::map<std::string,NoteNameEnum> LATINNAME_STRING_TO_ENUM;
extern const std::map<NoteNameEnum,std::string> LATINNAME_ENUM_TO_STRING;

} // namespace notename_str_enum_convert

namespace accidental_str_enum_convert {

extern const std::map<std::string,AccidentalEnum> ACCIDENTAL_STRING_TO_ENUM;
extern const std::map<AccidentalEnum,std::string> ACCIDENTAL_ENUM_TO_STRING;

} // namespace accidental_str_enum_convert

namespace octave_str_enum_convert {

extern const std::map<std::string,OctaveEnum> OCTAVE_STRING_TO_ENUM;
extern const std::map<OctaveEnum,std::string> OCTAVE_ENUM_TO_STRING;

} // namespace octave_str_enum_convert

} // namespace core
} // namespace hautbois

#endif