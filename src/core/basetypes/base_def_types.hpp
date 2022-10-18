#pragma once

#ifndef base_def_types_H
#define base_def_types_H
#endif

#include <cstdint>
#include <cfloat>
#include <stdexcept>
#include <string>
#include <map>

#define OPTIMIZATION_NONE  1
#undef  OPTIMIZATION_SPEED
#undef  OPTIMIZATION_MEM

#define INVALID_INPUT_ERROR 1
#define RUNTIME_ERROR 2

namespace hautbois {
/* Floating point types definition */
using Flt32   = float;
using Flt64   = double;
using Flt128  = long double;

/* Note: Large enough values, use them for safety purposes only. */
using LargeUIntValue = unsigned long long;
using LargeIntValue  = signed long long;
using LargeRatValue  = long double;

/* Fixed width integer type definition */
#ifdef OPTIMIZATION_MEM
using Int8   = int_least8_t;
using Int16  = int_least16_t;
using Int32  = int_least32_t;
using Int64  = int_least64_t;
using Int8   = int_least8_t;
using Int16  = int_least16_t;
using Int32  = int_least32_t;
using Int64  = int_least64_t;
using UInt8  = uint_least8_t;
using UInt16 = uint_least16_t;
using UInt32 = uint_least32_t;
using UInt64 = uint_least64_t;
using UInt8  = uint_least8_t;
using UInt16 = uint_least16_t;
using UInt32 = uint_least32_t;
using UInt64 = uint_least64_t;
#undef OPTIMIZATION_SPEED
#undef OPTIMIZATION_NONE
#endif

#ifdef OPTIMIZATION_SPEED
using Int8   = int_fast8_t;
using Int16  = int_fast16_t;
using Int32  = int_fast32_t;
using Int64  = int_fast64_t;
using Int8   = int_fast8_t;
using Int16  = int_fast16_t;
using Int32  = int_fast32_t;
using Int64  = int_fast64_t;
using UInt8  = uint_fast8_t;
using UInt16 = uint_fast16_t;
using UInt32 = uint_fast32_t;
using UInt64 = uint_fast64_t;
using UInt8  = uint_fast8_t;
using UInt16 = uint_fast16_t;
using UInt32 = uint_fast32_t;
using UInt64 = uint_fast64_t;
#undef OPTIMIZATION_NONE
#undef OPTIMIZATION_MEM
#endif

#ifdef OPTIMIZATION_NONE
using Int8   = int8_t;
using Int16  = int16_t;
using Int32  = int32_t;
using Int64  = int64_t;
using Int8   = int8_t;
using Int16  = int16_t;
using Int32  = int32_t;
using Int64  = int64_t;
using UInt8  = uint8_t;
using UInt16 = uint16_t;
using UInt32 = uint32_t;
using UInt64 = uint64_t;
using UInt8  = uint8_t;
using UInt16 = uint16_t;
using UInt32 = uint32_t;
using UInt64 = uint64_t;
#undef OPTIMIZATION_MEM
#undef OPTIMIZATION_SPEED
#endif

/* Exceptions */
using InvalidArgumentException = std::invalid_argument;
using RunTimeException = std::runtime_error;

/* Misc definition */

using Boolean = bool;
using StringField = std::string;
using NumberField = std::string;

} // namespace hautbois

/* Quick note about the range.
CHAR_BIT       = 8
MB_LEN_MAX     = 16
CHAR_MIN       = -128
CHAR_MAX       = 127
SCHAR_MIN      = -128
SHRT_MIN       = -32768
INT_MIN        = -2147483648
LONG_MIN       = -9223372036854775808
LLONG_MIN      = -9223372036854775808
SCHAR_MAX      = 127
SHRT_MAX       = 32767
INT_MAX        = 2147483647
LONG_MAX       = 9223372036854775807
LLONG_MAX      = 9223372036854775807
UCHAR_MAX      = 255
USHRT_MAX      = 65535
UINT_MAX       = 4294967295
ULONG_MAX      = 18446744073709551615
ULLONG_MAX     = 18446744073709551615
PTRDIFF_MIN    = -9223372036854775808
PTRDIFF_MAX    = 9223372036854775807
SIZE_MAX       = 18446744073709551615
SIG_ATOMIC_MIN = -2147483648
SIG_ATOMIC_MAX = 2147483647
WCHAR_MIN      = -2147483648
WCHAR_MAX      = 2147483647
WINT_MIN       = 0
WINT_MAX       = 4294967295
*/