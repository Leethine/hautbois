#include "note_grace.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "utility/hbexcept.hpp"

namespace hautbois {
namespace core {

void GraceNote::addPitch(Pitch * __p) {
  NoteSequence::addPitch(__p);
}

void GraceNote::setPitch(Pitch * __p, int pos) {
  NoteSequence::setPitch(__p, pos);
}

void GraceNote::addDuration(Duration *__d) {
  NoteSequence::addDuration(__d);
}

void GraceNote::setDuration(Duration *__d, int pos) {
  NoteGroup::setDuration(__d, pos);
}

void GraceNote::addProperty(Property *__p) {
  NoteSequence::addProperty(__p);
}

void GraceNote::setProperty(Property *__p, int pos) {
  NoteSequence::setProperty(__p, pos);
}

Pitch * GraceNote::getPitchyMod(int pos) {
  return NoteSequence::getPitchyMod(pos);
}

Duration * GraceNote::getDurationMod(int pos) {
  return NoteSequence::getDurationMod(pos);
}

Property * GraceNote::getPropertyMod(int pos) {
  return NoteSequence::getPropertyMod(pos);
}

void GraceNote::clearPitch() {
  NoteSequence::clearPitch();
}

void GraceNote::clearDuration() {
  NoteSequence::clearDuration();
}

void GraceNote::clearProperty() {
  NoteSequence::clearProperty();
}

std::string GraceNote::filterProperty(const std::string& __text) const {
  std::string s (__text);
  return s;
}

GraceNote::GraceNote(NoteType __type, int __num, int __denom, const char * __pitch,
                     const std::initializer_list<const char *> __args) :
  NoteSequence(__pitch, __num, __denom, __args, __type, 0) {
}

GraceNote::GraceNote(int __num, int __denom, const char * __pitch,
                     const std::initializer_list<const char *> __args) :
  NoteSequence(__pitch, __num, __denom, __args, NoteType::Grace, 0) {
}

GraceNote::GraceNote(int __num, int __denom, const std::string& __pitch,
                     const std::vector<std::string>& __args) :
  NoteSequence(__pitch, __num, __denom, __args, NoteType::Grace, 0) {
}

GraceNote::~GraceNote() {
}

void GraceNote::updateDuration(const std::string& __context) {
}

void GraceNote::updateDuration(const std::string& __context, size_t __pos) {
}

void GraceNote::updatePitch(const std::string& __context) {
}

void GraceNote::updatePitch(const std::string& __context, size_t __pos) {
}

void GraceNote::updateProperty(const std::string& __context) {
  if (!__context.empty()) {
    Property * p = new Property(__context);
    NoteGroup::setProperty(p, -1);
  }
  else {
    NoteGroup::setProperty(nullptr, -1);
  }
}

void GraceNote::updateProperty(const std::string& __context, size_t __pos) {
  if (!__context.empty()) {
    Property * p = new Property(__context);
    NoteSequence::setProperty(p, __pos);
  }
  else {
    NoteSequence::setProperty(nullptr, -__pos);
  }
}

void GraceNote::setTied() {
  NoteSequence::setTied();
}

void GraceNote::setTied(size_t __pos) {
  NoteGroup::setTied(__pos);
}

void GraceNote::setUntied() {
  NoteSequence::setUntied();
}

void GraceNote::setUntied(size_t __pos) {
  NoteGroup::setUntied(__pos);
}

int GraceNote::getSize() const {
  return NoteSequence::getPitchSize();
}

bool GraceNote::isValid() const {
  return NoteSequence::hasPitch() && NoteSequence::isValid();
}

bool GraceNote::isTied() const {
  return NoteSequence::isTied();
}

bool GraceNote::isTied(size_t __pos) const {
  return NoteGroup::isTied(__pos);
}

bool GraceNote::hasDuration() const {
  return NoteGroup::hasDuration();
}

bool GraceNote::hasDuration(size_t __pos) const {
  return NoteSequence::hasDuration(__pos);
}

bool GraceNote::hasPitch() const {
  return NoteSequence::hasPitch();
}

bool GraceNote::hasPitch(size_t __pos) const {
  return NoteGroup::hasPitch(__pos);
}

bool GraceNote::hasProperty() const {
  return NoteGroup::hasProperty();
}

bool GraceNote::hasProperty(size_t __pos) const {
  return NoteSequence::hasProperty(__pos);
}

const Duration * GraceNote::getDuration() const {
  return NoteGroup::getDuration();
}

const Duration * GraceNote::getDuration(size_t __pos) const {
  return NoteSequence::getDuration(__pos);
}

const Pitch * GraceNote::getPitch() const {
  return NoteSequence::getPitch();
}

const Pitch * GraceNote::getPitch(size_t __pos) const {
  return NoteGroup::getPitch(__pos);
}

const Property * GraceNote::getProperty() const {
  return NoteGroup::getProperty();
}

const Property * GraceNote::getProperty(size_t __pos) const {
  return NoteSequence::getProperty(__pos);
}

std::string GraceNote::getPropertyStr() const {
  std::string s;
  if (GraceNote::getProperty()) {
    s = GraceNote::getProperty()->toString();
  }
  return s;
}

std::string GraceNote::getPropertyStr(size_t __pos) const {
  std::string s;
  if (GraceNote::getProperty(__pos)) {
    s = GraceNote::getProperty(__pos)->toString();
  }
  return s;
}

int GraceNote::getPitchSize() const {
  return NoteGroup::getPitchSize();
}

int GraceNote::getDurationSize() const {
  return NoteSequence::getDurationSize();
}

int GraceNote::getPropertySize() const {
  return NoteSequence::getPropertySize();
}

void GraceNote::modify(const std::string& __context) {
}

std::string GraceNote::toString() const {
  std::string s = "N/A";
  if (GraceNote::isValid()) {
    s = "(";
    for (int i=0; i<GraceNote::getPitchSize(); i++) {
      if (GraceNote::hasPitch(i)) {
        s += GraceNote::getPitch(i)->toString() + ",1/";
      }
      if (GraceNote::hasDuration(i)) {
        s += std::to_string(GraceNote::getDuration(i)->getDenom());
      }
      s += ",";
    }
    s = ") ";
    if (GraceNote::hasPitch()) {
      s += GraceNote::getPitch()->toString() + ",";
    }
    if (GraceNote::hasDuration()) {
      s += GraceNote::getDuration()->toString();
    }
  }
  return s;
}

void * GraceNote::toStream(const std::string& __context, void * __ostream) const {
  return nullptr;
}

} // namespace core
} // namespace hautbois