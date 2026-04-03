#include "ly_singlenote.hpp"
#include "ly_pitch.hpp"
#include "ly_duration.hpp"
#include "ly_property.hpp"
#include "../utility/hbexcept.hpp"

#include <stdexcept>
#include <utility>

namespace hautbois {
namespace ly {

void LySingleNote::setNoteType(core::NoteType __ntype) {
  core::SingleNote::setNoteType(__ntype);
}

void LySingleNote::addPitch(core::Pitch * __p) {
  core::SingleNote::addPitch(__p);
}

void LySingleNote::setPitch(core::Pitch * __p, int __pos) {
  core::SingleNote::setPitch(__p, __pos);
}

void LySingleNote::addDuration(core::Duration * __d) {
  core::SingleNote::addDuration(__d);
}

void LySingleNote::setDuration(core::Duration * __d, int __pos) {
  core::SingleNote::setDuration(__d, __pos);
}

void LySingleNote::addProperty(core::Property * __p) {
  core::SingleNote::addProperty(__p);
}

void LySingleNote::setProperty(core::Property * __p, int __pos) {
  core::SingleNote::setProperty(__p, __pos);
}

core::Pitch * LySingleNote::getPitchMod(int __pos) {
  return core::SingleNote::getPitchMod(__pos);
}

core::Duration * LySingleNote::getDurationMod(int __pos) {
  return core::SingleNote::SingleNote::getDurationMod(__pos);
}

core::Property * LySingleNote::getPropertyMod(int __pos) {
  return core::SingleNote::getPropertyMod(__pos);
}

void LySingleNote::clearPitch() {
  core::SingleNote::clearPitch();
}

void LySingleNote::clearDuration() {
  core::SingleNote::clearDuration();
}

void LySingleNote::clearProperty() {
  core::SingleNote::clearProperty();
}

void * LySingleNote::verify(const char * __context) const {
  return nullptr;
}

std::string LySingleNote::filterProperty(const std::string& __text) const {
  std::string s;
  return s;
}

LySingleNote::LySingleNote(const std::string& __pitch, 
                           const std::string& __duration) : core::SingleNote() {
  core::Pitch * p = nullptr;
  core::Duration * d = nullptr;
  HB_NESTED_THROW_ACTION(std::invalid_argument,
    p = new LyPitch(__pitch);
    d = new LyDuration(__duration);
    ,
    LySingleNote::clearPitch();
    LySingleNote::clearDuration();
  )
  LySingleNote::addPitch(p);
  LySingleNote::addDuration(d);
}

LySingleNote::LySingleNote(const std::string& __duration) : core::SingleNote() {
  LySingleNote::setNoteType(core::NoteType::Silence);
  core::Duration * d = nullptr;
  HB_NESTED_THROW(std::invalid_argument,
    d = new LyDuration(__duration);
  )
  LySingleNote::addDuration(d);
}

LySingleNote::LySingleNote(const LySingleNote& __note) : 
  LySingleNote(std::forward<const LySingleNote>(__note)) {
}

LySingleNote::LySingleNote(const LySingleNote&& __note) : core::SingleNote() {
  LySingleNote::setNoteType(__note.getType());
  if (__note.getPitch()) {
    core::Pitch * p = new LyPitch(*(reinterpret_cast<const LyPitch *>(__note.getPitch())));
    LySingleNote::addPitch(p);
  }
  if (__note.getDuration()) {
    core::Duration * d = new LyDuration(*(reinterpret_cast<const LyDuration *>(__note.getDuration())));
    LySingleNote::addDuration(d);
  }
  if (__note.getProperty()) {
    core::Property * p = new LyProperty(*(reinterpret_cast<const LyProperty *>(__note.getProperty())));
    LySingleNote::addProperty(p);
  }
}

LySingleNote::LySingleNote(const core::SingleNote& __note) : 
  LySingleNote(std::forward<const core::SingleNote>(__note)) {
}

LySingleNote::LySingleNote(const core::SingleNote&& __note) : core::SingleNote() {
  LySingleNote::setNoteType(__note.getType());
  if (__note.getPitch()) {
    core::Pitch * p = new LyPitch(*(reinterpret_cast<const core::Pitch *>(__note.getPitch())));
    LySingleNote::addPitch(p);
  }
  if (__note.getDuration()) {
    core::Duration * d = new LyDuration(*(reinterpret_cast<const core::Duration *>(__note.getDuration())));
    LySingleNote::addDuration(d);
  }
  if (__note.getProperty()) {
    core::Property * p = new LyProperty(*(reinterpret_cast<const core::Property *>(__note.getProperty())));
    LySingleNote::addProperty(p);
  }
}

LySingleNote::~LySingleNote() {
}

void LySingleNote::updateDuration(const std::string& __context) {
  if (!__context.empty()) {
    HB_NESTED_THROW(std::invalid_argument,
      LySingleNote::getDurationMod(-1)->modify(__context.c_str());
    )
  }
}

void LySingleNote::updateDuration(const std::string& __context, size_t __pos) {
  LySingleNote::updateDuration(__context);
}
  
void LySingleNote::updatePitch(const std::string& __context) {
  if (!__context.empty()) {
    HB_NESTED_THROW(std::invalid_argument,
      LySingleNote::getPitchMod(-1)->modify(__context.c_str());
    )
  }
  if (LySingleNote::getPitch()) {
    if (LySingleNote::getPitch()->getName() == "r") {
      LySingleNote::setNoteType(core::NoteType::Rest);
    }
    else if (LySingleNote::getPitch()->getName() == "s") {
      LySingleNote::setNoteType(core::NoteType::Silence);
    }
  }
}

void LySingleNote::updatePitch(const std::string& __context, size_t __pos) {
  LySingleNote::updatePitch(__context);
}

void LySingleNote::updateProperty(const std::string& __context) {
  if (__context.empty()) {
    LySingleNote::addProperty(nullptr);
  }
  else {
    if (!LySingleNote::hasProperty()) {
      core::Property * p = new LyProperty();
      LySingleNote::addProperty(p);
    }
    HB_NESTED_THROW(std::invalid_argument,
      LySingleNote::getPropertyMod(-1)->modify(__context.c_str());
    )
  }
}

void LySingleNote::updateProperty(const std::string& __context, size_t __pos) {
  LySingleNote::updateProperty(__context);
}

void LySingleNote::setTied() {
  core::SingleNote::setTied();
}

void LySingleNote::setTied(size_t __pos) {
  core::SingleNote::setTied(__pos);
}

void LySingleNote::setUntied() {
  core::SingleNote::setUntied();
}

void LySingleNote::setUntied(size_t __pos) {
  core::SingleNote::setUntied(__pos);
}

int LySingleNote::getSize() const {
  return core::SingleNote::getSize();
}

core::NoteType LySingleNote::getType() const {
  return core::SingleNote::getType();
}

char LySingleNote::getTypeChar() const {
  return core::SingleNote::getTypeChar();
}

std::string LySingleNote::getTypeStr() const {
  return core::SingleNote::getTypeStr();
}

bool LySingleNote::isType(core::NoteType __ntype) const {
  return core::SingleNote::isType(__ntype);
}

bool LySingleNote::isSingle() const {
  return core::SingleNote::isSingle();
}

bool LySingleNote::isRest() const {
  return core::SingleNote::isRest();
}

bool LySingleNote::isSilence() const {
  return core::SingleNote::isSilence();
}

bool LySingleNote::isChord() const {
  return core::SingleNote::isChord();
}

bool LySingleNote::isTuplet() const {
  return core::SingleNote::isTuplet();
}

bool LySingleNote::isGrace() const {
  return core::SingleNote::isGrace();
}

bool LySingleNote::isAppoggiatura() const {
  return core::SingleNote::isAppoggiatura();
}

bool LySingleNote::isAcciaccatura() const {
  return core::SingleNote::isAcciaccatura();
}

bool LySingleNote::isValid() const {
  if (LySingleNote::isSingle()) {
    return core::SingleNote::isValid();
  }
  else {
    return core::SingleNote::hasDuration();
  }
}

bool LySingleNote::isTied() const {
  return core::SingleNote::isTied();
}

bool LySingleNote::isTied(size_t __pos) const {
  return core::SingleNote::isTied(__pos);
}

bool LySingleNote::hasDuration() const {
  return core::SingleNote::hasDuration();
}

bool LySingleNote::hasDuration(size_t __pos) const {
  return core::SingleNote::hasDuration(__pos);
}
 
bool LySingleNote::hasPitch() const {
  return core::SingleNote::hasPitch();
}

bool LySingleNote::hasPitch(size_t __pos) const {
  return core::SingleNote::hasPitch(__pos);
}

bool LySingleNote::hasProperty() const {
  return core::SingleNote::hasProperty();
}

bool LySingleNote::hasProperty(size_t __pos) const {
  return core::SingleNote::hasProperty(__pos);
}

const core::Duration * LySingleNote::getDuration() const {
  return core::SingleNote::getDuration();
}

const core::Duration * LySingleNote::getDuration(size_t __pos) const {
  return core::SingleNote::getDuration(__pos);
}

const core::Pitch * LySingleNote::getPitch() const {
  return core::SingleNote::getPitch();
}

const core::Pitch * LySingleNote::getPitch(size_t __pos) const {
  return core::SingleNote::getPitch(__pos);
}

const core::Property * LySingleNote::getProperty() const {
  return core::SingleNote::getProperty();
}

const core::Property * LySingleNote::getProperty(size_t __pos) const {
  return core::SingleNote::getProperty(__pos);
}

std::string LySingleNote::getPropertyStr() const {
  std::string s;
  if (LySingleNote::getProperty()) {
    s = LySingleNote::getProperty()->toString();
  }
  return s;
}

std::string LySingleNote::getPropertyStr(size_t __pos) const {
  return core::SingleNote::getPropertyStr(__pos);
}

int LySingleNote::getPitchSize() const {
  return core::SingleNote::getPitchSize();
}

int LySingleNote::getDurationSize() const {
  return core::SingleNote::getDurationSize();
}

int LySingleNote::getPropertySize() const {
  return core::SingleNote::getPropertySize();
}

void LySingleNote::modify(const std::string& __context) {
  if (__context == "\\rest") {
    LySingleNote::getPitchMod(-1)->modify("r");
    LySingleNote::setNoteType(core::NoteType::Rest);
  }
}

std::string LySingleNote::toString() const {
  std::string s;
  if (LySingleNote::isSilence())   { s += "s"; }
  else if (LySingleNote::isRest()) { s += "r"; }
  else {
    if (LySingleNote::getPitch())  {
      s += LySingleNote::getPitch()->toString();
    }
  }
  if (LySingleNote::getDuration()) {
    s += LySingleNote::getDuration()->toString();
  }
  return s;
}

void * LySingleNote::toStream(const std::string& __context, void * __ostream) const {
  return nullptr;
}

} // namespace hautbois
} // namespace core