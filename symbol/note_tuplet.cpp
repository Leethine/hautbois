#include "note_tuplet.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "../utility/hbexcept.hpp"

#include <utility>

namespace hautbois {
namespace core {

void Tuplet::setNoteType(NoteType __ntype) {
}

void Tuplet::addPitch(Pitch * __p) {
  if (__p) {
    _pitchList.push_back(__p);
    _tieList.push_back(false);
  }
}

void Tuplet::setPitch(Pitch * __p, int __pos) {
  if (__pos >= 0 && __pos < _pitchList.size() && __p) {
    delete _pitchList[__pos];
    _pitchList[__pos] = __p;
  }
  else if (_pitchList.empty() && __p) {
    _pitchList.push_back(__p);
  }
}

void Tuplet::addDuration(Duration * __d) {
  if (__d) {
    _durationList.push_back(__d);
  }
}

void Tuplet::setDuration(Duration * __d, int __pos) {
  if (__d) {
    if (__pos < 0) {
      delete _duration;
      _duration = __d;
    }
    else {
      if (__pos >= 0 && __pos < _durationList.size()) {
        delete _durationList[__pos];
        _durationList[__pos] = __d;
      }
      else if (_durationList.empty()) {
        _durationList.push_back(__d);
      }
    }
  }
}

void Tuplet::addProperty(Property * __p) {
  _propertyList.push_back(__p);
}

void Tuplet::setProperty(Property * __p, int __pos) {
  if (__pos < 0) {
    delete _property;
    _property = __p;
  }
  else {
    if (__pos >= 0 && __pos < _propertyList.size()) {
      delete _propertyList[__pos];
      _propertyList[__pos] = __p;
    }
    else if (_propertyList.empty()) {
      _propertyList.push_back(__p);
    }
  }
}

Pitch * Tuplet::getPitchMod(int __pos) {
  if (__pos >= 0 && __pos < _pitchList.size()) {
    return _pitchList[__pos];
  }
  return nullptr;
}

Duration * Tuplet::getDurationMod(int __pos) {
  if (__pos < 0) {
    return _duration;
  }
  else if (__pos < _durationList.size()) {
    return _durationList[__pos];
  }
  else {
    return nullptr;
  }
}

Property * Tuplet::getPropertyMod(int __pos) {
  if (__pos < 0) {
    return _property;
  }
  else if (__pos < _propertyList.size()) {
    return _propertyList[__pos];
  }
  else {
    return nullptr;
  }
}

void Tuplet::clearPitch() {
  for (auto it = _pitchList.begin(); it != _pitchList.end(); it++) {
    delete (*it);
  }
  _pitchList.clear();
  _tieList.clear();
}

void Tuplet::clearDuration() {
  delete _duration;
  _duration = nullptr;
  for (auto it = _durationList.begin(); it != _durationList.end(); it++) {
    delete (*it);
  }
  _durationList.clear();
}

void Tuplet::clearProperty() {
  delete _property;
  _property = nullptr;
  for (auto it = _propertyList.begin(); it != _propertyList.end(); it++) {
    delete (*it);
  }
  _propertyList.clear();
}

void * Tuplet::verify(const char * __context) const {
  return nullptr;
}

std::string Tuplet::Tuplet::filterProperty(const std::string& __text) const {
  std::string s (__text);
  return s;
}

Tuplet::Tuplet(const unsigned int __count) : 
  Note(NoteType::Tuplet),
  _duration (nullptr), _property (nullptr), _noteCount (__count),
  _pitchList {}, _tieList {}, _durationList {}, _propertyList {} {
}

Tuplet::Tuplet(const unsigned int __count, int __num, int __denom) : Tuplet(__count) {
  Duration * d = nullptr;
  HB_NESTED_THROW_MSG(std::invalid_argument,
    std::string("Failed to read duration: " + 
                 std::to_string(__num) + "/" + std::to_string(__denom)),
    d = new Duration(__num, __denom);
  )
  Tuplet::setDuration(d, -1);
}

Tuplet::Tuplet(int __num, int __denom,
               const std::initializer_list<const char *> __args,
               const unsigned int __count) : Tuplet(__count, __num, __denom) {
  int count = 0;
  for (auto token : __args) {
    Pitch    * p = nullptr;
    Duration * d = nullptr;
    if (++count % 2 == 1) {
      char name    = CHAR_PITCHNAME_SILENCE;
      char acc     = CHAR_ACCIDENTAL_NATURAL;
      char oct     = CHAR_OCTAVE_DEFAULT;
      if (std::strlen(token) == 3) { name = token[0]; acc = token[1]; oct = token[2]; }
      else if (std::strlen(token) == 2) { name = token[0]; oct = token[1]; }
      else if (std::strlen(token) == 1) { name = token[0]; }      
      else { // check pitch, must be 1 to 3 length
        HB_THROW_MSG(std::invalid_argument,
                     std::string("Invalid pitch token at pos 1: ") + std::string(token));
      }
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string("Failed to read token pos 1: " + std::string(token)),
        p = new Pitch(name, acc, oct - '0');
      )
      Tuplet::addPitch(p);
      Tuplet::addProperty(nullptr);
    }
    else {
      for (int i=0; i<std::strlen(token); i++) { // check duration must be digits
        if (!std::isdigit(token[i])) {
          HB_THROW_MSG(std::invalid_argument,
            std::string("Duration token must be digits at pos 2: " + std::string(token))
          );
        }
      }
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string("Failed to read token pos 2: " + std::string(token)),
        d = new Duration(std::atoi(token));
      )
      Tuplet::addDuration(d);
    }
  }
  if (count % 2 != 0) {
    HB_THROW_MSG(std::invalid_argument,
                 std::string("Arg list must be: <pitch1,value1>, <pitch2,value2>, ..."));
  }
}

