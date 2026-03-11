#pragma once

#ifndef NOTE_H
#define NOTE_H

#include <vector>
#include <string>

namespace hautbois {
namespace core {

enum class NoteType {
  SingleNote   =  0,
  Chord        =  1,
  Tuplet       =  2,
  Rest         = -1,
  Silence      = -2,
  Grace        =  3,
  Appoggiatura =  4,
  Acciaccatura =  5
};

class Duration;

class Pitch;

class Property;

class Note {

 private:

  NoteType _type;

 protected:

  virtual void setNoteType(NoteType __ntype) = 0;

  virtual void addPitch(Pitch * __p) = 0;

  virtual void setPitch(Pitch * __p) = 0;

  virtual void addDuration(Duration * __d) = 0;

  virtual void setDuration(Duration * __d) = 0;

  virtual void addProperty(Property * __p) = 0;

  virtual void setProperty(Property * __p) = 0;

  virtual void clearPitch() = 0;

  virtual void clearDuration() = 0;

  virtual void clearProperty() = 0;

  virtual NoteType guessNoteType(const std::string& __input) const = 0;

  virtual bool checkFormatThrowExp(const std::string& __pitch) const = 0;

  virtual std::vector<std::string> parseInput(const std::string& __input) const = 0;

  virtual std::string filterProperty(const std::string& __text) const = 0;

 public:

  inline Note() : _type ( NoteType::Silence ) {}

  inline Note(NoteType __itype) : _type ( __itype ) {}

  Note(Note&) = delete;
  
  Note(Note&&) = delete;

  virtual Note& operator=(const Note& __n) = delete;

  virtual ~Note() = 0;

  virtual void updateDuration(const std::string& __context) = 0;
  
  virtual void updatePitch(const std::string& __context) = 0;

  virtual void updateProperty(const std::string& __context) = 0;

  virtual void setTied() = 0;

  virtual void setTied(size_t __pos) = 0;

  virtual void setUntied() = 0;

  virtual void setUntied(size_t __pos) = 0;

  virtual int getSize() const = 0;

  virtual NoteType getType() const = 0;

  virtual char getTypeChar() const = 0;

  virtual std::string getTypeStr() const = 0;

  virtual bool isType(NoteType iType) const = 0;

  virtual bool isSingle() const = 0;

  virtual bool isChord() const = 0;

  virtual bool isRest() const = 0;

  virtual bool isSilent() const = 0;

  virtual bool isTuplet() const = 0;

  virtual bool isValid() const = 0;

  virtual bool isTied() const = 0;

  virtual bool isTied(size_t __pos) const = 0;

  virtual const bool hasDuration() const = 0;
  
  virtual const bool hasPitch() const = 0;

  virtual const bool hasProperty() const = 0;

  virtual const Duration * getDuration() const = 0;

  virtual const Duration * getDuration(size_t __pos) const = 0;

  virtual const Pitch * getPitch() const = 0;

  virtual const Pitch * getPitch(size_t __pos) const = 0;

  virtual const Property * getProperty() const = 0;

  virtual const Property * getProperty(size_t __pos) const = 0;

  virtual int getPitchSize() const = 0;

  virtual int getDurationSize() const = 0;

  virtual int getPropertySize() const = 0;

  virtual void modify(const std::string& __context) = 0;

  virtual void updateProperty(const std::string& __property) = 0;

  virtual void updateProperty(const std::string& __property, size_t __pos) = 0;

  virtual std::string toString() const = 0;

  virtual void * toStream(const std::string& __context, void * __ostream) const = 0;

};

} // namespace core
} // namespace hautbois

#endif