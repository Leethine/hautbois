#pragma once

#ifndef chart_def_types_H
#define chart_def_types_H
#endif

#include <map>
#include <string>
#include <cstdint>

#define OPTIMIZATION_NONE 1
#undef OPTIMIZATION_MEM
#undef OPTIMIZATION_SPEED

namespace hautbois {

#ifdef OPTIMIZATION_MEM
using UInt8 = uint_least8_t;
#undef OPTIMIZATION_SPEED
#undef OPTIMIZATION_NONE
#endif

#ifdef OPTIMIZATION_SPEED
using UInt8 = uint_fast8_t;
#undef OPTIMIZATION_MEM
#undef OPTIMIZATION_NONE
#endif

#ifdef OPTIMIZATION_NONE
using UInt8 = uint8_t;
#undef OPTIMIZATION_MEM
#undef OPTIMIZATION_NONE
#endif

/*
#ifdef REST_NOTE_INDEX
#undef REST_NOTE_INDEX
#define REST_NOTE_INDEX    109
#else
#define REST_NOTE_INDEX    109
#endif

#ifdef SILENCE_NOTE_INDEX
#undef SILENCE_NOTE_INDEX
#define SILENCE_NOTE_INDEX 111
#else
#define SILENCE_NOTE_INDEX 111
#endif

#ifdef CHORD_INDEX
#undef CHORD_INDEX
#define CHORD_INDEX 110
#else
#define CHORD_INDEX 110
#endif

#ifdef ERROR_NOTE_INDEX
#undef ERROR_NOTE_INDEX
#define ERROR_NOTE_INDEX 128
#else
#define ERROR_NOTE_INDEX 128
#endif
*/

namespace core {
namespace notename_str_index_table {

using StringToIndexMap = std::map<std::string, UInt8>;
using IndexToStringMap = std::map<UInt8, std::string>;

} // namespace notename_str_index_table

const UInt8 SILENCE_NOTE_INDEX = 109;
const UInt8 REST_NOTE_INDEX = 110;
const UInt8 CHORD_INDEX = 111;
const UInt8 XPLET_INDEX = 112;
const UInt8 ERROR_NOTE_INDEX = 120;

} // namespace core
} // namespace hautbois