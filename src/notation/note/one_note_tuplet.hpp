#pragma once
#include "one_note_base.hpp"

namespace hautbois {

class OneNoteTuplet : public OneNote {
protected:
    const GroupNoteName names;
    const GroupNoteIndex indices;
    const Duration duration;
public:
    OneNoteTuplet(GroupNoteName groupname, Duration duration):
    names { groupname },
    indices { base_mapping_utils::groupNoteName2Index(_SCI_NAME_NOTE_INDEX_TABLE,
                                                      groupname) },
    duration { duration }
    {
        //TODO Validate non empty
        assert(!names.empty());
    }

    NoteName getName() const override {
        return "Tuplet";
    }
    NoteIndex getIndex() const override {
        return _TUPLET_NOTE_INDEX;
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
        return names;
    }
    GroupNoteIndex getGroupIndex() const override {
        return indices;
    }
    GroupDuration getGroupDuration() const override {
        return { duration };
    }

    NoteType getType() const override { return NoteType::TUPLET; }

    const std::string printNote() const override {
        std::string notaneme_str;
        for (auto it=names.begin(); it != names.end(); it++) {
            notaneme_str += *it + "-";
        }
        notaneme_str.pop_back();
        return "(" + notaneme_str + "," + duration.printDuration() + ")";
    }

};

}