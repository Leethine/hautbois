#pragma once

#ifndef NOTE_HPP
#define NOTE_HPP

#include <cstddef>
#include <vector>
#include <string>

#include "../symbol/duration.hpp"
#include "../symbol/property.hpp"
#include "../symbol/pitch.hpp"

#define POS_SET_APPEND -1

namespace hautbois {

class Note {

private:

  char _type;

  std::vector<Duration *> _duration;

  std::vector<Pitch *> _pitch;

  std::vector<Property *> _property;

  std::vector<Note *> _tuplet_notes;

  std::vector<bool> _tied;

protected:

  /* If __pos < 0 append __ptr at the end of the vector
   * Otherwise, replace ptr at __pos.
   * Out-of-range __pos will be ignored and nothing is done. */
  virtual void setNote(Note * __ptr, const int __pos);

  virtual void setPitch(Pitch * __ptr, const int __pos);

  virtual void setDuration(Duration * __ptr, const int __pos);

  virtual void setProperty(Property * __ptr, const int __pos);

  virtual Pitch * getPitchModify(const size_t __pos);

  virtual Duration * getDurationModify(const size_t __pos);

  virtual Property * getPropertyModify(const size_t __pos);

  virtual Note * getNoteModify(const size_t __pos);

  virtual void setNoteType(const char __note_type);

  Note(const char __note_type);

public:

  virtual ~Note();

  virtual bool isType(const char __note_type) const;

  virtual char getType() const;

  virtual void makeTie(const size_t __pos);

  virtual void makeUntie(const size_t __pos);

  virtual bool isTied(const size_t __pos);

  /* Methods to be implemented in derived classes */

  virtual const Pitch * getPitch(const size_t __pos = 0) const = 0;

  virtual const Duration * getDuration(const size_t __pos = 0) const = 0;

  virtual const Property * getProperty(const size_t __pos = 0) const = 0;

  virtual const Note * getNote(const size_t __pos = 0) const = 0;

  virtual int getSize() const = 0;

  virtual bool isValid() const = 0;

  virtual void transpose(const int __degree, const std::string& __tonality, const std::string& __mode) = 0;

  virtual void enlarge(const int __factor) = 0;

  virtual void reduce(const int __factor) = 0;

  virtual void expand(const void * __param) = 0;

  virtual std::string toString() const = 0;

  virtual void * toStream(void * __output, void * __param) const = 0;

  virtual void * serialize(const int __version, void * __param) const = 0;

};

} // namespace hautbois

#endif