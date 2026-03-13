#pragma once

#ifndef NOTE_GROUP_H
#define NOTE_GROUP_H

#include <vector>
#include <string>
#include <cstring>
#include <initializer_list>

#include "note.hpp"
#include "pitch.hpp"
#include "utility/hbexcept.hpp"

namespace hautbois {
namespace core {

class NoteGroup : public Note {

private:

  std::vector<Pitch *> _pitchList;

  Duration *_duration;

  Property *_property;

  std::vector<bool> _tieList;

protected:

  inline virtual void addPitch(Pitch *__p) {
    if (__p) {
      _pitchList.push_back(__p);
      _tieList.push_back(false);
    }
  }

  inline virtual void setPitch(Pitch *__p) {
    if (__p) {
      NoteGroup::clearPitch();
      _pitchList.push_back(__p);
      _tieList.push_back(false);
    }
  }

  inline virtual void addDuration(Duration *__d) {
    if (__d) {
      delete _duration;
      _duration = __d;
    }
  }

  inline virtual void setDuration(Duration *__d) {
    if (__d) {
      delete _duration;
      _duration = __d;
    }
  }

  inline virtual void addProperty(Property *__p) {
    delete _property;
    _property = __p;
  }

  inline virtual void setProperty(Property *__p) {
    delete _property;
    _property = __p;
  }

  inline virtual void clearPitch() {
    for (auto it = _pitchList.begin(); it != _pitchList.end(); it++) {
      delete *it;
    }
    _pitchList.clear();
    _tieList.clear();
  }

  inline virtual void clearDuration() {
    delete _duration;
    _duration = nullptr;
  }

  inline virtual void clearProperty() {
    delete _property;
    _property = nullptr;
  }

  NoteGroup() = delete;

  inline NoteGroup(NoteType __type) :
    Note(__type), _pitchList {}, _duration(nullptr), _property(nullptr), _tieList {} {
  }

  inline NoteGroup(const std::initializer_list<const char *> __pitches,
                   NoteType __type) : NoteGroup(__type) {
    for (auto& token : __pitches) {
      Pitch * p = nullptr;
      if (std::strlen(token) > 3 || std::strlen(token) == 0) {
        HB_THROW_MSG(std::invalid_argument,
        std::string ("Invalid token: " + std::string(token)));
      }
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string ("Invalid token: " + std::string(token)),
        if (std::strlen(token) == 3) 
          { p = new Pitch(token[0],token[1], token[2] - '0'); }
        else if (std::strlen(token) == 2)
          { p = new Pitch(token[0], token[1] - '0'); }
        else if (std::strlen(token) == 1)
          { p = new Pitch(token[0]); }
      )
      NoteGroup::addPitch(p);
    }
  }

  inline NoteGroup(const std::vector<std::string> __pitches,
                   NoteType __type) : NoteGroup(__type) {
    for (auto& token : __pitches) {
      Pitch * p = nullptr;
      if (token.size() > 3 || token.size() == 0) {
        HB_THROW_MSG(std::invalid_argument,
        std::string ("Invalid token: " + std::string(token)));
      }
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string ("Invalid token: " + std::string(token)),
        if (token.size() == 3) 
          { p = new Pitch(token[0],token[1], token[2] - '0'); }
        else if (token.size() == 2)
          { p = new Pitch(token[0], token[1] - '0'); }
        else if (token.size() == 1)
          { p = new Pitch(token[0]); }
      )
      NoteGroup::addPitch(p);
    }
  }

  NoteGroup(NoteGroup&)=delete;

  NoteGroup(NoteGroup&&)=delete;

  virtual NoteGroup& operator=(const NoteGroup &__n) = delete;

public:

  inline virtual ~NoteGroup() {
    NoteGroup::clearDuration();
    NoteGroup::clearProperty();
    NoteGroup::clearPitch();
  }

  inline virtual void setTied() {
    for (auto it=_tieList.begin(); it!=_tieList.end(); it++) {
      *it = true;
    }
  }

  inline virtual void setTied(size_t __pos) {
    if (__pos >= _tieList.size() || __pos < 0) {
      HB_THROW_MSG(std::out_of_range, std::string("__pos == "
        + std::to_string(__pos) +" > _tieList.size() "
        + std::to_string(_tieList.size())));
    }
    else {
      _tieList[__pos] = true;
    }
  }

  inline virtual void setUntied() {
    for (auto it=_tieList.begin(); it!=_tieList.end(); it++) {
      *it = false;
    }
  }

  inline virtual void setUntied(size_t __pos) {
    if (__pos >= _tieList.size() || __pos < 0) {
      HB_THROW_MSG(std::out_of_range, std::string("__pos == "
        + std::to_string(__pos) +" > _tieList.size() "
        + std::to_string(_tieList.size())));
    }
    else {
      _tieList[__pos] = false;
    }
  }

  inline virtual int getSize() const {
    return _pitchList.size();
  }

  inline virtual bool isValid() const {
    if (_pitchList.empty() || _duration == nullptr) {
      return false;
    }
    else {
      for (auto it = _pitchList.cbegin(); it != _pitchList.cend(); it++) {
        if (*it == nullptr) {
          return false;
        }
      }
      return true;
    }
  }

  inline virtual bool isTied() const {
    for (auto it=_tieList.begin(); it!=_tieList.end(); it++) {
      if (*it == false) {
        return false;
      }
    }
    return true;
  }

  inline virtual bool isTied(size_t __pos) const {
    if (__pos >= _tieList.size() || __pos < 0) {
      HB_THROW_MSG(std::out_of_range, std::string("__pos == "
        + std::to_string(__pos) +" > _tieList.size() "
        + std::to_string(_tieList.size())));
    }
    else {
      return _tieList[__pos];
    }
  }

  inline virtual bool hasDuration() const {
    return _duration != nullptr;
  }

  inline virtual bool hasPitch() const {
    return !_pitchList.empty();
  }

  inline virtual bool hasPitch(size_t __pos) const {
    if (__pos >= _pitchList.size() || __pos < 0) {
      return false;
    }
    else {
      return _pitchList[__pos] != nullptr;
    }
  }

  inline virtual bool hasProperty() const {
    return _property != nullptr;
  }

  inline virtual const Duration *getDuration() const {
    return _duration;
  }

  inline virtual const Pitch *getPitch() const {
    if (_pitchList.empty()) {
      return nullptr;
    }
    else {
      return _pitchList.front();
    }
  }

  inline virtual const Pitch *getPitch(size_t __pos) const {
    if (__pos >= _pitchList.size() || __pos < 0) {
      HB_THROW_MSG(std::out_of_range, std::string("__pos == "
        + std::to_string(__pos) +" > _tieList.size() "
        + std::to_string(_tieList.size())));
    }
    else {
      return _pitchList[__pos];
    }
  }

  inline virtual const Property *getProperty() const {
    return _property;
  }

  inline virtual int getPitchSize() const {
    return _pitchList.size();
  }

};

} // namespace core
} // namespace hautbois

#endif