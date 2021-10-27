/* Ornament definitions mother class */
#pragma once
#include "../../defs/defs.hpp"
#include <boost/algorithm/string.hpp>

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

const std::map<OrnamentName, OrnamentType> ornament_dictionary {
    // To be deleted
    /*
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
    */

    // Italian
    {"ACCIACCATURA", OrnamentType::ACCIACCATURA},
    {"APPOGGIATURA", OrnamentType::APPOGGIATURA},
    {"ARPEGGIO", OrnamentType::ARPEGGIO},
    {"CADENZA", OrnamentType::CADENZA},
    {"DINAMICA", OrnamentType::DINAMICA},
    {"FIORITURA", OrnamentType::FIORITURA},
    {"GLISSANDO", OrnamentType::GLISSANDO},
    {"GRUPPETTO", OrnamentType::GRUPPETTO},
    {"MORDENTE", OrnamentType::MORDENTE},
    {"TREMOLO", OrnamentType::TREMOLO},
    {"TRILLO", OrnamentType::TRILLO},

    // French

    // German

    // English

};

struct NoteOrnament
{
    NoteOrnament()=delete;

    OrnamentType type;
    OrnamentValue value;

    void setType(const OrnamentName& name) {
        OrnamentName uname { name };
        boost::to_upper(uname);
        // string query
        try {
            this->type = ornament_dictionary.at(uname);
        }
        catch(std::exception& e) {
            std::cout << "Error: Invalid Ornament Name" << "\n"
                      << e.what() << "\n";
            exit(EXIT_FAILURE);
        }
    }

    NoteOrnament(OrnamentType type):
    type { type }
    {}

    NoteOrnament(const OrnamentName& name) {
        setType(name);
    }
};

}
