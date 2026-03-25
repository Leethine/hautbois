#include "note_group.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "../utility/hbexcept.hpp"

#include <cstring>

namespace hautbois {
namespace core {

void NoteGroup::addPitch(Pitch *__p) {
  if (__p) {
    _pitchList.push_back(__p);
    _tieList.push_back(false);
  }
}

void NoteGroup::setPitch(Pitch * __p, int pos) {
  if (pos >= 0 && pos < _pitchList.size() && __p) {
    delete _pitchList[pos];
    _pitchList[pos] = __p;
  }
  else if (_pitchList.empty() && __p) {
    _pitchList.push_back(__p);
  }
}

void NoteGroup::setDuration(Duration *__d, int pos) {
  if (__d) {
    NoteGroup::clearDuration();
    _duration = __d;
  }
}

void NoteGroup::setProperty(Property *__p, int pos) {
  NoteGroup::clearProperty();
  _property = __p;
}

Pitch * NoteGroup::getPitchyMod(int pos) {
  if (pos >= 0 && pos < _pitchList.size()) {
    return _pitchList[pos];
  }
  return nullptr;
}

Duration * NoteGroup::getDurationMod(int pos) {
  return _duration;
}

Property * NoteGroup::getPropertyMod(int pos) {
  return _property;
}

void NoteGroup::clearPitch() {
  for (auto it = _pitchList.begin(); it != _pitchList.end(); it++) {
    delete (*it);
  }
  _pitchList.clear();
  _tieList.clear();
}

void NoteGroup::clearDuration() {
  delete _duration;
  _duration = nullptr;
}

void NoteGroup::clearProperty() {
  delete _property;
  _property = nullptr;
}

NoteGroup::NoteGroup(NoteType __type) : Note(__type),
  _pitchList {}, _duration(nullptr), _property(nullptr), _tieList {} {
}

NoteGroup::NoteGroup(const std::initializer_list<const char *> __pitches,
                     NoteType __type) : NoteGroup(__type) {
  for (auto& token : __pitches) {
    Pitch * p = nullptr;
    if (std::strlen(token) > 3 || std::strlen(token) == 0) {
      NoteGroup::clearPitch();
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
    NoteGroup::addPitch(p);
  }
}

NoteGroup::NoteGroup(const std::vector<std::string>& __pitches,
                     NoteType __type) : NoteGroup(__type) {
  for (auto& token : __pitches) {
    Pitch * p = nullptr;
    if (token.size() > 3 || token.size() == 0) {
      NoteGroup::clearPitch();
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
    NoteGroup::addPitch(p);
  }
}

NoteGroup::~NoteGroup() {
  NoteGroup::clearDuration();
  NoteGroup::clearProperty();
  NoteGroup::clearPitch();
}

void NoteGroup::setTied(size_t __pos) {
  if (__pos < _tieList.size()) {
    _tieList[__pos] = true;
  }
}

void NoteGroup::setUntied(size_t __pos) {
  if (__pos < _tieList.size()) {
    _tieList[__pos] = false;
  }
}

bool NoteGroup::isValid() const {
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

bool NoteGroup::isTied(size_t __pos) const {
  if (__pos >= _tieList.size()) {
    return false;
  }
  else {
    return _tieList[__pos];
  }
}

bool NoteGroup::hasDuration() const {
  return _duration != nullptr;
}

bool NoteGroup::hasDuration(size_t __pos) const {
  return _duration != nullptr;
}

bool NoteGroup::hasPitch() const {
  return !_pitchList.empty();
}

bool NoteGroup::hasPitch(size_t __pos) const {
  if (__pos >= _pitchList.size()) {
    return false;
  }
  else {
    return _pitchList[__pos] != nullptr;
  }
}

bool NoteGroup::hasProperty() const {
  return _property != nullptr;
}

bool NoteGroup::hasProperty(size_t __pos) const {
  return _property != nullptr;
}

const Duration * NoteGroup::getDuration() const {
  return _duration;
}

const Duration * NoteGroup::getDuration(size_t __pos) const {
  return _duration;
}

const Pitch * NoteGroup::getPitch() const {
  if (_pitchList.empty()) {
    return nullptr;
  }
  else {
    return _pitchList[0];
  }
}

const Pitch * NoteGroup::getPitch(size_t __pos) const {
  if (__pos >= _pitchList.size()) {
    return nullptr;
  }
  else {
    return _pitchList[__pos];
  }
}

const Property * NoteGroup::getProperty() const {
  return _property;
}

const Property * NoteGroup::getProperty(size_t __pos) const {
  return _property;
}

int NoteGroup::getPitchSize() const {
  return _pitchList.size();
}

} // namespace core
} // namespace hautbois