Tuplet::Tuplet(int __num, int __denom,
               const std::vector<std::string>& __args,
               const unsigned int __count) : Tuplet(__count, __num, __denom) {
  int count = 0;
  for (auto token : __args) {
    Pitch    * p = nullptr;
    Duration * d = nullptr;
    if (++count % 2 == 1) {
      char name    = CHAR_PITCHNAME_SILENCE;
      char acc     = CHAR_ACCIDENTAL_NATURAL;
      char oct     = CHAR_OCTAVE_DEFAULT;
      if (token.size() == 3) { name = token[0]; acc = token[1]; oct = token[2]; }
      else if (token.size() == 2) { name = token[0]; oct = token[1]; }
      else if (token.size() == 1) { name = token[0]; }      
      else { // check pitch, must be 1 to 3 length
        HB_THROW_MSG(std::invalid_argument,
                     std::string("Invalid pitch token at pos 1: ") + token);
      }
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string("Failed to read token pos 1: " + token),
        p = new Pitch(name, acc, oct - '0');
      )
      Tuplet::addPitch(p);
      Tuplet::addProperty(nullptr);
    }
    else {
      int denom = 1;
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string("Duration token must be digits at pos 2: " + token),
        denom = std::stoi(token);
      )
      catch(const std::out_of_range&) {
        HB_THROW_MSG(std::invalid_argument,
          std::string("Duration token too big at pos 2: " + token));
      }
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string("Failed to read token pos 2: " + token),
        d = new Duration(denom);
      )
      Tuplet::addDuration(d);
    }
  }
  if (count % 2 != 0) {
    HB_THROW_MSG(std::invalid_argument,
                 std::string("Arg list must be: <pitch1,value1>, <pitch2,value2>, ..."));
  }
}

Tuplet::~Tuplet() {
  Tuplet::clearDuration();
  Tuplet::clearPitch();
  Tuplet::clearProperty();
}

Tuplet::Tuplet(const Tuplet& __other) : Tuplet(std::forward<const Tuplet>(__other)) {
}

Tuplet::Tuplet(const Tuplet&& __other) : Tuplet(__other.getSize()) {
  if (__other.hasDuration()) {
    Duration * d = new Duration(* __other.getDuration());
    Tuplet::setDuration(d, -1);
  }
  if (__other.hasProperty()) {
    Property * p = new Property(* __other.getProperty());
    Tuplet::setProperty(p, -1);
  }
  for (int i=0; i<__other.getPitchSize(); i++) {
    if (__other.getPitch(i)) {
      Pitch * p = new Pitch(* __other.getPitch(i));
      Tuplet::addPitch(p);
    }
  }
  for (int i=0; i<__other.getDurationSize(); i++) {
    if (__other.getDuration(i)) {
      Duration * d = new Duration(* __other.getDuration(i));
      Tuplet::addDuration(d);
    }
  }
  for (int i=0; i<__other.getPropertySize(); i++) {
    if (__other.getProperty(i)) {
      Property * p = new Property(* __other.getProperty(i));
      Tuplet::addProperty(p);
    }
    else { // fill empty property (nullptr)
      Tuplet::addProperty(nullptr);
    }
  }
  // set Ties
  for (int i=0; i < __other.getPitchSize(); i++) {
    if (__other.hasPitch(i) && __other.isTied(i)) {
      Tuplet::setTied(i);
    }
  }
}

