#pragma once

#ifndef DURATION_HPP
#define DURATION_HPP

#include <string>
#include <cstdint>

namespace hautbois {

class Duration {

private:

  uint32_t _n_value;

  uint32_t _d_value;

  bool _is_dot_notation;

protected:

  virtual void setNum(const uint32_t __val);

  virtual void setDenom(const uint32_t __val);

  virtual void setValue(const uint32_t __val);

  virtual void setDots(const uint32_t __val);

  virtual void setDotNotation();

  virtual void setMeterNotation();

  virtual void plus(const Duration * const __other);

  virtual void minus(const Duration * const __other);

  virtual void divide(const uint32_t __factor);

  virtual void multiply(const uint32_t __factor);

  virtual bool equals(const Duration * const __other) const;

public:

  Duration();

  Duration(const uint32_t __num, const uint32_t __denom);

  Duration(const uint32_t __value, const std::string& __dots); 

  Duration(const uint32_t __value);

  Duration(const std::string& __value);

  Duration(const Duration& __d);

  Duration(const Duration&& __d);

  virtual ~Duration();

  Duration& operator=(Duration&)=delete;

  virtual int getNum() const;

  virtual int getDenom() const;

  virtual int getValue() const;

  virtual std::string getDots() const;

  virtual std::string toString() const;

  virtual bool isMeter() const;

  virtual bool isNoteValue() const;

  virtual bool isValid() const;

};

} // namespace hautbois

#endif