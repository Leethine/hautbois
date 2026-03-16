#include "note_tuplet.hpp"
#include "note_single.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "utility/hbexcept.hpp"

namespace hautbois {
namespace core {

void Tuplet::addPitch(Pitch * __p) {
  NoteSequence::addPitch(__p);
}

void Tuplet::setPitch(Pitch * __p, int pos) {
  NoteSequence::setPitch(__p, pos);
}

void Tuplet::addDuration(Duration * __d) {
  NoteSequence::addDuration(__d);
}

void Tuplet::setDuration(Duration * __d, int pos) {
  NoteGroup::setDuration(__d, pos);
}

void Tuplet::addProperty(Property * __p) {
  NoteSequence::addProperty(__p);
}

void Tuplet::setProperty(Property * __p, int pos) {
  NoteSequence::setProperty(__p, pos);
}

Pitch * Tuplet::getPitchyMod(int pos) {
  return NoteSequence::getPitchyMod(pos);
}

Duration * Tuplet::getDurationMod(int pos) {
  return NoteSequence::getDurationMod(pos);
}

Property * Tuplet::getPropertyMod(int pos) {
  return NoteSequence::getPropertyMod(pos);
}

void Tuplet::clearPitch() {
  NoteSequence::clearPitch();
}

void Tuplet::clearDuration() {
  NoteSequence::clearDuration();
}

void Tuplet::clearProperty() {
  NoteSequence::clearProperty();
}

void * Tuplet::verify(const char * __context) const {
  return nullptr;
}

std::string Tuplet::Tuplet::filterProperty(const std::string& __text) const {
  std::string s (__text);
  return s;
}

Tuplet::Tuplet(const unsigned int __count) : NoteSequence(NoteType::Tuplet, __count) {
}

Tuplet::Tuplet(int __num, int __denom,
               const std::initializer_list<const char *> __args,
               const unsigned int __count) :
  NoteSequence("", __num, __denom, __args, NoteType::Tuplet, __count) {
}

Tuplet::Tuplet(int __num, int __denom,
               const std::vector<std::string>& __args,
               const unsigned int __count) :
  NoteSequence("", __num, __denom, __args, NoteType::Tuplet, __count) {
}

Tuplet::~Tuplet() { }

void Tuplet::updateDuration(const std::string& __context) { }

void Tuplet::updateDuration(const std::string& __context, size_t __pos) { }

void Tuplet::updatePitch(const std::string& __context) { }

void Tuplet::updatePitch(const std::string& __context, size_t __pos) { }

void Tuplet::updateProperty(const std::string& __context) {
  if (!__context.empty()) {
    Property * p = new Property(__context);
    NoteGroup::setProperty(p, -1);
  }
  else {
    NoteGroup::setProperty(nullptr, -1);
  }
}

void Tuplet::updateProperty(const std::string& __context, size_t __pos) {
  if (__pos >= 0 &&  __pos < NoteSequence::getPropertySize()) {
    if (!__context.empty()) {
      Property * p = new Property(__context);
      NoteSequence::setProperty(p, __pos);
    }
    else {
      NoteSequence::setProperty(nullptr, __pos);
    }
  }
}

void Tuplet::setTied() {
  NoteSequence::setTied();
}

void Tuplet::setTied(size_t __pos) {
  NoteSequence::setTied(__pos);
}

void Tuplet::setUntied() {
  NoteSequence::setUntied();
}

void Tuplet::setUntied(size_t __pos) {
  NoteSequence::setUntied(__pos);
}

int Tuplet::getSize() const {
  return NoteSequence::getSize();
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
  return NoteSequence::isValid();
}

bool Tuplet::isTied() const {
  return NoteSequence::isTied();
}

bool Tuplet::isTied(size_t __pos) const {
  return NoteSequence::isTied(__pos);
}

bool Tuplet::hasDuration() const {
  return NoteSequence::hasDuration();
}

bool Tuplet::hasDuration(size_t __pos) const {
  return NoteSequence::hasDuration(__pos);
}

bool Tuplet::hasPitch() const {
  return NoteSequence::hasPitch();
}

bool Tuplet::hasPitch(size_t __pos) const {
  return NoteSequence::hasPitch(__pos);
}

bool Tuplet::hasProperty() const {
  return NoteSequence::hasProperty();
}

bool Tuplet::hasProperty(size_t __pos) const {
  return NoteSequence::hasProperty(__pos);
}

const Duration * Tuplet::getDuration() const {
  return NoteGroup::getDuration();
}

const Duration * Tuplet::getDuration(size_t __pos) const {
  return NoteSequence::getDuration(__pos);
}

const Pitch * Tuplet::getPitch() const {
  return NoteSequence::getPitch();
}

const Pitch * Tuplet::getPitch(size_t __pos) const {
  return NoteGroup::getPitch(__pos);
}

const Property * Tuplet::getProperty() const {
  return NoteGroup::getProperty();
}

const Property * Tuplet::getProperty(size_t __pos) const {
  return NoteSequence::getProperty(__pos);
}

std::string Tuplet::getPropertyStr() const {
  std::string s;
  if (Tuplet::hasProperty()) {
    s = Tuplet::getProperty()->toString();
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
  return NoteSequence::getPitchSize();
}

int Tuplet::getDurationSize() const {
  return NoteSequence::getDurationSize();
}

int Tuplet::getPropertySize() const {
  return NoteSequence::getPropertySize();
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