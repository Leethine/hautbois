#include "base_note.hpp"

#include "basetypes/base_def_types.hpp"
#include "basetypes/note_enum_types.hpp"
#include "charts/sci_notename_to_index.hpp"
#include "base_duration.hpp"
#include "base_note_property.hpp"

#include <utility>
#include <vector>
#include <algorithm>
#include <exception>

hautbois::core::BaseNote::BaseNote():
  _name {NoteNameEnum::C},
  _accidental {AccidentalEnum::n},
  _octave {OctaveEnum::fourth},
  _index {40},
  _connected {false},
  _duration {nullptr},
  _chordNoteNameList {nullptr},
  _chordAccidentalList {nullptr},
  _chordOctaveList {nullptr},
  _chordIndexList {nullptr},
  _property {nullptr} {
}

hautbois::core::BaseNote::BaseNote(const BaseNote& ivRhNote) {
  BaseNote();
  this->_name = ivRhNote._name;
  this->_accidental = ivRhNote._accidental;
  this->_octave = ivRhNote._octave;
  this->_index = ivRhNote._index;
  this->_connected = ivRhNote._connected;
  this->_duration = new BaseDuration(*ivRhNote._duration);
  if(ivRhNote._chordNoteNameList) {
    this->_chordNoteNameList = new std::vector<NoteNameEnum>(*ivRhNote._chordNoteNameList);
  }
  if(ivRhNote._chordAccidentalList) {
    this->_chordAccidentalList = new std::vector<AccidentalEnum>(*ivRhNote._chordAccidentalList);
  }
  if(ivRhNote._chordOctaveList) {
    this->_chordOctaveList = new std::vector<OctaveEnum>(*ivRhNote._chordOctaveList);
  }
  if(ivRhNote._chordIndexList) {
    this->_chordIndexList = new std::vector<UInt8>(*ivRhNote._chordIndexList);
  }
  // No property copying
}

void hautbois::core::BaseNote::setNoteName(const std::string& ivName) {
  if (notename_str_enum_convert::SCINAME_STRING_TO_ENUM.find(ivName)
      != notename_str_enum_convert::SCINAME_STRING_TO_ENUM.end()) {
    _name = notename_str_enum_convert::SCINAME_STRING_TO_ENUM.at(ivName);
  }
  else {
    throwInvalidInputException(ivName, "<base_note::setNoteName>");
  }
}

void hautbois::core::BaseNote::setAccidental(const std::string& ivAccidental) {
  if (accidental_str_enum_convert::ACCIDENTAL_STRING_TO_ENUM.find(ivAccidental)
      != accidental_str_enum_convert::ACCIDENTAL_STRING_TO_ENUM.end()) {
    _accidental = accidental_str_enum_convert::ACCIDENTAL_STRING_TO_ENUM.at(ivAccidental);
  }
  else {
    throwInvalidInputException(ivAccidental, "<base_note::setAccidental>");
  }
}

void hautbois::core::BaseNote::setIndex(const std::string& ivIndex) {
  auto tvIndex = std::stoi(ivIndex); 
  if (tvIndex <= INT8_MAX && tvIndex >= 0) {
    _index = (UInt8) tvIndex;
  }
  else {
    throwInvalidInputException(ivIndex, "<base_note::setIndex>");
  }
}

void hautbois::core::BaseNote::throwInvalidInputException
  (const std::string& ivArg, const std::string& ivMethod) const {
  throw InvalidArgumentException("InvalidInputArgs: "
                               + ivArg + " in " + ivMethod);
  exit(INVALID_INPUT_ERROR);
}

hautbois::UInt8 hautbois::core::BaseNote::findIndexFromFullNoteName
  (const std::string& ivName) const {
  if (notename_str_index_table::SCINAME_STRING_TO_INDEX.find(ivName)
      != notename_str_index_table::SCINAME_STRING_TO_INDEX.end()) {
    return notename_str_index_table::SCINAME_STRING_TO_INDEX.at(ivName);
  }
  else {
    throwInvalidInputException(ivName, "<BaseNote::findIndexFromFullNoteName>");
  }
  return ERROR_NOTE_INDEX;
}

bool hautbois::core::BaseNote::checkFullNoteNameInput
  (const std::string& ivNameS,
   const std::string& ivAccS, const std::string& ivOctaveS) const {

  bool tvNameOK = 
    notename_str_enum_convert::SCINAME_STRING_TO_ENUM.find(ivNameS)
    != notename_str_enum_convert::SCINAME_STRING_TO_ENUM.end();

  bool tvAccidentalOK =
    accidental_str_enum_convert::ACCIDENTAL_STRING_TO_ENUM.find(ivAccS)
    != accidental_str_enum_convert::ACCIDENTAL_STRING_TO_ENUM.end();

  bool tvOctaveOK =
    octave_str_enum_convert::OCTAVE_STRING_TO_ENUM.find(ivOctaveS)
    != octave_str_enum_convert::OCTAVE_STRING_TO_ENUM.end();

  if (tvNameOK && tvAccidentalOK && tvOctaveOK) {
    return true;
  }
  else {
    throwInvalidInputException("NoteName: " + ivNameS +
                              " Accidental: " + ivAccS +
                              " Octave: " + ivOctaveS,
                                "<BaseNote::checkFullNoteNameInput>");
  }
  return false;
}

