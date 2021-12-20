#include "one_note_base.hpp"

namespace hautbois {

using GroupDuration=std::vector<Duration>;

class OneNoteChord : public OneNote {
protected:
    const GroupNoteName name;
    const GroupNoteIndex index;
    const GroupDuration duration;
public:
    OneNoteChord(GroupNoteName& groupname, GroupDuration& duration):
    name { groupname }
    index { note_utility::noteName2Index(groupname) },
    duration { duration }
    {
        type = NoteType::CHORD;
        //TODO Validate non empty
    }

    const std::string printNote() const override {
        std::string = ns;
        for (auto it=name.begin(); it != name.end(); it++) {
            ns += *it + "+";
        }
        ns.pop_back();
        std::string = ds;
        if (isSimpleChord() && !duration.empty()) {
            ds = std::to_string(duration[0].num) + "/" 
               + std::to_string(duration[0].denom);
        }
        else if (!isSimpleChord()) {
            for (auto it=duration.begin(); it != duration.end(); it++) {
                ds += std::to_string(it->num) + "/"
                    + std::to_string(it->denom) + "+";
            }
            ds.pop_back();
        }
        else { // in this case duration is empty
            ds = "";
        }

        std::string s { "(" + ns + "," + ds + ")" };
        return s;
    }

    bool isSimpleChord() const {
        Duration d { duration.front() };
        for (auto it=duration.begin() }; it != duration.end(); it++)
            if ( d.num * it->denom != d.denom * it->num )
                return false;
        return true;
    }
};

}