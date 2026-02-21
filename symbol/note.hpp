#pragma once

#ifndef NOTE_H
#define NOTE_H

#include <vector>
#include <string>
#include <tuple>

namespace hautbois {
namespace core {

enum class NoteType {
  SingleNote =  0,
  Chord      =  1,
  Tuplet     =  2,
  Rest       = -1,
  Silence    = -2
};

class Duration;

class Pitch;

class Property;

class Note {

 private:

  NoteType _type;

  Duration * _duration;

  std::vector<Pitch *> _pitch;

  Property * _property;

  bool _tied = false;

 protected:

  virtual void setNoteType(NoteType __ntype);

  virtual void addPitch(Pitch * __p);

  virtual void setPitch(Pitch * __p);

  virtual void clearPitch();

  virtual void setDuration(Duration * __d);

  virtual void setProperty(Property * __p);

  virtual NoteType guessNoteType(const std::string& __input) const;

  virtual bool checkFormatThrowExp(const std::string& __pitch) const;

  virtual std::tuple<std::string, std::string, std::string> 
    parseSingleNote(const std::string& __pitch) const;

  virtual std::vector< std::tuple<std::string, std::string, std::string> >
    parseGroupNote(const std::string& __pitch, NoteType __type=NoteType::Chord) const;

  virtual std::string filterProperty(const std::string& __text) const;

 public:

  Note();

  Note(const int& __num, const int& __denom);

  Note(const int& __num, const int& __denom, const std::string& __pitch);

  Note(const Note& __n);

  Note(const Note&& __n);

  virtual ~Note();

  virtual Note& operator=(const Note& __n);

  virtual void updateDuration(const std::string& __context);
  
  virtual void updatePitch(const std::string& __context);

  virtual void updateProperty(const std::string& __context);

  virtual void setTied();

  virtual void setUntied();

  virtual bool hasProperty() const;

  virtual int pitchSize() const;

  virtual NoteType getType() const;

  virtual char getTypeChar() const;

  virtual std::string getTypeStr() const;

  virtual bool isType(NoteType iType) const;

  virtual bool isSingle() const;

  virtual bool isChord() const;

  virtual bool isRest() const;

  virtual bool isSilent() const;

  virtual bool isTuplet() const;

  virtual bool isValid() const;

  virtual bool isTied() const;

  virtual const Duration * getDuration() const;

  virtual const Pitch * getPitch() const;

  virtual const Property * getProperty() const;

  virtual const std::vector<const Pitch *> getPitchGroup() const;

  virtual std::string getDurationStr() const;

  virtual std::string getPitchStr() const;

  virtual std::vector<std::string> getPitchGroupStr() const;

  virtual std::string getPropertyStr() const;

  virtual std::string toString() const;

  virtual void * toStream(const std::string& __context, void * __ostream) const;

};

} // namespace core
} // namespace hautbois

#endif