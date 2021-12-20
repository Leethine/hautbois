#pragma once

#include "../base/000_base.hpp"
#include "duration.hpp"

namespace hautbois 
{

//const NoteIndex _REST_NOTE_INDEX {101};
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
    /*
    virtual NoteName getName() const {
        return name;
    }
    virtual NoteIndex getIndex() const {
        return index;
    }
    virtual Beat getDurationNum() const {
        return duration.num;
    }
    virtual Beat getDurationDenom() const {
        return duration.denom;
    }
    */
    virtual OneNote duplicate() const {
        OneNote n { OneNote(*this) };
        return n;
    }

    virtual const std::string printNote() const {
        std::string s { "()" };
        return s;
    }

};

}
