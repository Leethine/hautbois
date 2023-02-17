#pragma once

#ifndef CHART_DEF_TYPES_H
#define CHART_DEF_TYPES_H

#include "../basetypes/base_def_types.hpp"

#include <map>
#include <string>
#include <cstdint>

namespace hautbois {
namespace core {

const UInt8 SILENCE_NOTE_INDEX = 109;
const UInt8 REST_NOTE_INDEX = 110;
const UInt8 CHORD_INDEX = 111;
const UInt8 XPLET_INDEX = 112;
const UInt8 ERROR_NOTE_INDEX = 120;

namespace notename_str_index_table {

using StringToIndexMap = std::map<std::string, UInt8>;
using IndexToStringMap = std::map<UInt8, std::string>;

} // namespace notename_str_index_table
} // namespace core
} // namespace hautbois

#endif