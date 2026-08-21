#include "basic_voice.hpp"
#include "../note/note.hpp"
#include "../note/single_note.hpp"
#include "../note/duration.hpp"
#include "../hbtype/hbdefs.hpp"

namespace hautbois {

void BasicVoice::cleanUp() {
  delete _meter;
  for (Duration * ptr : _meterList) {
    delete ptr;
  }
  for (Note * ptr : _noteList) {
    delete ptr;
  }
  _meterList.clear();
  _noteList.clear();
  _newbarPos.clear();
  _tempoList.clear();
}

void BasicVoice::insertNote(Note * __ptr, const int __pos) {
  if (__ptr) {
    if (__pos < 0 || __pos >= (int) _noteList.size()) {
      _noteList.push_back(__ptr);
    }
    else if (__pos >= 0 && __pos < (int) _noteList.size()) {
      _noteList.insert(_noteList.begin() + __pos, __ptr);
    }
  }
}

void BasicVoice::accumulateDuration(Duration& __d_out, const Note * __note) const {
  if (__note && __note->getDuration(0)) {
    if (__note->isType(CHAR_NOTETYPE_SINGLE)  ||
        __note->isType(CHAR_NOTETYPE_REST)    ||
        __note->isType(CHAR_NOTETYPE_SILENCE) ||
        __note->isType(CHAR_NOTETYPE_CHORD)) {
      __d_out.plus(__note->getDuration(0));
    }
    else if (__note->isType(CHAR_NOTETYPE_TUPLET)) {
      if (__note->getDuration(__note->getSize())) {
        Duration tuplet_value (1, __note->getDuration(__note->getSize())->getDenom());
        __d_out.plus(&tuplet_value);
      }
    }
    else if (__note->isType(CHAR_NOTETYPE_GRACE)        ||
             __note->isType(CHAR_NOTETYPE_ACCIACCATURA) ||
             __note->isType(CHAR_NOTETYPE_APPOGGIATURA)) {
      // only need the value of the main note
      size_t main_note_pos = (size_t) __note->getSize() - 1;
      __d_out.plus(__note->getDuration(main_note_pos));
    }
  }
}

BasicVoice::BasicVoice(const int __num, const int __denom, const int __tempo) {
  _meter = new Duration(__num, __denom);
  _tempo = __tempo;
  size_t reserve_amt = DEFAULT_NUMBER_OF_BARS;
  if (_meter) {
    reserve_amt *= _meter->getDenom();
  }
  _tempoList.reserve(reserve_amt);
  _newbarPos.reserve(reserve_amt);
  _meterList.reserve(reserve_amt);
  _noteList.reserve(reserve_amt);
}

BasicVoice::BasicVoice() : BasicVoice(4, 4, 120) {
}

BasicVoice::~BasicVoice() {
  cleanUp();
}

size_t BasicVoice::size() const {
  return _noteList.size();
}

size_t BasicVoice::barSize() const {
  return _newbarPos.size();
}

const Duration * BasicVoice::getMeter(const size_t __pos) const {
  if (__pos < _meterList.size() && _meterList[__pos]) {
    return _meterList[__pos];
  }
  return _meter;
}

uint32_t BasicVoice::getTempo(const size_t __pos) {
  if (__pos < _tempoList.size()) {
    return _tempoList[__pos];
  }
  return _tempo;
}

const Note * BasicVoice::getNote(const size_t __pos) const {
  if (__pos < _noteList.size()) {
    return _noteList[__pos];
  }
  return nullptr;
}

size_t BasicVoice::getBarPos(const size_t __pos) const {
  if (__pos < _newbarPos.size() && _newbarPos[__pos] < _noteList.size()) {
    return _newbarPos[__pos];
  }
  return 0;
}

void BasicVoice::addProperty(const std::string& __property, size_t __pos) {
  if (__pos < _noteList.size() && _noteList[__pos]) {
    _noteList[__pos]->addProperty(__property);
  }
}

void BasicVoice::transpose(const int __degree, const std::string& __tonality, const std::string& __mode, size_t __pos) {
  if (__pos < _noteList.size() && _noteList[__pos]) {
    _noteList[__pos]->transpose(__degree, __tonality,__mode);
  }
}

void BasicVoice::reshape(uint32_t __mul, uint32_t __div, size_t __pos) {
  if (__pos < _noteList.size() && _noteList[__pos] && _noteList[__pos]->getDuration(0)) {
    _noteList[__pos]->enlarge(__mul);
    _noteList[__pos]->reduce(__div);
  }
}

void BasicVoice::addBar() {
  _meterList.push_back(nullptr);
  _tempoList.push_back(_tempo);
  _newbarPos.push_back(_noteList.size());
}

void BasicVoice::addBar(const int __num, const int __denom) {
  _meterList.push_back(new Duration(__num, __denom));
  _tempoList.push_back(_tempo);
  _newbarPos.push_back(_noteList.size());
}

void BasicVoice::addBar(const int __num, const int __denom, const int __tempo) {
  _meterList.push_back(new Duration(__num, __denom));
  _tempoList.push_back(__tempo);
  _newbarPos.push_back(_noteList.size());
}

void BasicVoice::addNote(Note * __ptr) {
  if (__ptr) {
    _noteList.push_back(__ptr);
  }
}

int BasicVoice::findCounterPoint(const BasicVoice& __other, const size_t __pos) {
  Duration d_other(0,1);
  Duration d_this (0,1);
  if (__pos >= __other.size()) {
    return -2; // overflow
  }
  // calculate total duration
  for (size_t i = 0; i <= __pos; i++) {
    accumulateDuration(d_other, __other.getNote(i));
  }
  // find the counterpoint
  size_t targetPos = 0;
  while (targetPos < size()) {
    accumulateDuration(d_this, getNote(targetPos));
    if (d_this.equals(&d_other)) {
      return targetPos;
    }
    targetPos++;
  }
  return -1; // not found
}

void BasicVoice::patchBarsLeft(const BasicVoice& __other) {
  // calculate total value
  Duration d_other (0, 1);
  for (size_t i = 0; i <= __other.size(); i++) {
    accumulateDuration(d_other, __other.getNote(i));
  }
  // reshape the note so that the value becomes d_other
  Note * ptr = new SingleNote("S", "1");
  ptr->enlarge(d_other.getNum());
  ptr->reduce(d_other.getDenom());
  // append or insert the newly created note
  if (_noteList.empty()) {
    insertNote(ptr, NOTE_SETNOTE_APPEND_POS);
  }
  else {
    insertNote(ptr, 0);
  }
}

bool BasicVoice::barCheck(const size_t __barpos) const {
  Duration d_actual (0, 1);
  if (__barpos < _newbarPos.size() && _newbarPos[__barpos] < _noteList.size()) {
    size_t notepos = _newbarPos[__barpos];
    size_t nextbarnotepos = _noteList.size(); // last bar pos
    if (__barpos != _newbarPos.size() - 1) { // not the last bar
      nextbarnotepos = _newbarPos[__barpos+1];
    }
    // accumulate duration value
    for (size_t i = notepos; i < nextbarnotepos; i++) {
      accumulateDuration(d_actual, _noteList[i]);
    }
    return d_actual.equals(getMeter(__barpos));
  }
  return false;
}

std::string BasicVoice::barCheckReturnErr() const {
  std::string err;
  for (size_t barpos = 0; barpos < _newbarPos.size(); barpos++) {
    if (! barCheck(barpos)) {
      err.append("Bar check failed at:\n ==>" + std::to_string(barpos) +
                 ": " + toString(barpos)     + "\nExpected: " +
                 getBarCheckExpected(barpos) + " != Actual: " +
                 getBarCheckActual(barpos));
      return err;
    }
  }
  return "";
}

std::string BasicVoice::getBarCheckActual(const size_t __barpos) const {
  Duration d_actual (0, 1);
  if (__barpos < _newbarPos.size() && _newbarPos[__barpos] < _noteList.size()) {
    size_t notepos = _newbarPos[__barpos];
    size_t nextbarnotepos = _noteList.size();
    if (__barpos != _newbarPos.size() - 1) { // not the last bar
      nextbarnotepos = _newbarPos[__barpos+1];
    }
    // accumulate duration value
    for (size_t i = notepos; i < nextbarnotepos; i++) {
      accumulateDuration(d_actual, _noteList[i]);
    }
  }
  return d_actual.toString();
}

std::string BasicVoice::getBarCheckExpected(const size_t __barpos) const {
  if (getMeter(__barpos)) {
    return getMeter(__barpos)->toString();
  }
  return "";
}

std::string BasicVoice::toString(const size_t __barpos) const {
  std::string out;
  if (__barpos < _newbarPos.size() - 1) {
    for (size_t j = _newbarPos[__barpos]; j < _newbarPos[__barpos+1]; j++) {
      out.push_back(' ');
      if (_noteList[j]) {
        out.append(_noteList[j]->toString());
      }
      else {
        out.append("???");
      }
      out.push_back(' ');      
    }
  }
  else if (__barpos == _newbarPos.size() - 1) {
    for (size_t j = _newbarPos.back(); j < _noteList.size(); j++) {
      out.push_back(' ');
      if (_noteList[j]) {
        out.append(_noteList[j]->toString());
      }
      else {
        out.append("???");
      }
      out.push_back(' ');
    }
  }
  return out;
}

std::string BasicVoice::toString() const {
  std::string out;
  if (!_newbarPos.empty()) {
    for (size_t i = 0; i < _newbarPos.size() - 1; i++) {
      out.append(std::to_string(i) + ": ");
      for (size_t j = _newbarPos[i]; j < _newbarPos[i+1]; j++) {
        out.push_back(' ');
        if (_noteList[j]) {
          out.append(_noteList[j]->toString());
        }
        else {
          out.append("???");
        }
        out.push_back(' ');      
      }
      out.append("|\n");
    }
    // last bar
    out.append(std::to_string(_newbarPos.size() - 1) + ": ");
    for (size_t j = _newbarPos.back(); j < _noteList.size(); j++) {
      out.push_back(' ');
      if (_noteList[j]) {
        out.append(_noteList[j]->toString());
      }
      else {
        out.append("???");
      }
      out.push_back(' ');
    }
  }
  return out;
}

} // namespace hautbois