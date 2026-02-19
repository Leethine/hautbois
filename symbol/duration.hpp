#pragma once

#ifndef DURATION_H
#define DURATION_H

#include "symbol_raw/duration_raw.hpp"
#include <string>

namespace hautbois {
namespace core {

class Duration {

 protected:

  DurationRaw _raw;

 public:

  Duration(const int& __num, const int& __denom);
 
  Duration(const int& __value, const std::string& __dots);
 
  Duration(const int& __denom);
 
  Duration(const Duration& d);
 
  Duration(const Duration&& d);

  Duration(const DurationRaw& d);
 
  Duration(const DurationRaw&& d);
 
  virtual ~Duration();

  virtual int getNum() const;

  virtual int getDenom() const;

  virtual std::string toString() const;

  virtual void modify(const char * __context);

  virtual const DurationRaw& getRaw() const;

  virtual DurationRaw getRawCopy() const;

  virtual bool operator<(const Duration& d2) const;
 
  virtual bool operator>(const Duration& d2) const;
 
  virtual bool operator==(const Duration& d2) const;
 
  virtual bool operator!=(const Duration& d2) const;
 
  virtual bool operator>=(const Duration& d2) const;
 
  virtual bool operator<=(const Duration& d2) const;
  
  virtual Duration operator+(const Duration& d2) const;
  
  virtual Duration operator-(const Duration& d2) const;
  
  virtual Duration operator*(const int& __scale) const;
  
  virtual Duration operator/(const int& __scale) const;
  
  virtual void operator+=(const Duration& d2);
  
  virtual void operator*=(const int& __scale);
  
  virtual void operator/=(const int& __scale);

};

} // namespace core
} // namespace hautbois

#endif