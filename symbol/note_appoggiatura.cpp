#include "note_appoggiatura.hpp"
#include "duration.hpp"
#include "note.hpp"
#include "note_grace.hpp"
#include "pitch.hpp"
#include "property.hpp"

namespace hautbois {
namespace core {

void Appoggiatura::setNoteType(NoteType __ntype) {
}

void Appoggiatura::addPitch(Pitch * __p) {
  GraceNote::addPitch(__p);
}

void Appoggiatura::setPitch(Pitch * __p, int __pos) {
  GraceNote::setPitch(__p, __pos);
}

void Appoggiatura::addDuration(Duration * __d) {
  GraceNote::addDuration(__d);
}

void Appoggiatura::setDuration(Duration * __d, int __pos) {
  GraceNote::setDuration(__d, __pos);
}

void Appoggiatura::addProperty(Property * __p) {
  GraceNote::addProperty(__p);
}

void Appoggiatura::setProperty(Property * __p, int __pos) {
  GraceNote::setProperty(__p, __pos);
}

Pitch * Appoggiatura::getPitchMod(int __pos) {
  return GraceNote::getPitchMod(__pos);
}

Duration * Appoggiatura::getDurationMod(int __pos) {
  return GraceNote::getDurationMod(__pos);
}

Property * Appoggiatura::getPropertyMod(int __pos) {
  return GraceNote::getPropertyMod(__pos);
}

void Appoggiatura::clearPitch() {
  GraceNote::clearPitch();
}

void Appoggiatura::clearDuration() {
  GraceNote::clearDuration();
}

void Appoggiatura::clearProperty() {
  GraceNote::clearProperty();
}

void * Appoggiatura::verify(const char * __context) const {
  return GraceNote::verify(__context);
}

std::string Appoggiatura::filterProperty(const std::string& __text) const {
  return GraceNote::filterProperty(__text);
}

Appoggiatura::Appoggiatura(int __num, int __denom, const char * __pitch,
                           const std::initializer_list<const char *> __args) :
  GraceNote(NoteType::Appoggiatura, __num, __denom, __pitch, __args) {
}

Appoggiatura::Appoggiatura(int __num, int __denom, const std::string& __pitch,
                           const std::vector<std::string>& __args) :
  GraceNote(NoteType::Appoggiatura, __num, __denom, __pitch, __args) {
}

Appoggiatura::Appoggiatura(const Appoggiatura& __other) : GraceNote(NoteType::Appoggiatura) {
}

Appoggiatura::Appoggiatura(const Appoggiatura&& __other) : GraceNote(NoteType::Appoggiatura) {
}

Appoggiatura& Appoggiatura::operator=(const Appoggiatura& __other) {
  return *this;
}

Appoggiatura::~Appoggiatura() { }

void Appoggiatura::updateDuration(const std::string& __context) {
  GraceNote::updateDuration(__context);
}

void Appoggiatura::updateDuration(const std::string& __context, size_t __pos) {
  GraceNote::updateDuration(__context, __pos);
}
  
void Appoggiatura::updatePitch(const std::string& __context) {
  GraceNote::updatePitch(__context);
}

void Appoggiatura::updatePitch(const std::string& __context, size_t __pos) {
  GraceNote::updatePitch(__context, __pos);
}

void Appoggiatura::updateProperty(const std::string& __context) {
  GraceNote::updateProperty(__context);
}

void Appoggiatura::updateProperty(const std::string& __context, size_t __pos) {
  GraceNote::updateProperty(__context, __pos);
}

void Appoggiatura::setTied() {
  GraceNote::setTied();
}

void Appoggiatura::setTied(size_t __pos) {
  GraceNote::setTied(__pos);
}

void Appoggiatura::setUntied() {
  GraceNote::setUntied();
}

void Appoggiatura::setUntied(size_t __pos) {
  GraceNote::setUntied(__pos);
}

int Appoggiatura::getSize() const {
  return GraceNote::getSize();
}

bool Appoggiatura::isValid() const {
  return GraceNote::isValid();
}

bool Appoggiatura::isTied() const {
  return GraceNote::isTied();
}

bool Appoggiatura::isTied(size_t __pos) const {
  return GraceNote::isTied(__pos);
}

bool Appoggiatura::hasDuration() const {
  return GraceNote::hasDuration();
}

bool Appoggiatura::hasDuration(size_t __pos) const {
  return GraceNote::hasDuration(__pos);
}

bool Appoggiatura::hasPitch() const {
  return GraceNote::hasPitch();
}

bool Appoggiatura::hasPitch(size_t __pos) const {
  return GraceNote::hasPitch(__pos);
}

bool Appoggiatura::hasProperty() const {
  return GraceNote::hasProperty();
}

bool Appoggiatura::hasProperty(size_t __pos) const {
  return GraceNote::hasProperty(__pos);
}

const Duration * Appoggiatura::getDuration() const {
  return GraceNote::getDuration();
}

const Duration * Appoggiatura::getDuration(size_t __pos) const {
  return GraceNote::getDuration(__pos);
}

const Pitch * Appoggiatura::getPitch() const {
  return GraceNote::getPitch();
}

const Pitch * Appoggiatura::getPitch(size_t __pos) const {
  return GraceNote::getPitch(__pos);
}

const Property * Appoggiatura::getProperty() const {
  return GraceNote::getProperty();
}

const Property * Appoggiatura::getProperty(size_t __pos) const {
  return GraceNote::getProperty(__pos);
}

std::string Appoggiatura::getPropertyStr() const {
  return GraceNote::getPropertyStr();
}

std::string Appoggiatura::getPropertyStr(size_t __pos) const {
  return GraceNote::getPropertyStr(__pos);
}

int Appoggiatura::getPitchSize() const {
  return GraceNote::getPitchSize();
}

int Appoggiatura::getDurationSize() const {
  return GraceNote::getDurationSize();
}

int Appoggiatura::getPropertySize() const {
  return GraceNote::getPropertySize();
}

void Appoggiatura::modify(const std::string& __context) {
}

std::string Appoggiatura::toString() const {
  return GraceNote::toString();
}

void * Appoggiatura::toStream(const std::string& __context, void * __ostream) const {
  return nullptr; 
}

} // namespace core
} // namespace hautbois