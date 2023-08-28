#include "base_voice.hpp"

hautbois::core::BaseVoice::BaseVoice() {}

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

bool hautbois::core::BaseVoice::checkFull(const BaseDuration& ivDuration) const {
  if (_voice.empty() && ivDuration.getNum() != 0) {
    return false;
  }

  BaseDuration totalDuration = countTotalDuration();
  if (totalDuration >= ivDuration) {
    return true;
  }
  else {
    return false;
  }
}

bool hautbois::core::BaseVoice::padVoice(const BaseDuration& ivDuration, NoteNameEnum ivNoteName, bool ivPadFront=false) {
  BaseNote * paddingNote = nullptr;
  if (!checkFull(ivDuration)) {
    BaseDuration totalDuration = countTotalDuration();
    BaseDuration fullDuration = BaseDuration(ivDuration);
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
    throw OutOfRangeException("Error in BaseVoice::padVoice. Total duration: " + countTotalDuration().toString() + " Given max duration: " + ivDuration.toString());
    return false;
  }
  return true;
}

bool hautbois::core::BaseVoice::frontPadWithSilence(const BaseDuration& ivDuration) {
  return padVoice(ivDuration, NoteNameEnum::S, true);
}

bool hautbois::core::BaseVoice::frontPadWithRest(const BaseDuration& ivDuration) {
  return padVoice(ivDuration, NoteNameEnum::R, true);
}

bool hautbois::core::BaseVoice::backPadWithSilence(const BaseDuration& ivDuration) {
  return padVoice(ivDuration, NoteNameEnum::S, false);
}

bool hautbois::core::BaseVoice::backPadWithRest(const BaseDuration& ivDuration) {
  return padVoice(ivDuration, NoteNameEnum::R, false);
}

void hautbois::core::BaseVoice::trimFront(const BaseDuration& ivDuration) {
  if (_voice.empty()) {
    return ;
  }
  BaseDuration totalDuration = countTotalDuration();
  if (totalDuration > ivDuration) {
    BaseDuration extraDuration = totalDuration - ivDuration;
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

void hautbois::core::BaseVoice::trimBack(const BaseDuration& ivDuration) {
  if (_voice.empty()) {
    return ;
  }
  BaseDuration totalDuration = countTotalDuration();
  if (totalDuration > ivDuration) {
    BaseDuration extraDuration = totalDuration - ivDuration;
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
  _voice.push_back(ivNote);
}

void hautbois::core::BaseVoice::insertNote(BaseNote* ivNote, UInt16 ivPosition=0) {
  if (ivPosition >= _voice.size()) {
    throw OutOfRangeException("<BaseVoice::insertNote> position: " + std::to_string(ivPosition) + " but the number of notes is " + std::to_string(_voice.size()));
  }
  else {
    auto iter = _voice.begin();
    for (int i=0; i < ivPosition; i++) {
      iter++;
    }
    _voice.insert(iter, ivNote);
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