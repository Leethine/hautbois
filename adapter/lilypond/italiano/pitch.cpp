#include "symbol/pitch.hpp"
#include <string>
#include <map>
#include <iostream>

std::map<std::string, char> NOTENAME_MAP {
  {"do", 'C'},
  {"re", 'D'},
  {"mi", 'E'},
  {"fa", 'F'},
  {"sol",'G'},
  {"la", 'A'},
  {"si", 'B'}
};

std::map<char, std::string> NOTENAME_MAP_REV {
  {'C', "do"},
  {'D', "re"},
  {'E', "mi"},
  {'F', "fa"},
  {'G', "sol"},
  {'A', "la"},
  {'B', "si"}
};

using namespace hautbois;
using namespace core;

class LyPitchIt : public Pitch {

 public:

  LyPitchIt() : Pitch('S', 'n', 4) {
  }

  LyPitchIt(const std::string& __token) : LyPitchIt() {
    if (NOTENAME_MAP.find(__token) != NOTENAME_MAP.end()) {
      char name = NOTENAME_MAP[__token];
      _raw.setName(name);
    }
  }

  LyPitchIt(const LyPitchIt& p) : LyPitchIt() {
    _raw.setName(p.getRaw().getName());
    _raw.setAccidental(p.getRaw().getAccidental());
    _raw.setOctave(p.getRaw().getOctave());
  }

  LyPitchIt(const LyPitchIt&& p) : LyPitchIt() {
    _raw.setName(p.getRaw().getName());
    _raw.setAccidental(p.getRaw().getAccidental());
    _raw.setOctave(p.getRaw().getOctave());
  }

  LyPitchIt(const Pitch& p) : LyPitchIt() {
    _raw.setName(p.getRaw().getName());
    _raw.setAccidental(p.getRaw().getAccidental());
    _raw.setOctave(p.getRaw().getOctave());
  }

  LyPitchIt(const Pitch&& p) : LyPitchIt() {
    _raw.setName(p.getRaw().getName());
    _raw.setAccidental(p.getRaw().getAccidental());
    _raw.setOctave(p.getRaw().getOctave());
  }

  virtual ~LyPitchIt() {
    Pitch::~Pitch();
  }

  LyPitchIt& operator=(const LyPitchIt& p) {
    if (this != &p) {
      _raw.setName(p.getName().front());
      _raw.setAccidental(p.getAccidental().front());
      _raw.setOctave(p.getOctaveInt());
  }
    return *this;
  }

  virtual std::string getName() const {
    return Pitch::getName();
  }

  virtual std::string getAccidental() const {
    return Pitch::getAccidental();
  }
  
  virtual std::string getOctave() const {
    return Pitch::getOctave();
  }

  virtual int getOctaveInt() const {
    return Pitch::getOctaveInt();
  }

  virtual const PitchRaw& raw() const {
    return Pitch::raw();
  }
  
  virtual PitchRaw getRaw() const {
    return Pitch::getRaw();
  }

  virtual std::string toString() const {
    return NOTENAME_MAP_REV[raw().getNameRaw()];
  }

  virtual int toIndex() const {
    return 0;
  }

  virtual double toFrequency(const std::string& __temperament) const {
    return 0.0;
  }

  virtual void modify(const char * __context) {}

  virtual bool operator==(const LyPitchIt& p) const {
    return Pitch::operator==(p);
  }

  virtual bool operator!=(const LyPitchIt& p) const {
    return Pitch::operator!=(p);
  }

  virtual bool operator>(const LyPitchIt& p) const {
    return Pitch::operator>(p);
  }

  virtual bool operator<(const LyPitchIt& p) const {
    return Pitch::operator<(p);
  }

  virtual bool operator>=(const LyPitchIt& p) const {
    return Pitch::operator>=(p);
  }

  virtual bool operator<=(const LyPitchIt& p) const {
    return Pitch::operator<=(p);
  }

};


int main() {
  //LyPitchIt ut ("do");
  //Pitch * p = &ut;
  Pitch * p = new LyPitchIt("re");
  Pitch * p2 = new LyPitchIt("mi");

  LyPitchIt * p3 = new LyPitchIt("re");
  LyPitchIt * p4 = new LyPitchIt("mi");
  
  std::cout <<
    dynamic_cast<LyPitchIt *>(p)->LyPitchIt::toString()
  << "\n";

  std::cout <<
    std::to_string(* p3 > * p4)
  << "\n";
  return 0;
}