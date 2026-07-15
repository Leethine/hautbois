#pragma once

#ifndef PITCH_HPP
#define PITCH_HPP

#include <string>
#include <cstdint>
#include "../hbtype/hbdefs.hpp"

namespace hautbois {

class Pitch {

private:

  char _name;

  char _acc;

  uint8_t _oct;

protected:

  virtual void setName(const char __name);

  virtual void setAccidental(const char __acc);

  virtual void setName(const std::string& __name);

  virtual void setAccidental(const std::string& __acc);

  virtual void setOctave(const uint8_t __oct);

  virtual bool equals(const Pitch * const __other) const;

  virtual bool higher_than(const Pitch * const __other) const;

  virtual bool lower_than(const Pitch * const __other) const;

  virtual void transpose(const int __degree, const std::string& __tonality, const std::string& __mode);

  Pitch();

public:

  Pitch(const char __name, const char __acc, const uint8_t __oct);

  Pitch(const std::string& __p);

  Pitch(const Pitch& __pitch);

  Pitch(const Pitch&& __pitch);

  virtual ~Pitch();

  Pitch& operator=(Pitch&)=delete;

  virtual char getName() const;

  virtual char getAccidental() const;
  
  virtual int getOctave() const;

  virtual std::string toString() const;

  virtual int toIndex() const;

  virtual double toFrequency(const uint32_t __base, const int __temperament = TEMPERAMENT_EQUAL) const;

};

} // namespace hautbois

#endif