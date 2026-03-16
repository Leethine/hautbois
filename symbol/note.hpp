#pragma once

#ifndef NOTE_H
#define NOTE_H

#include <string>
#include "symbol_raw/core_types.hpp"

namespace hautbois {
namespace core {

enum class NoteType {
  SingleNote   =  0,
  Chord        =  1,
  Tuplet       =  2,
  Rest         = -1,
  Silence      = -2,
  Grace        =  3,
  Appoggiatura =  4,
  Acciaccatura =  5
};

class Duration;

class Pitch;

class Property;

class Note {

 private:

  NoteType _type;

 protected:

  inline virtual void setNoteType(NoteType __ntype) {
    _type = __ntype;
  }

  virtual void addPitch(Pitch * __p) = 0;

  virtual void setPitch(Pitch * __p, int pos) = 0;

  virtual void addDuration(Duration * __d) = 0;

  virtual void setDuration(Duration * __d, int pos) = 0;

  virtual void addProperty(Property * __p) = 0;

  virtual void setProperty(Property * __p, int pos) = 0;

  virtual Pitch * getPitchyMod(int pos) = 0;

  virtual Duration * getDurationMod(int pos) = 0;

  virtual Property * getPropertyMod(int pos) = 0;

  virtual void clearPitch() = 0;

  virtual void clearDuration() = 0;

  virtual void clearProperty() = 0;

  virtual void * verify(const char * __context) const = 0;

  virtual std::string filterProperty(const std::string& __text) const = 0;

 public:

  inline Note() : _type ( NoteType::Silence ) { }

  inline Note(NoteType __ntype) : _type ( __ntype ) { }

  Note(Note&) = delete;
  
  Note(Note&&) = delete;

  virtual Note& operator=(const Note& __n) = delete;

  inline virtual ~Note() { };

  virtual void updateDuration(const std::string& __context) = 0;

  virtual void updateDuration(const std::string& __context, size_t __pos) = 0;
  
  virtual void updatePitch(const std::string& __context) = 0;

  virtual void updatePitch(const std::string& __context, size_t __pos) = 0;

  virtual void updateProperty(const std::string& __context) = 0;

  virtual void updateProperty(const std::string& __context, size_t __pos) = 0;

  virtual void setTied() = 0;

  virtual void setTied(size_t __pos) = 0;

  virtual void setUntied() = 0;

  virtual void setUntied(size_t __pos) = 0;

  virtual int getSize() const = 0;

  inline virtual NoteType getType() const {
    return _type;
  };

  inline virtual char getTypeChar() const {
    switch (_type) {
      case NoteType::Silence :
        return CHAR_SILENCENOTE_TYPE;
      case NoteType::Rest :
        return CHAR_RESTNOTE_TYPE;
      case NoteType::SingleNote :
        return CHAR_SINGLENOTE_TYPE;
      case NoteType::Chord :
        return CHAR_CHORD_TYPE;
      case NoteType::Tuplet :
        return CHAR_TUPLET_TYPE;
      case NoteType::Grace :
        return CHAR_GRACENOTE_TYPE;
      case NoteType::Acciaccatura :
        return CHAR_ACCIACCATURA_TYPE;
      case NoteType::Appoggiatura :
        return CHAR_APPOGGIATURA_TYPE;
      default :
        return CHAR_SILENCENOTE_TYPE;
    }
  }

  inline virtual std::string getTypeStr() const {
    switch (_type) {
      case NoteType::Silence :
        return "Silence";
      case NoteType::Rest :
        return "Rest";
      case NoteType::SingleNote :
        return "SingleNote";
      case NoteType::Chord :
        return "Chord";
      case NoteType::Tuplet :
        return "Tuplet";
      case NoteType::Grace :
        return "Grace";
      case NoteType::Acciaccatura :
        return "Acciaccatura";
      case NoteType::Appoggiatura :
        return "Appoggiatura";
      default :
        return "";
    }
  }

  inline virtual bool isType(NoteType __ntype) const {
    return _type == __ntype;
  }

  inline virtual bool isSingle() const {
    return _type == NoteType::SingleNote;
  }

  inline virtual bool isRest() const {
    return _type == NoteType::Rest;
  }

  inline virtual bool isSilence() const {
    return _type == NoteType::Silence;
  }

  inline virtual bool isChord() const {
    return _type == NoteType::Chord;
  }

  inline virtual bool isTuplet() const {
    return _type == NoteType::Tuplet;
  }

  inline virtual bool isGrace() const {
    return _type == NoteType::Grace;
  }

  inline virtual bool isAppoggiatura() const {
    return _type == NoteType::Appoggiatura;
  }

  inline virtual bool isAcciaccatura() const {
    return _type == NoteType::Acciaccatura;
  }

  virtual bool isValid() const = 0;

  virtual bool isTied() const = 0;

  virtual bool isTied(size_t __pos) const = 0;

  virtual bool hasDuration() const = 0;

  virtual bool hasDuration(size_t __pos) const = 0;
  
  virtual bool hasPitch() const = 0;

  virtual bool hasPitch(size_t __pos) const = 0;

  virtual bool hasProperty() const = 0;

  virtual bool hasProperty(size_t __pos) const = 0;

  virtual const Duration * getDuration() const = 0;

  virtual const Duration * getDuration(size_t __pos) const = 0;

  virtual const Pitch * getPitch() const = 0;

  virtual const Pitch * getPitch(size_t __pos) const = 0;

  virtual const Property * getProperty() const = 0;

  virtual const Property * getProperty(size_t __pos) const = 0;

  virtual std::string getPropertyStr() const = 0;

  virtual std::string getPropertyStr(size_t __pos) const = 0;

  virtual int getPitchSize() const = 0;

  virtual int getDurationSize() const = 0;

  virtual int getPropertySize() const = 0;

  virtual void modify(const std::string& __context) = 0;

  virtual std::string toString() const = 0;

  virtual void * toStream(const std::string& __context, void * __ostream) const = 0;

};

} // namespace core
} // namespace hautbois

#endif