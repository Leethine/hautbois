#pragma once

#ifndef NOTE_SEQUENCE_H
#define NOTE_SEQUENCE_H

#include <vector>
#include <string>
#include <initializer_list>

#include "note_group.hpp"
#include "pitch.hpp"
#include "utility/hbexcept.hpp"

namespace hautbois {
namespace core {

class NoteSequence : public NoteGroup {

 private:
  /* Declared in class Note */
  ///: NoteType _type;

  /* Declared in class NoteGroup */
  ///: std::vector<Pitch *> _pitchList;
  ///: Duration * _duration;
  ///: Property * _property;
  ///: std::vector<bool> _tieList;
  
  std::vector<Duration *> _durationList;
  
  std::vector<Property *> _propertyList;

  Pitch * _pitch;

  bool _tied;

  const unsigned int _noteCount;

 protected:

  /* The commented out virtual methods are to be implemented in derived classes.
     Or they are already implemented in Note or NoteGroup, if it's not pure virtual. */

  ///+ virtual void setNoteType(NoteType __ntype);

  virtual void addPitch(Pitch *__p);

  virtual void setPitch(Pitch * __p);

  virtual void addDuration(Duration *__d);

  virtual void addProperty(Property *__p);

  virtual void setProperty(Property *__p);

  virtual Pitch * getPitchToModify(int pos);

  virtual Duration * getDurationToModify(int pos);

  virtual Property * getPropertyToModify(int pos);

  virtual void clearPitch();

  virtual void clearDuration();

  virtual void clearProperty();

  ///- virtual void * verify(const char * __context) const = 0;

  ///- virtual std::string filterProperty(const std::string& __text) const = 0;

  NoteSequence()=delete;
  NoteSequence(NoteSequence&)=delete;
  NoteSequence(NoteSequence&&)=delete;
  virtual NoteSequence& operator=(const NoteSequence& __n)=delete;

  NoteSequence(NoteType __type, const unsigned int __count);

  NoteSequence(const char * __pitch, const char * __duration,
               const std::initializer_list<const char *> __args,
               NoteType __type, const unsigned int __count);

  NoteSequence(const std::string& __pitch, const std::string& __duration,
               const std::vector<std::string>& __args,
               NoteType __type, const unsigned int __count);

 public:

  inline virtual ~NoteSequence() {
    NoteSequence::clearPitch();
    NoteSequence::clearDuration();
    NoteSequence::clearProperty();
  }

  ///- virtual void updateDuration(const std::string& __context) = 0;

  ///- virtual void updateDuration(const std::string& __context, size_t __pos) = 0;

  ///- virtual void updatePitch(const std::string& __context) = 0;

  ///- virtual void updatePitch(const std::string& __context, size_t __pos) = 0;

  ///- virtual void updateProperty(const std::string& __context) = 0;

  ///- virtual void updateProperty(const std::string& __context, size_t __pos) = 0;

  ///- virtual void setTied() = 0;

  ///+ virtual void setTied(size_t __pos);

  ///- virtual void setUntied() = 0;

  ///+ virtual void setUntied(size_t __pos);

  inline virtual int getSize() {
    return _noteCount;
  }

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
    if (NoteGroup::isValid() && ! _durationList.empty() &&
        _durationList.size() == _propertyList.size() && _noteCount > 0) {
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

  ///- virtual bool isTied() const = 0;

  ///+ virtual bool isTied(size_t __pos) const;

  ///+ virtual bool hasDuration() const;

  inline virtual bool hasDuration(size_t __pos) const {
    if (__pos >= _durationList.size() || __pos < 0) {
      return false;
    }
    else {
      return _durationList[__pos] != nullptr;
    }
  }

  ///- virtual bool hasPitch() const = 0;

  ///+ virtual bool hasPitch(size_t __pos) const;

  ///+ virtual bool hasProperty() const;

  inline virtual bool hasProperty(size_t __pos) const {
    if (__pos >= _propertyList.size() || __pos < 0) {
      return false;
    }
    else {
      return _propertyList[__pos] != nullptr;
    }
  }

  ///+ virtual const Duration *getDuration() const;

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

  ///- virtual const Pitch * getPitch() const = 0;

  ///+ virtual const Pitch *getPitch(size_t __pos) const;

  ///+ virtual const Property * getProperty() const;

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

  ///- virtual std::string getPropertyStr() const = 0;

  ///- virtual std::string getPropertyStr(size_t __pos) const = 0;

  ///+ virtual int getPitchSize() const;

  inline virtual int getDurationSize() const {
    return _durationList.size();
  }

  inline virtual int getPropertySize() const {
    return _propertyList.size();
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