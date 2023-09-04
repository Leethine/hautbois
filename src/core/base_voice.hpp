#pragma once

#ifndef BASE_VOICE_H
#define BASE_VOICE_H

#include "base_note.hpp"
#include "base_duration.hpp"
#include "basetypes/base_def_types.hpp"

namespace hautbois {
namespace core {

class BaseVoice {
  private:
    std::vector<BaseNote*> _voice;

  protected:
    virtual bool padVoice(const BaseDuration& ivDuration, NoteNameEnum ivNoteName, bool ivPadFront);

  public:
    BaseVoice();
    BaseVoice(const BaseVoice& ivRhVoice);
    virtual ~BaseVoice();
    
    virtual BaseDuration countTotalDuration() const;
    virtual bool checkFull(const BaseDuration& ivFullDuration) const;

    virtual bool frontPadWithSilence(const BaseDuration& ivFullDuration);
    virtual bool frontPadWithRest(const BaseDuration& ivFullDuration);
    virtual bool backPadWithSilence(const BaseDuration& ivFullDuration);
    virtual bool backPadWithRest(const BaseDuration& ivFullDuration);
    virtual void trimFront(const BaseDuration& ivFullDuration);
    virtual void trimBack(const BaseDuration& ivFullDuration);
    virtual void autoPadding(const BaseDuration& ivFrontDuration, const BaseDuration& ivBackDuration, bool padWithSilence);

    virtual void appendNote(BaseNote* ivNote);
    virtual void insertNote(BaseNote* ivNote, UInt16 ivPosition);
    virtual BaseNote* getNote(UInt16 ivPosition) const;
    virtual BaseNote* getNoteNoRangeLimit(UInt16 ivPosition) const;
    virtual void deleteNote(UInt16 ivPosition);
    virtual void deleteNoteNoRangeLimit(UInt16 ivPosition);
    virtual UInt16 getNumberOfNotes() const;
};

} // namespace core
} // namespace hautbois

#endif