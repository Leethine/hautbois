#pragma once

#ifndef PITCH_H
#define PITCH_H

#include "../symbol_raw/pitch_raw.hpp"
#include "../symbol_raw/core_types.hpp"

#include <string>
#include <array>

namespace hautbois {
namespace core {

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

const static int PITCH_OCTAVE_MIN = 0;
const static int PITCH_OCTAVE_MAX = 8;

class Pitch {

 protected:

  PitchRaw _raw;
  
  Pitch();

 public:

  Pitch(const char& __name, const char& __acc, const int& __oct);

  Pitch(const char& __name, const int& __oct);

  Pitch(const char& __name);

  Pitch(const Pitch& p);

  Pitch(const Pitch&& p);

  Pitch(const PitchRaw& p);

  Pitch(const PitchRaw&& p);

  virtual ~Pitch();

  Pitch& operator=(const Pitch& p);

  virtual std::string getName() const;

  virtual std::string getAccidental() const;

  virtual std::string getOctave() const;

  virtual int getOctaveInt() const;

  virtual const PitchRaw& raw() const;

  virtual PitchRaw getRaw() const;

  virtual std::string toString() const;

  virtual int toIndex() const;

  virtual double toFrequency(const std::string& __temperament) const;

  virtual void modify(const char * __context);

  virtual bool operator==(const Pitch& p) const;

  virtual bool operator!=(const Pitch& p) const;

  virtual bool operator>(const Pitch& p) const;

  virtual bool operator<(const Pitch& p) const;

  virtual bool operator>=(const Pitch& p) const;

  virtual bool operator<=(const Pitch& p) const;

};

} // namespace hautbois
} // namespace core

#endif