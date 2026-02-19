#pragma once

#ifndef NOTE_RAW_H
#define NOTE_RAW_H

#include "core_types.hpp"
#include "pitch_raw.hpp"
#include "duration_raw.hpp"
#include "property_raw.hpp"

#include <vector>
#include <string>

namespace hautbois {
namespace core {

class NoteRaw final {

 public:

  std::vector<PitchRaw> _pitch;

  PropertyRaw _property;

  DurationRaw _duration;

  bool _tied = false;

  inline NoteRaw() {}

  inline NoteRaw(const NoteRaw& n) {
    for (auto& p : n._pitch) {
      _pitch.emplace_back(p);
    }
    _duration = n._duration;
    _property = n._property;
    _tied     = n._tied;
  }

  inline NoteRaw(const NoteRaw&& n) {
    for (auto& p : n._pitch) {
      _pitch.emplace_back(p);
    }
    _duration = n._duration;
    _property = n._property;
    _tied     = n._tied;
  }

  inline ~NoteRaw() {}

  inline NoteRaw operator=(const NoteRaw& r) {
    NoteRaw(r);
  }

};

} // namespace hautbois
} // namespace core

#endif