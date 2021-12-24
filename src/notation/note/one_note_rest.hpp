#pragma once
#include "one_note_base.hpp"

namespace hautbois {

class OneNoteRest : public OneNoteBase {
protected:
    const Duration duration;
public:
    OneNoteRest(Duration duration):
    duration { duration }
    {}

    NoteName getName() const override {
        return "R";
    }
    NoteIndex getIndex() const override {
        return _REST_NOTE_INDEX;
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
        return { "R" };
    }

    GroupNoteIndex getGroupIndex() const override {
        return { _REST_NOTE_INDEX };
    }
    
    GroupDuration getGroupDuration() const override {
        return { duration };
    }


    NoteType getType() const override { return NoteType::REST; }

    const std::string printNote() const {
        std::string s { "(R," + duration.printDuration() + ")" };
        return s;
    }
};

}