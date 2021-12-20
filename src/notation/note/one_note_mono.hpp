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

    const std::string printNote() const override {
        std::string s {   "(" + name + "," + std::to_string(duration.num) 
                        + "/" + std::to_string(duration.denom) ")"  };
        return s;
    }
};

}