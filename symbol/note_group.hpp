#pragma once

#ifndef NOTE_GROUP_H
#define NOTE_GROUP_H

#include <vector>
#include <string>

#include "note.hpp"

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

  virtual void addPitch(Pitch *__p);

  virtual void setPitch(Pitch * __p, int pos);

  ///- virtual void addDuration(Duration * __d) = 0;

  virtual void setDuration(Duration *__d, int pos);

  ///- virtual void addProperty(Property * __p) = 0;

  virtual void setProperty(Property *__p, int pos);

  virtual Pitch * getPitchToModify(int pos);

  virtual Duration * getDurationToModify(int pos);

  virtual Property * getPropertyToModify(int pos);

  virtual void clearPitch();

  virtual void clearDuration();

  virtual void clearProperty();

  ///- virtual void * verify(const char * __context) const = 0;

  ///- virtual std::string filterProperty(const std::string& __text) const = 0;

  NoteGroup() = delete;
  NoteGroup(NoteGroup&)=delete;
  NoteGroup(NoteGroup&&)=delete;
  virtual NoteGroup& operator=(const NoteGroup &__n) = delete;

  NoteGroup(NoteType __type);

  NoteGroup(const std::initializer_list<const char *> __pitches, NoteType __type);

  NoteGroup(const std::vector<std::string>& __pitches, NoteType __type);

public:

  virtual ~NoteGroup();

  ///- virtual void updateDuration(const std::string& __context) = 0;

  ///- virtual void updateDuration(const std::string& __context, size_t __pos) = 0;

  ///- virtual void updatePitch(const std::string& __context) = 0;

  ///- virtual void updatePitch(const std::string& __context, size_t __pos) = 0;

  ///- virtual void updateProperty(const std::string& __context) = 0;

  ///- virtual void updateProperty(const std::string& __context, size_t __pos) = 0;

  ///- virtual void setTied() = 0;

  virtual void setTied(size_t __pos);

  ///- virtual void setUntied() = 0;

  virtual void setUntied(size_t __pos);

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

  virtual bool isValid() const;

  ///- virtual bool isTied() const = 0;

  virtual bool isTied(size_t __pos) const;

  virtual bool hasDuration() const;

  ///- virtual bool hasDuration(size_t __pos) const = 0;

  ///- virtual bool hasPitch() const = 0;

  virtual bool hasPitch(size_t __pos) const;

  virtual bool hasProperty() const;

  ///- virtual bool hasProperty(size_t __pos) const = 0;

  virtual const Duration * getDuration() const;

  ///- virtual const Duration * getDuration(size_t __pos) const = 0;

  ///- virtual const Pitch * getPitch() const = 0;

  virtual const Pitch * getPitch(size_t __pos) const;

  virtual const Property * getProperty() const;

  ///- virtual const Property * getProperty(size_t __pos) const = 0;

  ///- virtual std::string getPropertyStr() const = 0;

  ///- virtual std::string getPropertyStr(size_t __pos) const = 0;

  virtual int getPitchSize() const;

  ///- virtual int getDurationSize() const = 0;

  ///- virtual int getPropertySize() const = 0;

  ///- virtual void modify(const std::string& __context) = 0;

  ///- virtual std::string toString() const = 0;

  ///- virtual void * toStream(const std::string& __context, void * __ostream) const = 0;

};

} // namespace core
} // namespace hautbois

#endif