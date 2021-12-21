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

    GroupNoteName getName() const override {
        return name;
    }
    GroupNoteIndex getIndex() const override {
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
        std::string = ns;
        for (auto it=name.begin(); it != name.end(); it++) {
            ns += *it + "-";
        }
        ns.pop_back();
        std::string s {   "(" + names + "," + std::to_string(duration.num) 
                        + "/" + std::to_string(duration.denom) ")"  };
        return s;
    }
    
    bool operator==(const AnyNote& note2) const override {
        if (this->duration == note2.duration && 
            this->index.size() == note2.index.size()) {
            for (auto it1=this->index.begin(), it2=note2.index.begin();
                 it1 != this->index.end() && it2 != note2.index.end(); 
                 it1++, it2++) {
                if ( *it1 != *it2 ) {
                    return false;
                }
            }
            return true;
        }
        else { return false; }
    }
};

}