#include "hb_macro.hpp"
#include "note.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "voice.hpp"

#include <string>
#include <vector>
#include <list>

namespace hautbois {
namespace core {

const Duration * Voice::getMeter() const {
  return _meter;
}

const std::list<Duration *> Voice::getMeterList() const {
  return _meterList;
}

const Duration * Voice::getMeterAtBar(size_t barIndex) const {
  auto it=_meterList.begin();
  int count = 0;
  while (count < barIndex && it != _meterList.end()) {
    count++;
    it++;
  }
  if (it == _meterList.end()) {
    it--;
  }
  return *it;
}

const std::list<Note *> Voice::getNoteList() const {
  return _noteList;
}

const std::vector<TemporaryVoice> Voice::getTVList() const {
  return _temporaryVoiceList;
}

void Voice::setMeter(int iNum, int iDenom) {
  Duration * d = new Duration(iNum, iDenom);
  _durationPtrLog.push_back(d);
  _meter = d;
}

void Voice::setMeterAtBar(int iNum, int iDenom, size_t barIndex) {
  Duration * d = new Duration(iNum, iDenom);
  _durationPtrLog.push_back(d);
  if (_meterList.size() <= barIndex) {
    _meterList.back() = d;
  }
  else {
    auto it = _meterList.begin();
    for (size_t i=0; i < barIndex; i++) {
      it++;
    }
    *it = d;
  }
}

void Voice::resetNthNote(size_t noteIndex, Note * iNote) {
  _notePtrLog.push_back(iNote);
  if (_noteList.size() <= noteIndex) {
    _noteList.back() = iNote;
  }
  else {
    auto it = _noteList.begin();
    for (size_t i=0; i < noteIndex; i++) {
      it++;
    }
    *it = iNote;
  }
}

void Voice::resetNthNoteAtTempVoice(size_t noteIndex, Note * iNote) {
  _notePtrLog.push_back(iNote);

  TemporaryVoice& tv = _temporaryVoiceList[_currentTempVoice];
  if (tv._noteList.size() <= noteIndex) {
    tv._noteList.back() = iNote;
  }
  else {
    auto it = tv._noteList.begin();
    for (size_t i=0; i < noteIndex; i++) {
      it++;
    }
    *it = iNote;
  }
}

size_t Voice::getCurrentTempVoice() const {
  return _currentTempVoice;
}

void Voice::setCurrentTempVoice(const size_t iCurrVoice) {
  if (iCurrVoice < 0) {
    _currentTempVoice = 0;
  }
  else if (iCurrVoice >= _temporaryVoiceList.size()) {
    _currentTempVoice = _temporaryVoiceList.size() - 1;
  }
  else {
    _currentTempVoice = iCurrVoice;
  }
}

Voice::Voice() {
  Duration * d = new Duration(4,4);
  _durationPtrLog.push_back(d);
  _meter = d;
  _currentTempVoice = 0;
}

Voice::Voice(int iNum, int iDenom) {
  Duration * d = new Duration(iNum,iDenom);
  _durationPtrLog.push_back(d);
  _meter = d;
  _currentTempVoice = 0;
}

Voice::~Voice() {
  for (auto it=_durationPtrLog.begin(); it != _durationPtrLog.end(); it++) {
    delete (*it);
  }
  for (auto it=_notePtrLog.begin(); it != _notePtrLog.end(); it++) {
    delete (*it);
  }
}

void Voice::newBar(int iNum, int iDenom) {
  Duration * d = new Duration(iNum,iDenom);
  _durationPtrLog.push_back(d);
  _meterList.push_back(d);
}

void Voice::newBar() {
  Duration * d = new Duration(_meter->getNum(), _meter->getDenom());
  _durationPtrLog.push_back(d);
  _meterList.push_back(d);
}

void Voice::addNote(const int iNum, const int iDenom,
                    const std::string& iPitch) {
  Note * n = new Note(iNum, iDenom, iPitch);
  _notePtrLog.push_back(n);
  _noteList.push_back(n);
}

void Voice::addNotePtr(Note * iNotePtr) {
  if (iNotePtr) {
    _notePtrLog.push_back(iNotePtr);
    _noteList.push_back(iNotePtr);
  }
}

void Voice::newTempVoice(size_t startIndex) {
  TemporaryVoice t;
  t._startAtBar = startIndex;
  _temporaryVoiceList.push_back(t);
  _currentTempVoice++;
}

void Voice::addNoteAtTempVoice(const int iNum, const int iDenom, 
                               const std::string& iPitch) {
  Note * n = new Note(iNum, iDenom, iPitch);
  _notePtrLog.push_back(n);
  _temporaryVoiceList[_currentTempVoice]._noteList.push_back(n);
}

void Voice::addNotePtrAtTempVoice(Note * iNotePtr) {
  if (iNotePtr) {
    _notePtrLog.push_back(iNotePtr);
    _temporaryVoiceList[_currentTempVoice]._noteList.push_back(iNotePtr);
  }
}

bool Voice::barCheckMainVoice() const {
  auto noteIt = _noteList.begin();
  for (auto meterIt=_meterList.begin(); meterIt != _meterList.end(); meterIt++) {
    Duration d_result (1, 4);
    Duration d_compare = *(*meterIt) + d_result;
    while (d_result < d_compare && noteIt != _noteList.end()) {
      d_result += (*noteIt)->getDuration();
      noteIt++;
    }
    if (d_result != d_compare) {
      return false;
    }
  }
  return true;
}

bool Voice::barCheckTempVoice() const {
}

bool Voice::barCheck() const {
}

const Note * const Voice::at(size_t barIndex, size_t noteIndex) const {
  auto noteIt = _noteList.begin();
  // skip previous bars
  for (int i=0; i < barIndex && i < _meterList.size(); i++) {
    Duration d_result (1, 4);
    Duration d_compare =  *getMeterAtBar(i) + d_result;
    while (d_result < d_compare && noteIt != _noteList.end()) {
      d_result += (*noteIt)->getDuration();
      noteIt++;
    }
  }
  // get the nth note of the target measure
  for (int i=0; i < noteIndex && noteIt != _noteList.end(); i++) {
    noteIt++;
  }
  // just get the last note if the note or bar index exceed
  if (noteIt == _noteList.end()) {
    noteIt--;
  }
  return *noteIt;
}

const Note * const Voice::at(size_t noteIndex) const {
  auto it = _noteList.begin();
  for (int i=0; i < noteIndex; i++) {
    if (it != _noteList.end()) {
      it++;
    }
  }
  if (it == _noteList.end()) {
    it--;
  }
  const Note * const ptr = *it;
  return ptr;
}

} // namespace core
} // namespace hautbois