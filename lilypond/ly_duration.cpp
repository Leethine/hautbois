#include "ly_duration.hpp"
#include "../utility/hbexcept.hpp"
#include "../utility/hbmath.hpp"
#include <cctype>
#include <cstring>
#include <regex>

namespace hautbois {
namespace ly {

LyDuration::LyDuration() : core::Duration() { }

LyDuration::LyDuration(const int& __num, const int& __denom) : 
  core::Duration() {
  _raw.setNum(__num);
  _raw.setDenom(__num);
}

LyDuration::LyDuration(const int& __value) :
  core::Duration(__value) {
}

LyDuration::LyDuration(const std::string& __value) : core::Duration() {
  std::regex pattern ("^(1|2|4|8|16|32|64|128|256)(\\.{0,3})$");
  // Check if input format correct
  if (! std::regex_match(__value, pattern)) {
    HB_THROW_MSG(std::invalid_argument,
      std::string("Invalid input: " + __value));
  }
  std::string digits;
  int count_dots = 0;
  for (const char c : __value) {
    if (std::isdigit(c)) { digits.push_back(c); }
    else if (c == '.')   { count_dots++; }
  }
  int value = std::stoi(digits);
  switch (count_dots) {
    case 0:
      _raw.setNum(1); _raw.setDenom(value);   break;
    case 1:
      _raw.setNum(3); _raw.setDenom(value*2); break;
    case 2:
      _raw.setNum(5); _raw.setDenom(value*4); break;
    case 3:
      _raw.setNum(7); _raw.setDenom(value*8); break;
    default:
      break;
  }
}

LyDuration::LyDuration(const char * __value) :
  LyDuration(std::string(__value)) {
}

LyDuration::LyDuration(const core::Duration& d) :
  Duration(d.getNum(), d.getDenom()) {
}

LyDuration::LyDuration(const core::Duration&& d) :
  Duration(d.getNum(), d.getDenom()) { }

LyDuration::LyDuration(const LyDuration& d) :
  Duration(d.getNum(), d.getDenom()) { }
 
LyDuration::LyDuration(const LyDuration&& d) :
  Duration(d.getNum(), d.getDenom()) { }
 
LyDuration::~LyDuration() {
}

LyDuration& LyDuration::operator=(const LyDuration& d) {
  if (this != &d) {
    _raw.setNum(d.getNum());
    _raw.setDenom(d.getDenom());
  }
  return *this;
}

LyDuration& LyDuration::operator=(const core::Duration& d) {
  if (this != &d) {
    _raw.setNum(d.getNum());
    _raw.setDenom(d.getDenom());
  }
  return *this;
}

int LyDuration::getNum() const {
  return core::Duration::getNum();
}

int LyDuration::getDenom() const {
  return core::Duration::getDenom();
}

std::string LyDuration::toString() const {
  int num = LyDuration::getNum();
  int denom = LyDuration::getDenom();
  if (num == 1) {
    return std::to_string(denom);
  }
  else if (num == 3) {
    return std::to_string(denom / 2) + ".";
  }
  else if (num == 5) {
    return std::to_string(denom / 4) + "..";
  }
  else {
    return std::to_string(num) + "/" + std::to_string(denom);
  }
}

void LyDuration::modify(const char * __context) {
  if (__context && std::strlen(__context) > 0 && std::strlen(__context) < 10) {
    char oper = __context[0];
    std::string digits;
    std::string dots;
    for (int idx=1; idx < std::strlen(__context); idx++) {
      if (std::isdigit(__context[idx])) {
        digits.push_back(__context[idx]);
      }
      else if (__context[idx] == '.') {
        dots.push_back(__context[idx]);
      }
      else if (std::isspace(__context[idx])) {
        // ignore char
      }
      else {
        return ; // invalid char encountered, do nothing
      }
    }
    HB_NESTED_THROW(std::invalid_argument,
      switch (oper) {
        case '+': *this += LyDuration(digits+dots); break;
        case '*': *this *= std::stoi(digits); break;
        case '/': *this /= std::stoi(digits); break;
        default: break;
      }
    )
  }
}

const core::DurationRaw& LyDuration::raw() const {
  return core::Duration::raw();
}

core::DurationRaw LyDuration::getRaw() const {
  return core::Duration::getRaw();
}

bool LyDuration::operator<(const LyDuration& d2) const {
  return _raw.getNum() * d2.getDenom() < d2.getNum() * _raw.getDenom();
}

bool LyDuration::operator>(const LyDuration& d2) const {
  return _raw.getNum() * d2.getDenom() > d2.getNum() * _raw.getDenom();
}

bool LyDuration::operator==(const LyDuration& d2) const {
  return _raw.getNum() * d2.getDenom() == d2.getNum() * _raw.getDenom();
}

bool LyDuration::operator!=(const LyDuration& d2) const {
  return _raw.getNum() * d2.getDenom() != d2.getNum() * _raw.getDenom();
}

bool LyDuration::operator>=(const LyDuration& d2) const {
  return _raw.getNum() * d2.getDenom() >= d2.getNum() * _raw.getDenom();
}

bool LyDuration::operator<=(const LyDuration& d2) const {
  return _raw.getNum() * d2.getDenom() <= d2.getNum() * _raw.getDenom();
}

LyDuration LyDuration::operator+(const LyDuration& d2) const {
  int denom = d2.getDenom() * _raw.getDenom();
  int num = d2.getDenom() * _raw.getNum() + d2.getNum() * _raw.getDenom();
  int gcd = HB_GCD(num, denom);
  return LyDuration (num/gcd, denom/gcd);
}

LyDuration LyDuration::operator-(const LyDuration& d2) const {
  int denom = d2.getDenom() * _raw.getDenom();
  int num = d2.getDenom() * _raw.getNum() - d2.getNum() * _raw.getDenom();
  int gcd = HB_GCD(num, denom);
  if (num == 0) {
    return LyDuration (1, denom/gcd);
  }
  return LyDuration (num/gcd, denom/gcd);
}

core::Duration LyDuration::operator*(const int& __scale) const {
  int denom = _raw.getDenom();
  int num = _raw.getNum() * __scale;
  int gcd = HB_GCD(num, denom);
  return LyDuration (num/gcd, denom/gcd);
}

core::Duration LyDuration::operator/(const int& __scale) const {
  int denom = _raw.getDenom();
  int num = _raw.getNum() / __scale;
  int gcd = HB_GCD(num, denom);
  return LyDuration (num/gcd, denom/gcd);
}

LyDuration& LyDuration::operator+=(const Duration& d2) {
  int denom = d2.getDenom() * _raw.getDenom();
  int num = d2.getDenom() * _raw.getNum() + d2.getNum() * _raw.getDenom();
  int gcd = HB_GCD(num, denom);
  _raw.setNum(num/gcd);
  _raw.setDenom(denom/gcd);
  return *this;
}

LyDuration& LyDuration::operator-=(const Duration& d2) {
  int denom = d2.getDenom() * _raw.getDenom();
  int num = std::abs(d2.getDenom() * _raw.getNum() - d2.getNum() * _raw.getDenom());
  if (num != 0) {
    int gcd = HB_GCD(num, denom);
    _raw.setNum(num/gcd);
    _raw.setDenom(denom/gcd);
  }
  return *this;
}

LyDuration& LyDuration::operator*=(const int& __scale) {
  int denom = _raw.getDenom();
  int num = _raw.getNum() * __scale;
  int gcd = HB_GCD(num, denom);
  _raw.setNum(num/gcd);
  _raw.setDenom(denom/gcd);
  return *this;
}

LyDuration& LyDuration::operator/=(const int& __scale) {
  int denom = _raw.getDenom() * __scale;
  int num = _raw.getNum();
  int gcd = HB_GCD(num, denom);
  _raw.setNum(num/gcd);
  _raw.setDenom(denom/gcd);
  return *this;
}


} // namespace ly
} // namespace hautbois