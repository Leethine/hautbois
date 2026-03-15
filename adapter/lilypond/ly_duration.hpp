#pragma once

#ifndef LY_DURATION_H
#define LY_DURATION_H

#include "symbol/duration.hpp"

namespace hautbois {
namespace ly {

class LyDuration : public core::Duration {

 public:

  LyDuration(); 

  LyDuration(const int& __num, const int& __denom);

  LyDuration(const int& __value);
 
  LyDuration(const std::string& __value);

  LyDuration(const char * __value);

  LyDuration(const core::Duration& d);
 
  LyDuration(const core::Duration&& d);

  LyDuration(const LyDuration& d);
 
  LyDuration(const LyDuration&& d);
 
  virtual ~LyDuration();

  LyDuration& operator=(const LyDuration& d);

  LyDuration& operator=(const core::Duration& d);

  virtual int getNum() const;

  virtual int getDenom() const;

  virtual std::string toString() const;

  virtual void modify(const char * __context);

  virtual const core::DurationRaw& raw() const;

  virtual core::DurationRaw getRaw() const;

  virtual bool operator<(const LyDuration& d2) const;

  virtual bool operator>(const LyDuration& d2) const;

  virtual bool operator==(const LyDuration& d2) const;

  virtual bool operator==(const core::Duration& d2) const;

  virtual bool operator!=(const LyDuration& d2) const;

  virtual bool operator>=(const LyDuration& d2) const;

  virtual bool operator<=(const LyDuration& d2) const;

  virtual LyDuration operator+(const LyDuration& d2) const;

  virtual LyDuration operator-(const LyDuration& d2) const;

  virtual LyDuration& operator+=(const LyDuration& d2);

  virtual LyDuration& operator*=(const int& __scale);

  virtual LyDuration& operator/=(const int& __scale);

};

} // namespace ly
} // namespace hautbois

#endif