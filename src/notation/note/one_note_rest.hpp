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

    const std::string printNote() const override {
        std::string s {   "(" + "R," + std::to_string(duration.num) 
                        + "/" + std::to_string(duration.denom) ")"  };
        return s;
    }
};

}