#include "note.hpp"
#include "../hbtype/hbdefs.hpp"

namespace hautbois {

void Note::setNote(Note * __ptr, const int __pos) {
  if (__pos >= 0 && size_t(__pos) < _notes.size() && __ptr && dynamic_cast<Note *>(__ptr)) {
    delete _notes[__pos];
    _notes[__pos] = __ptr;
  }
  else if (__pos >= 0 && size_t(__pos) < _notes.size() && __ptr == nullptr) {
    delete _notes[__pos];
    _notes.erase(_notes.begin() + __pos);
  }
  else if (__pos < 0 && __ptr && dynamic_cast<Note *>(__ptr)) {
    _notes.push_back(__ptr);
  }
}

void Note::setPitch(Pitch * __ptr) {
  delete _pitch;
  _pitch = nullptr;
  if (__ptr && dynamic_cast<Pitch *>(__ptr)) {
    _pitch = __ptr;
  }
}

void Note::setDuration(Duration * __ptr) {
  delete _duration;
  _duration = nullptr;
  if (__ptr && dynamic_cast<Duration *>(__ptr)) {
    _duration = __ptr;
  }
}

void Note::setProperty(Property * __ptr) {
  delete _property;
  _property = nullptr;
  if (__ptr && dynamic_cast<Property *>(__ptr)) {
    _property = __ptr;
  }
}

void Note::setTie(bool __tie) {
  _tied = __tie;
}

Pitch * Note::getPitchModify() {
  return _pitch;
}

Duration * Note::getDurationModify() {
  return _duration;
}

Property * Note::getPropertyModify() {
  return _property;
}

Note * Note::getNoteModify(const size_t __pos) {
  if (__pos < _notes.size()) {
    return _notes[__pos];
  }
  return nullptr;
}

void Note::setNoteType(const char __note_type) {
  _type = __note_type;
}

Note::Note(const char __note_type) :
  _type (__note_type), _tied(false),
  _duration (nullptr), _pitch (nullptr), _property (nullptr),
  _notes ( ) {
  if (__note_type == CHAR_NOTETYPE_CHORD || __note_type == CHAR_NOTETYPE_GRACE || __note_type == CHAR_NOTETYPE_TUPLET) {
    _notes.reserve(3);
  }
}

Note::~Note() {
  delete _duration;
  delete _pitch;
  delete _property;
  for (auto it = _notes.begin(); it != _notes.end(); it++) {
    delete (*it);
  }
}

char Note::getType() const {
  return _type;
}

bool Note::isType(const char __note_type) const {
  return (_type == __note_type);
}

bool Note::isMute() const {
  return (_type == CHAR_NOTETYPE_REST || _type == CHAR_NOTETYPE_SILENCE);
}

bool Note::isTied(const size_t __pos) const {
  return _tied;
}

const Pitch * Note::getPitch(const size_t __pos) const {
  return _pitch;
}

const Duration * Note::getDuration(const size_t __pos) const {
  return _duration;
}

const Property * Note::getProperty(const size_t __pos) const {
  return _property;
}

const Note * Note::getNote(const size_t __pos) const {
  if (__pos < _notes.size()) {
    return _notes[__pos];
  }
  return nullptr;
}

int Note::getSize() const {
  return _notes.size();
}

} // namespace hautbois