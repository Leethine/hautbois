#pragma once

#ifndef HBCONST_HPP
#define HBCONST_HPP

#include <string>
#include <array>
#include <vector>
#include <cstdint>

namespace hautbois {

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

// namespace hautbois