#include "note_chord.hpp"
#include "note_single.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "utility/hbexcept.hpp"

namespace hautbois {
namespace core {

void Chord::addPitch(Pitch * __p) {
  if (__p) {
    _pitch.push_back(__p);
  }
}

void Chord::setPitch(Pitch * __p) {
  Chord::clearPitch();
  if (__p) {
    _pitch.push_back(__p);
  }
}

void Chord::addDuration(Duration * __d) {
  Chord::clearDuration();
  if (__d) {
    _duration = __d;
  }
}

void Chord::setDuration(Duration * __d) {
  Chord::clearDuration();
  if (__d) {
    _duration = __d;
  }
}

void Chord::addProperty(Property * __p) {
  Chord::clearProperty();
  if (__p) {
    _property = __p;
  }
}

void Chord::setProperty(Property * __p) {
  Chord::clearProperty();
  if (__p) {
    _property = __p;
  }
}

void Chord::clearPitch() {
  for (auto it=_pitch.begin(); it != _pitch.end(); it++) {
    delete (*it);
  }
  _pitch.clear();
}

void Chord::clearDuration() {
  delete _duration;
  _duration = nullptr;
}

void Chord::clearProperty() {
  delete _property;
  _property = nullptr;
}

std::string Chord::filterProperty(const std::string& __text) const {
  std::string s (__text);
  return s;
}

Chord::Chord() : Note(NoteType::Chord),
  _duration ( nullptr ), _pitch ( {} ), _property (), _tied ({}) {
}

Chord::Chord(const std::vector<std::string>& __pitches) : Chord() {
  for (auto it=__pitches.cbegin(); it != __pitches.cend(); it++) {
    try {
      SingleNote n(*it, 1,4);
      Pitch * p = new Pitch(*n.getPitch());
      Chord::addPitch(p);
    }
    catch (const std::invalid_argument& e) {
      std::string msg ("Failed to create Chord with invalid token: " + *it);
      HB_THROW_MSG(std::invalid_argument, msg);
    }
  }
}

Chord::Chord(const std::initializer_list<const char *> __pitches) : Chord() {
  for (auto& pitch : __pitches) {
    std::string token(pitch);
    try {
      SingleNote n(token, 1,4);
      Pitch * p = new Pitch(*n.getPitch());
      Chord::addPitch(p);
    }
    catch (const std::invalid_argument& e) {
      std::string msg ("Failed to create Chord with invalid token: " + token);
      HB_THROW_MSG(std::invalid_argument, msg);
    }
  }
}

Chord::Chord(const std::vector<std::string>& __pitches,
             const int& num, const int& denom) :
  Chord(__pitches) {
  Duration * d = new Duration(num, denom);
  Chord::setDuration(d);
}

Chord::Chord(const std::vector<std::string>& __pitches,
            const int& denom, const std::string& dots) :
  Chord(__pitches) {
  Duration * d = new Duration(denom, dots);
  Chord::setDuration(d);
}

Chord::Chord(const std::initializer_list<const char *> __pitches,
             const int& num, const int& denom) : Chord(__pitches) {
  Duration * d = new Duration(num, denom);
  Chord::setDuration(d);
}

Chord::Chord(const std::initializer_list<const char *> __pitches,
             const int& denom, const std::string& dots) : Chord(__pitches) {
  Duration * d = new Duration(denom, dots);
  Chord::setDuration(d);
}

Chord::Chord(Chord& __note) : Chord() {
  if (__note.hasPitch()) {
    for (size_t i=0; i < __note.getPitchSize(); i++) {
      Pitch * p = new Pitch(*__note.getPitch(i));
      Chord::addPitch(p);
    }
  }
  if (__note.hasDuration()) {
    Duration * d = new Duration(*__note.getDuration());
    Chord::setDuration(d);
  }
  if (__note.hasProperty()) {
    Property * p = new Property(*__note.getProperty());
    Chord::setProperty(p);
  }
}

Chord::Chord(Chord&& __note) : Chord() {
  if (__note.hasPitch()) {
    for (size_t i=0; i < __note.getPitchSize(); i++) {
      Pitch * p = new Pitch(*__note.getPitch(i));
      Chord::addPitch(p);
    }
  }
  if (__note.hasDuration()) {
    Duration * d = new Duration(*__note.getDuration());
    Chord::setDuration(d);
  }
  if (__note.hasProperty()) {
    Property * p = new Property(*__note.getProperty());
    Chord::setProperty(p);
  }
}

Chord& Chord::operator=(const Chord& __n) {
  setNoteType(NoteType::Chord);
  if (this != &__n) {
    Chord::clearPitch();
    Chord::clearDuration();
    Chord::clearProperty();
    if (__n.hasPitch()) {
      for (size_t i=0; i < __n.getPitchSize(); i++) {
        Pitch * p = new Pitch(*__n.getPitch(i));
        Chord::addPitch(p);
      }
    }
    if (__n.hasDuration()) {
      Duration * d = new Duration(*__n.getDuration());
      Chord::setDuration(d);
    }
    if (__n.hasProperty()) {
      Property * p = new Property(*__n.getProperty());
      Chord::setProperty(p);
    }
  }
  return *this;
}

Chord::~Chord() {
  Chord::clearPitch();
  Chord::clearDuration();
  Chord::clearProperty();
}

void Chord::updateDuration(const std::string& __context) { }

void Chord::updateDuration(const std::string& __context, size_t __pos) { }
  
void Chord::updatePitch(const std::string& __context) { }

void Chord::updatePitch(const std::string& __context, size_t __pos) { }

void Chord::updateProperty(const std::string& __context) {
  if (!__context.empty()) {
    Chord::clearProperty();
    Property * p = new Property(__context);
    Chord::setProperty(p);
  }
}

void Chord::updateProperty(const std::string& __context, size_t __pos) { 
  Chord::updateProperty(__context);
}

void Chord::setTied() {
  _tied.clear();
  for (auto it = _pitch.cbegin(); it != _pitch.cend(); it++) {
    _tied.push_back(true);
  }
}

void Chord::setTied(size_t __pos) {
  if (_pitch.size() != _tied.size()) {
    Chord::setUntied();
  }
  if (__pos >= _tied.size()) {
    _tied[_tied.size() - 1] = true;
  }
  else if (__pos < 0) {
    _tied[0] = true;
  }
  else {
    _tied[__pos] = true;
  }
}

void Chord::setUntied() {
  _tied.clear();
  for (auto it = _pitch.cbegin(); it != _pitch.cend(); it++) {
    _tied.push_back(false);
  }
}

void Chord::setUntied(size_t __pos) {
  if (_pitch.size() == _tied.size()) {
    if (__pos >= _tied.size()) {
      _tied[_tied.size() - 1] = false;
    }
    else if (__pos < 0) {
      _tied[0] = false;
    }
    else {
      _tied[__pos] = false;
    }
  }
  else {
    Chord::setUntied();
  }
}

int Chord::getSize() const {
  return _pitch.size();
}

bool Chord::isValid() const {
  if (_pitch.empty() || _duration == nullptr) {
    return false;
  }
  else {
    return true;
  }
}

bool Chord::isTied() const {
  if (!_tied.empty()) {
    for (const bool t: _tied) {
      if (t) {
        return true;
      }
    }
  }
  return false;
}

bool Chord::isTied(size_t __pos) const {
  if (_tied.size() == _pitch.size()) {
    if (__pos >= _tied.size()) {
      return _tied[_tied.size() - 1];
    }
    else if (__pos < 0) {
      return _tied[0];
    }
    else {
      return _tied[__pos];
    }
  }
  else {
    return false;
  }
}

bool Chord::hasDuration() const {
  return _duration != nullptr;
}

bool Chord::hasPitch() const {
  if (!_pitch.empty()) {
    for (auto it=_pitch.cbegin(); it != _pitch.cend(); it++) {
      if (*it == nullptr) {
        return false;
      }
    }
    return true;
  }
  else {
    return false;
  }
}

bool Chord::hasProperty() const {
  return _property != nullptr;
}

bool Chord::hasDuration(size_t __pos) const {
  return _duration != nullptr;
}

bool Chord::hasPitch(size_t __pos) const {
  if (__pos >= 0 && __pos < _pitch.size()) {
    if (_pitch[__pos] != nullptr) {
      return true;
    }
  }
  return false;
}

bool Chord::hasProperty(size_t __pos) const {
  return _property != nullptr;
}

const Duration * Chord::getDuration() const {
  if (_duration) {
    return _duration;
  }
  else {
    std::string msg = "duration is empty";
    HB_THROW_MSG(std::out_of_range, msg);
  }
}

const Duration * Chord::getDuration(size_t __pos) const {
  return Chord::getDuration();
}

const Pitch * Chord::getPitch() const {
  if (!_pitch.empty()) {
    if (_pitch.front()) {
      return _pitch.front();
    }
    else {
      std::string msg = "nullptr caught";
      HB_THROW_MSG(std::runtime_error, msg);
    }
  }
  else {
    std::string msg = "pitch is empty";
    HB_THROW_MSG(std::out_of_range, msg);
  }
}

const Pitch * Chord::getPitch(size_t __pos) const {
  if (__pos >= _pitch.size() || __pos < 0 || _pitch.empty()) {
    std::string msg = "Provided index " + std::to_string(__pos) 
                    + " exceeds size "  + std::to_string(_pitch.size());
    HB_THROW_MSG(std::out_of_range, msg);
  }
  else {
    if (_pitch[__pos]) {
      return _pitch[__pos];
    }
    else {
      std::string msg = "nullptr caught at pos " + std::to_string(__pos);
      HB_THROW_MSG(std::runtime_error, msg);
    }
  }
}

const Property * Chord::getProperty() const {
  if (_property) {
    return _property;
  }
  else {
    std::string msg = "property is empty";
    HB_THROW_MSG(std::out_of_range, msg);
  }
}

const Property * Chord::getProperty(size_t __pos) const {
  return Chord::getProperty();
}

std::string Chord::getPropertyStr() const {
  std::string s;
  if (_property) {
    s = _property->toString();
  }
  return s;
}

std::string Chord::getPropertyStr(size_t __pos) const {
  return Chord::getPropertyStr();
}

int Chord::getPitchSize() const {
  return _pitch.size();
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

void Chord::modify(const std::string& __context) {
}

std::string Chord::toString() const {
  std::string s;
  for (auto it=_pitch.cbegin(); it != _pitch.cend(); it++) {
    if(*it != nullptr) {
      s += (*it)->toString();
      s += ",";
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