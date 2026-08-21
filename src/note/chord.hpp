#pragma once

#ifndef CHORD_HPP
#define CHORD_HPP

#include "note.hpp"

namespace hautbois {

class Chord : public Note {

public:

  virtual ~Chord();
  virtual char getType() const;
  virtual bool isType(const char __note_type) const;
  virtual bool isMute() const;
  virtual bool isTied(const size_t __pos = 0) const;

  /* getPitch will return the pitch of the corresponding note in Note::_notes */
  virtual const Pitch * getPitch(const size_t __pos = 0) const;

  /* getDuration will return Note::_duration */
  virtual const Duration * getDuration(const size_t __pos = 0) const;

  /* getProperty will return Note::_property */
  virtual const Property * getProperty(const size_t __pos = 0) const;

  /* getNote will return the note in Note::_notes */
  virtual const Note * getNote(const size_t __pos = 0) const;
  
  /* getSize will return the size of Note::_notes */
  virtual int getSize() const;

  // Implemented in chord.cpp
  Chord(const std::vector<std::string>& __pitch, const std::string& __value);
  Chord(const Chord&  __other);
  Chord(const Chord&& __other);

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