#pragma once

#ifndef NOTE_H
#define NOTE_H

#include "basic/basic_note.hpp"

#include <vector>
#include <string>

namespace hautbois {
namespace core {

enum class NoteType {
  SingleNote =  0,
  Chord      =  1,
  Xuplet     =  2,
  Rest       = -1,
  Silence    = -2
};

class Note : public BasicNote {

 private:

  NoteType _type;

  virtual NoteType getNoteTypeFromInput(const std::string& iPitch) const;

  virtual bool checkPitchStrFormat(const std::string& iPitch) const;

  virtual void parseSingleNote(const std::string& iPitch);

  virtual void parseGroupNote(const std::string& iPitch, NoteType iType=NoteType::Chord);

 protected:

  virtual void setNoteType(NoteType iType);

  virtual void processProperty(const std::string& style);

 public:

  Note(const int iNum, const int iDenom, const std::string& iPitch);

  Note(const Note& iN);

  Note(const Note&& iN);

  virtual ~Note();

  virtual void updateProperty(const std::string& iFreeTxt);

  virtual void clearProperty();

  virtual bool hasProperty();

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

  virtual const Duration getDuration() const;

  virtual std::string getPitch() const;

  virtual std::vector<std::string> getChord() const;

  virtual std::vector<std::string> getTuplet() const;

  virtual std::string getProperty() const;

  virtual std::string toString() const;

  virtual void * toStream(const std::string& iStreamType) const;

};

} // namespace core
} // namespace hautbois

#endif