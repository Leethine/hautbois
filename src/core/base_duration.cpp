#include "base_duration.hpp"

#include <exception>
#include <numeric>
#include <algorithm>

void hautbois::core::BaseDuration::setNum(UInt8 ivNum) {
  if (ivNum <= 0) {
    throw InvalidArgumentException("InvalidInputArgs in setNum(): " + std::to_string(ivNum));
  }
  else {
    _num = ivNum;
  }
}

void hautbois::core::BaseDuration::setDenom(UInt8 ivDenom) {
  if (ivDenom <= 0) {
    throw InvalidArgumentException("InvalidInputArgs in setDenom(): " + std::to_string(ivDenom));
  }
  else {
    _denom = ivDenom;
  }
}

void hautbois::core::BaseDuration::throwInvalidInputException() const {
  if (_num <= 0 || _denom <= 0) {
    throw InvalidArgumentException("InvalidInputArgs: " + this->toString());
    exit(INVALID_INPUT_ERROR);
  }
}

hautbois::core::BaseDuration::BaseDuration():
  _num{1},
  _denom{1} {
}

hautbois::core::BaseDuration::BaseDuration(const UInt8 ivNum,
                                           const UInt8 ivDenom):
  _num{ivNum},
  _denom{ivDenom} {
  if (!(_num > 0 && _denom > 0)) {
    this->throwInvalidInputException();
  }
}

hautbois::core::BaseDuration::BaseDuration(const std::vector<UInt8> &ivDuration) : _num{ivDuration.front()},
                                                                                   _denom{ivDuration.back()} {
  if (!(_num > 0 && _denom > 0))
  {
    this->throwInvalidInputException();
  }
}

hautbois::core::BaseDuration::BaseDuration(const UInt8 ivValueD,
                                           const std::string &ivDotsS) {
  size_t tvNbrDots = std::count(ivDotsS.begin(), ivDotsS.end(), '.');
  if (tvNbrDots != ivDotsS.length() || ivValueD <= 0) {
    throw InvalidArgumentException("InvalidInputArgs: \nValue: " + std::to_string(ivValueD) + " Dots: " + ivDotsS);
    exit(INVALID_INPUT_ERROR);
  }

  if (ivDotsS.empty()) {
    _num = 1;
    _denom = ivValueD;
  }
  else if (tvNbrDots == 1) {
    _num = 3;
    _denom = ivValueD * 2;
  }
  else if (tvNbrDots == 2) {
    _num = 5;
    _denom = ivValueD * 4;
  }
  else {
    throw InvalidArgumentException("InvalidInputArgs: \nValue: " + std::to_string(ivValueD) + " Dots: " + ivDotsS + "\n Too many dots, not supported.");
    exit(INVALID_INPUT_ERROR);
  }
}

hautbois::core::BaseDuration::BaseDuration(const UInt8 ivValueD):
  _num{1},
  _denom{ivValueD} {
}

hautbois::core::BaseDuration::BaseDuration(const BaseDuration &d) {
  this->_num = d.getNum();
  this->_denom = d.getDenom();
}

hautbois::core::BaseDuration::~BaseDuration() {
}

hautbois::core::BaseDuration hautbois::core::BaseDuration::operator+
  (const BaseDuration& ivD2) const {
  
  UInt64 tvNum = (UInt64)this->getNum() * (UInt64)ivD2.getDenom()
                 + (UInt64)ivD2.getNum() * (UInt64)this->getDenom();
  UInt64 tvDenom = (UInt64)this->getDenom() * (UInt64)ivD2.getDenom();
  UInt64 tvGcd = std::gcd(tvNum, tvDenom);
  return BaseDuration((UInt8)(tvNum / tvGcd), (UInt8)(tvDenom / tvGcd));
}

hautbois::core::BaseDuration hautbois::core::BaseDuration::operator-
  (const BaseDuration& ivD2) const {
    if ((*this) == ivD2) {
      throw InvalidArgumentException(
          "Operation not supported between equal Durations: "
          + this->toString() + " and " + ivD2.toString());
    }
    else {
      UInt64 tvNum = (UInt64) this->getNum() * (UInt64) ivD2.getDenom() >
                     (UInt64) ivD2.getNum() * (UInt64) this->getDenom() ?
                     (UInt64) this->getNum() * (UInt64) ivD2.getDenom()
                   - (UInt64) ivD2.getNum() * (UInt64) this->getDenom()
                   : (UInt64) ivD2.getNum() * (UInt64) this->getDenom()
                   - (UInt64) this->getNum() * (UInt64) ivD2.getDenom();

      UInt64 tvDenom = (UInt64) this->getDenom() * (UInt64) ivD2.getDenom();
      UInt64 tvGcd = std::gcd(tvNum,tvDenom); 
      tvNum /= tvGcd;
      tvDenom /= tvGcd;

      return BaseDuration {(UInt8) tvNum, (UInt8) tvDenom};
    }
  }

void hautbois::core::BaseDuration::operator+=
  (const hautbois::core::BaseDuration& ivD2) {
  UInt64 tvNum = (UInt64) this->_num * (UInt64) ivD2.getDenom()
               + (UInt64) ivD2.getNum() * (UInt64) this->_denom;
  UInt64 tvDenom = this->_denom * ivD2.getDenom();
  Int64 tvGcd = std::gcd(tvNum, tvDenom);
  tvNum /= tvGcd;
  tvDenom /= tvGcd;

  this->_num = (UInt8) tvNum;
  this->_denom = (UInt8) tvDenom;
}
