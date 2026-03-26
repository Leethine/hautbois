#include "note_acciaccatura.hpp"
#include "duration.hpp"
#include "note.hpp"
#include "note_grace.hpp"
#include "pitch.hpp"
#include "property.hpp"

namespace hautbois {
namespace core {

void Acciaccatura::setNoteType(NoteType __ntype) {
}

void Acciaccatura::addPitch(Pitch * __p) {
  GraceNote::addPitch(__p);
}

void Acciaccatura::setPitch(Pitch * __p, int __pos) {
  GraceNote::setPitch(__p, __pos);
}

void Acciaccatura::addDuration(Duration * __d) {
  GraceNote::addDuration(__d);
}

void Acciaccatura::setDuration(Duration * __d, int __pos) {
  GraceNote::setDuration(__d, __pos);
}

void Acciaccatura::addProperty(Property * __p) {
  GraceNote::addProperty(__p);
}

void Acciaccatura::setProperty(Property * __p, int __pos) {
  GraceNote::setProperty(__p, __pos);
}

Pitch * Acciaccatura::getPitchMod(int __pos) {
  return GraceNote::getPitchMod(__pos);
}

Duration * Acciaccatura::getDurationMod(int __pos) {
  return GraceNote::getDurationMod(__pos);
}

Property * Acciaccatura::getPropertyMod(int __pos) {
  return GraceNote::getPropertyMod(__pos);
}

void Acciaccatura::clearPitch() {
  GraceNote::clearPitch();
}

void Acciaccatura::clearDuration() {
  GraceNote::clearDuration();
}

void Acciaccatura::clearProperty() {
  GraceNote::clearProperty();
}

void * Acciaccatura::verify(const char * __context) const {
  return GraceNote::verify(__context);
}

std::string Acciaccatura::filterProperty(const std::string& __text) const {
  return GraceNote::filterProperty(__text);
}

Acciaccatura::Acciaccatura(int __num, int __denom, const char * __pitch,
                           const std::initializer_list<const char *> __args) :
  GraceNote(NoteType::Acciaccatura, __num, __denom, __pitch, __args) {
}

Acciaccatura::Acciaccatura(int __num, int __denom, const std::string& __pitch,
                           const std::vector<std::string>& __args) :
  GraceNote(NoteType::Acciaccatura, __num, __denom, __pitch, __args) {
}

Acciaccatura::Acciaccatura(const Acciaccatura& __other) : GraceNote(NoteType::Acciaccatura) {
}

Acciaccatura::Acciaccatura(const Acciaccatura&& __other) : GraceNote(NoteType::Acciaccatura) {
}

Acciaccatura& Acciaccatura::operator=(const Acciaccatura& __other) {
  return *this;
}

Acciaccatura::~Acciaccatura() { }

void Acciaccatura::updateDuration(const std::string& __context) {
  GraceNote::updateDuration(__context);
}

void Acciaccatura::updateDuration(const std::string& __context, size_t __pos) {
  GraceNote::updateDuration(__context, __pos);
}
  
void Acciaccatura::updatePitch(const std::string& __context) {
  GraceNote::updatePitch(__context);
}

void Acciaccatura::updatePitch(const std::string& __context, size_t __pos) {
  GraceNote::updatePitch(__context, __pos);
}

void Acciaccatura::updateProperty(const std::string& __context) {
  GraceNote::updateProperty(__context);
}

void Acciaccatura::updateProperty(const std::string& __context, size_t __pos) {
  GraceNote::updateProperty(__context, __pos);
}

void Acciaccatura::setTied() {
  GraceNote::setTied();
}

void Acciaccatura::setTied(size_t __pos) {
  GraceNote::setTied(__pos);
}

void Acciaccatura::setUntied() {
  GraceNote::setUntied();
}

void Acciaccatura::setUntied(size_t __pos) {
  GraceNote::setUntied(__pos);
}

int Acciaccatura::getSize() const {
  return GraceNote::getSize();
}

bool Acciaccatura::isValid() const {
  return GraceNote::isValid();
}

bool Acciaccatura::isTied() const {
  return GraceNote::isTied();
}

bool Acciaccatura::isTied(size_t __pos) const {
  return GraceNote::isTied(__pos);
}

bool Acciaccatura::hasDuration() const {
  return GraceNote::hasDuration();
}

bool Acciaccatura::hasDuration(size_t __pos) const {
  return GraceNote::hasDuration(__pos);
}

bool Acciaccatura::hasPitch() const {
  return GraceNote::hasPitch();
}

bool Acciaccatura::hasPitch(size_t __pos) const {
  return GraceNote::hasPitch(__pos);
}

bool Acciaccatura::hasProperty() const {
  return GraceNote::hasProperty();
}

bool Acciaccatura::hasProperty(size_t __pos) const {
  return GraceNote::hasProperty(__pos);
}

const Duration * Acciaccatura::getDuration() const {
  return GraceNote::getDuration();
}

const Duration * Acciaccatura::getDuration(size_t __pos) const {
  return GraceNote::getDuration(__pos);
}

const Pitch * Acciaccatura::getPitch() const {
  return GraceNote::getPitch();
}

const Pitch * Acciaccatura::getPitch(size_t __pos) const {
  return GraceNote::getPitch(__pos);
}

const Property * Acciaccatura::getProperty() const {
  return GraceNote::getProperty();
}

const Property * Acciaccatura::getProperty(size_t __pos) const {
  return GraceNote::getProperty(__pos);
}

std::string Acciaccatura::getPropertyStr() const {
  return GraceNote::getPropertyStr();
}

std::string Acciaccatura::getPropertyStr(size_t __pos) const {
  return GraceNote::getPropertyStr(__pos);
}

int Acciaccatura::getPitchSize() const {
  return GraceNote::getPitchSize();
}

int Acciaccatura::getDurationSize() const {
  return GraceNote::getDurationSize();
}

int Acciaccatura::getPropertySize() const {
  return GraceNote::getPropertySize();
}

void Acciaccatura::modify(const std::string& __context) {
}

std::string Acciaccatura::toString() const {
  return GraceNote::toString();
}

void * Acciaccatura::toStream(const std::string& __context, void * __ostream) const {
  return nullptr; 
}

} // namespace core
} // namespace hautbois