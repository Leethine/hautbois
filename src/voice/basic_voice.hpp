#ifndef BASIC_VOICE_HPP
#define BASIC_VOICE_HPP

#include "../note/note.hpp"
#include "../utility/hbexcept.hpp"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#define DEFAULT_NUMBER_OF_NOTES 300

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

public:

  inline BasicVoice(const int __num, const int __denom, const int __tempo = 120) {
    _meter = new Duration(__num, __denom);
    _tempo = __tempo;
    _tempoList.reserve(DEFAULT_NUMBER_OF_NOTES);
    _newbarPos.reserve(DEFAULT_NUMBER_OF_NOTES);
    _meterList.reserve(DEFAULT_NUMBER_OF_NOTES);
    _noteList.reserve(DEFAULT_NUMBER_OF_NOTES);
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

  inline void addNote(const std::vector<std::string>& __pitches, const std::string& __value) {
    Note * ptr = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument ,
      ptr = new ChordType(__pitches, __value) ; 
      _noteList.push_back(ptr); 
      ,
      cleanUp();
    )
  }

  inline void addNote(const std::vector<std::string>& __notes, const std::string& __main_pitch, const std::string& __main_value) {
    Note * ptr = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument ,
      ptr = new GraceNoteType(__notes, __main_pitch, __main_value) ; 
      _noteList.push_back(ptr); 
      ,
      cleanUp();
    )
  }

  inline void addNote(const std::string& __pitch, const std::string& __value) {
    Note * ptr = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument ,
      ptr = new SingleNoteType(__pitch, __value) ; 
      _noteList.push_back(ptr); 
      ,
      cleanUp();
    )
  }

  inline void addNote(const size_t __total, const size_t __value, const std::vector<std::string>& __notes) {
    Note * ptr = nullptr;
    HB_NESTED_THROW_ACTION(std::invalid_argument ,
      ptr = new TupletType(__total, __value, __notes) ; 
      _noteList.push_back(ptr); 
      ,
      cleanUp();
    )
  }

  inline size_t getCounterPoint(const BasicVoice& __other, const size_t __pos) {
    //TODO
  }

  inline void patchBars(const BasicVoice& __voice) {
    //TODO
  }

  inline bool barCheck(const size_t __barPos) const {
    //TODO
  }

  inline bool barCheckAll() const {
    //TODO
  }

  inline std::string getBarCheckActual(const size_t __barPos) const {
    //TODO
  }

  inline std::string getBarCheckExpected(const size_t __barPos) const {
    //TODO
  }

};



} // namespace hautbois

#endif