#include "ly_chord.hpp"
#include "ly_pitch.hpp"
#include "ly_duration.hpp"
#include "ly_property.hpp"
#include "../utility/hbexcept.hpp"
#include <stdexcept>
#include <utility>

namespace hautbois {
namespace ly {

void LyChord::setNoteType(core::NoteType __ntype) {
  core::Chord::setNoteType(__ntype);
}

void LyChord::addPitch(core::Pitch * __p) {
  core::Chord::addPitch(__p);
}

void LyChord::setPitch(core::Pitch * __p, int __pos) {
  core::Chord::setPitch(__p, __pos);
}

void LyChord::addDuration(core::Duration * __d) {
  core::Chord::addDuration(__d);
}

void LyChord::setDuration(core::Duration * __d, int __pos) {
  core::Chord::setDuration(__d, __pos);
}

void LyChord::addProperty(core::Property * __p) {
  core::Chord::addProperty(__p);
}

void LyChord::setProperty(core::Property * __p, int __pos) {
  core::Chord::setProperty(__p, __pos);
}

core::Pitch * LyChord::getPitchMod(int __pos) {
  return core::Chord::getPitchMod(__pos);
}

core::Duration * LyChord::getDurationMod(int __pos) {
  return core::Chord::getDurationMod(__pos);
}

core::Property * LyChord::getPropertyMod(int __pos) {
  return core::Chord::getPropertyMod(__pos);
}

void LyChord::clearPitch() {
  core::Chord::clearPitch();
}

void LyChord::clearDuration() {
  core::Chord::clearDuration();
}

void LyChord::clearProperty() {
  core::Chord::clearProperty();
}

void * LyChord::verify(const char * __context) const {
  return nullptr;
}

std::string LyChord::filterProperty(const std::string& __text) const {
  std::string s;
  return s;
}

LyChord::LyChord(const std::string __value) : core::Chord() {
  core::Duration * d = nullptr;
  HB_NESTED_THROW(std::invalid_argument,
    d = new LyDuration(__value);
  )
  LyChord::addDuration(d);
}

LyChord::LyChord(const std::vector<std::string>& __pitches, 
                 const std::string __value) : LyChord(__value) {
  for (auto& pitch : __pitches) {
    core::Pitch * p = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument,
      p = new LyPitch(pitch);
      ,
      LyChord::clearDuration();
      LyChord::clearPitch();
    )
    LyChord::addPitch(p);
  }
}

LyChord::LyChord(const std::initializer_list<const char *> __pitches, 
                 const std::string __value) : LyChord(__value) {
  for (auto& ch_ptr : __pitches) {
    std::string pitch(ch_ptr);
    core::Pitch * p = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument,
      p = new LyPitch(pitch);
      ,
      LyChord::clearDuration();
      LyChord::clearPitch();
    )
    LyChord::addPitch(p);
  }
}

LyChord::LyChord(const LyChord& __note) : LyChord(std::forward<const LyChord>(__note)) {
}

LyChord::LyChord(const LyChord&& __note) : core::Chord() {
  if (__note.getDuration()) {
    core::Duration * d = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument,
      d = new LyDuration(*__note.getDuration());
      ,
      LyChord::clearDuration();
      LyChord::clearPitch();
      LyChord::clearProperty();
    )
    LyChord::addDuration(d);
  }
  if (__note.getProperty()) {
    core::Property * p = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument,
      p = new LyProperty(*__note.getProperty());
      ,
      LyChord::clearDuration();
      LyChord::clearPitch();
      LyChord::clearProperty();
    )
    LyChord::addProperty(p);
  }
  for (int i=0; i < __note.getPitchSize(); i++) {
    if (__note.hasPitch(i)) {
      core::Pitch * p = nullptr;
      HB_NESTED_THROW_ACTION(std::invalid_argument,
        p = new LyPitch(*__note.getPitch(i));
        ,
        LyChord::clearDuration();
        LyChord::clearPitch();
        LyChord::clearProperty();
      )
      LyChord::addPitch(p);
    }
  }
}

LyChord::LyChord(const core::Chord& __note) :
  LyChord(std::forward<const core::Chord>(__note)) {
}

LyChord::LyChord(const core::Chord&& __note) : core::Chord() {
  if (__note.getDuration()) {
    core::Duration * d = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument,
      d = new LyDuration(*__note.getDuration());
      ,
      LyChord::clearDuration();
      LyChord::clearPitch();
      LyChord::clearProperty();
    )
    LyChord::addDuration(d);
  }
  if (__note.getProperty()) {
    core::Property * p = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument,
      p = new LyProperty(*__note.getProperty());
      ,
      LyChord::clearDuration();
      LyChord::clearPitch();
      LyChord::clearProperty();
    )
    LyChord::addProperty(p);
  }
  for (int i=0; i < __note.getPitchSize(); i++) {
    if (__note.hasPitch(i)) {
      core::Pitch * p = nullptr;
      HB_NESTED_THROW_ACTION(std::invalid_argument,
        p = new LyPitch(*__note.getPitch(i));
        ,
        LyChord::clearDuration();
        LyChord::clearPitch();
        LyChord::clearProperty();
      )
      LyChord::addPitch(p);
    }
  }
}

LyChord::~LyChord() {
  LyChord::clearDuration();
  LyChord::clearPitch();
  LyChord::clearProperty();
}

