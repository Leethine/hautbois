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

  /* Declared in class Note */
  ///: NoteType _type;

  std::vector<Pitch *> _pitchList;

  Duration * _duration;

  Property * _property;

  std::vector<bool> _tieList;

protected:

  /* The commented out virtual methods are to be implemented in derived classes.
     Or they are already implemented in class Note, if it's not pure virtual. */

  ///+ virtual void setNoteType(NoteType __ntype);

  inline virtual void addPitch(Pitch *__p) {
    if (__p) {
      _pitchList.push_back(__p);
      _tieList.push_back(false);
    }
  }

  ///- virtual void setPitch(Pitch * __p) = 0;

  ///- virtual void addDuration(Duration * __d) = 0;

  inline virtual void setDuration(Duration *__d) {
    if (__d) {
      delete _duration;
      _duration = __d;
    }
  }

  ///- virtual void addProperty(Property * __p) = 0;

  inline virtual void setProperty(Property *__p) {
    delete _property;
    _property = __p;
  }

  inline virtual Pitch * getPitchToModify(int pos) {
    if (_pitchList.empty()) {
      return nullptr;
    }
    else {
      if (pos < 0) {
        return _pitchList.front();
      }
      else if (pos >= _pitchList.size()) {
        return _pitchList.back();
      }
      else {
        return _pitchList[pos];
      }
    }
  }

  inline virtual Duration * getDurationToModify(int pos) {
    return _duration;
  }

  inline virtual Property * getPropertyToModify(int pos) {
    return _property;
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

  ///- virtual void * verify(const char * __context) const = 0;

  ///- virtual std::string filterProperty(const std::string& __text) const = 0;

  NoteGroup() = delete;
  NoteGroup(NoteGroup&)=delete;
  NoteGroup(NoteGroup&&)=delete;
  virtual NoteGroup& operator=(const NoteGroup &__n) = delete;

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

public:

  inline virtual ~NoteGroup() {
    NoteGroup::clearDuration();
    NoteGroup::clearProperty();
    NoteGroup::clearPitch();
  }

  ///- virtual void updateDuration(const std::string& __context) = 0;

  ///- virtual void updateDuration(const std::string& __context, size_t __pos) = 0;

  ///- virtual void updatePitch(const std::string& __context) = 0;

  ///- virtual void updatePitch(const std::string& __context, size_t __pos) = 0;

  ///- virtual void updateProperty(const std::string& __context) = 0;

  ///- virtual void updateProperty(const std::string& __context, size_t __pos) = 0;

  ///- virtual void setTied() = 0;

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

  ///- virtual void setUntied() = 0;

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

  ///- virtual int getSize() const = 0;

  ///+ virtual NoteType getType() const;

  ///+ virtual char getTypeChar() const;

  ///+ virtual std::string getTypeStr() const;

  ///+ virtual bool isType(NoteType __ntype) const;

  ///+ virtual bool isSingle() const;

  ///+ virtual bool isRest() const;

  ///+ virtual bool isSilence() const;

  ///+ virtual bool isChord() const;

  ///+ virtual bool isTuplet() const;

  ///+ virtual bool isGrace() const;

  ///+ virtual bool isAppoggiatura() const;

  ///+ virtual bool isAcciaccatura() const;

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

  ///- virtual bool isTied() const = 0;

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

  ///- virtual bool hasDuration(size_t __pos) const = 0;

  ///- virtual bool hasPitch() const = 0;

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

  ///- virtual bool hasProperty(size_t __pos) const = 0;

  inline virtual const Duration *getDuration() const {
    return _duration;
  }

  ///- virtual const Pitch * getPitch() const = 0;

  inline virtual const Pitch *getPitch(size_t __pos) const {
    if (__pos >= _pitchList.size() || __pos < 0) {
      HB_THROW_MSG(std::out_of_range, std::string("__pos == "
        + std::to_string(__pos) +" > _pitchList.size() "
        + std::to_string(_pitchList.size())));
    }
    else {
      return _pitchList[__pos];
    }
  }

  inline virtual const Property * getProperty() const {
    return _property;
  }

  ///- virtual const Property * getProperty(size_t __pos) const = 0;

  ///- virtual std::string getPropertyStr() const = 0;

  ///- virtual std::string getPropertyStr(size_t __pos) const = 0;

  inline virtual int getPitchSize() const {
    return _pitchList.size();
  }

  ///- virtual int getDurationSize() const = 0;

  ///- virtual int getPropertySize() const = 0;

  ///- virtual void modify(const std::string& __context) = 0;

  ///- virtual std::string toString() const = 0;

  ///- virtual void * toStream(const std::string& __context, void * __ostream) const = 0;

};

} // namespace core
} // namespace hautbois

#endif