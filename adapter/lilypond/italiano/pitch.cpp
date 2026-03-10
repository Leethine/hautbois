#include "symbol/pitch.hpp"
#include "pitch.hpp"
#include <string>
#include <utility>
#include <map>

namespace hautbois {
namespace ly {

const static std::map<std::string, std::pair<char,char>> NOTENAME_MAP_QUICK {
  {"do", { 'C', 'n' } },
  {"re", { 'D', 'n' } },
  {"mi", { 'E', 'n' } },
  {"fa", { 'F', 'n' } },
  {"sol",{ 'G', 'n' } },
  {"la", { 'A', 'n' } },
  {"si", { 'B', 'n' } },
  {"dod", { 'C', 's' } },
  {"red", { 'D', 's' } },
  {"mid", { 'E', 's' } },
  {"fad", { 'F', 's' } },
  {"sold",{ 'G', 's' } },
  {"lad", { 'A', 's' } },
  {"sid", { 'B', 's' } },
  {"dob", { 'C', 'b' } },
  {"reb", { 'D', 'b' } },
  {"mib", { 'E', 'b' } },
  {"fab", { 'F', 'b' } },
  {"solb",{ 'G', 'b' } },
  {"lab", { 'A', 'b' } },
  {"sib", { 'B', 'b' } },
  {"dodd", { 'C', 'x' } },
  {"redd", { 'D', 'x' } },
  {"midd", { 'E', 'x' } },
  {"fadd", { 'F', 'x' } },
  {"soldd",{ 'G', 'x' } },
  {"ladd", { 'A', 'x' } },
  {"sidd", { 'B', 'x' } },
  {"dobb", { 'C', 'd' } },
  {"rebb", { 'D', 'd' } },
  {"mibb", { 'E', 'd' } },
  {"fabb", { 'F', 'd' } },
  {"solbb",{ 'G', 'd' } },
  {"labb", { 'A', 'd' } },
  {"sibb", { 'B', 'd' } },
  {"r",  { 'R', 'n' } },
  {"s",  { 'S', 'n' } },
  {"R",  { 'R', 'n' } },
  {"S",  { 'S', 'n' } }
};

const static std::map<std::string, char> NOTENAME_MAP {
  {"do", 'C'},
  {"re", 'D'},
  {"mi", 'E'},
  {"fa", 'F'},
  {"sol",'G'},
  {"la", 'A'},
  {"si", 'B'},
  {"r",  'R'},
  {"s",  'S'}
};

const static std::map<char, std::string> NOTENAME_MAP_REV {
  {'C', "do"},
  {'D', "re"},
  {'E', "mi"},
  {'F', "fa"},
  {'G', "sol"},
  {'A', "la"},
  {'B', "si"},
  {'R', "r"},
  {'S', "s"}
};

const static std::map<std::string, char> ACCIDENTAL_MAP {
  {"",   'n'},
  {"d",  's'},
  {"dd", 'x'},
  {"bb", 'd'},
  {"b",  'b'}
};

const static std::map<char, std::string> ACCIDENTAL_MAP_REV {
  {'n', ""},
  {'s', "d"},
  {'x', "dd"},
  {'d', "bb"},
  {'b', "b"}
};

LyPitchIt::LyPitchIt() : core::Pitch() { }

LyPitchIt::LyPitchIt(const std::string& __pitch) : core::Pitch() {
  if (__pitch == "r") {
    _raw.setName('R');
    _raw.setAccidental('n');
    _raw.setOctave(4);
  }
  else if (__pitch == "s") {
    _raw.setName('S');
    _raw.setAccidental('n');
    _raw.setOctave(4);
  }
  else {
    std::string name;
    std::string others;
    if (__pitch.size() >= 3 && __pitch.substr(0,3) == "sol") {
      name = __pitch.substr(0,3);
      others = __pitch.substr(3);
    }
    else if (__pitch.size() >= 2) {
      name = __pitch.substr(0,2);
      others = __pitch.substr(2);
    }
    else {
      throw std::invalid_argument(__pitch);
    }
    // set pitch name
    if (NOTENAME_MAP.find(name) != NOTENAME_MAP.cend()) {
      _raw.setName(NOTENAME_MAP.at(name));
    }
    else {
      throw std::invalid_argument(__pitch);
    }
    // set octave
    int oct = 4;
    while (!others.empty() && 
            (others.back() == ',' || others.back() == '\'')) {
      if (others.back() == ',') {
        oct--;
        others.pop_back();
      }
      else if (others.back() == '\'') {
        oct++;
        others.pop_back();
      }
    }
    _raw.setOctave(oct);
    // set accidental
    if (ACCIDENTAL_MAP.find(others) != ACCIDENTAL_MAP.cend()) {
      _raw.setAccidental(ACCIDENTAL_MAP.at(others));
    }
    else {
      throw std::invalid_argument(__pitch);
    }
  }
}

LyPitchIt::LyPitchIt(const std::string& __name, const int& __octave) {
    // set pitch name
    if (NOTENAME_MAP_QUICK.find(__name) != NOTENAME_MAP_QUICK.cend()) {
      _raw.setName(NOTENAME_MAP_QUICK.at(__name).first);
      _raw.setAccidental(NOTENAME_MAP_QUICK.at(__name).second);
    }
    else {
      throw std::invalid_argument(__name);
    }
    // set octave
    if (__octave >= 0 && __octave < 9) {
      _raw.setOctave(__octave);
    }
    else {
      throw std::invalid_argument(std::to_string(__octave));
    }
}

LyPitchIt::LyPitchIt(const Pitch& p) : Pitch (p) { }

LyPitchIt::LyPitchIt(const Pitch&& p) : Pitch (p) { }

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
    oct_str = std::string(oct - 4, '\'');
  }
  else if (oct < 4) {
    oct_str = std::string(4 - oct, ',');
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

