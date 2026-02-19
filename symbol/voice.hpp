#pragma once

#ifndef VOICE_H
#define VOICE_H

#include <list>
#include <vector>
#include <string>

namespace hautbois {
namespace core {

class Duration;
class Note;

struct TemporaryVoice {
  int _startAtBar;
  std::list<Note *> _noteList;
};

class Voice {
 private:
  std::list<Duration *> _meterList;
  std::list<Note *> _noteList;
  std::vector<TemporaryVoice> _temporaryVoiceList;
  Duration * _meter;
  std::vector<Duration *> _durationPtrLog;
  std::list<Note *> _notePtrLog;
  size_t _currentTempVoice = 0;

 protected:
  virtual const Duration * getMeter() const;
  virtual const std::list<Duration *> getMeterList() const;
  virtual const Duration * getMeterAtBar(size_t barIndex) const;
  virtual const std::list<Note *> getNoteList() const;
  virtual const std::vector<TemporaryVoice> getTVList() const;
  virtual void setMeter(int iNum, int iDenom);
  virtual void setMeterAtBar(int iNum, int iDenom, size_t barIndex);
  virtual void resetNthNote(size_t noteIndex, Note * iNote);
  virtual void resetNthNoteAtTempVoice(size_t noteIndex, Note * iNote);
  virtual size_t getCurrentTempVoice() const;
  virtual void setCurrentTempVoice(const size_t iCurrVoice);
  virtual bool barCheckMainVoice() const;
  virtual bool barCheckTempVoice() const;

 public:
  Voice();
  Voice(int iNum, int iDenom);
  Voice(const Voice&)=delete;
  virtual ~Voice();

  virtual void newBar(int iNum, int iDenom);
  virtual void newBar();
  virtual void addNote(const int iNum, const int iDenom,
                       const std::string& iPitch);
  virtual void addNotePtr(Note * iNotePtr);
  virtual void newTempVoice(size_t startIndex);
  virtual void addNoteAtTempVoice(const int iNum, const int iDenom,
                                  const std::string& iPitch);
  virtual void addNotePtrAtTempVoice(Note * iNotePtr);
  virtual bool barCheck() const;

  const Note * const at(size_t barIndex, size_t noteIndex) const;
  const Note * const at(size_t noteIndex) const;
};

} // namespace core
} // namespace hautbois

#endif