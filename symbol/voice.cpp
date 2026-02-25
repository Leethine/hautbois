#include "voice.hpp"
#include "note.hpp"
#include "duration.hpp"

#include <string>
#include <vector>
#include <algorithm>
// #include <utility>
#include <stdexcept>

namespace hautbois {
namespace core {

void Voice::logDurationPtr(Duration * __meter) {
  if (__meter) {
    _durationPtrLog.push_back(__meter);
  }
}

void Voice::logNotePtr(Note * __note) {
  if (__note) {
    _notePtrLog.push_back(__note);
  }
}

Voice::Voice() : 
_currentBar (0), _currentTV (0), _newBarPos ({0}),
_meter (nullptr), _meterDefault (nullptr),
_meterList ({}), _noteList ({}), _durationPtrLog ({}),
_notePtrLog ({}), _temporaryVoiceList ({})
{
  Duration * d = new Duration(4,4);
  logDurationPtr(d);
  _meter = d;
  _meterDefault = d;
}

Voice::Voice(const int& __num, const int& __denom): Voice() {
  Duration * d = new Duration(__num, __denom);
  logDurationPtr(d);
  _meter = d;
  _meterDefault = d;
}

Voice::~Voice() {
  for (auto it = _durationPtrLog.begin(); it != _durationPtrLog.end(); it++) {
    delete (*it);
  }
  for (auto it = _notePtrLog.begin(); it != _notePtrLog.end(); it++) {
    delete (*it);
  }
}

const Duration * Voice::getMeter() const {
  if (_meter) {
    return _meter;
  }
  else {
    return _meterDefault;
  }
}

const Duration * Voice::getMeter(const int& __bar) const {
  if (_meterList.empty()) {
    return _meterDefault;
  }
  else if (__bar < _meterList.size()) {
    return _meterList[__bar];
  }
  else {
    return _meterList.back();
  }
}

const Note * Voice::getNote(const int& __bar, const int& __nth) const {
  if (__bar < _newBarPos.size()) {
    int idx = _newBarPos[__bar] + __nth;
    if (idx < _noteList.size()) {
      return _noteList[idx];
    }
    else {
      throw std::out_of_range(" Note no. " + std::to_string(__nth));
    }
  }
  else {
    throw std::out_of_range("Bar no. "  + std::to_string(__bar));
  }
}

const Note * Voice::getNoteTV(const int& __bar,
                              const int& __nth,
                              int __voice) const {
  for (const TemporaryVoice& tv : _temporaryVoiceList) {
    if (__bar == tv._bar && __voice == tv._voice) {
      if (__nth < tv._noteList.size()) {
        return tv._noteList[__nth];
      }
    }
  }
  throw std::out_of_range("Bar no. "    + std::to_string(__bar) +
                          " Voice no. " + std::to_string(__voice) +
                          " Note no. "  + std::to_string(__nth));
}

void * Voice::toStream(const std::string& __instr, void * __ostream) const {
  // not supported
  return nullptr;
}

bool Voice::barHasTempVoice(const int& __bar) const {
  for (const TemporaryVoice& tv : _temporaryVoiceList) {
    if (__bar == tv._bar) {
      return true;
    }
  }
  return false;
}

int Voice::getNbrOfTempVoice(const int& __bar) const {
  int count = 0;
  for (const TemporaryVoice& tv : _temporaryVoiceList) {
    if (__bar == tv._bar) {
      count++;
    }
  }
  return count;
}

bool Voice::barCheckMainVoiceThrowExp() const {
  //TODO
  return true;
}

bool Voice::barCheckTempVoiceThrowExp() const {
  //TODO
  return true;
}

bool Voice::barCheck() const {
  return barCheckMainVoiceThrowExp() &&
         barCheckTempVoiceThrowExp();
}

void Voice::copyTo(Voice * __ivoice) const {
  //TODO
}

int Voice::getCurrentBar() const {
  return _currentBar;
}

void Voice::setCurrentBar(const int& __bar) {
  _currentBar = __bar;
}

void Voice::setCurrentTV(const int& __voice) {
  _currentTV = __voice;
}

void Voice::resetNthNote(const int& __bar, const int& __nth, Note * __note) {
  if (__bar < _newBarPos.size()) {
    int idx = _newBarPos[__bar] + __nth;
    if (idx < _noteList.size()) {
      if (__note) {
        _noteList[idx] = __note;
        logNotePtr(__note);
      }
      else {
        throw std::runtime_error("input was nullptr");
      }
    }
    else {
      throw std::out_of_range(" Note no. " + std::to_string(__nth));
    }
  }
  else {
    throw std::out_of_range("Bar no. "  + std::to_string(__bar));
  }
}

void Voice::resetNthNoteTV(const int& __bar, const int& __nth, const int& __voice, Note * __note) {
  for (TemporaryVoice& tv : _temporaryVoiceList) {
    if (__bar == tv._bar && __voice == tv._voice) {
      if (__nth < tv._noteList.size()) {
        if (__note) {
          tv._noteList[__nth] = __note;
          logNotePtr(__note);
          return ;
        }
        else {
          throw std::runtime_error("input was nullptr");
        }
      }
      else {
        throw std::out_of_range("Note no. "  + std::to_string(__nth));
      }
    }
  }
  throw std::out_of_range("Bar no. "    + std::to_string(__bar) +
                          " Voice no. " + std::to_string(__voice));
}

void Voice::addNote(const int& __num, const int& __denom,
             const std::string& __pitch) {
  Note * n = new Note(__num, __denom, __pitch);
  _noteList.push_back(n);
  logNotePtr(n);
}

void Voice::addNote(Note * __note) {
  if (__note) {
    _noteList.push_back(__note);
    logNotePtr(__note);
  }
  else {
    throw std::runtime_error("input was nullptr");
  }
}

void Voice::newBar(const int& __num, const int& __denom) {
  if (__num == _meter->getNum() && __denom == _meter->getDenom()) {
    _meterList.push_back(_meter);
  }
  else {
    Duration * d = new Duration(__num, __denom);
    logDurationPtr(d);
  }
  _currentBar++;
  _currentTV = 0;
  _newBarPos.push_back(_noteList.size()+1);
}

void Voice::newBar() {
  _meterList.push_back(_meter);
  _currentBar++;
  _currentTV = 0;
  _newBarPos.push_back(_noteList.size()+1);
}

void Voice::newTempVoice(const int& __bar) {
  if (__bar < _newBarPos.size()) {
    TemporaryVoice v;
    v._bar = __bar;
    v._voice = _currentTV++;
    _temporaryVoiceList.push_back(v);
  }
  else {
    throw std::out_of_range("Bar no. "  + std::to_string(__bar));
  }
}

void Voice::newTempVoice() {
  newTempVoice(_currentBar);
}

void Voice::addNoteTV(const int& __num, const int& __denom,
                      const std::string& __pitch) {
  for (TemporaryVoice& tv : _temporaryVoiceList) {
    if (tv._bar == _currentBar && tv._voice == _currentTV) {
      Note * n = new Note(__num, __denom, __pitch);
      logNotePtr(n);
      tv._noteList.push_back(n);
      return ;
    }
    else {
      throw std::out_of_range("Bar no. "    + std::to_string(_currentBar) +
                              " Voice no. " + std::to_string(_currentTV));
    }
  }
  throw std::out_of_range("Missing temporary voice");
}

void Voice::addNoteTV(Note * __note) {
  for (TemporaryVoice& tv : _temporaryVoiceList) {
    if (tv._bar == _currentBar && tv._voice == _currentTV) {
      if (__note) {
        logNotePtr(__note);
        tv._noteList.push_back(__note);
        return ;
      }
      else {
        std::runtime_error("input was nullptr");
      }
    }
    else {
      throw std::out_of_range("Bar no. "    + std::to_string(_currentBar) +
                              " Voice no. " + std::to_string(_currentTV));
    }
  }
  throw std::out_of_range("Missing temporary voice");
}

void Voice::deleteBar(const int& __bar) {
  if (__bar < _newBarPos.size() && (__bar + 1) < _newBarPos.size()) {
    int pos1 = _newBarPos[__bar];
    int pos2 = _newBarPos[__bar+1];
    std::vector<Note *> sliced (_noteList.begin(), _noteList.begin() + pos1);
    std::vector<Note *> sliced_end (_noteList.begin() + pos2, _noteList.end());
    sliced.insert(sliced.end(), sliced_end.begin(), sliced_end.end());
    _noteList = sliced;
  }
  else if (__bar < _newBarPos.size()) {
    int pos = _newBarPos[__bar];
    std::vector<Note *> sliced (_noteList.begin(), _noteList.begin() + pos);
    _noteList = sliced;
  }
  else {
    throw std::out_of_range("Bar no. " + std::to_string(__bar));
  }

  deleteBarTV(__bar);
}

void Voice::deleteBar() {
  deleteBar(_currentBar);
}

void Voice::deleteBarTV(const int& __bar, const int& __voice) {
  if (barHasTempVoice(__bar) && __voice < getNbrOfTempVoice(__bar)) {
    std::vector<TemporaryVoice>::iterator it_rm = _temporaryVoiceList.end();
    for (auto it = _temporaryVoiceList.begin();
              it != _temporaryVoiceList.end(); it++) {
      if (it->_bar == __bar && it->_voice == __voice) {
        it_rm = it;
        break;
      }
    }
    if (it_rm != _temporaryVoiceList.end()) {
      _temporaryVoiceList.erase(it_rm);
    }
  }
}

void Voice::deleteBarTV(const int& __bar) {
  if (barHasTempVoice(__bar)) {
    for (int i = 0; i < getNbrOfTempVoice(__bar); i++) {
      std::vector<TemporaryVoice>::iterator it_rm = _temporaryVoiceList.end();
      for (auto it = _temporaryVoiceList.begin();
                it != _temporaryVoiceList.end(); it++) {
        if (it->_bar == __bar) {
          it_rm = it;
          break;
        }
      }
      if (it_rm != _temporaryVoiceList.end()) {
        _temporaryVoiceList.erase(it_rm);
      }
    }
  }
}

} // namespace core
} // namespace hautbois