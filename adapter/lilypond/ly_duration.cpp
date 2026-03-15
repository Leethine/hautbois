#include "ly_duration.hpp"
#include "utility/hbexcept.hpp"
#include <algorithm>
#include <array>
#include <cctype>
#include <cstring>
#include <regex>

namespace hautbois {
namespace ly {

LyDuration::LyDuration() : core::Duration() { }

LyDuration::LyDuration(const int& __num, const int& __denom) :
  core::Duration(__num, __denom) { }

LyDuration::LyDuration(const int& __value) :
  core::Duration(__value) { }

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
    return "INVALID";
  }
}

void LyDuration::modify(const char * __context) {
  if (std::strlen(__context) > 0 && std::strlen(__context) < 10) {
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
  core::Duration d_1 (LyDuration::getNum(), LyDuration::getDenom());
  core::Duration d_2 (d2.getNum(), d2.getDenom());
  return d_1 < d_2;
}

bool LyDuration::operator>(const LyDuration& d2) const {
  core::Duration d_1 (LyDuration::getNum(), LyDuration::getDenom());
  core::Duration d_2 (d2.getNum(), d2.getDenom());
  return d_1 > d_2;
}

bool LyDuration::operator==(const LyDuration& d2) const {
  return LyDuration::getNum() * d2.getDenom() == LyDuration::getDenom() * d2.getNum();
}

bool LyDuration::operator==(const core::Duration& d2) const {
  core::Duration d1 (LyDuration::getNum(), LyDuration::getDenom());
  return d1 == d2;
}

bool LyDuration::operator!=(const LyDuration& d2) const {
  core::Duration d_1 (LyDuration::getNum(), LyDuration::getDenom());
  core::Duration d_2 (d2.getNum(), d2.getDenom());
  return d_1 == d_2;
}

bool LyDuration::operator>=(const LyDuration& d2) const {
  return core::Duration::operator>=(d2);
}

bool LyDuration::operator<=(const LyDuration& d2) const {
  return core::Duration::operator<=(d2);
}

LyDuration LyDuration::operator+(const LyDuration& d2) const {
  core::Duration d_1 (LyDuration::getNum(), LyDuration::getDenom());
  core::Duration d_2 (d2.getNum(), d2.getDenom());
  core::Duration d = d_1 + d_2;
  return LyDuration(d);
}

LyDuration LyDuration::operator-(const LyDuration& d2) const {
  core::Duration d_1 (LyDuration::getNum(), LyDuration::getDenom());
  core::Duration d_2 (d2.getNum(), d2.getDenom());
  core::Duration d = d_1 - d_2;
  return LyDuration(d);
}

LyDuration& LyDuration::operator+=(const LyDuration& d2) {
  core::Duration d_1 (LyDuration::getNum(), LyDuration::getDenom());
  core::Duration d_2 (d2.getNum(), d2.getDenom());
  core::Duration d = d_1 + d_2;
  _raw.setNum(d.getNum());
  _raw.setDenom(d.getDenom());
  return *this;
}

LyDuration& LyDuration::operator*=(const int& __scale) {
  core::Duration d_1 (LyDuration::getNum(), LyDuration::getDenom());
  core::Duration d = d_1 * __scale;
  _raw.setNum(d.getNum());
  _raw.setDenom(d.getDenom());
  return *this;
}

LyDuration& LyDuration::operator/=(const int& __scale) {
  core::Duration d_1 (LyDuration::getNum(), LyDuration::getDenom());
  core::Duration d = d_1 / __scale;
  _raw.setNum(d.getNum());
  _raw.setDenom(d.getDenom());
  return *this;
}

} // namespace core
} // namespace hautbois