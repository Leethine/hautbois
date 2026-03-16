#include "note_single.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "utility/hbexcept.hpp"
#include "symbol_raw/core_types.hpp"

#include <stdexcept>

namespace hautbois {
namespace core {

void SingleNote::addPitch(Pitch * __p) {
  if (__p) {
    delete _pitch;
    _pitch = __p;
  }
}

void SingleNote::setPitch(Pitch * __p, int pos) {
  if (__p) {
    delete _pitch;
    _pitch = __p;
    _tied = false;
  }
}

void SingleNote::addDuration(Duration * __d) {
  if (__d) {
    delete _duration;
    _duration = __d;
  }
}

void SingleNote::setDuration(Duration * __d, int pos) {
  if (__d) {
    delete _duration;
    _duration = __d;
  }
}

void SingleNote::addProperty(Property * __p) {
  delete _property; 
  _property = __p;
}

void SingleNote::setProperty(Property * __p, int pos) {
  delete _property;
  _property = __p;
}

Pitch * SingleNote::getPitchyMod(int pos) {
  return _pitch;
}

Duration * SingleNote::getDurationMod(int pos) {
  return _duration;
}

Property * SingleNote::getPropertyMod(int pos) {
  return _property;
}

void SingleNote::clearPitch() {
  delete _pitch;
  _pitch = nullptr;
  _tied = false;
}

void SingleNote::clearDuration() {
  delete _duration;
  _duration = nullptr;
}

void SingleNote::clearProperty() {
  delete _property;
  _property = nullptr;
}

void * SingleNote::verify(const char * __context) const {
  if (_pitch == nullptr || _duration == nullptr) {
    const char * str = "No _pitch or _duration available.";
    return (void *) str;
  }
  return nullptr;
}

std::string SingleNote::filterProperty(const std::string& __text) const {
  std::string s (__text);
  return s;
}

SingleNote::SingleNote() : Note (NoteType::SingleNote), 
  _duration ( nullptr ), _pitch ( nullptr ),
  _property ( nullptr ), _tied ( false ) {
}

SingleNote::SingleNote(const std::string& __pitch) : SingleNote() {
  char name = CHAR_PITCHNAME_C;
  char acc = CHAR_ACCIDENTAL_NATURAL;
  char oct = CHAR_OCTAVE_DEFAULT;
  if (__pitch.size() == 3) {
    name = __pitch[0];
    acc  = __pitch[1];
    oct  = __pitch[2];
  }
  else if (__pitch.size() == 2) {
    name = __pitch[0];
    oct  = __pitch[1];
  }
  else if (__pitch.size() == 1) {
    name = __pitch[0];
    if (name == CHAR_PITCHNAME_SILENCE) {
      setNoteType(NoteType::Silence);
    }
    if (name == CHAR_PITCHNAME_REST) {
      setNoteType(NoteType::Rest);
    }
  }
  else {
    HB_THROW_MSG(std::invalid_argument,
      std::string ("Cannot create SingleNote with Pitch: " + __pitch)
    );
  }
  HB_NESTED_THROW(std::invalid_argument,
    _pitch = new Pitch(name, acc, oct - '0');
  )
}

SingleNote::SingleNote(const std::string& __pitch, 
                       const int& __num, const int& __denom) : SingleNote(__pitch) {
  HB_NESTED_THROW(std::invalid_argument,
    _duration = new Duration(__num, __denom);
  )
}

SingleNote::SingleNote(const std::string& __pitch,
                       const int& __denom, const std::string& __dots) : SingleNote(__pitch) {
  HB_NESTED_THROW(std::invalid_argument,
    _duration = new Duration(__denom, __dots);
  )
}

SingleNote::SingleNote(SingleNote& __note) : SingleNote() {
  if (__note.hasPitch()) {
    _pitch = new Pitch(*__note.getPitch());
  }
  if (__note.hasDuration()) {
    _duration = new Duration(*__note.getDuration());
  }
  if (__note.hasProperty()) {
    _property = new Property(*__note.getProperty());
  }
  if (__note.isTied()) {
    SingleNote::setTied();
  }
}
  
SingleNote::SingleNote(SingleNote&& __note) : SingleNote() {
  if (__note.hasPitch()) {
    _pitch = new Pitch(*__note.getPitch());
  }
  if (__note.hasDuration()) {
    _duration = new Duration(*__note.getDuration());
  }
  if (__note.hasProperty()) {
    _property = new Property(*__note.getProperty());
  }
  if (__note.isTied()) {
    SingleNote::setTied();
  }
}

SingleNote& SingleNote::operator=(const SingleNote& __note) {
  if (this != &__note) {
    if (__note.hasPitch()) {
      _pitch = new Pitch(*__note.getPitch());
    }
    if (__note.hasDuration()) {
      _duration = new Duration(*__note.getDuration());
    }
    if (__note.hasProperty()) {
      _property = new Property(*__note.getProperty());
    }
    if (__note.isTied()) {
      SingleNote::setTied();
    }
  }
  return *this;
}

SingleNote::~SingleNote() {
  delete _pitch;
  delete _duration;
  delete _property;
}

void SingleNote::updateDuration(const std::string& __context) { }

void SingleNote::updateDuration(const std::string& __context, size_t __pos) { }

void SingleNote::updatePitch(const std::string& __context) { }

void SingleNote::updatePitch(const std::string& __context, size_t __pos) { }

void SingleNote::updateProperty(const std::string& __context) {
  SingleNote::clearProperty();
  if (!__context.empty()) {
    _property = new Property(__context);
  }
  else {
    delete _property;
    _property = nullptr;
  }
}

void SingleNote::updateProperty(const std::string& __context, size_t __pos) {
  SingleNote::updateProperty(__context);
}

void SingleNote::setTied() {
  _tied = true;
}

void SingleNote::setTied(size_t __pos) {
  _tied = true;
}

void SingleNote::setUntied() {
  _tied = false;
}

void SingleNote::setUntied(size_t __pos) {
  _tied = false;
}

int SingleNote::getSize() const {
  if (_duration) {
    return 1;
  }
  return 0;
}

NoteType SingleNote::getType() {
  return Note::getType();
}

char SingleNote::getTypeChar() const {
  return Note::getTypeChar();
}

std::string SingleNote::getTypeStr() const {
  return Note::getTypeStr();
}

bool SingleNote::isType(NoteType __ntype) const {
  return Note::isType(__ntype);
}

bool SingleNote::isSingle() const {
  return Note::isSingle();
}

bool SingleNote::isRest() const {
  return Note::isRest();
}

bool SingleNote::isSilence() const {
  return Note::isSilence();
}

bool SingleNote::isChord() const {
  return Note::isChord();
}

bool SingleNote::isTuplet() const {
  return Note::isTuplet();
}

bool SingleNote::isGrace() const {
  return Note::isGrace();
}

bool SingleNote::isAppoggiatura() const {
  return Note::isAppoggiatura();
}

bool SingleNote::isAcciaccatura() const {
  return Note::isAcciaccatura();
}

bool SingleNote::isValid() const {
  if (_duration != nullptr && _pitch != nullptr) {
    return true;
  }
  return false;
}

bool SingleNote::isTied() const {
  return _tied;
}

bool SingleNote::isTied(size_t __pos) const {
  return _tied;
}

bool SingleNote::hasDuration() const {
  return _duration != nullptr;
}

bool SingleNote::hasDuration(size_t __pos) const {
  return _duration != nullptr;
}

bool SingleNote::hasPitch() const {
  return _pitch != nullptr;
}

bool SingleNote::hasPitch(size_t __pos) const {
  return _pitch != nullptr;
}

bool SingleNote::hasProperty() const {
  return _property != nullptr;
}

bool SingleNote::hasProperty(size_t __pos) const {
  return _property != nullptr;
}

const Duration * SingleNote::getDuration() const {
  return _duration;
}

const Duration * SingleNote::getDuration(size_t __pos) const {
  return SingleNote::getDuration();
}

const Pitch * SingleNote::getPitch() const {
  return _pitch;
}

const Pitch * SingleNote::getPitch(size_t __pos) const {
  return SingleNote::getPitch();
}

const Property * SingleNote::getProperty() const {
  return _property;
}

const Property * SingleNote::getProperty(size_t __pos) const {
  return SingleNote::getProperty();
}

std::string SingleNote::getPropertyStr() const {
  std::string s;
  if (_property) {
    s = _property->toString();
  }
  return s;
}

std::string SingleNote::getPropertyStr(size_t __pos) const {
  return SingleNote::getPropertyStr();
}

int SingleNote::getPitchSize() const {
  if (_pitch) {
    return 1;
  }
  return 0;
}

int SingleNote::getDurationSize() const {
  if (_duration) {
    return 1;
  }
  return 0;
}

int SingleNote::getPropertySize() const {
  if (_property) {
    return 1;
  }
  return 0;
}

void SingleNote::modify(const std::string& __context) { }

std::string SingleNote::toString() const {
  std::string s;
  if (Note::isSilence())   { s += "S,"; }
  else if (Note::isRest()) { s += "R,"; }
  else {
    if (_pitch)  { s += _pitch->toString() + ","; }
  }
  if (_duration) { s += _duration->toString(); }
  return s;
}

void * SingleNote::toStream(const std::string& __context, void * __ostream) const {
  return nullptr;
}

} // namespace core
} // namespace hautbois