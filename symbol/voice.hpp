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

  std::vector<Note *> _noteList;

};

class Voice {

 protected:

  Duration * _meter;

  int _currentBar = 0;

  int _currentTV = 0;

  std::vector<Duration *> _meterList;

  std::vector<Note *> _noteList;

  std::vector<TemporaryVoice> _temporaryVoiceList;

  std::vector<Duration *> _durationPtrLog;

  std::vector<Note *> _notePtrLog;

  Voice(const Voice&)=delete;

  Voice(const Voice&&)=delete;

  Voice& operator=(const Voice&)=delete;

  Voice& operator=(const Voice&&)=delete;

 public:

  Voice();

  Voice(int iNum, int iDenom);

  virtual ~Voice();

  virtual const Duration * getMeter() const;

  virtual const Duration * getMeterAtBar(const int& __bar) const;

  virtual const Note * getNote(const int& __bar, const int& __nth) const;

  virtual const Note * getNoteTV(const int& __bar, const int& __nth, int __voice=0) const;

  virtual void barHasTempVoice(const int& __bar) const;

  virtual int getNbrOfTempVoice(const int& __bar) const;

  virtual bool barCheckMainVoiceThrowExp() const;

  virtual bool barCheckTempVoiceThrowExp() const;

  virtual bool barCheck() const;

  virtual void copyTo(Voice * __ivoice) const;

  virtual void resetNthNote(const int& __bar, const int& __nth, Note * __note);

  virtual void resetNthNoteTV(const int& __bar, const int& __nth, const int& __voice, Note * __note);

  virtual void newBar(int __num, int __denom);

  virtual void newBar();

  virtual void addNote(const int& __num, const int& __denom,
                       const std::string& __pitch);

  virtual void addNote(Note * __note);

  virtual void newTempVoice(const int& __bar);

  virtual void addNoteTV(const int& __num, const int& __denom,
                         const std::string& __pitch);

  virtual void addNoteTV(Note * __note);

};

} // namespace core
} // namespace hautbois

#endif