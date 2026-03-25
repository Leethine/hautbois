#pragma once

#ifndef NOTE_SEQUENCE_H
#define NOTE_SEQUENCE_H

#include <vector>
#include <string>
#include <initializer_list>

#include "note.hpp"
#include "note_group.hpp"
#include "pitch.hpp"

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

  virtual void addPitch(Pitch * __p);

  virtual void setPitch(Pitch * __p, int pos);

  virtual void addDuration(Duration * __d);

  virtual void setDuration(Duration * __d, int pos);

  virtual void addProperty(Property * __p);

  virtual void setProperty(Property * __p, int pos);

  virtual Pitch * getPitchyMod(int pos);

  virtual Duration * getDurationMod(int pos);

  virtual Property * getPropertyMod(int pos);

  virtual void clearPitch();

  virtual void clearDuration();

  virtual void clearProperty();

  ///- virtual void * verify(const char * __context) const = 0;

  ///- virtual std::string filterProperty(const std::string& __text) const = 0;

  NoteSequence()=delete;
  NoteSequence(NoteSequence&)=delete;
  NoteSequence(NoteSequence&&)=delete;
  // virtual NoteSequence& operator=(const NoteSequence& __n)=delete;

  NoteSequence(NoteType __type, const unsigned int __count);

  NoteSequence(const char * __pitch, int __num, int __denom,
               NoteType __type, const unsigned int __count);

  NoteSequence(const std::string& __pitch, int __num, int __denom,
               NoteType __type, const unsigned int __count);

  NoteSequence(const char * __pitch, int __num, int __denom,
               const std::initializer_list<const char *> __args,
               NoteType __type, const unsigned int __count);

  NoteSequence(const std::string& __pitch, int __num, int __denom,
               const std::vector<std::string>& __args,
               NoteType __type, const unsigned int __count);

 public:

  virtual ~NoteSequence();

  ///- virtual void updateDuration(const std::string& __context) = 0;

  ///- virtual void updateDuration(const std::string& __context, size_t __pos) = 0;

  ///- virtual void updatePitch(const std::string& __context) = 0;

  ///- virtual void updatePitch(const std::string& __context, size_t __pos) = 0;

  ///- virtual void updateProperty(const std::string& __context) = 0;

  ///- virtual void updateProperty(const std::string& __context, size_t __pos) = 0;

  virtual void setTied();

  virtual void setTied(size_t __pos);

  virtual void setUntied();

  virtual void setUntied(size_t __pos);

  virtual int getSize() const;

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

  virtual bool isValid() const;

  virtual bool isTied() const;

  virtual bool isTied(size_t __pos) const;

  virtual bool hasDuration() const;

  virtual bool hasDuration(size_t __pos) const;

  virtual bool hasPitch() const;

  virtual bool hasPitch(size_t __pos) const;

  virtual bool hasProperty() const;

  virtual bool hasProperty(size_t __pos) const;

  ///+ virtual const Duration * getDuration() const;

  virtual const Duration * getDuration(size_t __pos) const;

  virtual const Pitch * getPitch() const;

  ///+ virtual const Pitch *getPitch(size_t __pos) const;

  ///+ virtual const Property * getProperty() const;

  virtual const Property * getProperty(size_t __pos) const;

  ///- virtual std::string getPropertyStr() const = 0;

  ///- virtual std::string getPropertyStr(size_t __pos) const = 0;

  virtual int getPitchSize() const;

  virtual int getDurationSize() const;

  virtual int getPropertySize() const;

  ///- virtual void modify(const std::string& __context) = 0;

  ///- virtual std::string toString() const = 0;

  ///- virtual void * toStream(const std::string& __context, void * __ostream) const = 0;

};

} // namespace core
} // namespace hautbois

#endif