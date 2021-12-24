#pragma once
#include "one_note_base.hpp"

namespace hautbois {

class OneNoteChord : public OneNoteBase {
    bool isSimpleChord() const {
        Duration d1 = durations.front();
        for (auto it=durations.begin(); it != durations.end(); it++)
            if ( d1.getNum() * it->getDenom() != d1.getDenom() * it->getNum() )
                return false;
        return true;
    }
protected:
    const GroupNoteName names;
    const GroupNoteIndex indices;
    const GroupDuration durations;
public:
    OneNoteChord(GroupNoteName groupname, GroupDuration duration):
    names { groupname },
    indices { base_mapping_utils::groupNoteName2Index( _SCI_NAME_NOTE_INDEX_TABLE,
                                               groupname) },
    durations { duration }
    {
        //TODO Validate non empty
        assert(!names.empty());
        assert(!indices.empty());
    }

    NoteName getName() const override {
        return "Chord";
    }
    NoteIndex getIndex() const override {
        return _CHORD_NOTE_INDEX;
    }
    Beat getDurationNum() const override {
        return this->getDuration().getNum();
    }
    Beat getDurationDenom() const override {
        return this->getDuration().getDenom();
    }
    Duration getDuration() const override {
        return * std::max_element(durations.begin(),durations.end());
    }
    GroupNoteName getGroupName() const override {
        return names;
    }
    GroupNoteIndex getGroupIndex() const override {
        return indices;
    }
    GroupDuration getGroupDuration() const override {
        if (isSimpleChord()) {
            return { durations.front() };    
        }
        else { return durations; }
    }

    const std::string printNote() const override {
        std::string notename_str;
        for (auto it=names.begin(); it != names.end(); it++) {
            notename_str += *it + "+";
        }
        notename_str.pop_back();
        std::string duration_str;
        if (isSimpleChord()) {
            duration_str = durations[0].printDuration();
        }
        else {
            for (auto it=durations.begin(); it != durations.end(); it++) {
                duration_str += it->printDuration() + "+";
            }
            duration_str.pop_back();
        }

        return "(" + notename_str + "," + duration_str + ")";
    }

    NoteType getType() const override { return NoteType::CHORD; }
};

}