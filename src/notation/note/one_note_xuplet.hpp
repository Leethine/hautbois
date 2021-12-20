#include "one_note_base.hpp"

namespace hautbois {

class OneNoteXuplet : public OneNote {
protected:
    const GroupNoteName name;
    const GroupNoteIndex index;
    const Duration duration;
public:
    OneNoteXuplet(GroupNoteName& groupname, Duration& duration):
    name { groupname }
    index { note_utility::noteName2Index(groupname) },
    duration { duration }
    {
        type = NoteType::XUPLET;
        //TODO Validate non empty
    }

    const std::string printNote() const override {
        std::string = ns;
        for (auto it=name.begin(); it != name.end(); it++) {
            ns += *it + "-";
        }
        ns.pop_back();
        std::string s {   "(" + names + "," + std::to_string(duration.num) 
                        + "/" + std::to_string(duration.denom) ")"  };
        return s;
    }
};

}