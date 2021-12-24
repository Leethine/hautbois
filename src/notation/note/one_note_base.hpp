#pragma once
#include "../base/base.hpp"
#include "duration.hpp"

namespace hautbois 
{

const NoteIndex _REST_NOTE_INDEX {101};
const NoteIndex _CHORD_NOTE_INDEX {103};
const NoteIndex _TUPLET_NOTE_INDEX {106};

enum class NoteType {
    REST,
    MONO,
    CHORD,
    TUPLET,
    VIRTUAL,
};

class OneNoteBase {
protected:
    mutable bool tied;

    OneNoteBase& operator=(const OneNoteBase&)=delete;
    
public:
    //TODO enable somewhere
    //BaseOptional<NoteProperty> property;
    //BaseOptional<NoteOrnament> ornament;
    //BaseOptional<NoteTechnique> technique;

    OneNoteBase():    
    //type { NoteType::VIRTUAL },
    tied { false }
    {}

    virtual bool isTied() const {
        return tied;
    }
    virtual void makeTie() const {
        tied = true;
    }
    virtual void unTie() const {
        tied = false;
    }
    virtual NoteName getName() const {
        return "";
    }
    virtual NoteIndex getIndex() const {
        return 0;
    }
    virtual Beat getDurationNum() const {
        return 0;
    }
    virtual Beat getDurationDenom() const {
        return 1;
    }
    virtual Duration getDuration() const {
        return {0,1};
    }
    virtual GroupNoteName getGroupName() const {
        return {};
    }
    virtual GroupNoteIndex getGroupIndex() const {
        return {};
    }
    virtual GroupDuration getGroupDuration() const {
        return {};
    }
    
    virtual NoteType getType() const { return NoteType::VIRTUAL; }

    virtual OneNoteBase duplicate() const {
        OneNoteBase n { OneNoteBase(*this) };
        return n;
    }

    virtual const std::string printNote() const {
        std::string s { "()" };
        return s;
    }
};

}
