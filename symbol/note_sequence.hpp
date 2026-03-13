#pragma once

#ifndef NOTE_SEQUENCE_H
#define NOTE_SEQUENCE_H

#include <vector>
#include <string>
#include <cstring>
#include <initializer_list>

#include "note_group.hpp"
#include "pitch.hpp"
#include "utility/hbexcept.hpp"

namespace hautbois {
namespace core {

class NoteSequence : public NoteGroup {

 private:

  std::vector<Duration *> _durationList;

  std::vector<Property *> _propertyList;

  const unsigned int _durationDivisor;

 protected:

  inline virtual void addDuration(Duration *__d) {
    if (__d) {
      _durationList.push_back(__d);
    }
  }

  inline virtual void addProperty(Property *__p) {
    if (__p) {
      _propertyList.push_back(__p);
    }
  }

  inline virtual void clearPitch() {
    NoteGroup::clearPitch();
  }

  inline virtual void clearDuration() {
    NoteGroup::clearDuration();
    for (auto it = _durationList.begin(); it != _durationList.end(); it++) {
      delete *it;
    }
    _durationList.clear();
  }

  inline virtual void clearProperty() {
    NoteGroup::clearProperty();
    for (auto it = _propertyList.begin(); it != _propertyList.end(); it++) {
      delete *it;
    }
    _propertyList.clear();
  }

  NoteSequence()=delete;

  NoteSequence(NoteSequence&)=delete;
  
  NoteSequence(NoteSequence&&)=delete;

  virtual NoteSequence& operator=(const NoteSequence& __n)=delete;

  inline NoteSequence(NoteType __type, const unsigned int divisor) :
    NoteGroup(__type), _durationList {}, _propertyList {}, 
    _durationDivisor (divisor) { }

 public:

  inline virtual ~NoteSequence() {
    NoteSequence::clearPitch();
    NoteSequence::clearDuration();
    NoteSequence::clearProperty();
  }

  inline virtual int getSize() {
    return _durationDivisor;
  }

  inline virtual bool isValid() const {
    if (NoteGroup::isValid() && ! _durationList.empty() &&
        _durationList.size() == _propertyList.size() && _durationDivisor > 0) {
      for (auto it = _durationList.cbegin(); it != _durationList.cend(); it++) {
        if (*it == nullptr) {
          return false;
        }
      }
      return true;
    }
    else {
      return false;
    }
  }

  inline virtual bool hasDuration(size_t __pos) const {
    if (__pos >= _durationList.size() || __pos < 0) {
      return false;
    }
    else {
      return _durationList[__pos] != nullptr;
    }
  }

  inline virtual bool hasProperty(size_t __pos) const {
    if (__pos >= _propertyList.size() || __pos < 0) {
      return false;
    }
    else {
      return _propertyList[__pos] != nullptr;
    }
  }

  inline virtual const Duration * getDuration(size_t __pos) {
    if (__pos >= _durationList.size() || __pos < 0) {
      HB_THROW_MSG(std::out_of_range, std::string("__pos == "
        + std::to_string(__pos) +" > _durationList.size() "
        + std::to_string(_durationList.size())));
    }
    else {
      return _durationList[__pos];
    }
  }

  inline virtual const Property * getProperty(size_t __pos) const {
    if (__pos >= _propertyList.size() || __pos < 0) {
      HB_THROW_MSG(std::out_of_range, std::string("__pos == "
        + std::to_string(__pos) +" > _propertyList.size() "
        + std::to_string(_propertyList.size())));
    }
    else {
      return _propertyList[__pos];
    }
  }

  inline virtual int getDurationSize() const {
    return _durationList.size();
  }

  inline virtual int getPropertySize() const {
    return _propertyList.size();
  }

};

} // namespace core
} // namespace hautbois

#endif