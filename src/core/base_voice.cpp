#include "base_voice.hpp"

hautbois::core::BaseVoice::BaseVoice() {}

hautbois::core::BaseVoice::BaseVoice(const BaseVoice& ivRhVoice) {
  for (auto i = 0; i < ivRhVoice.getNumberOfNotes(); ++i) {
    BaseNote * newnote = new BaseNote(*getNote(i));
    _voice.push_back(newnote);
  }
}

hautbois::core::BaseVoice::~BaseVoice() {
  for (auto it = _voice.begin(); it != _voice.end(); ++it) {
    delete (*it);
  }
}

hautbois::core::BaseDuration hautbois::core::BaseVoice::countTotalDuration() const {
  BaseDuration totalDuration (0, 1);
  if (_voice.empty()) {
    return totalDuration;
  }
  for (auto it = _voice.begin(); it != _voice.end(); it++) {
    BaseNote * curNotePtr = (*it);
    totalDuration += curNotePtr->getDuration();
  }
  return totalDuration;
}

bool hautbois::core::BaseVoice::checkFull(const BaseDuration& ivFullDuration) const {
  if (_voice.empty() && ivFullDuration.getNum() != 0) {
    return false;
  }

  BaseDuration totalDuration = countTotalDuration();
  if (totalDuration >= ivFullDuration) {
    return true;
  }
  else {
    return false;
  }
}

bool hautbois::core::BaseVoice::padVoice(const BaseDuration& ivFullDuration, NoteNameEnum ivNoteName, bool ivPadFront=false) {
  BaseNote * paddingNote = nullptr;
  if (!checkFull(ivFullDuration)) {
    BaseDuration totalDuration = countTotalDuration();
    BaseDuration fullDuration = BaseDuration(ivFullDuration);
    BaseDuration paddingDuration = fullDuration - totalDuration;
    if (ivNoteName == NoteNameEnum::S) {
      paddingNote = new BaseNote("S", "", "", paddingDuration.getNum(),  paddingDuration.getDenom());
    }
    else if (ivNoteName == NoteNameEnum::R) {
      paddingNote = new BaseNote("R", "", "", paddingDuration.getNum(),  paddingDuration.getDenom());
    }
    else {
      throw LogicError("Error in BaseVoice::padVoice, Rest or Silence note only");
      return false;
    }
    if (ivPadFront) {
      _voice.insert(_voice.begin(), paddingNote);
    }
    else {
      _voice.push_back(paddingNote);
    }
  }
  else {
    throw OutOfRangeException("Error in BaseVoice::padVoice. Total duration: " + countTotalDuration().toString() + " Given max duration: " + ivFullDuration.toString());
    return false;
  }
  return true;
}

bool hautbois::core::BaseVoice::frontPadWithSilence(const BaseDuration& ivFullDuration) {
  return padVoice(ivFullDuration, NoteNameEnum::S, true);
}

bool hautbois::core::BaseVoice::frontPadWithRest(const BaseDuration& ivFullDuration) {
  return padVoice(ivFullDuration, NoteNameEnum::R, true);
}

bool hautbois::core::BaseVoice::backPadWithSilence(const BaseDuration& ivFullDuration) {
  return padVoice(ivFullDuration, NoteNameEnum::S, false);
}

bool hautbois::core::BaseVoice::backPadWithRest(const BaseDuration& ivFullDuration) {
  return padVoice(ivFullDuration, NoteNameEnum::R, false);
}

void hautbois::core::BaseVoice::trimFront(const BaseDuration& ivFullDuration) {
  if (_voice.empty()) {
    return ;
  }
  BaseDuration totalDuration = countTotalDuration();
  if (totalDuration > ivFullDuration) {
    BaseDuration extraDuration = totalDuration - ivFullDuration;
    BaseDuration zeroDuration(0,4);
    while (extraDuration > zeroDuration) {
      if (extraDuration >= _voice.front()->getDuration()) {
        extraDuration = extraDuration - _voice.front()->getDuration();
        BaseNote* frontNotePtr = _voice.front();
        _voice.erase(_voice.begin());
        delete frontNotePtr;
      }
      else {
        BaseNote* oldFrontNotePtr = _voice.front();
        BaseNote* newFrontNotePtr = new BaseNote(oldFrontNotePtr->getNoteNameAsString(), oldFrontNotePtr->getAccidentalAsString(), oldFrontNotePtr->getOctaveAsString(), extraDuration.getNum(), extraDuration.getDenom());
        _voice.front() = newFrontNotePtr;
        delete oldFrontNotePtr;
        extraDuration = zeroDuration;
      }
    }
  }
  else {
    // array not full, nothing to trim
    return ;
  }
}

