/* Ornament definitions mother class */
#pragma once
#include "../../defs/defs.hpp"

namespace hautbois 
{
using OrnamentName=std::string;
using OrnamentValue=int[3];
enum class OrnamentType
{
    ACCIACCATURA,
    APPOGGIATURA,
    ARPEGGIO,
    CADENZA,
    DINAMICA,
    FIORITURA,
    GLISSANDO,
    GRUPPETTO,
    MORDENTE,
    TREMOLO,
    TRILLO
};

const std::map<OrnamentName, OrnamentType> ornament_name_type_table {
    // Italian
    {"Acciaccatura", OrnamentType::ACCIACCATURA},
    {"acciaccatura", OrnamentType::ACCIACCATURA},
    {"ACCIACCATURA", OrnamentType::ACCIACCATURA},
    {"Appoggiatura", OrnamentType::APPOGGIATURA},
    {"appoggiatura", OrnamentType::APPOGGIATURA},
    {"APPOGGIATURA", OrnamentType::APPOGGIATURA},
    {"Arpeggio", OrnamentType::ARPEGGIO},
    {"arpeggio", OrnamentType::ARPEGGIO},
    {"ARPEGGIO", OrnamentType::ARPEGGIO},
    {"Cadenza", OrnamentType::CADENZA},
    {"cadenza", OrnamentType::CADENZA},
    {"CADENZA", OrnamentType::CADENZA},
    {"Dinamica", OrnamentType::DINAMICA},
    {"dinamica", OrnamentType::DINAMICA},
    {"DINAMICA", OrnamentType::DINAMICA},
    {"Fioritura", OrnamentType::FIORITURA},
    {"fioritura", OrnamentType::FIORITURA},
    {"FIORITURA", OrnamentType::FIORITURA},
    {"Glissando", OrnamentType::GLISSANDO},
    {"glissando", OrnamentType::GLISSANDO},
    {"GLISSANDO", OrnamentType::GLISSANDO},
    {"Gruppetto", OrnamentType::GRUPPETTO},
    {"gruppetto", OrnamentType::GRUPPETTO},
    {"GRUPPETTO", OrnamentType::GRUPPETTO},
    {"Mordente", OrnamentType::MORDENTE},
    {"mordente", OrnamentType::MORDENTE},
    {"MORDENTE", OrnamentType::MORDENTE},
    {"Tremolo", OrnamentType::TREMOLO},
    {"tremolo", OrnamentType::TREMOLO},
    {"TREMOLO", OrnamentType::TREMOLO},
    {"trillo", OrnamentType::TRILLO},
    {"Trillo", OrnamentType::TRILLO},
    {"TRILLO", OrnamentType::TRILLO}
};

struct NoteOrnament
{
    OrnamentName name;
    OrnamentType type;
    OrnamentValue value;
    NoteOrnament()=default;
};

}