Tuplet& Tuplet::operator=(const Tuplet& __other) {
  if (this != &__other) {
    if (Tuplet::getSize() == __other.getSize()) {
      if (__other.hasDuration()) {
        Duration * d = new Duration(* __other.getDuration());
        Tuplet::setDuration(d, -1);
      }
      if (__other.hasProperty()) {
        Property * p = new Property(* __other.getProperty());
        Tuplet::setProperty(p, -1);
      }
      for (int i=0; i<__other.getPitchSize(); i++) {
        if (__other.getPitch(i)) {
          Pitch * p = new Pitch(* __other.getPitch(i));
          Tuplet::addPitch(p);
          Tuplet::setTied(i);
        }
      }
      for (int i=0; i<__other.getDurationSize(); i++) {
        if (__other.getDuration(i)) {
          Duration * d = new Duration(* __other.getDuration(i));
          Tuplet::addDuration(d);
        }
      }
      for (int i=0; i<__other.getPropertySize(); i++) {
        if (__other.getProperty(i)) {
          Property * p = new Property(* __other.getProperty(i));
          Tuplet::addProperty(p);
        }
      }
    }
  }
  return *this;
}

void Tuplet::updateDuration(const std::string& __context) { }

void Tuplet::updateDuration(const std::string& __context, size_t __pos) { }

void Tuplet::updatePitch(const std::string& __context) { }

void Tuplet::updatePitch(const std::string& __context, size_t __pos) { }

void Tuplet::updateProperty(const std::string& __context) {
  if (!__context.empty()) {
    Property * p = new Property(__context);
    Tuplet::setProperty(p, -1);
  }
  else {
    Tuplet::setProperty(nullptr, -1);
  }
}

void Tuplet::updateProperty(const std::string& __context, size_t __pos) {
  if (__pos < Tuplet::getPropertySize()) {
    if (!__context.empty()) {
      Property * p = new Property(__context);
      Tuplet::setProperty(p, __pos);
    }
    else {
      Tuplet::setProperty(nullptr, __pos);
    }
  }
}

void Tuplet::setTied() {
  if (_tieList.empty()) {
    _tieList.push_back(true);
  }
  else {
    _tieList.back() = true;
  }
}

void Tuplet::setTied(size_t __pos) {
  if (__pos < _tieList.size()) {
    _tieList[__pos] = true;
  }
}

void Tuplet::setUntied() {
  if (_tieList.empty()) {
    _tieList.push_back(false);
  }
}

void Tuplet::setUntied(size_t __pos) {
  if (__pos < _tieList.size()) {
    _tieList[__pos] = false;
  }
}

int Tuplet::getSize() const {
  return _noteCount;
}

NoteType Tuplet::getType() const {
  return Note::getType();
}

char Tuplet::getTypeChar() const {
  return Note::getTypeChar();
}

std::string Tuplet::getTypeStr() const {
  return Note::getTypeStr();
}

bool Tuplet::isType(NoteType __ntype) const {
  return Note::isType(__ntype);
}

bool Tuplet::isSingle() const {
  return Note::isSingle();
}

bool Tuplet::isRest() const {
  return Note::isRest();
}

bool Tuplet::isSilence() const {
  return Note::isSilence();
}

bool Tuplet::isChord() const {
  return Note::isChord();
}

bool Tuplet::isTuplet() const {
  return Note::isTuplet();
}

bool Tuplet::isGrace() const {
  return Note::isGrace();
}

bool Tuplet::isAppoggiatura() const {
  return Note::isAppoggiatura();
}

bool Tuplet::isAcciaccatura() const {
  return Note::isAcciaccatura();
}

