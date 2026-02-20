#pragma once

#ifndef DURATION_RAW_H
#define DURATION_RAW_H

#include "core_types.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace hautbois {
namespace core {

class DurationRaw final {

 private:

  friend class boost::serialization::access;

  template<class Archive>
  inline void serialize(Archive & ar, const unsigned int version) {
    ar & _num;
    ar & _denom;
  }

  UINT8 _num;

  UINT8 _denom;

 public:

  inline DurationRaw(const DurationRaw& d) :
    DurationRaw(d.getNumRaw(), d.getDenomRaw()) {}

  inline DurationRaw(const DurationRaw&& d) :
    DurationRaw(d.getNumRaw(), d.getDenomRaw()) {}

  inline DurationRaw():
    _num { (UINT8) 1 }, _denom { (UINT8) 1} {}

  inline DurationRaw(UINT8 iNum, UINT8 iDenom):
     _num { iNum }, _denom { iDenom } {}

  template<typename T>
  inline DurationRaw(T&& iNum, T&& iDenom):
     _num { (UINT8) iNum }, _denom { (UINT8) iDenom } {}

  template<typename T>
  inline DurationRaw(T& iNum, T& iDenom):
     _num { (UINT8) iNum }, _denom { (UINT8) iDenom } {}

  inline ~DurationRaw() {}

  template<typename T>
  inline void setNum(T&& iNum) {
    _num = (UINT8) iNum;
  }

  template<typename T>
  inline void setDenom(T&& iDenom) {
    _denom = (UINT8) iDenom;
  }

  inline UINT8 getNumRaw() const {
    return _num;
  }

  inline UINT8 getDenomRaw() const {
    return _denom;
  }

  inline int getNum() const {
    return (int) _num;
  };

  inline int getDenom() const {
    return (int) _denom;
  }

  inline DurationRaw& operator=(const DurationRaw& r) {
    _num = r.getNumRaw();
    _denom = r.getDenomRaw();
    return *this;
  }

};

} // namespace core
} // namespace hautbois

#endif