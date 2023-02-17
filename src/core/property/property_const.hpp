#pragma once

#ifndef PROPERTY_CONST_H
#define PROPERTY_CONST_H

#include "../basetypes/base_def_types.hpp"

namespace hautbois {
namespace core {
namespace property_values {

const UInt8 UNKNOWN_VALUE = 0;
const UInt8 DEFAULT_VALUE = 0;

/* Ornaments */
// acciaccatura
// appoggiatura
// arpeggio
// cadenza
// fioritura
// glissando
// gruppetto
// mordente
const UInt8 MORDENT = 1;
const UInt8 PRALL = 2;
const UInt8 MORDENT_SEMITONE = 3;
const UInt8 PRALL_SEMITONE = 4;
const UInt8 UPMORDENT = 5;
const UInt8 PRALLUP = 6;
const UInt8 DOWNMORDENT = 7;
const UInt8 PRALLDOWN = 8;
const UInt8 DOWNPRALL = 9;
const UInt8 PRALLMORDENT = 10;
const UInt8 MORDENTMORDENT = 11;
const UInt8 PRALLPRALL = 12;

// trillo
// tremolo

//TODO add more property constants and spec

} // property_values
} // namespace core
} // namespace hautbois

#endif