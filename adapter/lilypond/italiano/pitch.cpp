#include "symbol/pitch.hpp"
#include "pitch.hpp"
#include <string>
#include <map>
#include <iostream>

namespace hautbois {
namespace ly {

const static std::map<std::string, char> NOTENAME_MAP {
  {"do", 'C'},
  {"re", 'D'},
  {"mi", 'E'},
  {"fa", 'F'},
  {"sol",'G'},
  {"la", 'A'},
  {"si", 'B'}
};

const static std::map<char, std::string> NOTENAME_MAP_REV {
  {'C', "do"},
  {'D', "re"},
  {'E', "mi"},
  {'F', "fa"},
  {'G', "sol"},
  {'A', "la"},
  {'B', "si"}
};

const static std::map<std::string, char> ACCIDENTAL_MAP {
  {"",   'n'},
  {"ss", 'x'},
  {"x",  'x'},
  {"bb", 'd'},
  {"b",  'b'}
};

const static std::map<char, std::string> ACCIDENTAL_MAP_REV {
  {'n', ""},
  {'x', "ss"},
  {'x', "x"},
  {'d', "bb"},
  {'b', "b"}
};


LyPitchIt::LyPitchIt() : core::Pitch() { }

LyPitchIt::LyPitchIt(const std::string& __pitch) : 
  core::Pitch() {
}

LyPitchIt::LyPitchIt(const Pitch& p) : Pitch (p) {
}

LyPitchIt::LyPitchIt(const Pitch&& p) : Pitch (p) {
}

LyPitchIt::LyPitchIt(const LyPitchIt& p) : Pitch() {
  _raw.setName(p.raw().getNameRaw());
  _raw.setAccidental(p.raw().getAccidentalRaw());
  _raw.setOctave(p.raw().getOctaveRaw());
}

LyPitchIt::LyPitchIt(const LyPitchIt&& p) : Pitch() {
  _raw.setName(p.raw().getNameRaw());
  _raw.setAccidental(p.raw().getAccidentalRaw());
  _raw.setOctave(p.raw().getOctaveRaw());
}

LyPitchIt::~LyPitchIt() {
  core::Pitch::~Pitch();
}

LyPitchIt& LyPitchIt::operator=(const LyPitchIt& p) {
  if (this != &p) {
    _raw.setName(p.raw().getNameRaw());
    _raw.setAccidental(p.raw().getAccidentalRaw());
    _raw.setOctave(p.raw().getOctaveRaw());
  }
  return *this;
}

std::string LyPitchIt::getName() const {
  std::string name;
  if (NOTENAME_MAP_REV.find(_raw.getNameRaw()) != NOTENAME_MAP_REV.cend()) {
    name = NOTENAME_MAP_REV.at(_raw.getNameRaw());
  }
  else {
    throw std::runtime_error("'" + std::string(_raw.getNameRaw(), 1) + "'" +
                             "not in the map index");
  }
  return name;
}

std::string LyPitchIt::getAccidental() const {
  std::string acc;
  if (ACCIDENTAL_MAP_REV.find(_raw.getAccidentalRaw())
      != ACCIDENTAL_MAP_REV.cend()) {
    acc = ACCIDENTAL_MAP_REV.at(_raw.getAccidentalRaw());
  }
  else {
    throw std::runtime_error(
      "'" + std::string(_raw.getAccidentalRaw(), 1) + "'" +
      "not in the map index");
  }
  return acc;
}
  
std::string LyPitchIt::getOctave() const {
  int oct = getOctaveInt();
  std::string oct_str;
  if (oct > 4) {
    oct_str = std::string('\'', oct - 4);
  }
  else if (oct < 4) {
    oct_str = std::string('\'', 4 - oct);
  }
  else {
    oct_str = "";
  }
  return oct_str;
}

int LyPitchIt::getOctaveInt() const {
  return _raw.getOctave();
}

const core::PitchRaw& LyPitchIt::raw() const {
  return core::Pitch::raw();
}

core::PitchRaw LyPitchIt::getRaw() const {
  return core::Pitch::getRaw();
}

std::string LyPitchIt::toString() const {
  return getName() + getAccidental() + getOctave();
}

int LyPitchIt::toIndex() const {
  return core::Pitch::toIndex();
}

double LyPitchIt::toFrequency(const std::string& __temperament) const {
  return core::Pitch::toFrequency(__temperament);
}

void LyPitchIt::modify(const char * __context) {
  //TODO
}

bool LyPitchIt::operator==(const LyPitchIt& p) const {
  if (getName() == p.getName() && 
      getAccidental() == p.getAccidental() &&
      getOctaveInt() == p.getOctaveInt()) {
    return true;
  }
  else {
    return false;
  }
}

bool LyPitchIt::operator!=(const LyPitchIt& p) const {
  return !(*this == p);
}

bool LyPitchIt::operator>(const LyPitchIt& p) const {
  if (toIndex() > p.toIndex()) {
    return true;
  }
  return false;
}

bool LyPitchIt::operator<(const LyPitchIt& p) const {
  return !(*this >= p);
}

bool LyPitchIt::operator>=(const LyPitchIt& p) const {
  return (*this > p || *this == p);
}

bool LyPitchIt::operator<=(const LyPitchIt& p) const {
  return !(*this > p);
}

} // ly
} // hautbois

