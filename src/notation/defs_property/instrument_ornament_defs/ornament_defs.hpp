/* Ornament definitions mother class */
#pragma once
#include "../../defs/defs.hpp"
#include <boost/algorithm/string.hpp>

/*
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
*/


namespace hautbois 
{

struct NoteOrnament {
    std::string key;
    int value;
    void addOrnament(const std::string& lkey, const std::string& lval) {
        std::set<std::string> valid_keys {
            "acciaccatura", "appoggiatura", "arpeggio",
            "cadenza", "dinamica", "fioritura", "glissando",
            "gruppetto", "mordente", "tremolo", "trillo"
        };
        auto search = valid_keys.find(lkey);
        if ( search != valid_keys.end() ) {
            this->key = lkey;
            if ( lval.empty() ) 
            this->value = 0;
            else {
                try {
                    this->value = std::stoi(lval);
                }
                catch(std::exception &e) {
                    std::cout << "Warning: " << "Value must be integer."
                            << "\n" << e.what() << "\n";
                    this->value = 0;
                }
            }
        }
        else {
            throw std::domain_error("Not supported Key: " + lkey);
        }
    };
};

}