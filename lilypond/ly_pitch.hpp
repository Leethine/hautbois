#pragma once

#include "../symbol/pitch.hpp"

#ifndef LY_PITCH_H
#define LY_PITCH_H

#include <string>

namespace hautbois {
namespace ly {

class LyPitch : public core::Pitch {

 protected:
  LyPitch();

 public:

  LyPitch(const std::string& __pitch);

  LyPitch(const std::string& __name, const int& __octave);

  LyPitch(const Pitch& p);

  LyPitch(const Pitch&& p);

  LyPitch(const LyPitch& p);

  LyPitch(const LyPitch&& p);

  virtual ~LyPitch();

  LyPitch& operator=(const LyPitch& p);

  LyPitch& operator=(const core::Pitch& p);

  virtual std::string getName() const;

  virtual std::string getAccidental() const;
  
  virtual std::string getOctave() const;

  virtual int getOctaveInt() const;

  virtual const core::PitchRaw& raw() const;
  
  virtual core::PitchRaw getRaw() const;

  virtual std::string toString() const;

  virtual int toIndex() const;

  virtual double toFrequency(const std::string& __temperament) const;

  virtual void modify(const char * __context);

  using core::Pitch::operator==;
  virtual bool operator==(const LyPitch& p) const;

  using core::Pitch::operator!=;
  virtual bool operator!=(const LyPitch& p) const;

  using core::Pitch::operator>;
  virtual bool operator>(const LyPitch& p) const;

  using core::Pitch::operator<;
  virtual bool operator<(const LyPitch& p) const;

  using core::Pitch::operator>=;
  virtual bool operator>=(const LyPitch& p) const;

  using core::Pitch::operator<=;
  virtual bool operator<=(const LyPitch& p) const;

};

} // namespace hautbois
} // namespace core

#endif