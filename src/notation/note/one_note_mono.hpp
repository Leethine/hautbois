#pragma once
#include "one_note_base.hpp"

namespace hautbois {

class OneNoteMono : public OneNote {
protected:
    const NoteName name;
    const NoteIndex index;
    const Duration duration;
public:
    OneNoteMono(NoteName name, Duration duration): 
    name { name },
    index { base_mapping_utils::noteName2Index(_SCI_NAME_NOTE_INDEX_TABLE, name) },
    duration { duration }
    {}

    NoteName getName() const override {
        return name;
    }
    NoteIndex getIndex() const override {
        return index;
    }
    Beat getDurationNum() const override {
        return duration.getNum();
    }
    Beat getDurationDenom() const override {
        return duration.getDenom();
    }
    Duration getDuration() const override {
        return duration;
    }

    GroupNoteName getGroupName() const override {
        return { name };
    }

    GroupNoteIndex getGroupIndex() const override {
        return { index };
    }

    GroupDuration getGroupDuration() const override {
        return { duration };
    }

    NoteType getType() const override { return NoteType::MONO; }
    
    const std::string printNote() const override {
        std::string s { "(" + name + "," + duration.printDuration() + ")" };
        return s;
    }
};

}