bool hautbois::core::BaseNote::checkDottedDurationInput
  (const UInt8 ivValueD, const std::string& ivDotsS) const {

  size_t tvNbrDots = std::count(ivDotsS.begin(), ivDotsS.end(), '.');
  if (tvNbrDots != ivDotsS.length() || ivValueD <= 0) {
    throw InvalidArgumentException("DottedValue: "
                                  + std::to_string(ivValueD) + ivDotsS);
    return false;
  }
  else { return true; }
}

bool hautbois::core::BaseNote::checkChordList(const std::vector<std::string>& ivSciNoteVec) {
  bool ovStatus = true;
  // check if the note names are uniform
  for (auto it = ivSciNoteVec.begin(); it != ivSciNoteVec.end(); it++) {
    if (it->size() != 2 || it->size() != 3 || it->size() != 4) {
      ovStatus = false;
    }
    // if length is 2 ==> "C2","D2",etc...
    if (it->size() == 2) {
      ovStatus =
        checkFullNoteNameInput(it->substr(0,1), "n", it->substr(1,1));
    }
    // if length is 3 ==> "C#2","Db2",etc...
    if (it->size() == 3) {
      ovStatus = checkFullNoteNameInput(it->substr(0,1), it->substr(1,1),
                                        it->substr(2,1));
    }
    // if length is 4 ==> "Css2","Dbb2",etc...
    if (it->size() == 4) {
      ovStatus = checkFullNoteNameInput(it->substr(0,1), it->substr(1,2),
                                        it->substr(3,1));
    }
  }
  return ovStatus;
}

void hautbois::core::BaseNote::throwExceptionForChordListInput
  (const std::string& ivMathod, const std::vector<std::string>& ivSciNoteVec) {

  std::string tvArgList;
  for (const auto &arg : ivSciNoteVec) tvArgList += arg + ",";
  tvArgList.pop_back(); // pop the last ','
  throwInvalidInputException("["+tvArgList+"]", ivMathod);
}

void hautbois::core::BaseNote::addToChordList(const std::string& ivFullNoteNameStr) {
  _chordIndexList->push_back(findIndexFromFullNoteName(ivFullNoteNameStr));

  if (ivFullNoteNameStr.size() == 2) {
    _chordNoteNameList->push_back(
      notename_str_enum_convert::SCINAME_STRING_TO_ENUM.at(
        ivFullNoteNameStr.substr(0,1)));

    _chordAccidentalList->push_back(AccidentalEnum::n);

    _chordOctaveList->push_back(
      octave_str_enum_convert::OCTAVE_STRING_TO_ENUM.at(
        ivFullNoteNameStr.substr(1,1)));
  }
  else if (ivFullNoteNameStr.size() == 3) {
    _chordNoteNameList->push_back(
      notename_str_enum_convert::SCINAME_STRING_TO_ENUM.at(
        ivFullNoteNameStr.substr(0,1)));

    _chordAccidentalList->push_back(
      accidental_str_enum_convert::ACCIDENTAL_STRING_TO_ENUM.at(
        ivFullNoteNameStr.substr(1,1)));

    _chordOctaveList->push_back(
      octave_str_enum_convert::OCTAVE_STRING_TO_ENUM.at(
        ivFullNoteNameStr.substr(2,1)));
  }
  else if (ivFullNoteNameStr.size() == 4) {
    _chordNoteNameList->push_back(
      notename_str_enum_convert::SCINAME_STRING_TO_ENUM.at(
        ivFullNoteNameStr.substr(0,1)));

    _chordAccidentalList->push_back(
      accidental_str_enum_convert::ACCIDENTAL_STRING_TO_ENUM.at(
        ivFullNoteNameStr.substr(1,2)));

    _chordOctaveList->push_back(
      octave_str_enum_convert::OCTAVE_STRING_TO_ENUM.at(
        ivFullNoteNameStr.substr(3,1)));
  }
  else {
    throwInvalidInputException(ivFullNoteNameStr,"<BaseNote::addToChordList>");
  }
}

void hautbois::core::BaseNote::reinitChordList() {
  delete _chordNoteNameList;
  delete _chordAccidentalList;
  delete _chordOctaveList;
  delete _chordIndexList;
  _chordNoteNameList = new std::vector<NoteNameEnum>;
  _chordAccidentalList = new std::vector<AccidentalEnum>;
  _chordOctaveList = new std::vector<OctaveEnum>;
  _chordIndexList = new std::vector<UInt8>;
}

