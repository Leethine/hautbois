#pragma once

#include <cassert>

#include "base.hpp"
#include "syntax_regexp.hpp"

namespace hautbois 
{
namespace base_syntax_utils 
{

void checkDurationSyntax(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::DURATION_TOKEN_PTN);
    assert(std::regex_match(token_ns, regexp));
}

void checkGroupDurationSyntax(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::GROUP_DURATION_TOKEN_PTN);
    assert(std::regex_match(token_ns, regexp));
}

void checkRestNoteSyntax(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::REST_NOTE_TOKEN_PTN);
    assert(std::regex_match(token_ns, regexp));
}

void checkMonoNoteSyntax(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::MONO_NOTE_TOKEN_PTN);
    assert(std::regex_match(token_ns, regexp));
}

void checkTupletSyntax(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::TUPLET_NOTE_TOKEN_PTN);
    assert(std::regex_match(token_ns, regexp));
}

void checkChordSyntax(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::CHORD_NOTE_TOKEN_PTN);
    assert(std::regex_match(token_ns, regexp));
}

// same functions that reurn bool type
bool checkDurationSyntaxBool(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::DURATION_TOKEN_PTN);
    return std::regex_match(token_ns, regexp);
}

bool checkGroupDurationSyntaxBool(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::GROUP_DURATION_TOKEN_PTN);
    return std::regex_match(token_ns, regexp);
}

bool checkRestNoteSyntaxBool(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::REST_NOTE_TOKEN_PTN);
    return std::regex_match(token_ns, regexp);
}

bool checkMonoNoteSyntaxBool(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::MONO_NOTE_TOKEN_PTN);
    return std::regex_match(token_ns, regexp);
}

bool checkTupletSyntaxBool(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::TUPLET_NOTE_TOKEN_PTN);
    return std::regex_match(token_ns, regexp);
}

bool checkChordSyntaxBool(const std::string& token_ns) {
    std::regex regexp(base_syntax_regexp::CHORD_NOTE_TOKEN_PTN);
    return std::regex_match(token_ns, regexp);
}

} // namespace hautbois
} // namespace base_syntax_utility
