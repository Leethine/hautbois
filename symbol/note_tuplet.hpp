#pragma once

#ifndef NOTE_TUPLET_H
#define NOTE_TUPLET_H

#include <vector>
#include <string>

#include "note.hpp"

namespace hautbois {
namespace core {

class Tuplet : public Note {

 private:

  Duration * _value_global;

  std::vector<Duration *> _duration;

  std::vector<Pitch *> _pitch;

  std::vector<Property *> _property;

  std::vector<bool> _tied;

  int nbr_of_notes;

 protected:

  virtual void addPitch(Pitch * __p);

  virtual void setPitch(Pitch * __p);

  virtual void addDuration(Duration * __d);

  virtual void setDuration(Duration * __d);

  virtual void addProperty(Property * __p);

  virtual void setProperty(Property * __p);

  virtual void clearPitch();

  virtual void clearDuration();

  virtual void clearProperty();

  virtual NoteType guessNoteType(const std::string& __input) const;

  virtual bool checkFormatThrowExp(const std::string& __pitch) const;

  virtual std::vector<std::string> parseInput(const std::string& __input) const;

  virtual std::string filterProperty(const std::string& __text) const;

 public:

  Tuplet();

  Tuplet(Tuplet& __note);
  
  Tuplet(Tuplet&& __note);

  virtual Tuplet& operator=(const Tuplet& __n);

  virtual ~Tuplet();

  virtual void updateDuration(const std::string& __context) = 0;

  virtual void updateDuration(const std::string& __context, size_t __pos) = 0;
  
  virtual void updatePitch(const std::string& __context) = 0;

  virtual void updatePitch(const std::string& __context, size_t __pos) = 0;

  virtual void updateProperty(const std::string& __context) = 0;

  virtual void updateProperty(const std::string& __context, size_t __pos) = 0;

  virtual void setTied();

  virtual void setTied(size_t __pos);

  virtual void setUntied();

  virtual void setUntied(size_t __pos);

  virtual int getSize() const;

  virtual bool isValid() const;

  virtual bool isTied() const;

  virtual bool isTied(size_t __pos) const;

  virtual const bool hasDuration() const;
  
  virtual const bool hasPitch() const;

  virtual const bool hasProperty() const;

  virtual const Duration * getDuration() const;

  virtual const Duration * getDuration(size_t __pos) const;

  virtual const Pitch * getPitch() const;

  virtual const Pitch * getPitch(size_t __pos) const;

  virtual const Property * getProperty() const;

  virtual const Property * getProperty(size_t __pos) const;

  virtual int getPitchSize() const;

  virtual int getDurationSize() const;

  virtual int getPropertySize() const;

  virtual void modify(const std::string& __context);

  virtual void updateProperty(const std::string& __property);

  virtual void updateProperty(const std::string& __property, size_t __pos);

  virtual std::string toString() const;

  virtual void * toStream(const std::string& __context, void * __ostream) const;

};

} // namespace core
} // namespace hautbois

#endif