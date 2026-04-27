#include "ly_tuplet.hpp"
#include "ly_pitch.hpp"
#include "ly_duration.hpp"
#include "ly_property.hpp"
#include "../utility/hbexcept.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>
#include <algorithm>
#include <cctype>

namespace hautbois {
namespace ly {

void LyTuplet::setNoteType(core::NoteType __ntype) {
  core::Tuplet::setNoteType(__ntype);
}

void LyTuplet::addPitch(core::Pitch * __p) {
  core::Tuplet::addPitch(__p);
}

void LyTuplet::setPitch(core::Pitch * __p, int __pos) {
  core::Tuplet::setPitch(__p, __pos);
}

void LyTuplet::addDuration(core::Duration * __d) {
  core::Tuplet::addDuration(__d);
}

void LyTuplet::setDuration(core::Duration * __d, int __pos) {
  core::Tuplet::setDuration(__d, __pos);
}

void LyTuplet::addProperty(core::Property * __p) {
  core::Tuplet::addProperty(__p);
}

void LyTuplet::setProperty(core::Property * __p, int __pos) {
  core::Tuplet::setProperty(__p, __pos);
}

core::Pitch * LyTuplet::getPitchMod(int __pos) {
  return core::Tuplet::getPitchMod(__pos);
}

core::Duration * LyTuplet::getDurationMod(int __pos) {
  return core::Tuplet::getDurationMod(__pos);
}

core::Property * LyTuplet::getPropertyMod(int __pos) {
  return core::Tuplet::getPropertyMod(__pos);
}

void LyTuplet::clearPitch() {
  core::Tuplet::clearPitch();
}

void LyTuplet::clearDuration() {
  core::Tuplet::clearDuration();
}

void LyTuplet::clearProperty() {
  core::Tuplet::clearProperty();
}

void * LyTuplet::verify(const char * __context) const {
  return nullptr;
}

std::string LyTuplet::filterProperty(const std::string& __text) const {
  std::string s(__text);
  return s;
}

LyTuplet::LyTuplet(const std::string& __value, const size_t __count, const size_t __fraction) :
  core::Tuplet(__count), _fraction(__fraction) {
  // set the total value of the note
  core::Duration * d_main = nullptr;
  HB_NESTED_THROW_ACTION(std::invalid_argument,
    d_main = new LyDuration(__value);
    ,
    LyTuplet::clearPitch();
    LyTuplet::clearDuration();
    LyTuplet::clearProperty();
  )
  LyTuplet::setDuration(d_main, -1);
}

LyTuplet::LyTuplet(const std::string& __value, const std::vector<std::string>& __args,
                   const size_t __count, const size_t __fraction) :
  LyTuplet(__value, __count, __fraction) {
  // read the pitch/value pair list, the total value was already handled
  for (const auto arg : __args) {
    // find the number as separater of pitch name and value
    const auto it = std::find_if(arg.begin(), arg.end(), 
      [](const char c) {
        return std::isdigit(c);
      }
    );
    // process pitch/value pair
    if (it != arg.end()) {
      size_t pos = it - arg.begin();
      std::string note_name = arg.substr(0, pos);
      std::string note_value = arg.substr(pos);
      core::Pitch * p = nullptr;
      core::Duration * d = nullptr;
      HB_NESTED_THROW_MSG_ACTION(std::invalid_argument, "Invalid note: " + arg,
        p = new LyPitch(note_name);
        d = new LyDuration(note_value);
        ,
        LyTuplet::clearPitch();
        LyTuplet::clearDuration();
        LyTuplet::clearProperty();
      )
      LyTuplet::addPitch(p);
      LyTuplet::addDuration(d);
    }
    else {
      HB_THROW_MSG(std::invalid_argument, "Missing value: " + arg);
    }
  }
}

LyTuplet::LyTuplet(const std::string& __value,
                   const std::initializer_list<const char *>& __args,
                   const size_t __count, const size_t __fraction) :
  LyTuplet(__value, __count, __fraction) {
  for (const auto arg_char_array : __args) {
    std::string arg (arg_char_array); // convert const char * to str
    const auto it = std::find_if(arg.begin(), arg.end(), 
      [](const char c) {
        return std::isdigit(c);
      }
    );
    if (it != arg.end()) {
      size_t pos = it - arg.begin();
      std::string note_name = arg.substr(0, pos);
      std::string note_value = arg.substr(pos);
      core::Pitch * p = nullptr;
      core::Duration * d = nullptr;
      HB_NESTED_THROW_MSG_ACTION(std::invalid_argument, "Invalid note: " + arg,
        p = new LyPitch(note_name);
        d = new LyDuration(note_value);
        ,
        LyTuplet::clearPitch();
        LyTuplet::clearDuration();
        LyTuplet::clearProperty();
      )
    }
    else {
      HB_THROW_MSG(std::invalid_argument, "Missing value: " + arg);
    }
  }
}

LyTuplet::LyTuplet(const std::string& __value, 
                   const std::vector<std::string>& __args,
                   const size_t __count) :
  LyTuplet(__value, __args, __count, 2) {
}

LyTuplet::LyTuplet(const std::string& __value,
                   const std::initializer_list<const char *>& __args,
                   const size_t __count) :
  LyTuplet(__value, __args, __count, 2) {
}

//LyTuplet::LyTuplet(const LyTuplet& __note);

//LyTuplet::LyTuplet(const LyTuplet&& __note);

//LyTuplet::LyTuplet(const core::Tuplet& __note);

//LyTuplet::LyTuplet(const core::Tuplet&& __note);

LyTuplet::~LyTuplet() {
  LyTuplet::clearPitch();
  LyTuplet::clearDuration();
  LyTuplet::clearProperty();
}

void LyTuplet::updateDuration(const std::string& __context) {
  if (!__context.empty() && LyTuplet::getDurationMod(-1)) {
    HB_NESTED_THROW(std::invalid_argument,
      LyTuplet::getDurationMod(-1)->modify(__context.c_str());
    )
  }
}

void LyTuplet::updateDuration(const std::string& __context, size_t __pos) {
  if (!__context.empty() && LyTuplet::getDurationMod(__pos)) {
    HB_NESTED_THROW(std::invalid_argument,
      LyTuplet::getDurationMod(__pos)->modify(__context.c_str());
    )
  }
}

void LyTuplet::updatePitch(const std::string& __context) {
  LyTuplet::updatePitch(__context, 0);
}

void LyTuplet::updatePitch(const std::string& __context, size_t __pos) {
  if (!__context.empty() && LyTuplet::getPitchMod(__pos)) {
    HB_NESTED_THROW(std::invalid_argument,
      LyTuplet::getPitchMod(__pos)->modify(__context.c_str());
    )
  }
}

void LyTuplet::updateProperty(const std::string& __context) {
  if (__context.empty()) {
    LyTuplet::setProperty(nullptr, -1);
  }
  else {
    if (LyTuplet::hasProperty()) {
      core::Property * p = new LyProperty();
      LyTuplet::setProperty(p, -1);
    }
    HB_NESTED_THROW(std::invalid_argument,
      LyTuplet::getPropertyMod(-1)->modify(__context.c_str());
    )
  }
}

void LyTuplet::updateProperty(const std::string& __context, size_t __pos) {
  if (__context.empty()) {
    LyTuplet::setProperty(nullptr, __pos);
  }
  else {
    if (LyTuplet::hasProperty(__pos)) {
      core::Property * p = new LyProperty();
      LyTuplet::setProperty(p, __pos);
    }
    HB_NESTED_THROW(std::invalid_argument,
      LyTuplet::getPropertyMod(__pos)->modify(__context.c_str());
    )
  }
}

void LyTuplet::setTied() {
  core::Tuplet::setTied();
}

void LyTuplet::setTied(size_t __pos) {
  core::Tuplet::setTied(__pos);
}

void LyTuplet::setUntied() {
  core::Tuplet::setUntied();
}

void LyTuplet::setUntied(size_t __pos) {
  core::Tuplet::setUntied(__pos);
}

int LyTuplet::getSize() const {
  return core::Tuplet::getSize();
}

core::NoteType LyTuplet::getType() const {
  return core::Tuplet::getType();
}

char LyTuplet::getTypeChar() const {
  return core::Tuplet::getTypeChar();
}

std::string LyTuplet::getTypeStr() const {
  return core::Tuplet::getTypeStr();
}

bool LyTuplet::isType(core::NoteType __ntype) const {
  return core::Tuplet::isType(__ntype);
}

bool LyTuplet::isSingle() const {
  return core::Tuplet::isSingle();
}

bool LyTuplet::isRest() const {
  return core::Tuplet::isRest();
}

bool LyTuplet::isSilence() const {
  return core::Tuplet::isSilence();
}

bool LyTuplet::isChord() const {
  return core::Tuplet::isChord();
}

bool LyTuplet::isTuplet() const {
  return core::Tuplet::isTuplet();
}

bool LyTuplet::isGrace() const {
  return core::Tuplet::isGrace();
}

bool LyTuplet::isAppoggiatura() const {
  return core::Tuplet::isAppoggiatura();
}

bool LyTuplet::isAcciaccatura() const {
  return core::Tuplet::isAcciaccatura();
}

bool LyTuplet::isValid() const {
  return core::Tuplet::isValid();
}

bool LyTuplet::isTied() const {
  return core::Tuplet::isTied();
}

bool LyTuplet::isTied(size_t __pos) const {
  return core::Tuplet::isTied();
}

bool LyTuplet::hasDuration() const {
  return core::Tuplet::hasDuration();
}

bool LyTuplet::hasDuration(size_t __pos) const {
  return core::Tuplet::hasDuration(__pos);
}

bool LyTuplet::hasPitch() const {
  return core::Tuplet::hasPitch();
}

bool LyTuplet::hasPitch(size_t __pos) const {
  return core::Tuplet::hasPitch(__pos);
}

bool LyTuplet::hasProperty() const {
  return core::Tuplet::hasProperty();
}

bool LyTuplet::hasProperty(size_t __pos) const {
  return core::Tuplet::hasProperty(__pos);
}

const core::Duration * LyTuplet::getDuration() const {
  return core::Tuplet::getDuration();
}

const core::Duration * LyTuplet::getDuration(size_t __pos) const {
  return core::Tuplet::getDuration(__pos);
}

const core::Pitch * LyTuplet::getPitch() const {
  return core::Tuplet::getPitch();
}

const core::Pitch * LyTuplet::getPitch(size_t __pos) const {
  return core::Tuplet::getPitch(__pos);
}

const core::Property * LyTuplet::getProperty() const {
  return core::Tuplet::getProperty();
}

const core::Property * LyTuplet::getProperty(size_t __pos) const {
  return core::Tuplet::getProperty(__pos);
}

std::string LyTuplet::getPropertyStr() const {
  return core::Tuplet::getPropertyStr();
}

std::string LyTuplet::getPropertyStr(size_t __pos) const {
  return core::Tuplet::getPropertyStr(__pos);
}

int LyTuplet::getPitchSize() const {
  return core::Tuplet::getPitchSize();
}

int LyTuplet::getDurationSize() const {
  return core::Tuplet::getDurationSize();
}

int LyTuplet::getPropertySize() const {
  return core::Tuplet::getPropertySize();
}

void LyTuplet::modify(const std::string& __context) {
  return core::Tuplet::modify(__context);
}

std::string LyTuplet::toString() const {
  std::string s = "\\tuplet " + std::to_string(LyTuplet::getSize()) + "/" + std::to_string(_fraction);
  s += " { ";
  for (int i = 0; i < LyTuplet::getPitchSize(); i++) {
    if (LyTuplet::getPitch(i)) {
      s += LyTuplet::getPitch(i)->toString();
    }
    if (LyTuplet::getDuration(i)) {
      s += LyTuplet::getDuration(i)->toString();
    }
    if (LyTuplet::isTied(i)) {
      s += "~";
    }
    s += " ";
  }
  s += "}";
  return s;
}

void * LyTuplet::toStream(const std::string& __context, void * __ostream) const {
  return nullptr;
}


} // namespace ly
} // namespace hautbois