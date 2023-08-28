#pragma once

#ifndef BASE_VOICE_H
#define BASE_VOICE_H

#include "base_note.hpp"
#include "base_duration.hpp"
#include "basetypes/base_def_types.hpp"
#include "basetypes/note_enum_types.hpp"
#include "charts/sci_notename_to_index.hpp"
#include "property/tempo_enum_types.hpp"

namespace hautbois {
namespace core {

class BaseVoice {
  private:
    std::vector<BaseNote*> _voice;

  protected:
    virtual bool padVoice(const BaseDuration& ivDuration, NoteNameEnum ivNoteName, bool ivPadFront=false);

  public:
    BaseVoice();
    virtual ~BaseVoice();
    virtual BaseDuration countTotalDuration() const;
    virtual bool checkFull(const BaseDuration& ivDuration) const;

    virtual bool frontPadWithSilence(const BaseDuration& ivDuration);
    virtual bool frontPadWithRest(const BaseDuration& ivDuration);
    virtual bool backPadWithSilence(const BaseDuration& ivDuration);
    virtual bool backPadWithRest(const BaseDuration& ivDuration);
    virtual bool trimFront(const BaseDuration& ivDuration);
    virtual bool trimBack(const BaseDuration& ivDuration);

    virtual void appendNote(BaseNote* ivNote);
    virtual void insertNote(BaseNote* ivNote, UInt16 ivPosition=0);
    virtual BaseNote* getNote(UInt16 ivPosition) const;
    virtual BaseNote* getNoteNoRangeLimit(UInt16 ivPosition) const;
};

} // namespace core
} // namespace hautbois

#endif