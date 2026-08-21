#pragma once

#ifndef BASIC_VOICE_HPP
#define BASIC_VOICE_HPP

#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>

#define DEFAULT_NUMBER_OF_BARS 50

namespace hautbois {

class Note;
class Duration;

class BasicVoice final {

private:
  Duration * _meter;
  uint32_t _tempo;
  std::vector<uint32_t> _tempoList;
  std::vector<size_t> _newbarPos;
  std::vector<Duration *> _meterList;
  std::vector<Note *> _noteList;

protected:
  void cleanUp();
  void insertNote(Note * __ptr, const int __pos);
  void accumulateDuration(Duration& __d_out, const Note * __note) const;

public:
  BasicVoice(const int __num, const int __denom, const int __tempo = 120);
  BasicVoice();
  ~BasicVoice();

  size_t size() const;
  size_t barSize() const;
  const Duration * getMeter(const size_t __pos) const;
  uint32_t getTempo(const size_t __pos);

  const Note * getNote(const size_t __pos) const;
  size_t getBarPos(const size_t __pos) const;

  void addProperty(const std::string& __property, size_t __pos);
  void transpose(const int __degree, const std::string& __tonality, const std::string& __mode, size_t __pos);
  void reshape(uint32_t __mul, uint32_t __div, size_t __pos);

  void addBar();
  void addBar(const int __num, const int __denom);
  void addBar(const int __num, const int __denom, const int __tempo);
  void addNote(Note * __ptr);

  /* Find the position of the first counterpoint note in this voice related to the note at __pos in __other voice.
   * __other : the voice to look for counterpoint
   * __pos   : the position of the note in __other voice
   * return  : the position of the first counterpoint note in this voice, return negative if not found or invalid
   */
  int findCounterPoint(const BasicVoice& __other, const size_t __pos);

  /* Patch this voice with silent notes according to __other voice by
   * creating silent notes according to each note value from __other voice.
   */
  void patchBarsLeft(const BasicVoice& __other);

  bool barCheck(const size_t __barpos) const;

  /* Return the bar where bar check failed */
  std::string barCheckReturnErr() const;

  std::string getBarCheckActual(const size_t __barpos) const;
  std::string getBarCheckExpected(const size_t __barpos) const;
  std::string toString(const size_t __barpos) const;
  std::string toString() const;

};

} // namespace hautbois
#endif