void LyChord::updateDuration(const std::string& __context) {
  if (!__context.empty()) {
    HB_NESTED_THROW(std::invalid_argument,
      LyChord::getDurationMod(-1)->modify(__context.c_str());
    )
  }
}

void LyChord::updateDuration(const std::string& __context, size_t __pos) {
  LyChord::updateDuration(__context);
}

void LyChord::updatePitch(const std::string& __context) {
  LyChord::updatePitch(__context, 0);
}

void LyChord::updatePitch(const std::string& __context, size_t __pos) {
  if (__pos < LyChord::getPitchSize()) {
    if (LyChord::getPropertyMod(__pos)) {
      HB_NESTED_THROW(std::invalid_argument,
        LyChord::getPitchMod(-1)->modify(__context.c_str());
      )
    }
  }
}

void LyChord::updateProperty(const std::string& __context) {
  if (__context.empty()) {
    LyChord::addProperty(nullptr);
  }
  else {
    if (!LyChord::hasProperty()) {
      core::Property * p = new LyProperty();
      LyChord::addProperty(p);
    }
    HB_NESTED_THROW(std::invalid_argument,
      LyChord::getPropertyMod(-1)->modify(__context.c_str());
    )
  }
}

void LyChord::updateProperty(const std::string& __context, size_t __pos) {
  LyChord::updateProperty(__context);
}

void LyChord::setTied() {
  core::Chord::setTied();
}

void LyChord::setTied(size_t __pos) {
  core::Chord::setTied(__pos);
}

void LyChord::setUntied() {
  core::Chord::setUntied();
}

void LyChord::setUntied(size_t __pos) {
  core::Chord::setUntied(__pos);
}

int LyChord::getSize() const {
  return LyChord::getPitchSize();
}

core::NoteType LyChord::getType() const {
  return core::Chord::getType();
}

char LyChord::getTypeChar() const {
  return core::Chord::getTypeChar();
}

std::string LyChord::getTypeStr() const {
  return core::Chord::getTypeStr();
}

bool LyChord::isType(core::NoteType __ntype) const {
  return core::Chord::isType(__ntype);
}

bool LyChord::isSingle() const {
  return core::Chord::isSingle();
}

bool LyChord::isRest() const {
  return core::Chord::isRest();
}

bool LyChord::isSilence() const {
  return core::Chord::isSilence();
}

bool LyChord::isChord() const {
  return core::Chord::isChord();
}

bool LyChord::isTuplet() const {
  return core::Chord::isTuplet();
}

bool LyChord::isGrace() const {
  return core::Chord::isGrace();
}

bool LyChord::isAppoggiatura() const {
  return core::Chord::isAppoggiatura();
}

bool LyChord::isAcciaccatura() const {
  return core::Chord::isAcciaccatura();
}

bool LyChord::isValid() const {
  return core::Chord::isValid();
}

bool LyChord::isTied() const {
  return core::Chord::isTied();
}

bool LyChord::isTied(size_t __pos) const {
  return core::Chord::isTied();
}

bool LyChord::hasDuration() const {
  return core::Chord::hasDuration();
}

bool LyChord::hasDuration(size_t __pos) const {
  return core::Chord::hasDuration();
}

bool LyChord::hasPitch() const {
  return core::Chord::hasPitch();
}

bool LyChord::hasPitch(size_t __pos) const {
  return core::Chord::hasPitch();
}

bool LyChord::hasProperty() const {
  return core::Chord::hasProperty();
}

bool LyChord::hasProperty(size_t __pos) const {
  return core::Chord::hasProperty();
}

const core::Duration * LyChord::getDuration() const {
  return core::Chord::getDuration();
}

const core::Duration * LyChord::getDuration(size_t __pos) const {
  return core::Chord::getDuration(__pos);
}

const core::Pitch * LyChord::getPitch() const {
  return core::Chord::getPitch(); 
}

const core::Pitch * LyChord::getPitch(size_t __pos) const {
  return core::Chord::getPitch(__pos);
}

const core::Property * LyChord::getProperty() const {
  return core::Chord::getProperty();
}

const core::Property * LyChord::getProperty(size_t __pos) const {
  return core::Chord::getProperty(__pos);
}

std::string LyChord::getPropertyStr() const {
  return core::Chord::getPropertyStr();
}

std::string LyChord::getPropertyStr(size_t __pos) const {
  return core::Chord::getPropertyStr(__pos);
}

int LyChord::getPitchSize() const {
  return core::Chord::getPitchSize();
}

int LyChord::getDurationSize() const {
  return core::Chord::getDurationSize();
}

int LyChord::getPropertySize() const {
  return core::Chord::getPropertySize();
}

void LyChord::modify(const std::string& __context) {
  return core::Chord::modify(__context);
}

std::string LyChord::toString() const {
  std::string s = "<";
  for (int i = 0; i < LyChord::getPitchSize(); i++) {
    if (LyChord::getPitch(i)) {
      s += LyChord::getPitch(i)->toString();
      s += " ";
    }
  }
  if (LyChord::getPitchSize() > 0) {
    s.pop_back();
  }
  s += ">";
  if (LyChord::getDuration()) {
    s += LyChord::getDuration()->toString();
  }
  return s;
}

void * LyChord::toStream(const std::string& __context, void * __ostream) const {
  return nullptr;
}

} // namespace ly
} // namespace hautbois