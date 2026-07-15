#include "duration.hpp"
#include "../utility/hbexcept.hpp"

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <array>
#include <stdexcept>
#include <string>
#include <utility>

#if __cplusplus >= 201703L
#define HB_GCD(X, Y) std::gcd((X),(Y))
#else
#define HB_GCD(X, Y)    \
[&](int x_, int y_) {   \
  int a = std::abs(x_); \
  int b = std::abs(y_); \
  int remainder;        \
  while (b != 0) {      \
    remainder = a % b;  \
    a = b;              \
    b = remainder;      \
  }                     \
  return a;             \
}((X),(Y))
#endif

namespace hautbois {

void Duration::setNum(const uint32_t __val) {
  if (!_is_dot_notation) {
    _n_value = __val;
  }
}

void Duration::setDenom(const uint32_t __val) {
  if (!_is_dot_notation) {
    _d_value = __val;
  }
}
void Duration::setValue(const uint32_t __val) {
  if (_is_dot_notation) {
    _d_value = __val;
  }
}

void Duration::setDots(const uint32_t __val) {
  if (_is_dot_notation) {
    _n_value = __val;
  }
}

void Duration::setDotNotation() {
  _is_dot_notation = true;
}

void Duration::setMeterNotation() {
  _is_dot_notation = false;
}

void Duration::plus(const Duration * const __other) {
  if (__other) {
    int newNum = __other->getNum() * Duration::getDenom() + __other->getDenom() * Duration::getNum();
    int newDenom = __other->getDenom() * Duration::getDenom();
    _is_dot_notation = false;
    int ngcd = std::gcd(newNum, newDenom);
    _n_value = (uint32_t) (newNum / ngcd);
    _d_value = (uint32_t) (newDenom / ngcd);
  }
}

void Duration::minus(const Duration * const __other) {
  if (__other) {
    int newNum = __other->getNum() * Duration::getDenom() - __other->getDenom() * Duration::getNum();
    int newDenom = __other->getDenom() * Duration::getDenom();
    _is_dot_notation = false;
    int ngcd = std::gcd(newNum, newDenom);
    _n_value = (uint32_t) std::abs(newNum / ngcd);
    _d_value = (uint32_t) std::abs(newDenom / ngcd);
  }
}

void Duration::divide(const uint32_t __factor) {
  int newNum = Duration::getNum();
  int newDenom = Duration::getDenom() * (int) __factor;
  _is_dot_notation = false;
  int ngcd = std::gcd(newNum, newDenom);
  _n_value = (uint32_t) (newNum / ngcd);
  _d_value = (uint32_t) (newDenom / ngcd);
}

void Duration::multiply(const uint32_t __factor) {
  int newNum = Duration::getNum() * (int) __factor;
  int newDenom = Duration::getDenom();
  _is_dot_notation = false;
  int ngcd = std::gcd(newNum, newDenom);
  _n_value = (uint32_t) (newNum / ngcd);
  _d_value = (uint32_t) (newDenom / ngcd);
}

bool Duration::equals(const Duration * const __other) const {
  if (__other) {
    if (__other->getNum() * Duration::getDenom() == __other->getDenom() * Duration::getNum()) {
      return true;
    }
  }
  return false;
}

Duration::Duration() : _n_value(1), _d_value(1), _is_dot_notation(false) {}

Duration::Duration(const uint32_t __num, const uint32_t __denom) : 
  _n_value(__num), _d_value(__denom), _is_dot_notation(false) {}

Duration::Duration(const uint32_t __value, const std::string& __dots) :
  _n_value(__dots.size()), _d_value(__value), _is_dot_notation(true) {
  if (_n_value > 3) {
    HB_THROW_MSG(std::invalid_argument, "Too many dots: " + std::to_string(_n_value));
  }
  std::array<uint32_t, 8> validValue {1,2,4,8,16,32,64,128};
  if (std::find(validValue.begin(), validValue.end(), __value) == validValue.end()) {
    HB_THROW_MSG(std::invalid_argument, "Invalid note value: " + std::to_string(__value));
  }
}

Duration::Duration(const uint32_t __value) : Duration(__value, "") {
}

Duration::Duration(const Duration& d) : Duration(std::forward<const Duration&&>(d)) { 
}

Duration::Duration(const Duration&& d) : Duration() {
  if (d.isMeter()) {
    _n_value = (uint32_t) d.getNum();
    _d_value = (uint32_t) d.getDenom();
    _is_dot_notation = false;
  }
  else {
    _n_value = (uint32_t) d.getValue();
    _d_value = (uint32_t) d.getDots().size();
    _is_dot_notation = true;
  }
}

Duration::~Duration() {}

int Duration::getNum() const {
  if (_is_dot_notation) {
    if (_n_value == 0) {
      return 1;
    }
    else if (_n_value == 1) {
      return 3;
    }
    else if (_n_value == 2) {
      return 5;
    }
    else if (_n_value == 3) {
      return 7;
    }
    else {
      return 99991;
    }
  }
  else {
    return _n_value;
  }
}

int Duration::getDenom() const {
  if (_is_dot_notation) {
    if (_n_value == 0) {
      return _d_value;
    }
    else if (_n_value == 1) {
      return _d_value * 2;
    }
    else if (_n_value == 2) {
      return _d_value * 4;
    }
    else if (_n_value == 3) {
      return _d_value * 8;
    }
    else {
      return 99901;
    }
  }
  else {
    return _d_value;
  }
}

int Duration::getValue() const {
  if (_is_dot_notation) {
    return _d_value;
  }
  else {
    return 0;
  }
}

std::string Duration::getDots() const {
  if (_is_dot_notation && _n_value > 0) {
    return std::string(_n_value, '.');
  }
  else {
    return "";
  }
}

std::string Duration::toString() const {
  std::string out;
  if (_is_dot_notation) {
    out = std::to_string(_d_value);
    if (_n_value > 0) {
      out.append(std::string(_n_value, '.'));
    }
  }
  else {
    out = std::to_string(_n_value) + "/" + std::to_string(_d_value);
  }
  return out;
}

bool Duration::isMeter() const {
  return ! _is_dot_notation;
}

bool Duration::isNoteValue() const {
  return _is_dot_notation;
}

bool Duration::isValid() const {
  if (_is_dot_notation) {
    if (_n_value > 3) {
      return false;
    }
    std::array<uint32_t, 8> validValue {1,2,4,8,16,32,64,128};
    if (std::find(validValue.begin(), validValue.end(), _d_value) == validValue.end()) {
      return false;
    }
  }
  else {
    if (_d_value == 0) {
      return false;
    }
  }
  return true;
}

} // namespace hautbois