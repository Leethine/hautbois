#include "note_chord.hpp"
#include "note_group.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "utility/hbexcept.hpp"

#include <initializer_list>
#include <cstring>

namespace hautbois {
namespace core {

void Chord::setPitch(Pitch * __p) {
  if (__p) {
    NoteGroup::addPitch(__p);
  }
}

void Chord::addDuration(Duration * __d) {
  if (__d) {
    NoteGroup::setDuration(__d);
  }
}

void Chord::addProperty(Property * __p) {
  NoteGroup::setProperty(__p);
}

void * Chord::verify(const char * __context) const {
  return nullptr;
}

std::string Chord::filterProperty(const std::string& __text) const {
  std::string s (__text);
  return s;
}

Chord::Chord() : NoteGroup(NoteType::Chord) {}
 
Chord::Chord(const std::initializer_list<const char *> __pitches) :
    NoteGroup(NoteType::Chord) {
  for (auto& token : __pitches) {
    Pitch * p = nullptr;
    if (std::strlen(token) > 3 || std::strlen(token) == 0) {
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

Chord::Chord(const std::vector<std::string>& __pitches) :
    NoteGroup(NoteType::Chord) {
  for (auto& token : __pitches) {
    Pitch * p = nullptr;
    if (token.size() > 3 || token.size() == 0) {
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

Chord::Chord(const std::vector<std::string>& __pitches,
             const int& num, const int & denom) :
  Chord(__pitches) {
  
  Duration * d = nullptr;
  HB_NESTED_THROW(std::invalid_argument,
    d = new Duration(num, denom);
  )
  NoteGroup::setDuration(d);
}

Chord::Chord(const std::vector<std::string>& __pitches,
             const int& denom, const std::string& dots) : 
  Chord(__pitches) {
  
  Duration * d = nullptr;
  HB_NESTED_THROW(std::invalid_argument,
    d = new Duration(denom, dots);
  )
  NoteGroup::setDuration(d);
}

Chord::Chord(const std::initializer_list<const char *> __pitches, 
             const int& num, const int & denom) : 
  Chord(__pitches) {
  
  Duration * d = nullptr;
  HB_NESTED_THROW(std::invalid_argument,
    d = new Duration(num, denom);
  )
  NoteGroup::setDuration(d);
}

Chord::Chord(const std::initializer_list<const char *> __pitches,
             const int& denom, const std::string& dots) :
  Chord(__pitches) {

  Duration * d = nullptr;
  HB_NESTED_THROW(std::invalid_argument,
    d = new Duration(denom, dots);
  )
  NoteGroup::setDuration(d);
}

Chord::Chord(Chord& __note) : NoteGroup(NoteType::Chord) {
  HB_NESTED_THROW(std::out_of_range,
    for (int i=0; i<__note.getPitchSize(); i++) {
      if (__note.hasPitch(i)) {
        Pitch * p = new Pitch(*__note.getPitch(i));
        NoteGroup::addPitch(p);
        if (NoteGroup::isTied(i)) {
          NoteGroup::setTied(i);
        }
      }
    }
    if (__note.hasDuration()) {
      Duration * d = new Duration(*__note.getDuration());
      NoteGroup::setDuration(d);
    }
    if (NoteGroup::hasProperty()) {
      Property * p = new Property(*__note.getProperty());
      NoteGroup::setProperty(p);
    }
  )
}

Chord::Chord(Chord&& __note) : NoteGroup(NoteType::Chord) {
  HB_NESTED_THROW(std::out_of_range,
    for (int i=0; i<__note.getPitchSize(); i++) {
      if (__note.hasPitch(i)) {
        Pitch * p = new Pitch(*__note.getPitch(i));
        NoteGroup::addPitch(p);
        if (NoteGroup::isTied(i)) {
          NoteGroup::setTied(i);
        }
      }
    }
    if (__note.hasDuration()) {
      Duration * d = new Duration(*__note.getDuration());
      NoteGroup::setDuration(d);
    }
    if (NoteGroup::hasProperty()) {
      Property * p = new Property(*__note.getProperty());
      NoteGroup::setProperty(p);
    }
  )
}

Chord& Chord::operator=(const Chord& __n) {
  if (this != &__n) {
    NoteGroup::clearPitch();
    NoteGroup::clearDuration();
    NoteGroup::clearProperty();
    HB_NESTED_THROW(std::out_of_range,
      for (int i=0; i<__n.getPitchSize(); i++) {
        if (__n.hasPitch(i)) {
          Pitch * p = new Pitch(*__n.getPitch(i));
          NoteGroup::addPitch(p);
          if (NoteGroup::isTied(i)) {
            NoteGroup::setTied(i);
          }
        }
      }
      if (__n.hasDuration()) {
        Duration * d = new Duration(*__n.getDuration());
        NoteGroup::setDuration(d);
      }
      if (NoteGroup::hasProperty()) {
        Property * p = new Property(*__n.getProperty());
        NoteGroup::setProperty(p);
      }
    )
  }
  return *this;
}

Chord::~Chord() {
  //NoteGroup::~NoteGroup();
  NoteGroup::clearDuration();
  NoteGroup::clearProperty();
  NoteGroup::clearPitch();
}

void Chord::updateDuration(const std::string& __context) { }

void Chord::updateDuration(const std::string& __context, size_t __pos) { }

void Chord::updatePitch(const std::string& __context) { }

void Chord::updatePitch(const std::string& __context, size_t __pos) { }

void Chord::updateProperty(const std::string& __context) {
  if (!__context.empty()) {
    NoteGroup::clearProperty();
    Property * p = new Property(__context);
  }
}

void Chord::updateProperty(const std::string& __context, size_t __pos) {
  if (!__context.empty()) {
    NoteGroup::clearProperty();
    Property * p = new Property(__context);
  }
}

void Chord::setTied() {
  for (int i=0; i<NoteGroup::getPitchSize();i++) {
    NoteGroup::setTied(i);
  }
}

void Chord::setTied(size_t __pos) {
  NoteGroup::setTied(__pos);
}

void Chord::setUntied() {
  HB_NESTED_THROW(std::out_of_range,
    for (int i=0; i<NoteGroup::getPitchSize();i++) {
      NoteGroup::setUntied(i);
    }
  )
}

void Chord::setUntied(size_t __pos) {
  NoteGroup::setUntied(__pos);
}

int Chord::getSize() const {
  return NoteGroup::getPitchSize();
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
  return NoteGroup::isValid();
}

bool Chord::isTied() const {
  HB_NESTED_THROW(std::out_of_range,
    for (int i=0; i<NoteGroup::getPitchSize();i++) {
      if (NoteGroup::isTied(i)) {
        return true;
      }
    }
  )
  return false;
}

bool Chord::isTied(size_t __pos) const {
  return NoteGroup::isTied(__pos);
}

bool Chord::hasDuration() const {
  return NoteGroup::hasDuration();
}

bool Chord::hasDuration(size_t __pos) const {
  return NoteGroup::hasDuration();
}

bool Chord::hasPitch() const {
  return NoteGroup::hasPitch(0);
}

bool Chord::hasPitch(size_t __pos) const {
  return NoteGroup::hasPitch(__pos);
}

bool Chord::hasProperty() const {
  return NoteGroup::hasProperty();
}

bool Chord::hasProperty(size_t __pos) const {
  return NoteGroup::hasProperty();
}

const Duration * Chord::getDuration() const {
  return NoteGroup::getDuration();
}

const Duration * Chord::getDuration(size_t __pos) const {
  if (NoteGroup::hasDuration()) {
    return NoteGroup::getDuration();
  }
  return nullptr;
}

const Pitch * Chord::getPitch() const {
  if (NoteGroup::hasPitch(0)) {
    return NoteGroup::getPitch(0);
  }
  return nullptr;
}

const Pitch * Chord::getPitch(size_t __pos) const {
  return NoteGroup::getPitch(__pos);
}

const Property * Chord::getProperty() const {
  return NoteGroup::getProperty();
}

const Property * Chord::getProperty(size_t __pos) const {
  return NoteGroup::getProperty();
}

std::string Chord::getPropertyStr() const {
  std::string s;
  if (NoteGroup::hasProperty()) {
    s = NoteGroup::getProperty()->toString();
  }
  return s;
}

std::string Chord::getPropertyStr(size_t __pos) const {
  return Chord::getPropertyStr();
}

int Chord::getPitchSize() const {
  return NoteGroup::getPitchSize();
}

int Chord::getDurationSize() const {
  if (NoteGroup::hasDuration()) {
    return 1;
  }
  return 0;
}

int Chord::getPropertySize() const {
  if (NoteGroup::hasProperty()) {
    return 1;
  }
  return 0;
}

void Chord::modify(const std::string& __context) { }

std::string Chord::toString() const {
  std::string s;
  for (int i=0; i<NoteGroup::getPitchSize();i++) {
    if (NoteGroup::hasPitch(i)) {
      s += NoteGroup::getPitch(i)->toString();
      s.push_back(',');
    }
  }
  if (NoteGroup::hasDuration()) {
    s += NoteGroup::getDuration()->toString();
  }
  return s;
}

void * Chord::toStream(const std::string& __context, void * __ostream) const {
  return nullptr;
}

} // namespace core
} // namespace hautbois