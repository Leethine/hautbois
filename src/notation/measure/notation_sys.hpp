#pragma once
#include "../defs/defs.hpp"
#include "../note/any_note.hpp"

namespace hautbois {

using NotationSystemName=std::string;

enum class NotationSystemType {
    LATIN,
    SCIENTIFIC,
    HELMHOLTZ
};

const std::map<NotationSystemName,NotationSystemType> NOTATION_SYSTEM_TABLE {
    {"Latin", NotationSystemType::LATIN},
    {"latin", NotationSystemType::LATIN},
    {"LATIN", NotationSystemType::LATIN},
    {"Fr", NotationSystemType::LATIN},
    {"fr", NotationSystemType::LATIN},
    {"FR", NotationSystemType::LATIN},
    {"French", NotationSystemType::LATIN},
    {"french", NotationSystemType::LATIN},
    {"FRENCH", NotationSystemType::LATIN},
    {"It", NotationSystemType::LATIN},
    {"it", NotationSystemType::LATIN},
    {"IT", NotationSystemType::LATIN},
    {"Italian", NotationSystemType::LATIN},
    {"italian", NotationSystemType::LATIN},
    {"ITALIAN", NotationSystemType::LATIN},
    {"Sci", NotationSystemType::SCIENTIFIC},
    {"sci", NotationSystemType::SCIENTIFIC},
    {"SCI", NotationSystemType::SCIENTIFIC},
    {"SCIENTIFIC", NotationSystemType::SCIENTIFIC},
    {"Scientific", NotationSystemType::SCIENTIFIC},
    {"scientific", NotationSystemType::SCIENTIFIC},
    {"US", NotationSystemType::SCIENTIFIC},
    {"us", NotationSystemType::SCIENTIFIC},
    {"Us", NotationSystemType::SCIENTIFIC},
    {"American", NotationSystemType::SCIENTIFIC},
    {"american", NotationSystemType::SCIENTIFIC},
    {"En", NotationSystemType::SCIENTIFIC},
    {"en", NotationSystemType::SCIENTIFIC},
    {"English", NotationSystemType::SCIENTIFIC},
    {"english", NotationSystemType::SCIENTIFIC},
    {"Ger", NotationSystemType::HELMHOLTZ},
    {"ger", NotationSystemType::HELMHOLTZ},
    {"GER", NotationSystemType::HELMHOLTZ},
    {"de", NotationSystemType::HELMHOLTZ},
    {"De", NotationSystemType::HELMHOLTZ},
    {"DE", NotationSystemType::HELMHOLTZ},
    {"German", NotationSystemType::HELMHOLTZ},
    {"GERMAN", NotationSystemType::HELMHOLTZ},
    {"german", NotationSystemType::HELMHOLTZ},
    {"Deutsch", NotationSystemType::HELMHOLTZ},
    {"deutsch", NotationSystemType::HELMHOLTZ},
    {"DEUTSCH", NotationSystemType::HELMHOLTZ},
    {"allemand", NotationSystemType::HELMHOLTZ},
    {"Allemand", NotationSystemType::HELMHOLTZ},
    {"ALLEMAND", NotationSystemType::HELMHOLTZ},
    {"HELMHOLTZ", NotationSystemType::HELMHOLTZ},
    {"Helmholtz", NotationSystemType::HELMHOLTZ},
    {"helmholtz", NotationSystemType::HELMHOLTZ}
};

}