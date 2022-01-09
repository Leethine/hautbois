#pragma once

#include <regex>
#include "base.hpp"

namespace hautbois 
{
namespace base_syntax_regexp 
{

const std::string DURATION_TOKEN_PTN = "([0-9]+/[1-9]+){1}";
const std::string GROUP_DURATION_TOKEN_PTN = "([0-9]+/[1-9]+)\\+([0-9]+/[1-9]+\\+)*([0-9]+/[1-9]+)";
const std::string MONO_NOTE_TOKEN_PTN = "([A-G](#|b)?[0-8]){1}";
const std::string CHORD_NOTE_TOKEN_PTN = "[A-G](#|b)?[0-8]\\+([A-Z](#|b)?[0-8]\\+)*[A-G](#|b)?[0-8]";
const std::string TUPLET_NOTE_TOKEN_PTN = "[A-G](#|b)?[0-8]\\-([A-Z](#|b)?[0-8]\\-)*[A-G](#|b)?[0-8]";
const std::string REST_NOTE_TOKEN_PTN = "([R|r](est)?){1}";
const std::string VOID_NOTE_TOKEN_PTN = "([V|v](oid)?){1}";

} // namespace hautbois
} // namespace base_syntax_regexp