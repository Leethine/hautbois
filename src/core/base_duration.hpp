#pragma once

#ifndef base_duration_H
#define base_duration_H
#endif

#include "basetypes/base_def_types.hpp"
#include "basetypes/note_enum_types.hpp"
#include <iostream>
#include <numeric>
#include <vector>
#include <exception>
#include <string>
#include <algorithm>

namespace hautbois {
namespace core {

class BaseDuration {
 private:
  UInt8 _num;
  UInt8 _denom;

 protected:
  virtual void setNum(UInt8 ivNum) {
    if (ivNum <= 0) {
      throw InvalidArgumentException("InvalidInputArgs in setNum(): "
                                    + std::to_string(ivNum));
    }
    else {
      _num = ivNum;
    }
  }

  virtual void setDenom(UInt8 ivDenom) {
    if (ivDenom <= 0) {
      throw InvalidArgumentException("InvalidInputArgs in setDenom(): "
                                    + std::to_string(ivDenom));
    }
    else {
      _denom = ivDenom;
    }
  }

  virtual void throwInvalidInputException() const {
    if (_num <= 0 || _denom <= 0) {
      throw InvalidArgumentException("InvalidInputArgs: " + this->toString());
      exit(INVALID_INPUT_ERROR);
    }
  }

 public:
  BaseDuration(): 
    _num { 1 },
    _denom { 1 }
  {}
  
  BaseDuration(const UInt8 ivNum, const UInt8 ivDenom): 
    _num { ivNum },
    _denom { ivDenom }
    {
      if (!(_num > 0 && _denom > 0)) {
        this->throwInvalidInputException();
      }
    }

  BaseDuration(const std::vector<UInt8>& ivDuration): 
    _num { ivDuration.front() },
    _denom { ivDuration.back() }
    {
      if (!(_num > 0 && _denom > 0)) {
        this->throwInvalidInputException();
      }
    }

  BaseDuration(const UInt8 ivValueD, const std::string& ivDotsS) {
    int tvNbrDots = std::count(ivDotsS.begin(), ivDotsS.end(), '.');
    if (tvNbrDots != ivDotsS.length() || ivValueD <= 0) {
      throw InvalidArgumentException("InvalidInputArgs: \nValue: "
                                    + std::to_string(ivValueD)
                                    + " Dots: " + ivDotsS);
      exit(INVALID_INPUT_ERROR);
    }

    if (ivDotsS.empty()) {
      _num = 1;
      _denom = ivValueD;
    }
    else if (tvNbrDots == 1) {
      _num = 3;
      _denom = ivValueD * 2;
    }
    else if (tvNbrDots == 2) {
      _num = 5;
      _denom = ivValueD * 4;
    }
    else {
      throw InvalidArgumentException("InvalidInputArgs: \nValue: "
                                    + std::to_string(ivValueD)
                                    + " Dots: " + ivDotsS
                                    + "\n Too many dots, not supported.");
      exit(INVALID_INPUT_ERROR);
    }
  }

  BaseDuration(const UInt8 ivValueD): 
  _num { 1 },
  _denom { ivValueD }
  {}

  BaseDuration(const BaseDuration& d) { // Copy constructor
    this->_num = d.getNum();
    this->_denom = d.getDenom();
  }

  virtual UInt8 getNum() const {
    return _num;
  }

  virtual UInt8 getDenom() const {
    return _denom;
  }
  
  virtual std::string toString() const {
    return std::to_string(_num) + "/" + std::to_string(_denom);
  }

  friend bool operator<(const BaseDuration& ivD1, const BaseDuration& ivD2) {
    return (UInt64) ivD1.getNum() * (UInt64) ivD2.getDenom()
         < (UInt64) ivD2.getNum() * (UInt64) ivD1.getDenom();
  }

  friend bool operator>(const BaseDuration& ivD1, const BaseDuration& ivD2) {
    return (UInt64) ivD1.getNum() * (UInt64) ivD2.getDenom()
         > (UInt64) ivD2.getNum() * (UInt64) ivD1.getDenom();
  }

  friend bool operator==(const BaseDuration& ivD1, const BaseDuration& ivD2) {
    return (UInt64) ivD1.getNum() * (UInt64) ivD2.getDenom()
        == (UInt64) ivD2.getNum() * (UInt64) ivD1.getDenom();
  }

  friend bool operator!=(const BaseDuration& ivD1, const BaseDuration& ivD2) {
    return (UInt64) ivD1.getNum() * (UInt64) ivD2.getDenom()
        != (UInt64) ivD2.getNum() * (UInt64) ivD1.getDenom();
  }

  friend BaseDuration operator+(const BaseDuration& ivD1, const BaseDuration& ivD2) {
    UInt64 tvNum = (UInt64) ivD1.getNum() * (UInt64) ivD2.getDenom()
                 + (UInt64) ivD2.getNum() * (UInt64) ivD1.getDenom();
    
    UInt64 tvDenom = (UInt64) ivD1.getDenom() * (UInt64) ivD2.getDenom();
    
    UInt64 tvGcd = std::gcd(tvNum, tvDenom);
    return BaseDuration ((UInt8) (tvNum/tvGcd), (UInt8) (tvDenom/tvGcd));
  }

  friend BaseDuration operator-(const BaseDuration& ivD1, const BaseDuration& ivD2) {
    if (ivD1 == ivD2) {
      throw InvalidArgumentException(
          "Operation not supported between equal Durations: "
          + ivD1.toString() + " and " + ivD2.toString());
    }
    else {
      UInt64 tvNum = (UInt64) ivD1.getNum() * (UInt64) ivD2.getDenom() >
                     (UInt64) ivD2.getNum() * (UInt64) ivD1.getDenom() ?
                     (UInt64) ivD1.getNum() * (UInt64) ivD2.getDenom()
                   - (UInt64) ivD2.getNum() * (UInt64) ivD1.getDenom()
                   : (UInt64) ivD2.getNum() * (UInt64) ivD1.getDenom()
                   - (UInt64) ivD1.getNum() * (UInt64) ivD2.getDenom();

      UInt64 tvDenom = (UInt64) ivD1.getDenom() * (UInt64) ivD2.getDenom();
      UInt64 tvGcd = std::gcd(tvNum,tvDenom); 
      tvNum /= tvGcd;
      tvDenom /= tvGcd;

      return BaseDuration {(UInt8) tvNum, (UInt8) tvDenom};
    }
  }

  void operator+=(const BaseDuration& ivD2) {
      UInt64 tvNum = (UInt64) this->_num * (UInt64) ivD2.getDenom()
                    + (UInt64) ivD2.getNum() * (UInt64) this->_denom;
      UInt64 tvDenom = this->_denom * ivD2.getDenom();
      UInt64 tvGcd = std::gcd(tvNum, tvDenom);
      tvNum /= tvGcd;
      tvDenom /= tvGcd;

      this->_num = (UInt8) tvNum;
      this->_denom = (UInt8) tvDenom;
  }
};

} // namespace core
} // namespace hautbois