bool Tuplet::isValid() const {
  if (_durationList.empty() || _pitchList.empty() || _tieList.empty() || 
      _duration == nullptr || _pitchList.size() != _tieList.size() ||
      _durationList.size() != _propertyList.size() ||
      _durationList.size() != _pitchList.size()) {
    return false;
  }
  for (auto it = _durationList.cbegin(); it != _durationList.cend(); it++) {
    if ((*it) == nullptr) {
      return false;
    }
  }
  for (auto it = _pitchList.cbegin(); it != _pitchList.cend(); it++) {
    if ((*it) == nullptr) {
      return false;
    }
  }
  return true;
}

bool Tuplet::isTied() const {
  if (_tieList.empty()) {
    return false;
  }
  else {
    return _tieList.back();
  }
}

bool Tuplet::isTied(size_t __pos) const {
  if (__pos >= _tieList.size()) {
    return false;
  }
  else {
    return _tieList[__pos];
  }
}

bool Tuplet::hasDuration() const {
  return _duration != nullptr;
}

bool Tuplet::hasDuration(size_t __pos) const {
  if (__pos >= _durationList.size()) {
    return false;
  }
  else {
    return _durationList[__pos] != nullptr;
  }
}

bool Tuplet::hasPitch() const {
  if (!_pitchList.empty()) {
    for (auto it = _pitchList.begin(); it != _pitchList.end(); it++) {
      if ((*it) == nullptr) {
        return false;
      }
      return true;
    }
  }
  return false;
}

bool Tuplet::hasPitch(size_t __pos) const {
  if (__pos >= _pitchList.size()) {
    return false;
  }
  else {
    return _pitchList[__pos] != nullptr;
  }
}

bool Tuplet::hasProperty() const {
  return _property != nullptr;
}

bool Tuplet::hasProperty(size_t __pos) const {
  if (__pos >= _propertyList.size()) {
    return false;
  }
  else {
    return _propertyList[__pos] != nullptr;
  }
}

const Duration * Tuplet::getDuration() const {
  return _duration;
}

const Duration * Tuplet::getDuration(size_t __pos) const {
  if (__pos >= _durationList.size()) {
    return nullptr;
  }
  else {
    return _durationList[__pos];
  }
}

const Pitch * Tuplet::getPitch() const {
  if (_pitchList.empty()) {
    return nullptr;
  }
  else {
    return _pitchList.back();
  }
}

const Pitch * Tuplet::getPitch(size_t __pos) const {
  if (__pos >= _pitchList.size()) {
    return nullptr;
  }
  else {
    return _pitchList[__pos];
  }
}

const Property * Tuplet::getProperty() const {
  return _property;
}

const Property * Tuplet::getProperty(size_t __pos) const {
  if (__pos >= _propertyList.size()) {
    return nullptr;
  }
  else {
    return _propertyList[__pos];
  }
}

std::string Tuplet::getPropertyStr() const {
  std::string s;
  if (_property) {
    s = _property->toString();
  }
  return s;
}

std::string Tuplet::getPropertyStr(size_t __pos) const {
  std::string s;
  if (Tuplet::hasProperty(__pos)) {
    s = Tuplet::getProperty(__pos)->toString();
  }
  return s;
}

int Tuplet::getPitchSize() const {
  return _pitchList.size();
}

int Tuplet::getDurationSize() const {
  return _durationList.size();
}

int Tuplet::getPropertySize() const {
  return _propertyList.size();
}

void Tuplet::modify(const std::string& __context) {
}

std::string Tuplet::toString() const {
  std::string s = "N/A";
  if (Tuplet::isValid()) {
    s = "";
    for (int i=0; i<Tuplet::getPitchSize(); i++) {
      if (Tuplet::hasPitch(i)) {
        s += Tuplet::getPitch(i)->toString() + ",1/";
      }
      if (Tuplet::hasDuration(i)) {
        s += std::to_string(Tuplet::getDuration(i)->getDenom());
      }
      s += ",";
    }
    s += " [";
    if (Tuplet::hasDuration()) {
      s += std::to_string(Tuplet::getDuration()->getNum());
      s += "/";
      s += std::to_string(Tuplet::getDuration()->getDenom());
      s += "] [" + std::to_string(Tuplet::getSize()) + "]";
    }
    else {
      s += "?/?]";
    }
  }
  return s;
}

void * Tuplet::toStream(const std::string& __context, void * __ostream) const {
  return nullptr;
}


} // namespace core
} // namespace hautbois