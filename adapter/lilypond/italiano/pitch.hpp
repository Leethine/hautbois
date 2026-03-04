#pragma once

#include "symbol/pitch.hpp"

#ifndef LY_PITCH_IT_H
#define LY_PITCH_IT_H

#include <string>
#include <vector>

namespace hautbois {
namespace ly {

class LyPitchIt : public core::Pitch {

 public:

  LyPitchIt();

  LyPitchIt(const std::string& __pitch);

  LyPitchIt(const Pitch& p);

  LyPitchIt(const Pitch&& p);

  LyPitchIt(const LyPitchIt& p);

  LyPitchIt(const LyPitchIt&& p);

  virtual ~LyPitchIt();

  LyPitchIt& operator=(const LyPitchIt& p);

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

  virtual bool operator==(const LyPitchIt& p) const;

  virtual bool operator!=(const LyPitchIt& p) const;

  virtual bool operator>(const LyPitchIt& p) const;

  virtual bool operator<(const LyPitchIt& p) const;

  virtual bool operator>=(const LyPitchIt& p) const;

  virtual bool operator<=(const LyPitchIt& p) const;

};

} // namespace hautbois
} // namespace core

#endif