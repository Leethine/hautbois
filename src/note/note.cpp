#include "note.hpp"
#include <cstddef>

namespace hautbois {

void Note::setNote(Note * __ptr, const int __pos) {
  auto& elems = _tuplet_notes;
  if (__pos >= 0 && __pos < elems.size() && __ptr) {
    delete elems[__pos];
    elems[__pos] = __ptr;
  }
  else if (__pos >= 0 && __pos < elems.size() && __ptr == nullptr) {
    delete elems[__pos];
    elems.erase(elems.begin() + __pos);
  }
  else if (__pos < 0 && __ptr) {
    elems.push_back(__ptr);
  }
}

void Note::setPitch(Pitch * __ptr, const int __pos) {
  auto& elems = _pitch;
  if (__pos >= 0 && __pos < elems.size() && __ptr) {
    delete elems[__pos];
    elems[__pos] = __ptr;
  }
  else if (__pos >= 0 && __pos < elems.size() && __ptr == nullptr) {
    delete elems[__pos];
    elems.erase(elems.begin() + __pos);
  }
  else if (__pos < 0 && __ptr) {
    elems.push_back(__ptr);
  }
}

void Note::setDuration(Duration * __ptr, const int __pos) {
  auto& elems = _duration;
  if (__pos >= 0 && __pos < elems.size() && __ptr) {
    delete elems[__pos];
    elems[__pos] = __ptr;
  }
  else if (__pos >= 0 && __pos < elems.size() && __ptr == nullptr) {
    delete elems[__pos];
    elems.erase(elems.begin() + __pos);
  }
  else if (__pos < 0 && __ptr) {
    elems.push_back(__ptr);
  }
}

void Note::setProperty(Property * __ptr, const int __pos) {
  auto& elems = _property;
  if (__pos >= 0 && __pos < elems.size() && __ptr) {
    delete elems[__pos];
    if (__ptr->toList().empty()) {
      elems[__pos] = nullptr;
    }
    else {
      elems[__pos] = __ptr;
    }
  }
  else if (__pos >= 0 && __pos < elems.size() && __ptr == nullptr) {
    delete elems[__pos];
    elems.erase(elems.begin() + __pos);
  }
  else if (__pos < 0) {
    if (__ptr && __ptr->toList().empty()) {
      elems.push_back(nullptr);
    }
    else {
      elems.push_back(__ptr);
    }
  }
}

Pitch * Note::getPitchModify(const size_t __pos) {
  auto& elems = _pitch;
  if (__pos < elems.size()) {
    return elems[__pos];
  }
  return nullptr;
}

Duration * Note::getDurationModify(const size_t __pos) {
  auto& elems = _duration;
  if (__pos < elems.size()) {
    return elems[__pos];
  }
  return nullptr;
}

Property * Note::getPropertyModify(const size_t __pos) {
  auto& elems = _property;
  if (__pos < elems.size()) {
    return elems[__pos];
  }
  return nullptr;
}

Note * Note::getNoteModify(const size_t __pos) {
  auto& elems = _tuplet_notes;
  if (__pos < elems.size()) {
    return elems[__pos];
  }
  return nullptr;
}

void Note::setNoteType(const char __note_type) {
  _type = __note_type;
}

Note::Note(const char __note_type) :
  _type (__note_type), _duration (), _pitch (), _property (), _tuplet_notes (), _tied() {
}

Note::~Note() {
  for (auto it = _duration.begin(); it != _duration.end(); it++) {
    delete (*it);
  }
  for (auto it = _pitch.begin(); it != _pitch.end(); it++) {
    delete (*it);
  }
  for (auto it = _property.begin(); it != _property.end(); it++) {
    delete (*it);
  }
  for (auto it = _tuplet_notes.begin(); it != _tuplet_notes.end(); it++) {
    delete (*it);
  }
}

bool Note::isType(const char __note_type) const {
  return (_type == __note_type);
}

char Note::getType() const {
  return _type;
}

void Note::makeTie(const size_t __pos) {
  if (__pos < _tied.size()) {
    _tied[__pos] = true;
  }
}

void Note::makeUntie(const size_t __pos) {
  if (__pos < _tied.size()) {
    _tied[__pos] = false;
  }
}

bool Note::isTied(const size_t __pos) {
  if (__pos < _tied.size()) {
    return _tied[__pos];
  }
  return false;
}

const Pitch * Note::getPitch(const size_t __pos) const {
  if (__pos < _pitch.size()) {
    return _pitch[__pos];
  }
  return nullptr;
}

const Duration * Note::getDuration(const size_t __pos) const {
  if (__pos < _duration.size()) {
    return _duration[__pos];
  }
  return nullptr;
}

const Property * Note::getProperty(const size_t __pos) const {
  if (__pos < _property.size()) {
    return _property[__pos];
  }
  return nullptr;
}

const Note * Note::getNote(const size_t __pos) const {
  if (__pos < _tuplet_notes.size()) {
    return _tuplet_notes[__pos];
  }
  return nullptr;
}

} // namespace hautbois