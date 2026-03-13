#pragma once

#ifndef NOTE_TUPLET_H
#define NOTE_TUPLET_H

#include <vector>
#include <string>
#include <initializer_list>

#include "note.hpp"

namespace hautbois {
namespace core {

class Tuplet : public Note {

 private:

  Duration * _noteValue;

  std::vector<Duration *> _duration;

  std::vector<Pitch *> _pitch;

  std::vector<Property *> _property;

  std::vector<bool> _tied;

  const int nbr_of_notes;

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

  virtual void * verify(const char * __context) const;

  virtual std::string filterProperty(const std::string& __text) const;

  Tuplet(const int& __nbr_of_notes);

  Tuplet();

  Tuplet(const std::initializer_list<std::string> __group, const int& __nbr_of_notes);

  Tuplet(const std::vector<std::string>& __group, const int& __nbr_of_notes);

 public:

  Tuplet(const std::initializer_list<std::string> __group,
         const int& num, const int& denom,
         const int& __nbr_of_notes = 0);

  Tuplet(const std::vector<std::string>& __group,
         const int& num, const int& denom,
         const int& __nbr_of_notes = 0);

  Tuplet(const std::initializer_list<std::string> __group,
         const int& denom, const std::string& dots,
         const int& __nbr_of_notes = 0);

  Tuplet(const std::vector<std::string>& __group,
         const int& denom, const std::string& dots,
         const int& __nbr_of_notes = 0);

  Tuplet(Tuplet& __note);
  
  Tuplet(Tuplet&& __note);

  virtual Tuplet& operator=(const Tuplet& __n);

  virtual ~Tuplet();

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

  virtual bool hasDuration(size_t __pos) const;
  
  virtual bool hasPitch(size_t __pos) const;

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