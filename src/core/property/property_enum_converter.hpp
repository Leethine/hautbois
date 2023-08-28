#pragma once

#ifndef PROPERTY_ENUM_CONVERTER_H
#define PROPERTY_ENUM_CONVERTER_H

#include "property_enum_types.hpp"
#include <string>
#include <map>

namespace hautbois {
namespace core {

namespace articulation_str_enum_convert {
extern const std::map<std::string, ArticulationEnum> ARTICULATION_STRING_TO_ENUM;
extern const std::map<ArticulationEnum, std::string> ARTICULATION_ENUM_TO_STRING;
}

namespace dynamics_str_enum_convert {
extern const std::map<std::string, DynamicsEnum> DYNAMICS_STRING_TO_ENUM;
extern const std::map<DynamicsEnum, std::string> DYNAMICS_ENUM_TO_STRING;
}

namespace ornament_str_enum_convert {
extern const std::map<std::string, OrnamentEnum> ORNAMENT_STRING_TO_ENUM;
extern const std::map<OrnamentEnum, std::string> ORNAMENT_ENUM_TO_STRING;
}

} // namespace core
} // namespace hautbois

#endif