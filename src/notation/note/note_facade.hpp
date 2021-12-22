#pragma once
#include "note_creator_utils.hpp"

namespace hautbois 
{

using NotePtr=std::unique_ptr<OneNote>;

class Note {
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
        case NoteType::VIRTUAL :
            std::cerr << "Syntax Error: " << note_name_token << "\n";
            exit(EXIT_FAILURE);
        break;
        default:
            return std::make_unique<OneNote>();
        break;
        }
    }

protected:
    const NotePtr note;
public:
    Note(const std::string& note_name_token, 
         const std::string& duration_token):
    note { newNotePtr(note_name_token, duration_token) }
    {}

    NoteType getType() const {
        return note->getType();
    }

    Duration getDuration() const {
        return note->getDuration();
    }

    std::string printNote() const {
        return note->printNote();
    }
};

}
