#pragma once

#ifndef SINGLENOTE_HPP
#define SINGLENOTE_HPP

#include "note.hpp"

namespace hautbois {

class SingleNote : public Note {

protected:

  inline virtual void setNote(Note * __ptr, const int __pos) {
    Note::setNote(__ptr, __pos);
  }

  inline virtual void setPitch(Pitch * __ptr, const int __pos) {
    Note::setPitch(__ptr, __pos);
  }

  inline virtual void setDuration(Duration * __ptr, const int __pos) {
    Note::setDuration(__ptr, __pos);
  }

  inline virtual void setProperty(Property * __ptr, const int __pos) {
    Note::setProperty(__ptr, __pos);
  }

  inline virtual Pitch * getPitchModify(const size_t __pos) {
    return Note::getPitchModify(__pos);
  }

  inline virtual Duration * getDurationModify(const size_t __pos) {
    return Note::getDurationModify(__pos);
  }

  inline virtual Property * getPropertyModify(const size_t __pos) {
    return Note::getPropertyModify(__pos);
  }

  inline virtual Note * getNoteModify(const size_t __pos) {
    return Note::getNoteModify(__pos);
  }

  virtual void setNoteType(const char __note_type);

public:

  inline virtual ~SingleNote() {}

  inline virtual bool isType(const char __note_type) const {
    return Note::isType(__note_type);
  }

  inline virtual char getType() const {
    return Note::getType();
  }

  inline virtual void makeTie(const size_t __pos = 0) {
    Note::makeTie(0);
  }

  inline virtual void makeUntie(const size_t __pos = 0) {
    Note::makeUntie(0);
  }

  inline virtual bool isTied(const size_t __pos = 0) const {
    return Note::isTied(0);
  }

  inline virtual const Pitch * getPitch(const size_t __pos = 0) const {
    return Note::getPitch(0);
  }

  inline virtual const Duration * getDuration(const size_t __pos = 0) const {
    return Note::getDuration(0);
  }

  inline virtual const Property * getProperty(const size_t __pos = 0) const {
    return Note::getProperty(0);
  }

  inline virtual const Note * getNote(const size_t __pos = 0) const {
    return nullptr;
  }

  SingleNote(const std::string& __pitch, const std::string& __value);
  
  SingleNote(const SingleNote& __other);

  SingleNote(const SingleNote&& __other);

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