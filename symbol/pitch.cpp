#include "pitch.hpp"

#include <set>
#include <map>
#include <stdexcept>
#include <cctype>
#include <cmath>

namespace hautbois {
namespace core {

Pitch::Pitch(const char& __name, const char& __acc, const int& __oct) :
  _raw (__name, __acc, __oct) {
  // check note name
  if (__name >= 'A' && __name <= 'G' || __name == 'S' || __name == 'R') {
    _raw.setName(__name);
  }
  else {
    throw std::invalid_argument("Name: '" + std::string(1,__name) + "'");
  }
  // check accidental
  if (__acc == 'b' || __acc == 'd' || __acc == 's' || __acc == 'x' || __acc == 'n') {
    _raw.setAccidental(__acc);
  }
  else {
    throw std::invalid_argument("Accidental: " + std::string(1,__acc));
  }
  // check octave
  if (__oct >= 0 && __oct <= 9) {
    _raw.setOctave(__oct);
  }
  else {
    throw std::invalid_argument("Octave: " + std::to_string(__oct));
  }
}

Pitch::Pitch(const std::string& __name, const std::string& __acc,
             const int& __oct) : Pitch ('C','n',4) {
  // set pitch name
  std::string valid_chars = "ABCDEFGSR";
  if (__name.length() == 1 && valid_chars.find(__name[0]) != std::string::npos) {
    _raw.setName(__name[0]);
  }
  else {
    throw std::invalid_argument("Name: " + __name);
  }
  // set accidental
  valid_chars = "nsdbx";
  if (__acc.empty()) {
    _raw.setAccidental('n');
  }
  else if (__acc.length() == 1 && valid_chars.find(__acc[0]) != std::string::npos) {
    _raw.setAccidental(__acc[0]);
  }
  else if (__acc.length() == 1 && __acc == "#") {
    _raw.setAccidental('s');
  }
  else if (__acc.length() == 2 && __acc == "ss") {
    _raw.setAccidental('x');
  }
  else if (__acc.length() == 2 && __acc == "bb") {
    _raw.setAccidental('d');
  }
  else {
    throw std::invalid_argument("Accidental: " + __acc);
  }
  if (__oct >= 0 && __oct <= 9) {
    _raw.setOctave(__oct);
  }
  else {
    throw std::invalid_argument("Octave: " + std::to_string(__oct));
  }
}

Pitch::Pitch(const std::string& __name, const std::string& __acc,
             const std::string& __oct) : Pitch (__name, __acc, 9) {
  // check and set octave
  std::string valid_chars = "0123456789";
  if (__oct.length() == 1 && valid_chars.find(__oct) != std::string::npos) {
    _raw.setOctave(std::stoi(__oct));
  }
  else {
    throw std::invalid_argument("Octave: " + __oct);
  }
}

Pitch::Pitch(const std::string& __name) : Pitch ('R', 'n', 4) {
  if (__name != "R" && __name != "S") {
    throw std::invalid_argument("Only 'R' or 'S' allowed!");
  }
  _raw.setName(__name[0]);
}

Pitch::Pitch(const Pitch& p) :
  Pitch(p.getName(), p.getAccidental(), p.getOctaveInt()) {
}

Pitch::Pitch(const Pitch&& p) :
  Pitch(p.getName(), p.getAccidental(), p.getOctaveInt()) {
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
  s.append(getName());
  if (getName() != "R" && getName() != "S") {
    s.append(getAccidental());
    s.append(getOctave());
  }
  return s;
}

int Pitch::toIndex() const {
  if (_raw.getName() == 'R' || _raw.getName() == 'S') {
    return 0;
  }
  std::map<char,int> nameMap {
    {'C', 4}, {'D', 6}, {'E', 8}, {'F', 9},
    {'G', 11}, {'A', 13}, {'B', 15}
  };
  std::map<char,int> accMap {
    {'n', 0}, {'s', 1}, {'b', -1}, {'x', 2}, {'d', -2}
  };
  std::map<char,int>::iterator it1 = nameMap.find(_raw.getName());
  std::map<char,int>::iterator it2 = accMap.find(_raw.getAccidental());
  if (it1 == nameMap.end() || it2 == accMap.end()) {
    throw std::runtime_error("Invalid pitch: "
                              + _raw.getName()
                              + _raw.getAccidental());
  }
  int idx = nameMap[_raw.getName()] + accMap[_raw.getAccidental()]
          + 12 * (_raw.getOctave() - 1);
  return idx;
}

double Pitch::toFrequency(const std::string& iTemperament) const {
  // not supported
  return 0.0;
}

void Pitch::modify(const char * __context) {
  // not supported
}

bool Pitch::operator==(const Pitch& p) const {
  if (p.getName() == getName() &&
      p.getAccidental() == getAccidental() &&
      p.getOctaveInt() == getOctaveInt()) {
    return true;
  }
  else {
    return false;
  }
}

bool Pitch::operator!=(const Pitch& p) const {
  if (p.getName() == getName() &&
      p.getAccidental() == getAccidental() &&
      p.getOctaveInt() == getOctaveInt()) {
    return false;
  }
  else {
    return true;
  }
}

bool Pitch::operator>(const Pitch& p) const {
  if (toIndex() > p.toIndex()) {
    return true;
  }
  else {
    return false;
  }
}

bool Pitch::operator<(const Pitch& p) const {
  if (toIndex() < p.toIndex()) {
    return true;
  }
  else {
    return false;
  }
}

bool Pitch::operator<=(const Pitch& p) const {
  if (toIndex() < p.toIndex() || (
      p.getName() == getName() &&
      p.getAccidental() == getAccidental() &&
      p.getOctaveInt() == getOctaveInt())) {
    return true;
  }
  else {
    return false;
  }
}

bool Pitch::operator>=(const Pitch& p) const {
  if (toIndex() > p.toIndex() || (
      p.getName() == getName() &&
      p.getAccidental() == getAccidental() &&
      p.getOctaveInt() == getOctaveInt())) {
    return true;
  }
  else {
    return false;
  }
}

} // namespace hautbois
} // namespace core
    