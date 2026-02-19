#pragma once

#ifndef NOTE_RAW_H
#define NOTE_RAW_H

#include "core_types.hpp"
#include "pitch_raw.hpp"
#include "duration_raw.hpp"
#include "property_raw.hpp"

#include <vector>
#include <utility>

namespace hautbois {
namespace core {

class NoteRaw final {

 private:

  std::vector<PitchRaw> _pitch;

  PropertyRaw _property;

  DurationRaw _duration;

  bool _tied = false;

 public:
 
  inline NoteRaw() {}

  inline NoteRaw(const NoteRaw& n) {
    auto it = n.getPitch().cbegin();
    auto it_end = n.getPitch().cend();
    for (; it != it_end; it++) {
      addPitch(*it);
    }
    _duration = n.getDuration();
    _property = n.getProperty();
    _tied     = n.isTied();
  }

  inline NoteRaw(const NoteRaw&& n) {
    auto it = n.getPitch().cbegin();
    auto it_end = n.getPitch().cend();
    for (; it != it_end; it++) {
      addPitch(*it);
    }
    _duration = n.getDuration();
    _property = n.getProperty();
    _tied     = n.isTied();
  }

  inline ~NoteRaw() {}

  inline void setPitch(const PitchRaw& p) {
    clearPitch();
    _pitch.emplace_back(p);
  }

  inline void addPitch(const PitchRaw& p) {
    _pitch.emplace_back(p);
  }

  inline void setPitch(const char& name, const char& acc, const int& oct) {
    clearPitch();
    _pitch.emplace_back(PitchRaw(name, acc, oct));
  }

  inline void addPitch(const char& name, const char& acc, const int& oct) {
    _pitch.emplace_back(PitchRaw(name, acc, oct));
  }

  inline void setProperty(const char * text) {
    _property = PropertyRaw();
    _property.set(text);
  }

  inline void setDuration(const int& num, const int& denom) {
    _duration = DurationRaw(num, denom);
  }

  inline void clearPitch() {
    _pitch.clear();
  }

  bool setTied() {
    _tied = true;
  }

  bool setUntied() {
    _tied = false;
  }

  bool isTied() const {
    return _tied;
  }

  inline const std::vector<const PitchRaw>& getPitch() const {
    std::vector<const PitchRaw> p;
    p.reserve(_pitch.size());
    for (auto it=_pitch.begin(); it != _pitch.end(); it++) {
      p.emplace_back((*it));
    }
    return p;
  }

  inline const DurationRaw getDuration() const {
    return _duration;
  }

  inline const PropertyRaw getProperty() const {
    return _property;
  }

  inline void toStream(const char* option, void* out) const {}

};

} // namespace hautbois
} // namespace core

#endif