void hautbois::core::BaseNote::makeChordFromList
  (const std::vector<std::string>& ivSciNoteVec) {
  
  reinitChordList();
  
  if (checkChordList(ivSciNoteVec)) {
    for (auto it = ivSciNoteVec.begin(); it != ivSciNoteVec.end(); it++) {
      addToChordList(*it);
    }
  }
  else {
    throwExceptionForChordListInput("<BaseNote::makeChordFromList>",
                                    ivSciNoteVec);
  }

  // post-check chordlist size
  if (_chordNoteNameList->size() != _chordAccidentalList->size() ||
      _chordNoteNameList->size() != _chordOctaveList->size() ||
      _chordAccidentalList->size() != _chordOctaveList->size()) {
    throw RunTimeException("Runtime Error: non uniformed Chord list!");
    exit(RUNTIME_ERROR);
  }
}

hautbois::core::BaseNote::BaseNote(const std::string& ivNameS,
                                   const std::string& ivAccS,
                                   const std::string& ivOctaveS,
                                   UInt8 ivNumD, UInt8 ivDenomD):
  _duration {nullptr},
  _chordNoteNameList {nullptr},
  _chordAccidentalList {nullptr},
  _chordOctaveList {nullptr},
  _chordIndexList {nullptr},
  _property {nullptr} {
  
  if (!checkFullNoteNameInput(ivNameS, ivAccS, ivOctaveS)) {
    exit(INVALID_INPUT_ERROR);
  }
  
  _name = notename_str_enum_convert::SCINAME_STRING_TO_ENUM.at(ivNameS);
  _accidental = accidental_str_enum_convert::ACCIDENTAL_STRING_TO_ENUM.at(ivAccS);
  _octave = octave_str_enum_convert::OCTAVE_STRING_TO_ENUM.at(ivOctaveS);
  _index = findIndexFromFullNoteName(ivNameS+ivAccS+ivOctaveS);
  _duration = new BaseDuration(ivNumD, ivDenomD);
  _connected = false;
}

hautbois::core::BaseNote::BaseNote(const std::string& ivNameS,
                                   const std::string& ivAccS,
                                   const std::string& ivOctaveS,
                                   const UInt8 ivNoteValueD, const std::string& ivDotsS):
  _duration {nullptr},
  _chordNoteNameList {nullptr},
  _chordAccidentalList {nullptr},
  _chordOctaveList {nullptr},
  _chordIndexList {nullptr},
  _property {nullptr} {

  if (!checkFullNoteNameInput(ivNameS, ivAccS, ivOctaveS) ||
      !checkDottedDurationInput(ivNoteValueD, ivDotsS) ) {
    exit(INVALID_INPUT_ERROR);
  }

  _name = notename_str_enum_convert::SCINAME_STRING_TO_ENUM.at(ivNameS);
  _accidental =
    accidental_str_enum_convert::ACCIDENTAL_STRING_TO_ENUM.at(ivAccS);
  _octave = octave_str_enum_convert::OCTAVE_STRING_TO_ENUM.at(ivOctaveS);
  _index = findIndexFromFullNoteName(ivNameS+ivAccS+ivOctaveS);
  _duration = new BaseDuration(ivNoteValueD, ivDotsS);
  _connected = false;
}

hautbois::core::BaseNote::BaseNote(const std::vector<std::string>& ivListNoteV,
                                   UInt8 ivNumD, UInt8 ivDenomD):
  _duration {nullptr},
  _chordNoteNameList {nullptr},
  _chordAccidentalList {nullptr},
  _chordOctaveList {nullptr},
  _chordIndexList {nullptr},
  _property {nullptr} {
  
  _name = NoteNameEnum::CHORD;
  _accidental = AccidentalEnum::n;
  _octave = OctaveEnum::zeroth;
  _index = CHORD_INDEX;

  _duration = new BaseDuration(ivNumD, ivDenomD);
  _connected = false;
  makeChordFromList(ivListNoteV);
}

hautbois::core::BaseNote::BaseNote(const std::vector<std::string>& ivListNoteV,
                                   const UInt8 ivNoteValueD,
                                   const std::string& ivDotsS):
  _duration {nullptr},
  _chordNoteNameList {nullptr},
  _chordAccidentalList {nullptr},
  _chordOctaveList {nullptr},
  _chordIndexList {nullptr},
  _property {nullptr} {

  _name = NoteNameEnum::CHORD;
  _accidental = AccidentalEnum::n;
  _octave = OctaveEnum::zeroth;
  _index = CHORD_INDEX;

  _duration = new BaseDuration(ivNoteValueD, ivDotsS);
  _connected = false;
  makeChordFromList(ivListNoteV);
}

