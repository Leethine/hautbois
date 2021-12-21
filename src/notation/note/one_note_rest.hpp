#include "one_note_base.hpp"

namespace hautbois {

class OneNoteRest : public OneNote {
protected:
    const Duration duration;
public:
    OneNoteRest(Duration& duration):
    duration { duration }
    {
        type = NoteType::REST;
    }

    NoteName getName() const override {
        return "R";
    }
    NoteIndex getIndex() const override {
        return _REST_NOTE_INDEX;
    }
    Beat getDuration() const override {
        return duration.getNum();
    }
    Beat getDurationDenom() const override {
        return duration.getDenom();
    }
    Beat getDuration() const override {
        return duration;
    }

    const std::string printNote() const override {
        std::string s {   "(" + "R," + std::to_string(duration.num) 
                        + "/" + std::to_string(duration.denom) ")"  };
        return s;
    }

    bool operator==(const AnyNote& note2) const override {
        if (this->duration == note2.duration)
            return true;
        else
            return false;
    }
};

}