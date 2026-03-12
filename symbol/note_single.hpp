#pragma once

#ifndef NOTE_SINGLE_H
#define NOTE_SINGLE_H

#include <string>

#include "note.hpp"

namespace hautbois {
namespace core {

class SingleNote : public Note {

 private:

  Duration * _duration;

  Pitch * _pitch;

  Property * _property;

  bool _tied;

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

  SingleNote();

  SingleNote(const std::string& __pitch);

 public:

  SingleNote(const std::string& __pitch, const int& __num, const int& __denom);

  SingleNote(const std::string& __pitch, const int& __denom, const std::string& __dots);

  SingleNote(SingleNote& __note);
  
  SingleNote(SingleNote&& __note);

  virtual SingleNote& operator=(const SingleNote& __n);

  virtual ~SingleNote();

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

  virtual bool hasDuration() const;
  
  virtual bool hasPitch() const;

  virtual bool hasProperty() const;

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