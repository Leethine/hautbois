#pragma once

#ifndef BASIC_DURATION_H
#define BASIC_DURATION_H

#include "core_types.hpp"

namespace hautbois {
namespace core {

class BasicDuration {

 private:

  UINT8 _num;

  UINT8 _denom;

 protected:

  template<typename T>
  inline void setNum(T&& iNum) {
    _num = (UINT8) iNum;
  }

  template<typename T>
  inline void setDenom(T&& iDenom) {
    _denom = (UINT8) iDenom;
  }

  inline virtual UINT8 getNumFast() const {
    return _num;
  }

  inline virtual UINT8 getDenomFast() const {
    return _denom;
  }

 public:

  inline BasicDuration(const BasicDuration& d) :
    BasicDuration(d.getNumFast(), d.getDenomFast()) {}

  inline BasicDuration(const BasicDuration&& d) :
    BasicDuration(d.getNumFast(), d.getDenomFast()) {}

  inline BasicDuration():
    _num { (UINT8) 1 }, _denom { (UINT8) 1} {}

  inline BasicDuration(UINT8 iNum, UINT8 iDenom):
     _num { iNum }, _denom { iDenom } {}

  template<typename T>
  inline BasicDuration(T&& iNum, T&& iDenom):
     _num { (UINT8) iNum }, _denom { (UINT8) iDenom } {}

  inline virtual ~BasicDuration() {}

  inline virtual int getNum() const {
    return (int) _num;
  };

  inline virtual int getDenom() const {
    return (int) _denom;
  }

  inline virtual bool isValid() const {
    UINT8 possible_num[3] = { (UINT8) 1, (UINT8) 3, (UINT8) 5 };
    UINT8 possible_denom[10] = { (UINT8) 1, (UINT8) 2, (UINT8) 4,
      (UINT8) 8, (UINT8) 16, (UINT8) 32, (UINT8) 64, (UINT8) 128 };
    bool valid_num = false;
    bool valid_denom = false;
    for (int i=0; i<3; i++) {
      if (_num == possible_num[i]) {
        valid_num = true;
        break;
      }
    }
    for (int i=0; i<10; i++) {
      if (_denom == possible_denom[i]) {
        valid_denom = true;
        break;
      }
    }
    return (valid_num && valid_denom);
  }

};

} // namespace core
} // namespace hautbois

#endif