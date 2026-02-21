#pragma once

#ifndef PITCH_H
#define PITCH_H

#include "symbol_raw/pitch_raw.hpp"

#include <string>
#include <vector>

namespace hautbois {
namespace core {

class Pitch {

 protected:

  PitchRaw _raw;

 public:

  Pitch(const char& __name, const char& __acc, const int& __oct);

  Pitch(const std::string& __name, const std::string& __acc, const int& __oct);

  Pitch(const std::string& __name, const std::string& __acc, const std::string& __oct);

  Pitch(const std::string& __name);

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

  virtual double toFrequency(const std::string& iTemperament) const;

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