hautbois::core::BaseNote::~BaseNote() {
  if (_duration) {
    delete _duration;
  }
  if (_chordNoteNameList) {
    delete _chordNoteNameList;
  }
  if (_chordAccidentalList) {
    delete _chordAccidentalList;
  }
  if (_chordOctaveList) {
    delete _chordOctaveList;
  }
  if (_chordIndexList) {
    delete _chordIndexList;
  }
  if (_property) {
    delete _property;
  }
}

hautbois::core::BaseDuration hautbois::core::BaseNote::getDuration() const {
  if (_duration == nullptr) {
    return BaseDuration(1,1);
  }
  else {
    return BaseDuration(*_duration);
  }
}

std::string hautbois::core::BaseNote::getFullNoteNameAsString() const {
  if (_name != NoteNameEnum::CHORD && _name != NoteNameEnum::XPLET) {
    return getNoteNameAsString()
         + getAccidentalAsString() + getOctaveAsString();
  }
  else {
    std::string tvConnector;
    if (_name == NoteNameEnum::CHORD) {
      tvConnector = "+";
    }
    if (_name == NoteNameEnum::XPLET) {
      tvConnector = "-";
    } 

    if (_chordNoteNameList == nullptr ||
        _chordAccidentalList == nullptr ||
        _chordIndexList == nullptr) {
      throw RunTimeException("Runtime error: No Chordlist available!"); 
      exit(RUNTIME_ERROR);
    }
    if (_chordNoteNameList->size() != _chordAccidentalList->size() ||
        _chordNoteNameList->size() != _chordIndexList->size() ||
        _chordAccidentalList->size() != _chordIndexList->size()) {
      throw RunTimeException("Runtime error: Non-uniform Chordlist size!"); 
      exit(RUNTIME_ERROR);
    }
    std::vector<NoteNameEnum> tvNameVec = * _chordNoteNameList;
    std::vector<AccidentalEnum> tvAccVec = * _chordAccidentalList;
    std::vector<OctaveEnum> tvOctVec = * _chordOctaveList;
    std::string ovChordName;
    for (size_t i = 0; i < tvNameVec.size(); i++) {
      ovChordName +=
        notename_str_enum_convert::SCINAME_ENUM_TO_STRING.at(tvNameVec[i]);
      ovChordName +=
        accidental_str_enum_convert::ACCIDENTAL_ENUM_TO_STRING.at(tvAccVec[i]);
      ovChordName +=
        octave_str_enum_convert::OCTAVE_ENUM_TO_STRING.at(tvOctVec[i]);
      ovChordName += tvConnector;
    }
    ovChordName.pop_back(); // pop the last char '+'
    return ovChordName;
  }
}

std::string hautbois::core::BaseNote::getDurationAsString() const {
  if (_duration == nullptr) {
    return "?/?";
  }
  else {
    return std::to_string((UInt64) _duration->getNum()) + "/"
         + std::to_string((UInt64) _duration->getDenom());
  }
}

void hautbois::core::BaseNote::addProperty(const std::string& ivProperty) {
  if (_property == nullptr) {
    _property = new BaseNoteProperty();
  }
  _property->set(ivProperty);
}

void hautbois::core::BaseNote::addProperty(const std::string& ivProperty, UInt8 ivValue) {
  if (_property == nullptr) {
    _property = new BaseNoteProperty();
  }
  _property->set(ivProperty, ivValue);
}

std::map<std::string, hautbois::core::BaseNote::PropertyNameValuePair>
  hautbois::core::BaseNote::getPropertyAsMap() const {
  std::map<std::string, hautbois::core::BaseNote::PropertyNameValuePair> ovMap;
  if (_property == nullptr) {
    return ovMap;
  }
  else {
    if (_property->hasArticulation()) {
      auto tvPair = _property->getArticulation();
      //ovMap.emplace("articulation", tvPair);
      ovMap.emplace("a", tvPair);
    }
    if (_property->hasDynamics()) {
      auto tvPair = _property->getDynamics();
      //ovMap.emplace("dynamics", tvPair);
      ovMap.emplace("d", tvPair);
    }
    if (_property->hasOrnament()) {
      auto tvPair = _property->getOrnament();
      //ovMap.emplace("ornament", tvPair);
      ovMap.emplace("o", tvPair);
    }
    return ovMap;
  }
}

hautbois::core::BaseNoteProperty hautbois::core::BaseNote::getProperty() const {
  if (_property == nullptr) {
    return BaseNoteProperty();
  }
  else {
    return BaseNoteProperty(*_property);
  }
}

hautbois::core::BaseNoteProperty * hautbois::core::BaseNote::getPropertyPtr() const {
  return _property;
}