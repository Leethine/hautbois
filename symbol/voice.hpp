#pragma once

#ifndef VOICE_H
#define VOICE_H

#include <vector>
#include <string>

namespace hautbois {
namespace core {

class Duration;
class Note;

struct TemporaryVoice {

  int _bar;

  int _voice;

  std::vector<Note *> _noteList;

};

class Voice {

 protected:

  int _currentBar;

  int _currentTV;

  std::vector<int> _newBarPos;

  Duration * _meter;

  Duration * _meterDefault;

  std::vector<Duration *> _meterList;

  std::vector<Note *> _noteList;

  std::vector<Duration *> _durationPtrLog;

  std::vector<Note *> _notePtrLog;
  
  std::vector<TemporaryVoice> _temporaryVoiceList;

  virtual void logDurationPtr(Duration * __meter);

  virtual void logNotePtr(Note * __note);

  Voice(const Voice&)=delete;

  Voice(const Voice&&)=delete;

  Voice& operator=(const Voice&)=delete;

  Voice& operator=(const Voice&&)=delete;

 public:

  Voice();

  Voice(const int& __num, const int& __denom);

  virtual ~Voice();

  virtual const Duration * getMeter() const;

  virtual const Duration * getMeter(const int& __bar) const;

  virtual const Note * getNote(const int& __bar, const int& __nth) const;

  virtual const Note * getNoteTV(const int& __bar, const int& __nth, int __voice=0) const;

  virtual void * toStream(const std::string& __instr, void * __ostream) const;

  virtual bool barHasTempVoice(const int& __bar) const;

  virtual int getNbrOfTempVoice(const int& __bar) const;

  virtual bool barCheckMainVoiceThrowExp() const;

  virtual bool barCheckTempVoiceThrowExp() const;

  virtual bool barCheck() const;

  virtual void copyTo(Voice * __ivoice) const;

  virtual int getCurrentBar() const;

  virtual void setCurrentBar(const int& __bar);

  virtual void setCurrentTV(const int& __voice=0);

  virtual void resetNthNote(const int& __bar, const int& __nth, Note * __note);

  virtual void resetNthNoteTV(const int& __bar, const int& __nth, const int& __voice, Note * __note);


  virtual void addNote(const int& __num, const int& __denom,
                       const std::string& __pitch);

  virtual void addNote(Note * __note);

  virtual void newBar(const int& __num, const int& __denom);

  virtual void newBar();

  virtual void newTempVoice(const int& __bar);

  virtual void newTempVoice();

  virtual void addNoteTV(const int& __num, const int& __denom,
                         const std::string& __pitch);

  virtual void addNoteTV(Note * __note);

};

} // namespace core
} // namespace hautbois

#endif