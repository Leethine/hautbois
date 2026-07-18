#pragma once

#ifndef HBCONST_HPP
#define HBCONST_HPP

#include <array>
#include <string>
#include <cstdint>

#include "hbdefs.hpp"

namespace hautbois {
namespace hbconst {

const static std::array<char, 9> VALID_PITCH_NAME {
  CHAR_PITCHNAME_C,
  CHAR_PITCHNAME_D,
  CHAR_PITCHNAME_E,
  CHAR_PITCHNAME_F,
  CHAR_PITCHNAME_G,
  CHAR_PITCHNAME_A,
  CHAR_PITCHNAME_B,
  CHAR_PITCHNAME_REST,
  CHAR_PITCHNAME_SILENCE
};

const static std::array<char, 6> VALID_PITCH_ACCIDENTAL {
  CHAR_ACCIDENTAL_NATURAL,
  CHAR_ACCIDENTAL_FLAT,
  CHAR_ACCIDENTAL_DOUBLEFLAT,
  CHAR_ACCIDENTAL_DOUBLEFLAT,
  CHAR_ACCIDENTAL_SHARP,
  CHAR_ACCIDENTAL_DOUBLESHARP
};

const static std::array<uint8_t, 9> VALID_PITCH_OCTAVE {
  0, 1, 2, 3, 4, 5, 6, 7, 8
};

const static std::array<uint8_t, 8> VALID_NOTE_VALUE {
  1, 2, 4, 8, 16, 32, 64, 128
};

const static std::array<std::string, 16> VALID_PROPERTY_ORNAMENT {
  "prall", "prallup", "pralldown", "upprall", "downprall", "prallprall", "lineprall",
  "prallmordent", "mordent", "upmordent", "downmordent", "trill", "turn", "reverseturn",
  "slashturn", "haydnturn"
};

const static std::array<std::string, 10> VALID_PROPERTY_ARTICULATION {
  "accent", "espressivo", "marcato", "portato", "staccatissimo",
  "staccato", "tenuto", "fermata", "longfermata", "shortfermata"
};

const static std::array<std::string, 7> VALID_PROPERTY_DYNAMIC {
  "p", "pp", "ppp", "mf", "f", "ff", "fff"
};

const static std::array<std::string, 8> VALID_PROPERTY_CONTROL {
  "<", ">", "!", "cresc.", "decresc.", "rit.", "ral.", "a-tempo"
};

} // namespace hbconst
} // namespace hautbois

#endif