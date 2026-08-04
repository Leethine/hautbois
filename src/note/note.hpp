#pragma once

#ifndef NOTE_HPP
#define NOTE_HPP

#include <cstddef>
#include <vector>
#include <string>

#include "duration.hpp"
#include "property.hpp"
#include "pitch.hpp"

#define NOTE_SETNOTE_APPEND_POS -1

namespace hautbois {

class Note {

private:

  char _type;
  bool _tied;

  Duration * _duration;
  Pitch    * _pitch;
  Property * _property;

  std::vector<Note *> _notes;

protected:

  /* If __pos < 0, append __ptr at the end of the vector, otherwise, replace ptr at __pos.
   * Out-of-range __pos will be ignored and nothing will be done.
   * If the provided __ptr is nullptr, the element at __pos will be removed (freed + erased).
   */
  virtual void setNote(Note * __ptr, const int __pos);

  /* If __ptr is nullptr, the element at __pos will be removed (freed + erased),
   * otherwise the element will be freed and replaced.
   */
  virtual void setPitch   (Pitch    * __ptr);
  virtual void setDuration(Duration * __ptr);
  virtual void setProperty(Property * __ptr);
  virtual void setTie     (bool __tie);

  /* GetModify methods, use with caution!
   */
  virtual Pitch    * getPitchModify();
  virtual Duration * getDurationModify();
  virtual Property * getPropertyModify();

  /* If __pos is out of range, nullptr is returned. */
  virtual Note * getNoteModify(const size_t __pos);

  virtual void setNoteType(const char __note_type);
  Note(const char __note_type);

public:

  virtual ~Note();

  virtual char getType() const;
  virtual bool isType(const char __note_type) const;
  virtual bool isMute() const;
  virtual bool isTied(const size_t __pos = 0) const;

  virtual const Pitch    * getPitch   (const size_t __pos = 0) const;
  virtual const Duration * getDuration(const size_t __pos = 0) const;
  virtual const Property * getProperty(const size_t __pos = 0) const;

  virtual const Note * getNote(const size_t __pos = 0) const;
  virtual int getSize() const;

  /* Methods to be implemented in derived classes */
  virtual void makeTie  (const size_t __pos = 0) = 0;
  virtual void makeUntie(const size_t __pos = 0) = 0;

  virtual bool isValid() const = 0;
  virtual void addProperty(const std::string& __property, const int __pos = 0) = 0;
  virtual void transpose  (const int __degree, const std::string& __tonality, const std::string& __mode) = 0;
  virtual void enlarge    (const int __factor) = 0;
  virtual void reduce     (const int __factor) = 0;

  virtual std::string toString() const = 0;
  virtual void toStream(void * __output, void * __param1, void * __param2, void * __param3) const = 0;
  virtual void * serialize(const int __version, void * __param) const = 0;

};

} // namespace hautbois

#endif