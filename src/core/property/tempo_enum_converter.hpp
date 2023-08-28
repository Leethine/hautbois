#pragma once

#ifndef TEMPO_ENUM_CONVERTER_H
#define TEMPO_ENUM_CONVERTER_H

#include "tempo_enum_types.hpp"
#include <string>
#include <map>

namespace hautbois {
namespace core {

namespace tempo_str_enum_convert {

extern std::map<std::string, TempoEnum> TEMPO_STRING_TO_ENUM;
extern std::map<TempoEnum, std::string> TEMPO_ENUM_TO_STRING;

} // namespace tempo_str_enum_convert

} // namespace core
} // namespace hautbois

#endif
