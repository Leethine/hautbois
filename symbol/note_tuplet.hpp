#pragma once

#ifndef NOTE_TUPLET_H
#define NOTE_TUPLET_H

#include <vector>
#include <string>
#include <initializer_list>

#include "note_sequence.hpp"

namespace hautbois {
namespace core {

class Tuplet : public NoteSequence {

 protected:

  virtual void addPitch(Pitch *__p);

  virtual void setPitch(Pitch * __p, int pos);

  virtual void addDuration(Duration *__d);

  virtual void setDuration(Duration *__d, int pos);

  virtual void addProperty(Property *__p);

  virtual void setProperty(Property *__p, int pos);

  virtual Pitch * getPitchyMod(int pos);

  virtual Duration * getDurationMod(int pos);

  virtual Property * getPropertyMod(int pos);

  virtual void clearPitch();

  virtual void clearDuration();

  virtual void clearProperty();

  virtual void * verify(const char * __context) const;

  virtual std::string filterProperty(const std::string& __text) const;

  Tuplet(const unsigned int __count);

 public:

  Tuplet(int __num, int __denom,
         const std::initializer_list<const char *> __args,
         const unsigned int __count);

  Tuplet(int __num, int __denom,
         const std::vector<std::string>& __args,
         const unsigned int __count);

  virtual ~Tuplet();

  Tuplet(const Tuplet& __other);

  Tuplet(const Tuplet&& __other);

  virtual Tuplet& operator=(const Tuplet& __other);

  virtual void updateDuration(const std::string& __context);

  virtual void updateDuration(const std::string& __context, size_t __pos);

  virtual void updatePitch(const std::string& __context);

  virtual void updatePitch(const std::string& __context, size_t __pos);

  virtual void updateProperty(const std::string& __context);

  virtual void updateProperty(const std::string& __context, size_t __pos);

  virtual void setTied();

  virtual void setTied(size_t __pos);

  virtual void setUntied();

  virtual void setUntied(size_t __pos);

  virtual int getSize() const;

  virtual NoteType getType() const;

  virtual char getTypeChar() const;

  virtual std::string getTypeStr() const;

  virtual bool isType(NoteType __ntype) const;

  virtual bool isSingle() const;

  virtual bool isRest() const;

  virtual bool isSilence() const;

  virtual bool isChord() const;

  virtual bool isTuplet() const;

  virtual bool isGrace() const;

  virtual bool isAppoggiatura() const;

  virtual bool isAcciaccatura() const;

  virtual bool isValid() const;

  virtual bool isTied() const;

  virtual bool isTied(size_t __pos) const;

  virtual bool hasDuration() const;

  virtual bool hasDuration(size_t __pos) const;

  virtual bool hasPitch() const;

  virtual bool hasPitch(size_t __pos) const;

  virtual bool hasProperty() const;

  virtual bool hasProperty(size_t __pos) const;

  virtual const Duration * getDuration() const;

  virtual const Duration * getDuration(size_t __pos) const;

  virtual const Pitch * getPitch() const;

  virtual const Pitch * getPitch(size_t __pos) const;

  virtual const Property * getProperty() const;

  virtual const Property * getProperty(size_t __pos) const;

  virtual std::string getPropertyStr() const;

  virtual std::string getPropertyStr(size_t __pos) const;

  virtual int getPitchSize() const;

  virtual int getDurationSize() const;

  virtual int getPropertySize() const;

  virtual void modify(const std::string& __context);

  virtual std::string toString() const;

  virtual void * toStream(const std::string& __context, void * __ostream) const;

};

} // namespace core
} // namespace hautbois

#endif