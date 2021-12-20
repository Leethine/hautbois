#include <cassert>
#include <iostream>
#include <algorithm>

#include "../base/000_base.hpp"
#include "duration.hpp"

namespace hautbois 
{
namespace note_utility 
{

NoteIndex noteName2Index(const NameIndexTable& name_index_table,
                              const NoteName& note_name) {
    NoteIndex index;
    try {
        index = name_index_table.at(note_name);
        return index;
    }
    catch (std::out_of_range& e) {
        std::cout << "Error encountered while processing "
            << "\"" << note_name << "\"" << ": "
            << "Invalid Note Value!" << "\n";
            exit(EXIT_FAILURE);
    }
}

GroupNoteIndex groupNoteName2Index(const NameIndexTable& name_index_table,
                                   const GroupNoteName& group_note_name) {
    GroupNoteIndex indices;
    auto it = group_note_name.begin();
    try {
        for ( ; it != group_note_name.end(); it++ ) {
            indices.push_back(name_index_table.at(*it));
        }
        return indices;
    }
    catch (std::out_of_range& e) {
        std::cout << "Error encountered while processing "
            << "\"" << *it << "\"" << ": "
            << "Invalid Note Value!" << "\n";
            exit(EXIT_FAILURE);
    }
}

} // namespace hautbois
} // namespace note_utility

/*

    GroupIndex groupName2IndexQuery(const NameIndexTable& name_index_table, 
                               const GroupName& names) const {
        GroupIndex indices;
        try {
            for (auto it {begin(names)}; it != end(names); ++it)
                indices.push_back(name_index_table.at(*it));
            return indices;
        }
        catch (std::out_of_range& e) {
            std::cout << "Error encountered while processing "
             << "chord: "
             << "Invalid Note Value!" << "\n";
            exit(EXIT_FAILURE);
        }
    }

    bool isSimpleChord(const GroupDuration durations) const {
        Duration d { durations.front() };

        for (auto it {begin(durations)}; it != end(durations); ++it)
            if ( d.num != it->num || d.denom != it->denom )
                return false;
        
        return true;
    }
    bool verifySingleNote(const NameIndexTable& name_index_table) const {
        if ( index != name_index_table.at(name) )
            return false;
        return true;
    }
    
    bool verifyGroupNote(const NameIndexTable& name_index_table) const {
        if ( groupname.empty()  || 
             groupindex.empty() || 
             groupduration.empty() )
            return false;

        if ( groupname.size()  != groupduration.size() ||
             groupname.size()  != groupindex.size()    ||
             groupindex.size() != groupduration.size() )
             return false;
        
        for ( int i { 0 }; i < groupname.size(); ++i )
            if ( groupindex[i] != name_index_table.at(groupname[i]) )
                return false;
        
        return true;
    }
    
    bool verifyRestNote() const {
        if ( index != REST_NOTE_INDEX )
            return false;
        return true;
    }

    bool verifyNote(const NameIndexTable& name_index_table) const  {
        switch (type)
        {
        case NoteType::RestNote :
            return verifyRestNote();
            break;
        case NoteType::GroupNote :
            return verifyGroupNote(name_index_table);
            break;
        case NoteType::SingleNote :
            return verifySingleNote(name_index_table);
            break;
        default:
            return false;
            break;
        }
        return false;
    }
*/