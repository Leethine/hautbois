#pragma once

#ifndef SINGLENOTE_HPP
#define SINGLENOTE_HPP

#include "note.hpp"

namespace hautbois {

class SingleNote : public Note {

public:

  virtual ~SingleNote();

  virtual char getType() const;
  virtual bool isType(const char __note_type) const;
  virtual bool isMute() const;

  /* Simply return class member Note::_tied */
  virtual bool isTied(const size_t __pos = 0) const;

  /* Simply return class member Note::_pitch */
  virtual const Pitch * getPitch(const size_t __pos = 0) const;

  /* Simply return class member Note::_duration */
  virtual const Duration * getDuration(const size_t __pos = 0) const;

  /* Simply return class member Note::_property */
  virtual const Property * getProperty(const size_t __pos = 0) const;

  /* SingleNote does not have appended notes as member */
  virtual const Note * getNote(const size_t __pos = 0) const;

  virtual int getSize() const;


  // Implemented in single_note.cpp
  SingleNote(const std::string& __pitch, const std::string& __value);
  SingleNote(const SingleNote&  __other);
  SingleNote(const SingleNote&& __other);

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