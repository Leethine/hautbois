#pragma once
#include "one_note_base.hpp"

namespace hautbois {

class OneNoteVoid : public OneNoteBase {
protected:
    const Duration duration;
public:
    OneNoteVoid(Duration duration):
    duration { duration }
    {}

    NoteName getName() const override {
        return "V";
    }
    NoteIndex getIndex() const override {
        return _VOID_NOTE_INDEX;
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
        return { "V" };
    }

    GroupNoteIndex getGroupIndex() const override {
        return { _VOID_NOTE_INDEX };
    }
    
    GroupDuration getGroupDuration() const override {
        return { duration };
    }

    NoteType getType() const override { return NoteType::VOID; }

    const std::string printNote() const {
        std::string s { "(V," + duration.printDuration() + ")" };
        return s;
    }
};

}