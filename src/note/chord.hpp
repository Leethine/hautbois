#pragma once

#ifndef CHORD_HPP
#define CHORD_HPP

#include "note.hpp"

namespace hautbois {

class Chord : public Note {

public:

  inline virtual ~Chord() {}

  inline virtual bool isType(const char __note_type) const {
    return Note::isType(__note_type);
  }

  inline virtual char getType() const {
    return Note::getType();
  }

  inline virtual void makeTie(const size_t __pos = 0) {
    Note::makeTie(__pos);
  }

  inline virtual void makeUntie(const size_t __pos = 0) {
    Note::makeUntie(__pos);
  }

  inline virtual bool isTied(const size_t __pos = 0) const {
    return Note::isTied(__pos);
  }

  inline virtual const Pitch * getPitch(const size_t __pos = 0) const {
    return Note::getPitch(__pos);
  }

  inline virtual const Duration * getDuration(const size_t __pos = 0) const {
    return Note::getDuration(__pos);
  }

  inline virtual const Property * getProperty(const size_t __pos = 0) const {
    return Note::getProperty(__pos);
  }

  inline virtual const Note * getNote(const size_t __pos = 0) const {
    return nullptr;
  }

  Chord(const std::vector<std::string>& __pitch, const std::string& __value);

  Chord(const Chord& __other);

  Chord(const Chord&& __other);

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