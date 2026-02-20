#include "duration.hpp"
#include "symbol_raw/core_types.hpp"

#include <algorithm>
#include <stdexcept>
#include <numeric>

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

Duration::Duration(const int& __num, const int& __denom) :
  _raw (__num, __denom) {
  std::vector<int> valid_num {1,3,5,2,4,6};
  std::vector<int> valid_denom {1,2,4,8,16,32,64,128};
  if (std::find(valid_num.begin(), valid_num.end(), __num) == valid_num.end() ||
    std::find(valid_denom.begin(), valid_denom.end(), __denom) == valid_denom.end()
  ) {
    throw std::invalid_argument(std::to_string(__num) + "," + std::to_string(__denom));
  }
}

Duration::Duration(const int& __value, const std::string& __dots) :
  _raw (1, 1) {
  size_t n_dots = std::count(__dots.begin(), __dots.end(), '.');
  if (n_dots != __dots.length()) {
    throw std::invalid_argument(std::to_string(__value) + __dots);
  }
  std::vector<int> valid_denom {1,2,4,8,16,32,64,128};
  if (std::find(valid_denom.begin(), valid_denom.end(), __value) == valid_denom.end()) {
    throw std::invalid_argument(std::to_string(__value) + __dots);
  }

  if (__dots.empty()) {
    _raw.setNum(1);
    _raw.setDenom(__value);
  }
  else if (n_dots == 1) {
    _raw.setNum(3);
    _raw.setDenom(__value * 2);
  }
  else if (n_dots == 2) {
    _raw.setNum(7);
    _raw.setDenom(__value * 4);
  }
  else {
    throw std::invalid_argument(std::to_string(__value) + __dots);
  }
}

Duration::Duration(const int& __denom) :
  _raw (1, __denom) {}

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
  return this->getNum() * d2.getDenom()
        < d2.getNum() * this->getDenom();
}

bool Duration::operator>(const Duration& d2) const {
  return this->getNum() * d2.getDenom()
        > d2.getNum() * this->getDenom();
}

bool Duration::operator==(const Duration& d2) const {
  return this->getNum() * d2.getDenom()
        == d2.getNum() * this->getDenom();
}

bool Duration::operator!=(const Duration& d2) const {
  return this->getNum() * d2.getDenom()
        != d2.getNum() * this->getDenom();
}

bool Duration::operator>=(const Duration& d2) const {
  return (*this) > d2 || (*this) == d2;
}

bool Duration::operator<=(const Duration& d2) const {
  return (*this) < d2 || (*this) == d2;
}

Duration Duration::operator+ (const Duration& d2) const {
  int tNum = this->getNum() * d2.getDenom()
           + d2.getNum() * this->getDenom();
  int tDenom = this->getDenom() * d2.getDenom();
  int tGcd   = HB_GCD(tNum, tDenom);
  return Duration((tNum / tGcd), (tDenom / tGcd));
}

Duration Duration::operator- (const Duration& d2) const {
  if ((*this) == d2) {
    throw std::logic_error("d1 == d2");
  }
  else {
    int tNum = this->getNum() * d2.getDenom() >
               d2.getNum() * this->getDenom() ?
               this->getNum() * d2.getDenom()
             - d2.getNum() * this->getDenom()
             : d2.getNum() * this->getDenom()
             - this->getNum() * d2.getDenom();

    int tDenom = this->getDenom() * d2.getDenom();
    int tGcd   = HB_GCD(tNum,tDenom); 
    return Duration((tNum/tGcd), (tDenom/tGcd));
  }
}

Duration Duration::operator* (const int& __scale) const {
  if (__scale <= 0) {
    throw std::invalid_argument(__scale + " < 0");
  }
  else {
    int tNum   = this->getNum() * __scale;
    int tDenom = this->getDenom();
    int tGcd   = HB_GCD(tNum,tDenom);
    return Duration((tNum / tGcd), (tDenom / tGcd));
  }
}

Duration Duration::operator/ (const int& __scale) const {
  if (__scale <= 0) {
    throw std::invalid_argument(__scale + " <= 0");
  }
  else {
    int tNum   = this->getNum();
    int tDenom = this->getDenom() * __scale;
    int tGcd   = HB_GCD(tNum,tDenom);
    return Duration((tNum / tGcd), (tDenom / tGcd));
  }
}

void Duration::operator+= (const Duration& d2) {
  int tNum = this->getNum() * d2.getDenom()
            + d2.getNum() * this->getDenom();
  int tDenom = this->getDenom() * d2.getDenom();
  int tGcd = HB_GCD(tNum, tDenom);
  _raw.setNum(tNum/tGcd);
  _raw.setDenom(tDenom/tGcd);
}

void Duration::operator*= (const int& __scale) {
  if (__scale <= 0) {
    throw std::invalid_argument(__scale + " <= 0");
  }
  int tNum = getNum() * __scale;
  int tGcd = HB_GCD(tNum, getDenom());
  _raw.setNum(tNum/tGcd);
  _raw.setDenom(getDenom()/tGcd);
}

void Duration::operator/= (const int& __scale) {
  if (__scale <= 0) {
    throw std::invalid_argument(__scale + " <= 0");
  }
  int tDenom = getDenom() * __scale;
  int tGcd = HB_GCD(getNum(), tDenom);
  _raw.setNum(getNum()/tGcd);
  _raw.setDenom(tDenom/tGcd);
}

} // namespace hautbois
} //namespace core
