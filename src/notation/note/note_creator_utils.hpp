#pragma once

#include <boost/algorithm/string.hpp>
#include "one_note_base.hpp"
#include "one_note_rest.hpp"
#include "one_note_mono.hpp"
#include "one_note_tuplet.hpp"
#include "one_note_chord.hpp"
#include "one_note_void.hpp"
#include "../base/base_syntax.hpp"

#define _DISABLE_UNSAFE_PTR_

namespace hautbois 
{
namespace note_creator_utils 
{

void rmWhiteSpace(std::string& token) {
    boost::erase_all(token, " ");
}
std::string rmWhiteSpace_copy(const std::string& token) {
    return boost::erase_all_copy(token, " ");
}

std::vector<std::string> splitToken(const std::string& token,
                                    const std::string& delim) {
    std::vector<std::string> split_vec;
    boost::split(split_vec, token,
                 boost::is_any_of(delim),
                 boost::token_compress_on);
    return split_vec;
}

NoteName str2NoteName(const std::string& token) {
    std::string token_ns = rmWhiteSpace_copy(token);
    //TODO replace assert: add exception handling
    base_syntax_utils::checkMonoNoteSyntax(token_ns);
    return token_ns;
}

Duration str2Duration(const std::string& token) {
    std::string token_ns = rmWhiteSpace_copy(token);
    //TODO replace assert: add exception handling
    base_syntax_utils::checkDurationSyntax(token_ns);
    TokenVector token_vec = splitToken(token_ns, "/");
    return {(Beat) std::stoi(token_vec[0]), (Beat) std::stoi(token_vec[1])};
}

GroupDuration str2GroupDuration(const std::string& token) {
    std::string token_ns = rmWhiteSpace_copy(token);
    //TODO replace assert: add exception handling
    base_syntax_utils::checkGroupDurationSyntax(token_ns);
    TokenVector token_vec = splitToken(token_ns, "+");
    GroupDuration durations;
    for (auto it=token_vec.begin(); it != token_vec.end(); it++) {
        durations.emplace_back(str2Duration(*it));
    }
    return durations;
}

GroupDuration str2GroupDuration(const std::string& token, size_t dup) {
    std::string token_ns = rmWhiteSpace_copy(token);
    //TODO replace assert: add exception handling
    base_syntax_utils::checkDurationSyntax(token_ns);
    Duration d = str2Duration(token_ns);
    GroupDuration durations;
    for (int i = 0; i < dup; i++) {
        durations.emplace_back(d);
    }
    return durations;
}

GroupNoteName str2GroupNoteNameTuplet(const std::string& token) {
    std::string token_ns = rmWhiteSpace_copy(token);
    //TODO replace assert: add exception handling
    base_syntax_utils::checkTupletSyntax(token_ns);
    TokenVector token_vec = splitToken(token_ns, "-");
    GroupNoteName names;
    for (auto it=token_vec.begin(); it != token_vec.end(); it++) {
        names.emplace_back(*it);
    }
    return names;
}

GroupNoteName str2GroupNoteNameChord(const std::string& token) {
    std::string token_ns = rmWhiteSpace_copy(token);
    //TODO replace assert: add exception handling
    base_syntax_utils::checkChordSyntax(token_ns);
    TokenVector token_vec = splitToken(token_ns, "+");
    GroupNoteName names;
    for (auto it=token_vec.begin(); it != token_vec.end(); it++) {
        names.emplace_back(*it);
    }
    return names;
}

bool checkIfSingleDuration(const std::string& duration_token) {
    std::string token_ns = rmWhiteSpace_copy(duration_token);
    //TODO abolish assertion
    assert(base_syntax_utils::checkDurationSyntaxBool(token_ns) ||
           base_syntax_utils::checkGroupDurationSyntaxBool(token_ns));

    if ( base_syntax_utils::checkDurationSyntaxBool(token_ns) )
        return true;
    else 
        return false;
}

NoteType checkNoteType(const std::string& note_name_token) {
    std::string token_ns = rmWhiteSpace_copy(note_name_token);
    if ( base_syntax_utils::checkRestNoteSyntaxBool(token_ns) ) {
        return NoteType::REST;
    }
    else if ( base_syntax_utils::checkVoidNoteSyntaxBool(token_ns) ) {
        return NoteType::VOID;
    }
    else if ( base_syntax_utils::checkMonoNoteSyntaxBool(token_ns) ) {
        return NoteType::MONO;
    }
    else if ( base_syntax_utils::checkChordSyntaxBool(token_ns) ) {
        return NoteType::CHORD;
    }
    else if ( base_syntax_utils::checkTupletSyntaxBool(token_ns) ) {
        return NoteType::TUPLET;
    }
    else { return NoteType::VIRTUAL; }
}

#ifndef _DISABLE_UNSAFE_PTR_
OneNoteBase * newOneNote(const std::string& note_name_token, 
                     const std::string& duration_token) {
    switch(note_creator_utils::checkNoteType(note_name_token)) {
    case NoteType::REST :
        return new OneNoteRest(str2Duration(duration_token));
    break;
    case NoteType::MONO :
        return new OneNoteMono(str2NoteName(note_name_token),
                               str2Duration(duration_token) );
    break;
    case NoteType::TUPLET :
        return new OneNoteTuplet(str2GroupNoteNameTuplet(note_name_token),
                                 str2Duration(duration_token) );
    break;
    case NoteType::CHORD :
        if ( checkIfSingleDuration(duration_token) )
            return new OneNoteChord(str2GroupNoteNameChord(note_name_token),
                       str2GroupDuration(duration_token, 
                       str2GroupNoteNameChord(note_name_token).size() ));
        else
            return new OneNoteChord(str2GroupNoteNameChord(note_name_token),
                                    str2GroupDuration(duration_token) );
    break;
    case NoteType::VIRTUAL :
        std::cerr << "Syntax Error: " << note_name_token << "\n";
        exit(EXIT_FAILURE);
    break;
    default:
        return new OneNoteBase();
    break;
    }
}
#endif

} // namespace hautbois
} // namespace note_creator_utils