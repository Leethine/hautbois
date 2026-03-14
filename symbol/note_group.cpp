#include "note_group.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"

namespace hautbois {
namespace core {

void NoteGroup::addPitch(Pitch *__p) {
  if (__p) {
    _pitchList.push_back(__p);
    _tieList.push_back(false);
  }
}

void NoteGroup::setDuration(Duration *__d) {
  if (__d) {
    NoteGroup::clearDuration();
    _duration = __d;
  }
}

void NoteGroup::setProperty(Property *__p) {
  NoteGroup::clearProperty();
  _property = __p;
}

Pitch * NoteGroup::getPitchToModify(int pos) {
  if (_pitchList.empty()) {
    return nullptr;
  }
  else {
    if (pos < 0) { return _pitchList.front(); }
    else if (pos >= _pitchList.size()) { return _pitchList.back(); }
    else { return _pitchList[pos]; }
  }
}

Duration * NoteGroup::getDurationToModify(int pos) {
  return _duration;
}

Property * NoteGroup::getPropertyToModify(int pos) {
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

NoteGroup::~NoteGroup() {
  NoteGroup::clearDuration();
  NoteGroup::clearProperty();
  NoteGroup::clearPitch();
}

void NoteGroup::setTied(size_t __pos) {
  if (__pos >= 0 && __pos < _tieList.size()) {
    _tieList[__pos] = true;
  }
}

void NoteGroup::setUntied(size_t __pos) {
  if (__pos >= 0 && __pos < _tieList.size()) {
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
  if (__pos >= _tieList.size() || __pos < 0) {
    return false;
  }
  else {
    return _tieList[__pos];
  }
}

bool NoteGroup::hasDuration() const {
  return _duration != nullptr;
}

bool NoteGroup::hasPitch(size_t __pos) const {
  if (__pos >= _pitchList.size() || __pos < 0) {
    return false;
  }
  else {
    return _pitchList[__pos] != nullptr;
  }
}

bool NoteGroup::hasProperty() const {
  return _property != nullptr;
}

const Duration * NoteGroup::getDuration() const {
  return _duration;
}

const Pitch * NoteGroup::getPitch(size_t __pos) const {
  if (__pos >= _pitchList.size() || __pos < 0) {
    return nullptr;
  }
  else {
    return _pitchList[__pos];
  }
}

const Property * NoteGroup::getProperty() const {
  return _property;
}

int NoteGroup::getPitchSize() const {
  return _pitchList.size();
}

} // namespace core
} // namespace hautbois