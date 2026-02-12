#pragma once

#ifndef BASIC_PITCH_H
#define BASIC_PITCH_H

#include "core_types.hpp"

namespace hautbois {
namespace core {

class BasicPitch {

 private:

  char _name;
 
  char _acc;
 
  UINT8 _octave;

 protected:
 
  inline void setName(const char& name) {
    _name = name;
  }

  inline void setAccidential(const char& acc) {
    _acc = acc;
  }

  template<typename T>
  inline void setOctave(const T&& octave) {
    _octave = (UINT8) octave;
  }

  inline virtual char getNameFast() const {
    return _name;
  }

  inline virtual char getAccidentialFast() const {
    return _acc;
  }

  inline virtual UINT8 getOctaveFast() const {
    return _octave;
  }

 public:

  template<typename T>
  inline BasicPitch(const char& name, const char& acc, const T&& octave) :
    _name { name }, _acc { acc }, _octave { (UINT8) octave } {}

  inline BasicPitch() :
    _name { 'C' }, _acc { 'n' }, _octave { (UINT8) 4 } {}
  
  inline BasicPitch(const BasicPitch& p) :
    BasicPitch(p.getNameFast(), p.getAccidentialFast(), p.getOctaveFast()) {}

  inline BasicPitch(const BasicPitch&& p) :
    BasicPitch(p.getNameFast(), p.getAccidentialFast(), p.getOctaveFast()) {}
  
  inline virtual ~BasicPitch() {}

  inline virtual bool isValid() const {
    if ((_name == 'S' || _name == 'R' || _name >= 'A' && _name <= 'G') &&
        _octave >= (UINT8) 0 && _octave < (UINT8) 9 &&
        (_acc == 'n' || _acc == 's' || _acc == 'x' ||
         _acc == 'b' || _acc == 'd') ) {
      return true;
    }
    else {
      return false;
    }
  }

};

} // namespace hautbois
} // namespace core

#endif