#pragma once

#ifndef TUPLET_HPP
#define TUPLET_HPP

#include "note.hpp"

namespace hautbois {

class Tuplet : public Note {

public:

  inline virtual ~Tuplet() {}

  inline virtual bool isType(const char __note_type) const {
    return Note::isType(__note_type);
  }

  inline virtual char getType() const {
    return Note::getType();
  }

  inline virtual void makeTie(const size_t __pos = 0) {
    if (Note::getNoteModify(__pos)) {
      Note::getNoteModify(__pos)->makeTie(0);
    }
  }

  inline virtual void makeUntie(const size_t __pos = 0) {
    if (Note::getNoteModify(__pos)) {
      Note::getNoteModify(__pos)->makeUntie(0);
    }
  }

  inline virtual bool isTied(const size_t __pos = 0) const {
    if (Tuplet::getNote(__pos)) {
      return Tuplet::getNote(__pos)->isTied(0);
    }
    return false;
  }

  inline virtual const Pitch * getPitch(const size_t __pos = 0) const {
    return nullptr;
  }

  inline virtual const Duration * getDuration(const size_t __pos = 0) const {
    return Note::getDuration(0);
  }

  inline virtual const Property * getProperty(const size_t __pos = 0) const {
    return nullptr;
  }

  inline virtual const Note * getNote(const size_t __pos = 0) const {
    return Note::getNote(__pos);
  }

  // Note that double Tuplet (Tuplet inside another tuplet) is not yet supported
  Tuplet(const size_t __total, const size_t __value, const std::vector<std::string>& __notes);

  Tuplet(const Tuplet& __other);

  Tuplet(const Tuplet&& __other);

  // was declared abstract
  virtual void addProperty(const std::string& __property, const int __pos = 0);

  virtual int getSize() const;

  virtual bool isValid() const;

  virtual void transpose(const int __degree, const std::string& __tonality, const std::string& __mode);

  virtual void enlarge(const int __factor);

  virtual void reduce(const int __factor);

  virtual std::string toString() const;

  virtual void * toStream(void * __output, void * __param) const;

  virtual void * serialize(const int __version, void * __param) const;

};

} // namespace hautbois

#endif