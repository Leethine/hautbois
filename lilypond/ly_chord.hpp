#pragma once

#include "../symbol/note_chord.hpp"

#ifndef LY_CHORD_H
#define LY_CHORD_H

namespace hautbois {
namespace ly {

class LyChord : public core::Chord {

 protected:

  virtual void setNoteType(core::NoteType __ntype);

  virtual void addPitch(core::Pitch * __p);

  virtual void setPitch(core::Pitch * __p, int __pos);

  virtual void addDuration(core::Duration * __d);

  virtual void setDuration(core::Duration * __d, int __pos);

  virtual void addProperty(core::Property * __p);

  virtual void setProperty(core::Property * __p, int __pos);

  virtual core::Pitch * getPitchMod(int __pos);

  virtual core::Duration * getDurationMod(int __pos);

  virtual core::Property * getPropertyMod(int __pos);

  virtual void clearPitch();

  virtual void clearDuration();

  virtual void clearProperty();

  virtual void * verify(const char * __context) const;

  virtual std::string filterProperty(const std::string& __text) const;

  LyChord(const std::string __value);

 public:
 
  LyChord(const std::vector<std::string>& __pitches,
          const std::string __value);

  LyChord(const std::initializer_list<const char *> __pitches, 
          const std::string __value);

  LyChord(const LyChord& __note);

  LyChord(const LyChord&& __note);

  LyChord(const core::Chord& __note);

  LyChord(const core::Chord&& __note);

  using core::Chord::operator=;
  virtual LyChord& operator=(const LyChord& __n)=delete;

  virtual ~LyChord();

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

  virtual core::NoteType getType() const;

  virtual char getTypeChar() const;

  virtual std::string getTypeStr() const;

  virtual bool isType(core::NoteType __ntype) const;

  virtual bool isSingle() const;

  virtual bool isRest() const;

  virtual bool isSilence() const;

  virtual bool isChord() const;

  virtual bool isTuplet() const;

  virtual bool isGrace() const;

  virtual bool isAppoggiatura() const;

  virtual bool isAcciaccatura() const;

  virtual bool isValid() const;

  virtual bool isTied() const;

  virtual bool isTied(size_t __pos) const;

  virtual bool hasDuration() const;

  virtual bool hasDuration(size_t __pos) const;

  virtual bool hasPitch() const;

  virtual bool hasPitch(size_t __pos) const;

  virtual bool hasProperty() const;

  virtual bool hasProperty(size_t __pos) const;

  virtual const core::Duration * getDuration() const;

  virtual const core::Duration * getDuration(size_t __pos) const;

  virtual const core::Pitch * getPitch() const;

  virtual const core::Pitch * getPitch(size_t __pos) const;

  virtual const core::Property * getProperty() const;

  virtual const core::Property * getProperty(size_t __pos) const;

  virtual std::string getPropertyStr() const;

  virtual std::string getPropertyStr(size_t __pos) const;

  virtual int getPitchSize() const;

  virtual int getDurationSize() const;

  virtual int getPropertySize() const;

  virtual void modify(const std::string& __context);

  virtual std::string toString() const;

  virtual void * toStream(const std::string& __context, void * __ostream) const;

};


} // namespace ly
} // namespace hautbois

#endif