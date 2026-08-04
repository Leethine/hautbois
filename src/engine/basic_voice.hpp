#pragma once

#ifndef BASIC_VOICE_HPP
#define BASIC_VOICE_HPP

#include "../note/note.hpp"
#include "../note/duration.hpp"
#include "../utility/hbexcept.hpp"
#include "../hbtype/hbdefs.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#define DEFAULT_NUMBER_OF_BARS 50

namespace hautbois {

class Note;
class Duration;

template<class SingleNoteType, class ChordType, class GraceNoteType, class TupletType>
class BasicVoice final {

private:

  Duration * _meter;

  uint32_t _tempo;

  std::vector<uint32_t> _tempoList;

  std::vector<size_t> _newbarPos;

  std::vector<Duration *> _meterList;

  std::vector<Note *> _noteList;

protected:

  inline void cleanUp() {
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

  inline void insertNote(Note * __ptr, const int __pos) {
    if (__ptr) {
      if (__pos < 0 || __pos >= (int) _noteList.size()) {
        _noteList.push_back(__ptr);
      }
      else if (__pos >= 0 && __pos < (int) _noteList.size()) {
        _noteList.insert(_noteList.begin() + __pos, __ptr);
      }
    }
  }

  inline void accumulateDuration(Duration& __d_out, const Note * __note) const {
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

public:

  inline BasicVoice(const int __num, const int __denom, const int __tempo = 120) {
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

  inline BasicVoice() : BasicVoice(4, 4, 120) {
  }

  inline ~BasicVoice() {
    cleanUp();
  }

  inline size_t size() const {
    return _noteList.size();
  }

  inline size_t barSize() const {
    return _newbarPos.size();
  }

  inline const Duration * getMeter(const size_t __pos) const {
    if (__pos < _meterList.size() && _meterList[__pos]) {
      return _meterList[__pos];
    }
    return _meter;
  }

  inline uint32_t getTempo(const size_t __pos) {
    if (__pos < _tempoList.size()) {
      return _tempoList[__pos];
    }
    return _tempo;
  }

  inline const Note * getNote(const size_t __pos) const {
    if (__pos < _noteList.size()) {
      return _noteList[__pos];
    }
    return nullptr;
  }

  inline size_t getBarPos(const size_t __pos) const {
    if (__pos < _newbarPos.size() && _newbarPos[__pos] < _noteList.size()) {
      return _newbarPos[__pos];
    }
    return 0;
  }

  inline Note * getNoteModify(const size_t __pos) {
    if (__pos < _noteList.size()) {
      return _noteList[__pos];
    }
    return nullptr;
  }

  inline Note * getNoteModify() {
    if (!_noteList.empty()) {
      return _noteList.back();
    }
    return nullptr;
  }

  inline void addBar() {
    _meterList.push_back(nullptr);
    _tempoList.push_back(_tempo);
    _newbarPos.push_back(_noteList.size());
  }

  inline void addBar(const int __num, const int __denom) {
    _meterList.push_back(new Duration(__num, __denom));
    _tempoList.push_back(_tempo);
    _newbarPos.push_back(_noteList.size());
  }

  void addBar(const int __num, const int __denom, const int __tempo) {
    _meterList.push_back(new Duration(__num, __denom));
    _tempoList.push_back(__tempo);
    _newbarPos.push_back(_noteList.size());
  }

  inline void addNote(const std::string& __pitch, const std::string& __value, const int __pos = NOTE_SETNOTE_APPEND_POS) {
    Note * ptr = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument ,
      ptr = new SingleNoteType(__pitch, __value) ; 
      ,
      cleanUp();
    )
    insertNote(ptr, __pos);
  }

  inline void addNote(const std::vector<std::string>& __pitches, const std::string& __value, const int __pos = NOTE_SETNOTE_APPEND_POS) {
    Note * ptr = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument ,
      ptr = new ChordType(__pitches, __value) ; 
      ,
      cleanUp();
    )
    insertNote(ptr, __pos);
  }

  inline void addNote(const std::vector<std::string>& __notes, const std::string& __main_pitch, const std::string& __main_value, const int __pos = NOTE_SETNOTE_APPEND_POS) {
    Note * ptr = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument ,
      ptr = new GraceNoteType(__notes, __main_pitch, __main_value) ; 
      ,
      cleanUp();
    )
    insertNote(ptr, __pos);
  }

  inline void addNote(const size_t __total, const size_t __value, const std::vector<std::string>& __notes, const int __pos = NOTE_SETNOTE_APPEND_POS) {
    Note * ptr = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument ,
      ptr = new TupletType(__total, __value, __notes) ; 
      ,
      cleanUp();
    )
    insertNote(ptr, __pos);
  }

  /* Find the position of the first counterpoint note in this voice related to the note at __pos in __other voice.
   * __other : the voice to look for counterpoint
   * __pos   : the position of the note in __other voice
   * return  : the position of the first counterpoint note in this voice, return negative if not found or invalid
   */
  inline int findCounterPoint(const BasicVoice& __other, const size_t __pos) {
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
    int targetPos = 0;
    while (targetPos < size()) {
      accumulateDuration(d_this, getNote(targetPos));
      if (d_this.equals(&d_other)) {
        return targetPos;
      }
      targetPos++;
    }
  
    return -1; // not found
  }

  /* Patch this voice with silent notes according to __other voice by
   * creating silent notes according to each note value from __other voice.
   */
  inline void patchBarsLeft(const BasicVoice& __other) {
    // calculate total value
    Duration d_other (0, 1);
    for (int i = 0; i <= __other.size(); i++) {
      accumulateDuration(d_other, __other.getNote(i));
    }

    // reshape the note so that the value becomes d_other
    Note * ptr = new SingleNoteType("S", "1");
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

  inline bool barCheck(const size_t __barpos) const {
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

  /* Return the bar where bar check failed */
  inline std::string barCheckReturnErr() const {
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

  inline std::string getBarCheckActual(const size_t __barpos) const {
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

  inline std::string getBarCheckExpected(const size_t __barpos) const {
    if (getMeter(__barpos)) {
      return getMeter(__barpos)->toString();
    }
    return "";
  }

  inline std::string toString(const size_t __barpos) const {
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

  inline std::string toString() const {
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

};

} // namespace hautbois
#endif