void hautbois::core::BaseVoice::trimBack(const BaseDuration& ivFullDuration) {
  if (_voice.empty()) {
    return ;
  }
  BaseDuration totalDuration = countTotalDuration();
  if (totalDuration > ivFullDuration) {
    BaseDuration extraDuration = totalDuration - ivFullDuration;
    BaseDuration zeroDuration(0,4);
    while (extraDuration > zeroDuration) {
      if (extraDuration >= _voice.back()->getDuration()) {
        extraDuration = extraDuration - _voice.back()->getDuration();
        BaseNote* backNotePtr = _voice.back();
        _voice.pop_back();
        delete backNotePtr;
      }
      else {
        BaseNote* oldBackNotePtr = _voice.back();
        BaseNote* newBackNotePtr = new BaseNote(oldBackNotePtr->getNoteNameAsString(), oldBackNotePtr->getAccidentalAsString(), oldBackNotePtr->getOctaveAsString(), extraDuration.getNum(), extraDuration.getDenom());
        _voice.front() = newBackNotePtr;
        delete oldBackNotePtr;
        extraDuration = zeroDuration;
      }
    }
  }
  else {
    // array not full, nothing to trim
    return ;
  }
}

void hautbois::core::BaseVoice::appendNote(BaseNote* ivNote) {
  if (ivNote != nullptr) {
    _voice.push_back(ivNote);
  }
}

void hautbois::core::BaseVoice::insertNote(BaseNote* ivNote, UInt16 ivPosition=0) {
  if (ivPosition >= _voice.size()) {
    throw OutOfRangeException("<BaseVoice::insertNote> position: " + std::to_string(ivPosition) + " but the number of notes is " + std::to_string(_voice.size()));
  }
  else {
    if (ivNote != nullptr) {
      auto iter = _voice.begin();
      for (int i=0; i < ivPosition; i++) {
        iter++;
      }
      _voice.insert(iter, ivNote);
    }
  }
}

hautbois::core::BaseNote* hautbois::core::BaseVoice::getNote(UInt16 ivPosition) const {
  if (ivPosition >= _voice.size()) {
    throw OutOfRangeException("<BaseVoice::insertNote> position: " + std::to_string(ivPosition) + " but the number of notes is " + std::to_string(_voice.size()));
    return nullptr;
  }
  else {
    return _voice[ivPosition];
  }
}

hautbois::core::BaseNote* hautbois::core::BaseVoice::getNoteNoRangeLimit(UInt16 ivPosition) const {
  if (ivPosition >= _voice.size()) {
    return _voice.back();
  }
  else {
    return _voice[ivPosition];
  }
}

void hautbois::core::BaseVoice::deleteNote(UInt16 ivPosition) {
  if (ivPosition >= _voice.size()) {
    throw OutOfRangeException("<BaseVoice::insertNote> position: " + std::to_string(ivPosition) + " but the number of notes is " + std::to_string(_voice.size()));
  }
  else {
    _voice.erase(_voice.begin() + int(ivPosition));
  }
}

void hautbois::core::BaseVoice::deleteNoteNoRangeLimit(UInt16 ivPosition) {
  if (ivPosition < _voice.size()) {
    _voice.erase(_voice.begin() + int(ivPosition));
  }
}

void hautbois::core::BaseVoice::autoPadding(const BaseDuration& ivFrontDuration, const BaseDuration& ivBackDuration, bool padWithSilence=true) {
  if (_voice.empty()) {
    return;
  }
  else {
    std::string note_name = padWithSilence ? "S" : "R";
    BaseNote * frontNote = new BaseNote(note_name, "", "", ivFrontDuration.getNum(), ivFrontDuration.getDenom());
    BaseNote * backNote = new BaseNote(note_name, "", "", ivBackDuration.getNum(), ivBackDuration.getDenom());
    _voice.insert(_voice.begin(), frontNote);
    _voice.push_back(backNote);
  }
}

hautbois::UInt16 hautbois::core::BaseVoice::getNumberOfNotes() const {
  return _voice.size();
}
