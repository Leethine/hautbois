#pragma once

#include "keymap.hpp"
#include "tonality_map.hpp"

namespace hautbois 
{
namespace base_mapping_utils 
{

NoteIndex noteName2Index(const NoteNameIndexTable& name_index_table,
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

GroupNoteIndex groupNoteName2Index(const NoteNameIndexTable& name_index_table,
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

TonalityType tonalityStr2Type(const ScaleName& scale,
                              const TonalityStrTypeTable& table) {
    try { return table.at(scale); }
    catch (std::out_of_range& e) {
        std::cout << "Error: Tonality: " 
                  << scale << " is invalid." << "\n";
        exit(EXIT_FAILURE);
    }
}

TonalityType findRelativeScale(TonalityType tonality_type,
                                const CircleOfFifthTable& table) {
    return table.at(tonality_type);
}

} // namespace hautbois
} // namespace note_utility
