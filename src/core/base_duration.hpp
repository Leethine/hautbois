#pragma once

#ifndef BASE_DURATION_H
#define BASE_DURATION_H

#include "basetypes/base_def_types.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

namespace hautbois {
namespace core {

class BaseDuration {
 private:
  UInt8 _num;
  UInt8 _denom;

 protected:
  virtual void setNum(UInt8 ivNum);
  virtual void setDenom(UInt8 ivDenom);
  virtual void throwInvalidInputException() const;

 public:
  BaseDuration();
  BaseDuration(const UInt8 ivNum, const UInt8 ivDenom);
  BaseDuration(const std::vector<UInt8>& ivDuration);
  BaseDuration(const UInt8 ivValueD, const std::string& ivDotsS);
  BaseDuration(const UInt8 ivValueD);
  
  // Copy constructor
  BaseDuration(const BaseDuration& ivRhD);

  virtual ~BaseDuration();

  inline virtual UInt8 getNum() const {
    return _num;
  }
  inline virtual UInt8 getDenom() const {
    return _denom;
  }
  inline virtual std::string toString() const {
    return std::to_string(_num) + "/" + std::to_string(_denom);
  }
  inline virtual bool operator<(const BaseDuration& ivD2) const {
    return (UInt64) this->getNum() * (UInt64) ivD2.getDenom()
         < (UInt64) ivD2.getNum() * (UInt64) this->getDenom();
  }
  inline virtual bool operator>(const BaseDuration& ivD2) const {
    return (UInt64) this->getNum() * (UInt64) ivD2.getDenom()
         > (UInt64) ivD2.getNum() * (UInt64) this->getDenom();
  }
  inline virtual bool operator==(const BaseDuration& ivD2) const {
    return (UInt64) this->getNum() * (UInt64) ivD2.getDenom()
        == (UInt64) ivD2.getNum() * (UInt64) this->getDenom();
  }
  inline virtual bool operator!=(const BaseDuration& ivD2) const {
    return (UInt64) this->getNum() * (UInt64) ivD2.getDenom()
        != (UInt64) ivD2.getNum() * (UInt64) this->getDenom();
  }
  inline virtual bool operator>=(const BaseDuration& ivD2) const {
    return (*this) > ivD2 || (*this) == ivD2;
  }
  inline virtual bool operator<=(const BaseDuration& ivD2) const {
    return (*this) < ivD2 || (*this) == ivD2;
  }
  inline virtual BaseDuration operator=(const BaseDuration& ivD2) const {
    BaseDuration newDuration(ivD2);
    return newDuration;
  }

  virtual BaseDuration operator+(const BaseDuration& ivD2) const;
  virtual BaseDuration operator-(const BaseDuration& ivD2) const;
  void operator+=(const BaseDuration& ivD2);
};

} // namespace core
} // namespace hautbois

#endif