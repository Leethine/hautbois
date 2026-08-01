#pragma once

#ifndef TUPLET_HPP
#define TUPLET_HPP

#include "note.hpp"

namespace hautbois {

class Tuplet : public Note {

public:

public:

  inline virtual ~Tuplet() {}

  inline virtual char getType() const {
    return Note::getType();
  }

  inline virtual bool isType(const char __note_type) const {
    return Note::isType(__note_type);
  }

  inline virtual bool isMute() const {
    return false;
  }

  inline virtual bool isTied(const size_t __pos = 0) const {
    if (Tuplet::getNote(__pos)) {
      return Tuplet::getNote(__pos)->isTied(0);
    }
    return false;
  }

  /* getPitch will return the pitch of the corresponding note in Note::_notes */
  inline virtual const Pitch * getPitch(const size_t __pos = 0) const {
    if (Note::getNote(__pos)) {
      return Note::getNote(__pos)->getPitch(0);
    }
    return nullptr;
  }

  /* getDuration will return the duration of the corresponding note in Note::_notes
   * However, if getSize() is passed as argument, it will return Note::_duration,
   * i.e. the dividable value of the tuplet (e.g. total note count such as <3,5,7,...> / total note value)
   */
  inline virtual const Duration * getDuration(const size_t __pos = 0) const {
    if (__pos == (size_t) Tuplet::getSize()) {
      return Note::getDuration(0);
    }
    if (Note::getNote(__pos)) {
      return Note::getNote(__pos)->getDuration(0);
    }
    return nullptr;
  }

  /* getProperty will return the property of the corresponding note in Note::_notes */
  inline virtual const Property * getProperty(const size_t __pos = 0) const {
    if (Note::getNote(__pos)) {
      return Note::getNote(__pos)->getProperty(0);
    }
    return nullptr;
  }

  /* getNote will return the note in Note::_notes */
  inline virtual const Note * getNote(const size_t __pos = 0) const {
    return Note::getNote(__pos);
  }

  /* getSize will return the size of Note::_notes */
  inline virtual int getSize() const {
    return Note::getSize();
  }

  // Implemented in tuplet.cpp
  Tuplet(const size_t __total, const size_t __value, const std::vector<std::string>& __notes);
  Tuplet(const Tuplet&  __other);
  Tuplet(const Tuplet&& __other);

  // was declared abstract in base class
  /* Methods to be implemented in derived classes */
  virtual void makeTie  (const size_t __pos = 0);
  virtual void makeUntie(const size_t __pos = 0);

  virtual bool isValid() const;
  virtual void addProperty(const std::string& __property, const int __pos = 0);
  virtual void transpose  (const int __degree, const std::string& __tonality, const std::string& __mode);
  virtual void enlarge    (const int __factor);
  virtual void reduce     (const int __factor);

  virtual std::string toString() const;
  virtual void toStream(void * __output, void * __param1, void * __param2, void * __param3) const;
  virtual void * serialize(const int __version, void * __param) const;

};

} // namespace hautbois

#endif