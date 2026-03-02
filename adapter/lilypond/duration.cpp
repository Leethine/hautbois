#include "duration.hpp"

#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace hautbois {
namespace ly {

LyDuration::LyDuration() : core::Duration() { }

LyDuration::LyDuration(const int& __num, const int& __denom) :
  core::Duration(__num, __denom) { }

LyDuration::LyDuration(const int& __value) :
  core::Duration(__value) { }

LyDuration::LyDuration(const std::string& __value) {
  bool is_valid = std::find_if(__value.cbegin(), __value.cend(),
    [](unsigned char c) {
      return !(std::isdigit(c) || c == '.');
    }) ==  __value.cend();
  if (!is_valid) {
    throw std::invalid_argument(__value);
  }

  std::string digits = __value;
  digits.erase(std::remove_if(digits.begin(), digits.end(),
    [](unsigned char c) {
      return !std::isdigit(c);
    }), digits.end());
  std::string dots = __value;
  dots.erase(std::remove_if(dots.begin(), dots.end(),
    [](unsigned char c) {
      return c != '.';
    }), dots.end());
  
  core::Duration(std::stoi(digits), dots);
}

LyDuration::LyDuration(const core::Duration& d) :
  Duration(d.getNum(), d.getDenom()) { }

LyDuration::LyDuration(const core::Duration&& d) :
  Duration(d.getNum(), d.getDenom()) { }

LyDuration::LyDuration(const LyDuration& d) :
  Duration(d.getNum(), d.getDenom()) { }
 
LyDuration::LyDuration(const LyDuration&& d) :
  Duration(d.getNum(), d.getDenom()) { }
 
LyDuration::~LyDuration() {
  core::Duration::~Duration();
}

LyDuration& LyDuration::operator=(const LyDuration& d) {
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
  if (getNum() == 1) {
    return std::to_string(getDenom());
  }
  else if (getNum() == getDenom()) {
    return "1";
  }
  else if (getNum() == 3) {
    return std::to_string(getDenom()/2) + ".";
  }
  else if (getNum() == 5) {
    return std::to_string(getDenom()/4) + "..";
  }
  else {
    throw std::runtime_error("Cannot convert to string from " +
                              core::Duration::toString());
    return "";
  }
}

void LyDuration::modify(const char * __context) {
  // not supported
}

const core::DurationRaw& LyDuration::raw() const {
  return core::Duration::raw();
}

core::DurationRaw LyDuration::getRaw() const {
  return core::Duration::getRaw();
}

bool LyDuration::operator<(const LyDuration& d2) const {
  return core::Duration::operator<(d2);
}

bool LyDuration::operator>(const LyDuration& d2) const {
  return core::Duration::operator>(d2);
}

bool LyDuration::operator==(const LyDuration& d2) const {
  return core::Duration::operator==(d2);
}

bool LyDuration::operator!=(const LyDuration& d2) const {
  return core::Duration::operator!=(d2);
}

bool LyDuration::operator>=(const LyDuration& d2) const {
  return core::Duration::operator>=(d2);
}

bool LyDuration::operator<=(const LyDuration& d2) const {
  return core::Duration::operator<=(d2);
}

LyDuration LyDuration::operator+(const LyDuration& d2) const {
  core::Duration d1 (getNum(), getDenom());
  core::Duration d = d1 + d2;
  return LyDuration(d);
}

LyDuration LyDuration::operator-(const LyDuration& d2) const {
  core::Duration d1 (getNum(), getDenom());
  core::Duration d = d1 - d2;
  return LyDuration(d);
}

core::Duration LyDuration::operator*(const int& __scale) const {
  core::Duration d (getNum(), getDenom());
  return Duration(d * __scale);
}

core::Duration LyDuration::operator/(const int& __scale) const {
  core::Duration d (getNum(), getDenom());
  return Duration(d / __scale);
}

void LyDuration::operator+=(const LyDuration& d2) {
  core::Duration::operator+=(d2);
}

void LyDuration::operator*=(const int& __scale) {
  core::Duration::operator*=(__scale);
}

void LyDuration::operator/=(const int& __scale) {
  core::Duration::operator/=(__scale);
}

} // namespace core
} // namespace hautbois