#include "pitch.hpp"
#include "../utility/hbexcept.hpp"
#include "../hbtype/hbconst.hpp"
#include "../hbtype/hbdefs.hpp"

#include <unordered_map>
#include <stdexcept>
#include <algorithm>

namespace hautbois {

void Pitch::setName(const char __name) {
  const auto& vld = hbconst::VALID_PITCH_NAME;
  if (std::find(vld.cbegin(), vld.cend(), __name) != vld.cend()) {
    _name = __name;
  }
}

void Pitch::setName(const std::string& __name) {
  if (__name.size() == 1) {
    const auto& vld = hbconst::VALID_PITCH_NAME;
    if (std::find(vld.cbegin(), vld.cend(), __name.front()) != vld.cend()) {
      _name = __name.front();
    }
  }
}

void Pitch::setAccidental(const char __acc) {
  const auto& vld = hbconst::VALID_PITCH_ACCIDENTAL;
  if (std::find(vld.cbegin(), vld.cend(), __acc) != vld.cend()) {
    _acc = __acc;
  }
}

void Pitch::setAccidental(const std::string& __acc) {
  if (__acc.size() == 1) {
    const auto& vld = hbconst::VALID_PITCH_NAME;
    if (std::find(vld.cbegin(), vld.cend(), __acc.front()) != vld.cend()) {
      _acc = __acc.front();
    }
  }
}

void Pitch::setOctave(const uint8_t __oct) {
  if (__oct >= INT_OCTAVE_LOWEST && __oct <= INT_OCTAVE_HIGHEST) {
    _oct = __oct;
  }
}

bool Pitch::equals(const Pitch * const __other) const {
  if (_name == __other->getName()       &&
      _acc  == __other->getAccidental() && 
      _oct  == __other->getOctave()) {
    return true;
  }
  return false;
}

bool Pitch::higher_than(const Pitch * const __other) const {
  if (_oct > __other->getOctave()) {
    return true;
  }
  else if (_oct < __other->getOctave()) {
    return false;
  }
  else {
    if (Pitch::toIndex() > __other->toIndex()) {
      return true;
    }
  }
  return false;
}

bool Pitch::lower_than(const Pitch * const __other) const {
  if (__other->getOctave() > _oct) {
    return true;
  }
  else if (__other->getOctave() < _oct) {
    return false;
  }
  else {
    if (Pitch::toIndex() < __other->toIndex()) {
      return true;
    }
  }
  return false;
}

void Pitch::transpose(const int __degree, const std::string& __tonality, const std::string& __mode) {
  // Not supported in base class
}

double Pitch::toFrequency(const uint32_t __base, const int __temperament) const {
  // Not supported in base class
  return .0;
}

Pitch::Pitch() :
  _name (CHAR_PITCHNAME_A), _acc (CHAR_ACCIDENTAL_NATURAL), _oct (INT_OCTAVE_DEFAULT) {
}

Pitch::Pitch(const char __name, const char __acc, const uint8_t __oct) :
  _name (__name), _acc(__acc), _oct(__oct) {
  const auto& vld_name = hbconst::VALID_PITCH_NAME;
  const auto& vld_acc = hbconst::VALID_PITCH_ACCIDENTAL;
  if (std::find(vld_name.cbegin(), vld_name.cend(), __name) == vld_name.cend()) {
    HB_THROW_MSG(std::invalid_argument, "Invalid pitch name: " + std::string(1, __name));
  }
  if (std::find(vld_acc.cbegin(), vld_acc.cend(), __acc) == vld_acc.cend()) {
    HB_THROW_MSG(std::invalid_argument, "Invalid pitch accidental: " + std::string(1, __acc));
  }
  if (__oct > INT_OCTAVE_HIGHEST || __oct < INT_OCTAVE_LOWEST) {
    HB_THROW_MSG(std::invalid_argument, "Invalid pitch octave: " + std::to_string(__oct));
  }
}

Pitch::Pitch(const std::string& __p) {
  _name = CHAR_PITCHNAME_A;
  _acc = CHAR_ACCIDENTAL_NATURAL;
  _oct = INT_OCTAVE_DEFAULT;

  if (__p.size() == 3) {
    _name = __p.at(0);
    _acc = __p.at(1);
    _oct = __p.at(2) - '0';
  }
  else if (__p.size() == 2) {
    _name = __p.at(0);
    _oct = __p.at(1) - '0';
  }
  else if (__p.size() == 1) {
    _name = __p.at(0);
  }
  else {
    HB_THROW_MSG(std::invalid_argument, "Invalid pitch: " + __p);
  }

  const auto& vld_name = hbconst::VALID_PITCH_NAME;
  const auto& vld_acc = hbconst::VALID_PITCH_ACCIDENTAL;
  if (std::find(vld_name.cbegin(), vld_name.cend(), _name) == vld_name.cend()) {
    HB_THROW_MSG(std::invalid_argument, "Invalid pitch: " + __p);
  }
  if (std::find(vld_acc.cbegin(), vld_acc.cend(), _acc) == vld_acc.cend()) {
    HB_THROW_MSG(std::invalid_argument, "Invalid pitch: " + __p);
  }
  if (_oct > INT_OCTAVE_HIGHEST || _oct < INT_OCTAVE_LOWEST) {
    HB_THROW_MSG(std::invalid_argument, "Invalid pitch: " + __p);
  }
}

Pitch::Pitch(const Pitch& __pitch) : Pitch(std::forward<const Pitch&&>(__pitch)) {
}

Pitch::Pitch(const Pitch&& __pitch) :
  Pitch(__pitch.getName(), __pitch.getAccidental(), __pitch.getOctave()) {
}

Pitch::~Pitch() {
}

char Pitch::getName() const {
  return _name;
}

char Pitch::getAccidental() const {
  return _acc;
}
  
int Pitch::getOctave() const {
  return _oct;
}

std::string Pitch::toString() const {
  std::string out;
  out.push_back(_name);
  out.push_back(_acc);
  out.push_back((char)_oct + '0');
  return out;
}

int Pitch::toIndex() const {
  if (_name == CHAR_PITCHNAME_REST || _name == CHAR_PITCHNAME_SILENCE) {
    return 0;
  }
  std::unordered_map<char,int> nameMap {
    {CHAR_PITCHNAME_C, 4}, {CHAR_PITCHNAME_D, 6},
    {CHAR_PITCHNAME_E, 8}, {CHAR_PITCHNAME_F, 9},
    {CHAR_PITCHNAME_G, 11}, {CHAR_PITCHNAME_A, 13},
    {CHAR_PITCHNAME_B, 15}
  };
  std::unordered_map<char,int> accMap {
    {CHAR_ACCIDENTAL_NATURAL, 0}, {CHAR_ACCIDENTAL_SHARP, 1},
    {CHAR_ACCIDENTAL_FLAT, -1}, {CHAR_ACCIDENTAL_DOUBLESHARP, 2},
    {CHAR_ACCIDENTAL_DOUBLEFLAT, -2}
  };
  auto it1 = nameMap.find(_name);
  auto it2 = accMap.find(_acc);
  if (it1 == nameMap.end() || it2 == accMap.end()) {
    return -1;
  }
  int idx = nameMap[_name] + accMap[_acc] + 12 * (_oct - 1);
  return idx;
}

bool Pitch::isValid() const {
  bool isvalid = true;
  const auto& vld_name = hbconst::VALID_PITCH_NAME;
  const auto& vld_acc = hbconst::VALID_PITCH_ACCIDENTAL;
  if (std::find(vld_name.cbegin(), vld_name.cend(), _name) == vld_name.cend()) {
    isvalid = false;
  }
  if (std::find(vld_acc.cbegin(), vld_acc.cend(), _acc) == vld_acc.cend()) {
    isvalid = false;
  }
  if (_oct > INT_OCTAVE_HIGHEST || _oct < INT_OCTAVE_LOWEST) {
    isvalid = false;
  }
  return isvalid;
}

bool Pitch::isRest() const {
  return _name == CHAR_PITCHNAME_REST;
}

bool Pitch::isSilence() const {
  return _name == CHAR_PITCHNAME_SILENCE;
}
  
bool Pitch::isPitch() const {
  return (_name != CHAR_PITCHNAME_REST && _name != CHAR_PITCHNAME_SILENCE);
}

} // namespace hautbois