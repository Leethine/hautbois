#include "note_chord.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "../utility/hbexcept.hpp"

#include <initializer_list>
#include <cstring>
#include <utility>

namespace hautbois {
namespace core {

void Chord::setNoteType(NoteType __ntype) {
}

void Chord::addPitch(Pitch * __p) {
  if (__p) {
    _pitchList.push_back(__p);
    _tieList.push_back(false);
  }
}

void Chord::setPitch(Pitch * __p, int __pos) {
  if (__pos >= 0 && __pos < _pitchList.size() && __p) {
    delete _pitchList[__pos];
    _pitchList[__pos] = __p;
  }
  else if (_pitchList.empty()) {
    Chord::addPitch(__p);
  }
}

void Chord::addDuration(Duration * __d) {
  if (__d) {
    delete _duration;
    _duration = __d;
  }
}

void Chord::setDuration(Duration * __d, int __pos) {
  Chord::addDuration(__d);
}

void Chord::addProperty(Property * __p) {
  delete _property;
  _property = __p;
}

void Chord::setProperty(Property * __p, int __pos) {
  Chord::addProperty(__p);
}

Pitch * Chord::getPitchMod(int __pos) {
  if (__pos >= 0 && __pos < _pitchList.size()) {
    return _pitchList[__pos];
  }
  return nullptr;
}

Duration * Chord::getDurationMod(int __pos) {
  return _duration;
}

Property * Chord::getPropertyMod(int __pos) {
  return _property;
}

void Chord::clearPitch() {
  for (auto it = _pitchList.begin(); it != _pitchList.end(); it++) {
    delete (*it);
  }
  _pitchList.clear();
  _tieList.clear();
}

void Chord::clearDuration() {
  delete _duration;
  _duration = nullptr;
}

void Chord::clearProperty() {
  delete _property;
  _property = nullptr;
}

void * Chord::verify(const char * __context) const {
  return nullptr;
}

std::string Chord::filterProperty(const std::string& __text) const {
  std::string s (__text);
  return s;
}

Chord::Chord() : Note(NoteType::Chord), 
  _pitchList {}, _duration (nullptr), _property (nullptr), _tieList {} {
}

Chord::Chord(const std::initializer_list<const char *> __pitches) : Chord() {
  for (auto& token : __pitches) {
    Pitch * p = nullptr;
    if (std::strlen(token) > 3 || std::strlen(token) == 0) {
      Chord::clearPitch();
      HB_THROW_MSG(std::invalid_argument,
      std::string ("Invalid token: " + std::string(token)));
    }
    HB_NESTED_THROW_MSG(std::invalid_argument,
      std::string ("Invalid token: " + std::string(token)),
        if (std::strlen(token) == 3) 
          { p = new Pitch(token[0],token[1], token[2] - '0'); }
        else if (std::strlen(token) == 2)
          { p = new Pitch(token[0], token[1] - '0'); }
        else if (std::strlen(token) == 1)
          { p = new Pitch(token[0]); }
    )
    Chord::addPitch(p);
  }
}

Chord::Chord(const std::vector<std::string>& __pitches,
             const int& num, const int& denom) : Chord(__pitches) {
  Duration * d = nullptr;
  HB_NESTED_THROW(std::invalid_argument,
    d = new Duration(num, denom);
  )
  Chord::addDuration(d);
}

Chord::Chord(const std::initializer_list<const char *> __pitches,
             const int& num, const int& denom) : Chord(__pitches) {
  Duration * d = nullptr;
  HB_NESTED_THROW(std::invalid_argument,
    d = new Duration(num, denom);
  )
  Chord::addDuration(d);
}

Chord::Chord(const std::vector<std::string>& __pitches) : Chord() {
  for (auto& token : __pitches) {
    Pitch * p = nullptr;
    if (token.size() > 3 || token.size() == 0) {
      Chord::clearPitch();
      HB_THROW_MSG(std::invalid_argument,
      std::string ("Invalid token: " + std::string(token)));
    }
    HB_NESTED_THROW_MSG(std::invalid_argument,
      std::string ("Invalid token: " + std::string(token)),
        if (token.size() == 3) 
          { p = new Pitch(token[0],token[1], token[2] - '0'); }
        else if (token.size() == 2)
          { p = new Pitch(token[0], token[1] - '0'); }
        else if (token.size() == 1)
          { p = new Pitch(token[0]); }
    )
    Chord::addPitch(p);
  }
}

Chord::Chord(const Chord& __note) : Chord(std::forward<const Chord>(__note)) {
}

Chord::Chord(const Chord&& __note) : Chord() {
  for (int i=0; i < __note.getPitchSize(); i++) {
    if (__note.hasPitch(i)) {
      Pitch * p = new Pitch(* __note.getPitch(i));
      Chord::addPitch(p);
    }
  }
  if (__note.hasDuration()) {
    Duration * d = new Duration(* __note.getDuration());
    Chord::addDuration(d);
  }
  if (__note.hasProperty()) {
    Property * p = new Property(* __note.getProperty());
    Chord::addProperty(p);
  }
  for (int i=0; i < __note.getPitchSize(); i++) {
    if (__note.hasPitch(i)) {
      if (__note.isTied(i)) {
        Chord::setTied(i);
      }
    }
  }
}

Chord::~Chord() {
  Chord::clearDuration();
  Chord::clearProperty();
  Chord::clearPitch();
}

void Chord::updateDuration(const std::string& __context) { }

void Chord::updateDuration(const std::string& __context, size_t __pos) { }

void Chord::updatePitch(const std::string& __context) { }

void Chord::updatePitch(const std::string& __context, size_t __pos) { }

void Chord::updateProperty(const std::string& __context) {
  if (!__context.empty()) {
    Property * p = new Property(__context);
    Chord::setProperty(p,-1);
  }
  else {
    Chord::setProperty(nullptr,-1); // Wipe off
  }
}

void Chord::updateProperty(const std::string& __context, size_t __pos) {
  if (!__context.empty()) {
    Property * p = new Property(__context);
    Chord::setProperty(p,-1);
  }
  else {
    Chord::setProperty(nullptr,-1);
  }
}

void Chord::setTied() {
  if (!_tieList.empty()) {
    _tieList.back() = true;
  }
}

void Chord::setTied(size_t __pos) {
  if (__pos < _tieList.size()) {
    _tieList[__pos] = true;
  }
}

void Chord::setUntied() {
  if (!_tieList.empty()) {
    _tieList.back() = false;
  }
}

void Chord::setUntied(size_t __pos) {
  if (__pos < _tieList.size()) {
    _tieList[__pos] = false;
  }
}

int Chord::getSize() const {
  return Chord::getPitchSize();
}

NoteType Chord::getType() const {
  return Note::getType();
}

char Chord::getTypeChar() const {
  return Note::getTypeChar();
}

std::string Chord::getTypeStr() const {
  return Note::getTypeStr();
}

bool Chord::isType(NoteType __ntype) const {
  return Note::isType(__ntype);
}

bool Chord::isSingle() const {
  return Note::isSingle();
}

bool Chord::isRest() const {
  return Note::isRest();
}

bool Chord::isSilence() const {
  return Note::isSilence();
}

bool Chord::isChord() const {
  return Note::isChord();
}

bool Chord::isTuplet() const {
  return Note::isTuplet();
}

bool Chord::isGrace() const {
  return Note::isGrace();
}

bool Chord::isAppoggiatura() const {
  return Note::isAppoggiatura();
}

bool Chord::isAcciaccatura() const {
  return Note::isAcciaccatura();
}

bool Chord::isValid() const {
  if (_pitchList.empty() || _duration == nullptr || 
      _pitchList.size() != _tieList.size()) {
    return false;
  }
  else {
    for (auto it = _pitchList.cbegin(); it != _pitchList.cend(); it++) {
      if (*it == nullptr) {
        return false;
      }
    }
    return true;
  }
}

bool Chord::isTied() const {
  if (!_tieList.empty() && _tieList.back() == true) {
    return true;
  }
  return false;
}

bool Chord::isTied(size_t __pos) const {
  if (__pos >= _tieList.size()) {
    return false;
  }
  else {
    return _tieList[__pos];
  }
}

bool Chord::hasDuration() const {
  return _duration != nullptr;
}

bool Chord::hasDuration(size_t __pos) const {
  return Chord::hasDuration();
}

bool Chord::hasPitch() const {
  return !_pitchList.empty();
}

bool Chord::hasPitch(size_t __pos) const {
  if (__pos >= _pitchList.size()) {
    return false;
  }
  else {
    return _pitchList[__pos] != nullptr;
  }
}

bool Chord::hasProperty() const {
  return _property != nullptr;
}

bool Chord::hasProperty(size_t __pos) const {
  return Chord::hasProperty();
}

const Duration * Chord::getDuration() const {
  return _duration;
}

const Duration * Chord::getDuration(size_t __pos) const {
  return Chord::getDuration();
}

const Pitch * Chord::getPitch() const {
  if (_pitchList.empty()) {
    return nullptr;
  }
  else {
    return _pitchList[0];
  }
}

const Pitch * Chord::getPitch(size_t __pos) const {
  if (__pos >= _pitchList.size()) {
    return nullptr;
  }
  else {
    return _pitchList[__pos];
  }
}

const Property * Chord::getProperty() const {
  return _property;
}

const Property * Chord::getProperty(size_t __pos) const {
  return Chord::getProperty();
}

std::string Chord::getPropertyStr() const {
  std::string s;
  if (_property != nullptr) {
    s = _property->toString();
  }
  return s;
}

std::string Chord::getPropertyStr(size_t __pos) const {
  return Chord::getPropertyStr();
}

int Chord::getPitchSize() const {
  return _pitchList.size();
}

int Chord::getDurationSize() const {
  if (_duration) {
    return 1;
  }
  return 0;
}

int Chord::getPropertySize() const {
  if (_property) {
    return 1;
  }
  return 0;
}

void Chord::modify(const std::string& __context) { }

std::string Chord::toString() const {
  std::string s;
  for (auto it = _pitchList.begin(); it != _pitchList.end(); it++) {
    if (*it) {
      s += (*it)->toString();
      s.push_back(',');
    }
  }
  if (_duration) {
    s += _duration->toString();
  }
  return s;
}

void * Chord::toStream(const std::string& __context, void * __ostream) const {
  return nullptr;
}

} // namespace core
} // namespace hautbois