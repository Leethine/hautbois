#pragma once

#ifndef BASE_NOTE_H
#define BASE_NOTE_H

#include <utility>
#include <vector>
#include <algorithm>

#include "basetypes/base_def_types.hpp"
#include "basetypes/note_enum_types.hpp"
#include "charts/sci_notename_to_index.hpp"
#include "base_duration.hpp"
#include "base_note_property.hpp"

namespace hautbois {
namespace core {

class BaseNote {
 private:
  NoteNameEnum _name;
  AccidentalEnum _accidental;
  OctaveEnum _octave;
  UInt8 _index;
  bool _connected;
  BaseDuration * _duration;

  std::vector<NoteNameEnum> * _chordNoteNameList;
  std::vector<AccidentalEnum> * _chordAccidentalList;
  std::vector<OctaveEnum> * _chordOctaveList;
  std::vector<UInt8> * _chordIndexList;

  BaseNoteProperty * _property;

 protected:
  BaseNote();

  inline virtual void setNoteName(NoteNameEnum ivName) {
    _name = ivName;
  }

  inline virtual void setAccidental(AccidentalEnum ivAccidental) {
    _accidental = ivAccidental;
  }

  inline virtual void setIndex(const UInt8 ivIndex) {
    _index = ivIndex;
  }

  virtual void setNoteName(const std::string& ivName);

  virtual void setAccidental(const std::string& ivAccidental);

  virtual void setIndex(const std::string& ivIndex);

  inline virtual void setDuration(const UInt8 ivNum, const UInt8 ivDenom) {
    delete _duration;
    _duration = new BaseDuration(ivNum, ivDenom);
  }

  inline virtual void setDuration(const UInt8 ivValueD, const std::string& ivDotsS) {
    delete _duration;
    _duration = new BaseDuration(ivValueD, ivDotsS);
  }

  virtual void throwInvalidInputException(const std::string& ivArg,
                                          const std::string& ivMethod) const;

  virtual UInt8 findIndexFromFullNoteName(const std::string& ivName) const;

  virtual bool checkFullNoteNameInput(const std::string& ivNameS,
                                      const std::string& ivAccS,
                                      const std::string& ivOctaveS) const;

  virtual bool checkDottedDurationInput(const UInt8 ivValueD,
                                        const std::string& ivDotsS) const;

  virtual bool checkChordList(const std::vector<std::string>& ivSciNoteVec);

  virtual void throwExceptionForChordListInput(const std::string& ivMathod, 
                               const std::vector<std::string>& ivSciNoteVec);
 
  virtual void addToChordList(const std::string& ivFullNoteNameStr);

  virtual void reinitChordList();

  virtual void makeChordFromList(const std::vector<std::string>& 
                                                    ivSciNoteVec);

 public: 
  BaseNote(const std::string& ivNameS, const std::string& ivAccS,
           const std::string& ivOctaveS, UInt8 ivNumD, UInt8 ivDenomD);

  BaseNote(const std::string& ivNameS, const std::string& ivAccS,
           const std::string& ivOctaveS,
           const UInt8 ivNoteValueD, const std::string& ivDotsS);

  BaseNote(const std::vector<std::string>& ivListNoteV,
           UInt8 ivNumD, UInt8 ivDenomD);

  BaseNote(const std::vector<std::string>& ivListNoteV,
           const UInt8 ivNoteValueD, const std::string& ivDotsS);

  ~BaseNote();

  inline virtual std::string getNoteNameAsString() const {
    return notename_str_enum_convert::SCINAME_ENUM_TO_STRING.at(_name);
  }

  inline virtual std::string getAccidentalAsString() const {
    return accidental_str_enum_convert::ACCIDENTAL_ENUM_TO_STRING.at(_accidental);
  }

  inline virtual std::string getOctaveAsString() const {
    return octave_str_enum_convert::OCTAVE_ENUM_TO_STRING.at(_octave);
  }

  inline virtual UInt8 getOctaveAsInt() const {
    return (UInt8)
      std::stoi(octave_str_enum_convert::OCTAVE_ENUM_TO_STRING.at(_octave));
  }

  virtual BaseDuration getDuration() const;

  inline virtual std::string getIndexAsString() const {
    return std::to_string(_index);
  }

  virtual UInt8 getIndexAsInt() const {
    return _index;
  }

  virtual std::string getFullNoteNameAsString() const;

  virtual std::string getDurationAsString() const;

  inline virtual NoteNameEnum getNoteName() const {
    return this->_name;
  }

  inline virtual AccidentalEnum getAccidental() const {
    return this->_accidental;
  }

  inline virtual UInt8 getIndex() const {
    return this->_index;
  }

  inline virtual void setConnected() {
    this->_connected = true;
  }

  inline virtual void unsetConnected() {
    this->_connected = false;
  }

  virtual void addProperty(const std::string& ivProperty);
  
  virtual void addProperty(const std::string& ivProperty, UInt8 ivValue);

  using PropertyType = std::string;
  using PropertyNameValuePair = std::pair<std::string, UInt8>;
  virtual std::map<PropertyType, PropertyNameValuePair> getPropertyAsMap() const;

  virtual BaseNoteProperty getProperty() const;
};

} // namespace core
} // namespace hautbois

#endif