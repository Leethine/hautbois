#pragma once
#include "note_creator_utils.hpp"

#include "../note_property/control.hpp"
#include "../note_property/ornament.hpp"
#include "../note_property/technique.hpp"

#include "../base/base_optional.hpp"

namespace hautbois 
{

using NotePtr=std::unique_ptr<OneNoteBase>;

class OneNote {
    NotePtr newNotePtr(const std::string& note_name_token, 
                        const std::string& duration_token) {
        switch(note_creator_utils::checkNoteType(note_name_token)) {
        case NoteType::REST :
            return std::make_unique<OneNoteRest>
                (note_creator_utils::str2Duration(duration_token));
            break;
        case NoteType::MONO :
            return std::make_unique<OneNoteMono>
                (note_creator_utils::str2NoteName(note_name_token),
                 note_creator_utils::str2Duration(duration_token) );
            break;
        case NoteType::TUPLET :
            return std::make_unique<OneNoteTuplet>
                (note_creator_utils::str2GroupNoteNameTuplet(note_name_token),
                    note_creator_utils::str2Duration(duration_token) );
            break;
        case NoteType::CHORD :
            if ( note_creator_utils::checkIfSingleDuration(duration_token) )
                return std::make_unique<OneNoteChord>
                    (note_creator_utils::str2GroupNoteNameChord(note_name_token),
                     note_creator_utils::str2GroupDuration(duration_token,note_creator_utils::str2GroupNoteNameChord(note_name_token).size() ));
            else
                return std::make_unique<OneNoteChord>
                    (note_creator_utils::str2GroupNoteNameChord(note_name_token),
                     note_creator_utils::str2GroupDuration(duration_token) );
            break;
        case NoteType::VOID :
            return std::make_unique<OneNoteVoid>
                (note_creator_utils::str2Duration(duration_token));
            break;
        case NoteType::VIRTUAL :
            std::cerr << "Syntax Error: " << note_name_token << "\n";
            exit(EXIT_FAILURE);
            break;
        default:
            return std::make_unique<OneNoteBase>();
            break;
        }
    }

protected:
    const NotePtr note;
public:
    // TODO handle note properties
    //BaseOptional<NoteControl> control;
    //BaseOptional<NoteOrnament> ornament;
    //BaseOptional<NoteTechnique> technique;

    OneNote(const std::string& note_name_token, 
         const std::string& duration_token):
    note { newNotePtr(note_name_token, duration_token) }
    {}

    virtual NoteType getType() const {
        return note->getType();
    }

    virtual std::string getDuration() const {
        std::string sout;
        GroupDuration d = note->getGroupDuration();
        for(auto it = d.begin(); it != d.end(); it++) {
            sout += it->printDuration() + "+";
        }
        sout.pop_back();
        return sout;
    }

    virtual Duration getPrincipalDuration() const {
        GroupDuration d = note->getGroupDuration();
        Duration d_max = *std::max_element(d.begin(),d.end());
        return d_max;
    }

    virtual std::string getIndex() const {
        std::string sout;
        GroupNoteIndex idx = note->getGroupIndex();
        for(auto it = idx.begin(); it != idx.end(); it++) {
            sout += std::to_string(*it) + "+";
        }
        sout.pop_back();
        return sout;
    }

    virtual std::string printNote() const {
        return note->printNote();
    }

    friend std::ostream& operator<<(std::ostream& o, const OneNote& n) {
        o << n.printNote();
        return o;
    } 
};

}
