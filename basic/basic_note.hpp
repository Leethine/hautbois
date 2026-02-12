#pragma once

#ifndef NOTE_SIMPLE_H
#define NOTE_SIMPLE_H

#include "core_types.hpp"
#include "basic_pitch.hpp"
#include "basic_duration.hpp"
#include "basic_property.hpp"

#include <vector>

namespace hautbois {
namespace core {

class NoteSimple {

 private:

  std::vector<BasicPitch*> _pitch;

  BasicProperty * _property = nullptr;

  BasicDuration * _duration = nullptr;

 protected:

  inline virtual void setPitch(BasicPitch * p) {
    clearPitch();
    _pitch.push_back(p);
  }

  inline virtual void addPitch(BasicPitch * p) {
    _pitch.push_back(p);
  }

  inline virtual void clearPitch() {
    for (auto it = _pitch.begin(); it != _pitch.end(); it++) {
      delete (*it);
    }
    _pitch.clear();
  }

  inline virtual void setProperty(BasicProperty * p) {
    delete _property;
    _property = p;
  }

  inline virtual void setDuration(BasicDuration * d) {
    delete _duration;
    _duration = d;
  }

 public:

  inline NoteSimple() {}

  inline ~NoteSimple() {
    delete _duration;
    delete _property;
    clearPitch();
  }

  inline virtual bool isValid() const {
    if (_duration == nullptr || _pitch.empty()) {
      return false;
    }
    else {
      if (!_duration->isValid()) {
        return false;
      }
      for (auto it=_pitch.begin(); it != _pitch.end(); it++) {
        if (!(*it)->isValid()) {
          return false;
        }
      }
      if (_property && !_property->isValid()) {
        return false;
      }
    }
    return true;
  }

  inline virtual void toStream(const char* option, void* out) const {}

  //TODO Serialize

};

} // namespace hautbois
} // namespace core

#endif