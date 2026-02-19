#pragma once

#ifndef PITCH_RAW_H
#define PITCH_RAW_H

#include "core_types.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace hautbois {
namespace core {

class PitchRaw final {

 private:

  friend class boost::serialization::access;

  template<class Archive>
  inline void serialize(Archive & ar, const unsigned int version) {
    ar & _name;
    ar & _acc;
    ar & _octave;
  }

  char _name;
 
  char _acc;
 
  UINT8 _octave;

 public:

  template<typename T>
  inline PitchRaw(const char& name, const char& acc, const T& octave) :
    _name { name }, _acc { acc }, _octave { (UINT8) octave } {}

  template<typename T>
  inline PitchRaw(const char&& name, const char&& acc, const T&& octave) :
    _name { name }, _acc { acc }, _octave { (UINT8) octave } {}

  inline PitchRaw() :
    _name { 'C' }, _acc { 'n' }, _octave { (UINT8) 4 } {}
  
  inline PitchRaw(const PitchRaw& p) :
    PitchRaw(p.getNameRaw(), p.getAccidentalRaw(), p.getOctaveRaw()) {}

  inline PitchRaw(const PitchRaw&& p) :
    PitchRaw(p.getNameRaw(), p.getAccidentalRaw(), p.getOctaveRaw()) {}
  
  inline virtual ~PitchRaw() {}

  inline void setName(const char& name) {
    _name = name;
  }

  inline void setName(const char&& name) {
    _name = name;
  }

  inline void setAccidental(const char& acc) {
    _acc = acc;
  }

  inline void setAccidental(const char&& acc) {
    _acc = acc;
  }

  template<typename T>
  inline void setOctave(const T&& octave) {
    _octave = (UINT8) octave;
  }

  template<typename T>
  inline void setOctave(const T& octave) {
    _octave = (UINT8) octave;
  }

  inline char getNameRaw() const {
    return _name;
  }

  inline char getAccidentalRaw() const {
    return _acc;
  }

  inline UINT8 getOctaveRaw() const {
    return _octave;
  }

  inline char getName() const {
    return _name;
  }

  inline char getAccidental() const {
    return _acc;
  }

  inline int getOctave() const {
    return (int) _octave;
  }

  inline PitchRaw operator=(const PitchRaw& r) {
    _name   = r.getNameRaw();
    _acc    = r.getAccidentalRaw();
    _octave = r.getOctaveRaw();
  }

};

} // namespace hautbois
} // namespace core

#endif