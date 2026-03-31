#include "ly_pitch.hpp"
#include "../symbol/pitch.hpp"
#include "../utility/hbexcept.hpp"
#include <string>
#include <cctype>
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

LyPitch::LyPitch() : core::Pitch() { }

LyPitch::LyPitch(const std::string& __pitch) : core::Pitch() {
  bool creation_failed = false;
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
      creation_failed = true;
    }
    // set pitch name
    if (NOTENAME_MAP.find(name) != NOTENAME_MAP.cend()) {
      _raw.setName(NOTENAME_MAP.at(name));
    }
    else {
      creation_failed = true;
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
      creation_failed = true;
    }
    if (creation_failed) {
      HB_THROW_MSG(std::invalid_argument,
                   std::string("Invalid pitch: ") + __pitch);
    }
  }
}

LyPitch::LyPitch(const std::string& __name, const int& __octave) {
  // set pitch name
  if (NOTENAME_MAP_QUICK.find(__name) != NOTENAME_MAP_QUICK.cend()) {
    _raw.setName(NOTENAME_MAP_QUICK.at(__name).first);
    _raw.setAccidental(NOTENAME_MAP_QUICK.at(__name).second);
  }
  else {
    HB_THROW_MSG(std::invalid_argument,
                 std::string("Invalid pitch name: ") + __name);
  }
  // set octave
  if (__octave >= 0 && __octave < 9) {
    _raw.setOctave(__octave);
  }
  else {
    HB_THROW_MSG(std::invalid_argument,
                 std::string("Invalid octave: ") + std::to_string(__octave));
  }
}

LyPitch::LyPitch(const Pitch& p) : Pitch (p) { }

LyPitch::LyPitch(const Pitch&& p) : Pitch (p) { }

LyPitch::LyPitch(const LyPitch& p) : Pitch() {
  _raw.setName(p.raw().getNameRaw());
  _raw.setAccidental(p.raw().getAccidentalRaw());
  _raw.setOctave(p.raw().getOctaveRaw());
}

LyPitch::LyPitch(const LyPitch&& p) : Pitch() {
  _raw.setName(p.raw().getNameRaw());
  _raw.setAccidental(p.raw().getAccidentalRaw());
  _raw.setOctave(p.raw().getOctaveRaw());
}

LyPitch::~LyPitch() {
}

LyPitch& LyPitch::operator=(const LyPitch& p) {
  if (this != &p) {
    _raw.setName(p.raw().getNameRaw());
    _raw.setAccidental(p.raw().getAccidentalRaw());
    _raw.setOctave(p.raw().getOctaveRaw());
  }
  return *this;
}

LyPitch& LyPitch::operator=(const Pitch& p) {
  if (this != &p) {
    _raw.setName(p.raw().getNameRaw());
    _raw.setAccidental(p.raw().getAccidentalRaw());
    _raw.setOctave(p.raw().getOctaveRaw());
  }
  return *this;
}

std::string LyPitch::getName() const {
  std::string name;
  if (NOTENAME_MAP_REV.find(_raw.getNameRaw()) != NOTENAME_MAP_REV.cend()) {
    name = NOTENAME_MAP_REV.at(_raw.getNameRaw());
  }
  return name;
}

std::string LyPitch::getAccidental() const {
  std::string acc;
  if (ACCIDENTAL_MAP_REV.find(_raw.getAccidentalRaw())
      != ACCIDENTAL_MAP_REV.cend()) {
    acc = ACCIDENTAL_MAP_REV.at(_raw.getAccidentalRaw());
  }
  return acc;
}
  
std::string LyPitch::getOctave() const {
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

int LyPitch::getOctaveInt() const {
  return _raw.getOctave();
}

const core::PitchRaw& LyPitch::raw() const {
  return core::Pitch::raw();
}

core::PitchRaw LyPitch::getRaw() const {
  return core::Pitch::getRaw();
}

std::string LyPitch::toString() const {
  return LyPitch::getName() + LyPitch::getAccidental() + LyPitch::getOctave();
}

int LyPitch::toIndex() const {
  return core::Pitch::toIndex();
}

double LyPitch::toFrequency(const std::string& __temperament) const {
  return 0.0; // Not implemented
}

void LyPitch::modify(const char * __context) {
  if (__context == nullptr) {
    return ;
  }
  std::string newpitch (__context);
  int oct = _raw.getOctave();
  std::string name;
  for (char c : newpitch) {
    if (std::isalpha(c)) {
      name.push_back(c);
    }
    else if (c == ',') {
      oct--;
    }
    else if (c == '\'') {
      oct++;
    }
  }
  if (oct > 0 && oct < 9) {
    if (NOTENAME_MAP_QUICK.find(name) != NOTENAME_MAP_QUICK.end()) {
      _raw.setName(NOTENAME_MAP_QUICK.at(name).first);
      _raw.setAccidental(NOTENAME_MAP_QUICK.at(name).second);
      _raw.setOctave(oct);
    }
    else if (name.empty()) {
      _raw.setOctave(oct);
    }
  }
}

bool LyPitch::operator==(const LyPitch& p) const {
  return LyPitch::getName() == p.getName()
    && LyPitch::getOctaveInt() == p.getOctaveInt()
    && LyPitch::getAccidental() == p.getAccidental();
}

bool LyPitch::operator!=(const LyPitch& p) const {
  return LyPitch::getName() != p.getName()
    || LyPitch::getOctaveInt() != p.getOctaveInt()
    || LyPitch::getAccidental() != p.getAccidental();
}

bool LyPitch::operator>(const LyPitch& p) const {
  if (LyPitch::toIndex() > p.toIndex()) {
    return true;
  }
  return false;
}

bool LyPitch::operator<(const LyPitch& p) const {
  return !(*this >= p);
}

bool LyPitch::operator>=(const LyPitch& p) const {
  return (*this > p || *this == p);
}

bool LyPitch::operator<=(const LyPitch& p) const {
  return !(*this > p);
}

} // ly
} // hautbois

