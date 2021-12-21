#pragma once

#include "../base/000_base.hpp"
#include "duration.hpp"

namespace hautbois 
{

const NoteIndex _REST_NOTE_INDEX {101};
//const NoteIndex _CHORD_NOTE_INDEX {103};
//const NoteIndex _XUPLET_NOTE_INDEX {106};

enum class NoteType {
    REST,
    MONO,
    CHORD,
    XUPLET,
    VIRTUAL,
};

class OneNote {
protected:
    NoteType type;
    bool tied;

    OneNote& operator=(const OneNote&)=delete;
    OneNote(const OneNote&);

public:
    //BaseOptional<NoteProperty> property;
    //BaseOptional<NoteOrnament> ornament;
    //BaseOptional<NoteTechnique> technique;

    OneNote()=delete;

    OneNote(NoteName& name, NoteIndex& index, Duration& duration):
    type { NoteType::VIRTUAL },
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

    virtual OneNote duplicate() const {
        OneNote n { OneNote(*this) };
        return n;
    }

    virtual const std::string printNote() const {
        std::string s { "()" };
        return s;
    }

    virtual bool operator==(const AnyNote& n) const {
        return true;
    }

};

}
