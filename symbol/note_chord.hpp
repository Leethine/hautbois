#pragma once

#ifndef NOTE_CHORD_H
#define NOTE_CHORD_H

#include <vector>
#include <string>
#include <initializer_list>

#include "note.hpp"

namespace hautbois {
namespace core {

class Chord : public Note {

 private:

  Duration * _duration;

  std::vector<Pitch *> _pitch;

  Property * _property;

  std::vector<bool> _tied;

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

  virtual std::string filterProperty(const std::string& __text) const;

  Chord();

  Chord(const std::vector<std::string>& __pitches);

  Chord(const std::initializer_list<const char *> __pitches);

 public:
 
  Chord(const std::vector<std::string>& __pitches,
        const int& num, const int& denom);

  Chord(const std::vector<std::string>& __pitches,
        const int& denom, const std::string& dots);

  Chord(const std::initializer_list<const char *> __pitches, 
        const int& num, const int& denom);

  Chord(const std::initializer_list<const char *> __pitches,
        const int& denom, const std::string& dots);

  Chord(Chord& __note);

  Chord(Chord&& __note);

  virtual Chord& operator=(const Chord& __n);

  virtual ~Chord();

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