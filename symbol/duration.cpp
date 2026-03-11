#include "duration.hpp"
#include "utility/hbexcept.hpp"

#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <array>

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
namespace core {

Duration::Duration() : _raw (1, 1) { }

Duration::Duration(const int& __num, const int& __denom) : _raw (__num, __denom) {
  std::array<int,8> valid_denom {1,2,4,8,16,32,64,128};
  if ( __num < 1 || __num > 128 || 
      std::find(valid_denom.begin(),valid_denom.end(), __denom) == valid_denom.end()) {
    std::string msg = "Failed to create Duration with: " +
                      std::to_string(__num) + "," + std::to_string(__denom);
    HB_THROW_MSG(std::invalid_argument, msg);
  }
}

Duration::Duration(const int& __value, const std::string& __dots) : _raw (1, 1) {
  size_t n_dots = std::count(__dots.begin(), __dots.end(), '.');
  std::array<int,8> valid_denom {1,2,4,8,16,32,64,128};
  if (n_dots != __dots.length() || n_dots > 2 ||
      std::find(valid_denom.begin(), valid_denom.end(), __value) == valid_denom.end()) {
    std::string msg = "Failed to create Duration with "
                    + std::to_string(__value) + " " + __dots;
    HB_THROW_MSG(std::invalid_argument, msg);
  }
  if (n_dots == 1) {
    _raw.setNum(3);
    _raw.setDenom(__value * 2);
  }
  else if (n_dots == 2) {
    _raw.setNum(7);
    _raw.setDenom(__value * 4);
  }
  else {
    _raw.setNum(1);
    _raw.setDenom(__value);
  }
}

Duration::Duration(const int& __denom) : Duration(1, __denom) { }

Duration::Duration(const Duration& d) :
  Duration(d.getNum(), d.getDenom()) {}

Duration::Duration(const Duration&& d) :
  Duration(d.getNum(), d.getDenom()) {}

Duration::Duration(const DurationRaw& d) :
  Duration(d.getNum(), d.getDenom()) {}

Duration::Duration(const DurationRaw&& d) :
  Duration(d.getNum(), d.getDenom()) {}

Duration::~Duration() {}

Duration& Duration::operator=(const Duration& d) {
  if (this != &d) {
    _raw.setNum(d.getNum());
    _raw.setDenom(d.getDenom());
  }
  return *this;
}

int Duration::getNum() const {
  return _raw.getNum();
}

int Duration::getDenom() const {
  return _raw.getDenom();
}

std::string Duration::toString() const {
  return std::to_string(getNum()) + "/" + std::to_string(getDenom());
}

void Duration::modify(const char * __context) {
  // Not supported in base class
}

const DurationRaw& Duration::raw() const {
  return _raw;
}

DurationRaw Duration::getRaw() const {
  DurationRaw r (_raw);
  return r;
}

bool Duration::operator<(const Duration& d2) const {
  return Duration::getNum() * d2.getDenom() <
         d2.getNum() * Duration::getDenom();
}

bool Duration::operator>(const Duration& d2) const {
  return Duration::getNum() * d2.getDenom() >
         d2.getNum() * Duration::getDenom();
}

bool Duration::operator==(const Duration& d2) const {
  return Duration::getNum() * d2.getDenom() ==
         d2.getNum() * Duration::getDenom();
}

bool Duration::operator!=(const Duration& d2) const {
  return Duration::getNum() * d2.getDenom() != 
         d2.getNum() * Duration::getDenom();
}

bool Duration::operator>=(const Duration& d2) const {
  return (*this) > d2 || (*this) == d2;
}

bool Duration::operator<=(const Duration& d2) const {
  return (*this) < d2 || (*this) == d2;
}

Duration Duration::operator+ (const Duration& d2) const {
  int tNum = Duration::getNum() * d2.getDenom()
           + d2.getNum() * Duration::getDenom();
  int tDenom = Duration::getDenom() * d2.getDenom();
  int tGcd   = HB_GCD(tNum, tDenom);
  return Duration((tNum / tGcd), (tDenom / tGcd));
}

Duration Duration::operator- (const Duration& d2) const {
  if ((*this) == d2) {
    std::string msg ("Cannot apply operator-() if d1 == d2");
    HB_THROW_MSG(std::logic_error, msg);
  }
  else {
    int tNum = Duration::getNum() * d2.getDenom() >
               d2.getNum() * Duration::getDenom() ?
               Duration::getNum() * d2.getDenom()
             - d2.getNum() * Duration::getDenom()
             : d2.getNum() * Duration::getDenom()
             - Duration::getNum() * d2.getDenom();

    int tDenom = Duration::getDenom() * d2.getDenom();
    int tGcd   = HB_GCD(tNum,tDenom); 
    return Duration((tNum/tGcd), (tDenom/tGcd));
  }
}

Duration Duration::operator* (const int& __scale) const {
  if (__scale <= 0) {
    std::string msg ("Cannot apply operator* if scale <= 0");
    HB_THROW_MSG(std::logic_error, msg);
  }
  else {
    int tNum   = Duration::getNum() * __scale;
    int tDenom = Duration::getDenom();
    int tGcd   = HB_GCD(tNum,tDenom);
    return Duration((tNum / tGcd), (tDenom / tGcd));
  }
}

Duration Duration::operator/ (const int& __scale) const {
  if (__scale <= 0) {
    std::string msg ("Cannot apply operator/ if scale <= 0");
    HB_THROW_MSG(std::logic_error, msg);
  }
  else {
    int tNum   = Duration::getNum();
    int tDenom = Duration::getDenom() * __scale;
    int tGcd   = HB_GCD(tNum,tDenom);
    return Duration((tNum / tGcd), (tDenom / tGcd));
  }
}

void Duration::operator+= (const Duration& d2) {
  int tNum = Duration::getNum() * d2.getDenom()
            + d2.getNum() * Duration::getDenom();
  int tDenom = Duration::getDenom() * d2.getDenom();
  int tGcd = HB_GCD(tNum, tDenom);
  _raw.setNum(tNum/tGcd);
  _raw.setDenom(tDenom/tGcd);
}

void Duration::operator*= (const int& __scale) {
  if (__scale <= 0) {
    std::string msg ("Cannot apply operator*= if scale <= 0");
    HB_THROW_MSG(std::logic_error, msg);
  }
  int tNum = getNum() * __scale;
  int tGcd = HB_GCD(tNum, getDenom());
  _raw.setNum(tNum/tGcd);
  _raw.setDenom(getDenom()/tGcd);
}

void Duration::operator/= (const int& __scale) {
  if (__scale <= 0) {
    std::string msg ("Cannot apply operator/= if scale <= 0");
    HB_THROW_MSG(std::logic_error, msg);
  }
  int tDenom = getDenom() * __scale;
  int tGcd = HB_GCD(getNum(), tDenom);
  _raw.setNum(getNum()/tGcd);
  _raw.setDenom(tDenom/tGcd);
}

} // namespace hautbois
} //namespace core
