#include "one_note_base.hpp"

namespace hautbois {

class OneNoteMono : public OneNote {
protected:
    const NoteName name;
    const NoteIndex index;
    const Duration duration;
public:
    OneNoteMono(NoteName& name, Duration& duration): 
    name { name },
    index { note_utility::noteName2Index(_SCI_NAME_NOTE_INDEX_TABLE, name) },
    duration { duration }
    {
        type = NoteType::MONO;
    }

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
    Beat getDuration() const override {
        return duration;
    }

    const std::string printNote() const override {
        std::string s {   "(" + name + "," + std::to_string(duration.num) 
                        + "/" + std::to_string(duration.denom) ")"  };
        return s;
    }

    bool operator==(const AnyNote& note2) const override {
        if (this->index == note2.index && this->duration == note2.duration)
            return true;
        else
            return false;
    }
};

}