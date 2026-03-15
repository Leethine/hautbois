#include "pitch.hpp"
#include "utility/hbexcept.hpp"

#include <unordered_map>
#include <stdexcept>
#include <algorithm>
// #include <cctype>
// #include <cmath>

namespace hautbois {
namespace core {

Pitch::Pitch() : _raw (CHAR_PITCHNAME_SILENCE, CHAR_ACCIDENTAL_NATURAL, 4) {}

Pitch::Pitch(const char& __name, const char& __acc, const int& __oct) :
  _raw (__name, __acc, __oct) {
  // Check arguments
  auto it1 = std::find(VALID_PITCH_NAME.begin(),VALID_PITCH_NAME.end(), __name);
  auto it2 = std::find(VALID_PITCH_ACCIDENTAL.begin(),VALID_PITCH_ACCIDENTAL.end(), __acc);

  if (! (it1 != VALID_PITCH_NAME.end() && it2 != VALID_PITCH_ACCIDENTAL.end() && 
         __oct >= 0 && __oct <= 8) ) {
    std::string msg = "Failed to create Pitch with: " + std::string(1,__name)
                    + "," + std::string(1,__acc) + "," + std::to_string(__oct);
    HB_THROW_MSG(std::invalid_argument, msg);
  }
}

Pitch::Pitch(const char& __name, const int& __oct) :
  Pitch(__name, 'n', __oct) {}

Pitch::Pitch(const char& __name) :
  Pitch(__name, 'n', 4) {}

Pitch::Pitch(const Pitch& p) :
  Pitch(p.raw().getName(), p.raw().getAccidental(), p.raw().getOctave()) {
}

Pitch::Pitch(const Pitch&& p) :
  Pitch(p.raw().getName(), p.raw().getAccidental(), p.raw().getOctave()) {
}

Pitch::Pitch(const PitchRaw& p) :
  Pitch(p.getName(), p.getAccidental(), p.getOctave()) {
}

Pitch::Pitch(const PitchRaw&& p) :
  Pitch(p.getName(), p.getAccidental(), p.getOctave()) {
}

Pitch::~Pitch() {
}

Pitch& Pitch::operator=(const Pitch& p) {
  if (this != &p) {
    _raw.setName(p.getName().front());
    _raw.setAccidental(p.getAccidental().front());
    _raw.setOctave(p.getOctaveInt());
  }
  return *this;
}

std::string Pitch::getName() const {
  std::string s(1, _raw.getName());
  return s;
}

std::string Pitch::getAccidental() const {
  std::string s(1, _raw.getAccidental());
  return s;
}

std::string Pitch::getOctave() const {
  return std::to_string(_raw.getOctave());
}

int Pitch::getOctaveInt() const {
  return _raw.getOctave();
}

const PitchRaw& Pitch::raw() const {
  return _raw;
}

PitchRaw Pitch::getRaw() const {
  PitchRaw p (_raw);
  return p;
}

std::string Pitch::toString() const {
  std::string s;
  s.push_back(_raw.getName());
  if (_raw.getName() != 'R' && _raw.getName() != 'S') {
    s.push_back(_raw.getAccidental());
    s.push_back(_raw.getOctave() + '0');
  }
  return s;
}

int Pitch::toIndex() const {
  if (_raw.getName() == 'R' || _raw.getName() == 'S') {
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
  auto it1 = nameMap.find(_raw.getName());
  auto it2 = accMap.find(_raw.getAccidental());
  if (it1 == nameMap.end() || it2 == accMap.end()) {
    return -1;
  }
  int idx = nameMap[_raw.getName()] + accMap[_raw.getAccidental()]
          + 12 * (_raw.getOctave() - 1);
  return idx;
}

double Pitch::toFrequency(const std::string& __temperament) const {
  // not supported
  return 0.0;
}

void Pitch::modify(const char * __context) {
  // not supported
}

bool Pitch::operator==(const Pitch& p) const {
  if (p.getName() == Pitch::getName() &&
      p.getAccidental() == Pitch::getAccidental() &&
      p.getOctaveInt() == Pitch::getOctaveInt()) {
    return true;
  }
  else if (p.getName() == Pitch::getName() && 
           (Pitch::getName() == "R" || Pitch::getName() == "S") ) {
    return true;
  }
  else {
    return false;
  }
}

bool Pitch::operator!=(const Pitch& p) const {
  if (p.getName() == Pitch::getName() && 
      (Pitch::getName() == "R" || Pitch::getName() == "S") ) {
    return false;
  }
  else if (p.getName() != Pitch::getName() ||
           p.getAccidental() != Pitch::getAccidental() ||
           p.getOctaveInt() != Pitch::getOctaveInt()) {
    return true;
  }
  else {
    return false;
  }
}

bool Pitch::operator>(const Pitch& p) const {
  if (Pitch::toIndex() > p.toIndex()) {
    return true;
  }
  else {
    return false;
  }
}

bool Pitch::operator<(const Pitch& p) const {
  if (Pitch::toIndex() < p.toIndex()) {
    return true;
  }
  else {
    return false;
  }
}

bool Pitch::operator<=(const Pitch& p) const {
  if (Pitch::toIndex() < p.toIndex() || (
      p.getName() == Pitch::getName() &&
      p.getAccidental() == Pitch::getAccidental() &&
      p.getOctaveInt() == Pitch::getOctaveInt())) {
    return true;
  }
  else {
    return false;
  }
}

bool Pitch::operator>=(const Pitch& p) const {
  if (Pitch::toIndex() > p.toIndex() || (
      p.getName() == Pitch::getName() &&
      p.getAccidental() == Pitch::getAccidental() &&
      p.getOctaveInt() == Pitch::getOctaveInt())) {
    return true;
  }
  else {
    return false;
  }
}

} // namespace hautbois
} // namespace core
    