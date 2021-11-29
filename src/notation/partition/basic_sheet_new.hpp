#pragma once
#include "sheet_defs.hpp"
#include "one_voice.hpp"

namespace hautbois 
{

using VoiceVecPtr=std::vector<std::unique_ptr<OneVoice>>;

class BasicSheet {
    protected:

    const UIntValue nb_voice;
    mutable Tempo tempo;
    const TonalityType tonality;
    const ScaleName scale;
    const Meter meter;

    const std::vector<InstrumentType> instrusment_list;
    const std::vector<myPairClef> clefs_list;

    VoiceVecPtr voices;

    // append clef-at pair from token string, e.g. G-2
    void appendClef(std::vector<myPairClef>& clefs_list, 
                     const std::string& token) {
        BarParserUtl parser;
        TokenVector vec = parser.splitToken(token,"-");
        std::string clef = vec[0];
        std::string at;
        if ( vec.size() == 1 ) { at = ""; }
        else if ( vec.size() == 2 ) { at = vec[1]; }
        else {
            throw std::domain_error("Wrong format in clef pair: " + token);
        }

        assert(clefs_list.size() < nb_voice);
        if ( clefs_list.size() >= nb_voice ) {
            throw std::domain_error("Clefs already full!");
        }

        const UIntValue G_AT_DEFAULT = 2;
        const UIntValue F_AT_DEFAULT = 4;
        const UIntValue C_AT_DEFAULT = 3;

        if ( clef == "G" || clef == "g" ) {
            clefs_list.emplace_back( at.empty() ? 
                myPairClef(clef[0], G_AT_DEFAULT) :
                myPairClef(clef[0], static_cast<UIntValue>(std::stoi(at)))
            );
        }
        else if ( clef == "C" || clef == "c" ) {
            clefs_list.emplace_back( at.empty() ? 
                myPairClef(clef[0], C_AT_DEFAULT) :
                myPairClef(clef[0], static_cast<UIntValue>(std::stoi(at)))
            );
        }
        else if ( clef == "F" || clef == "f" ) {
            clefs_list.emplace_back( at.empty() ? 
                myPairClef(clef[0], F_AT_DEFAULT) :
                myPairClef(clef[0], static_cast<UIntValue>(std::stoi(at)))
            );
        }
        else {
            throw std::domain_error("Wrong format in clef pair: " + token);
        }
    }
    
    std::vector<InstrumentType>& makeClefList() {
        
    }

    void appendInstrument(std::vector<InstrumentType>& instrusment_list, 
                          const std::string& instrument_name) {
        instrusment_list.emplace_back(Instrument::str2Type(instrument_name));
    }

    std::vector<InstrumentType>& makeInstrumentList() {
        
    }

    /*
    void checkSetUp() {
        if ( nb_voice == 0 || 
             scale == "unknown" ||
             meter.num == 0 ) {
            throw std::runtime_error("Sheet not yet set up.");
        }

        if ( instrusment_list.size() != nb_voice ||
             clefs_list.size() != nb_voice ) {
            throw std::runtime_error("Sheet not yet set up.");
        }
        
        if ( nb_voice == 0 ||
             tempo == Tempo::UNKNOWN ||
             tonality == TonalityType::UNKNOWN || 
             scale == "unknown" ||
             meter.num == 0 ) {
            throw std::runtime_error("Sheet not yet set up.");
        }
    }
    */

    public:
    BasicSheet(UIntValue nbvoices) :
    nb_voice { nbvoices },
    tempo { Tempo::UNKNOWN },
    tonality { TonalityType::UNKNOWN },
    scale { "unknown" },
    meter { Meter(0,1) }
    {
    }
    
    void setTempo(const std::string& tempostr) {
        BarParserUtl parser;
        std::string tempostr_ns = parser.rmSpace(tempostr);
        boost::to_lower(tempostr_ns);
        try {
            tempo = TEMPO_TEXT_TABLE_IT.at(tempostr_ns);
        }
        catch(std::exception& e) {
            std::cout << "Error: invalid tempo: " << tempostr << "!\n";
        }
    }

    OneVoice& getVoiceN(size_t n) {
        assert(n < nb_voice);
        if ( n > nb_voice ) {
            throw std::range_error("Given value more than total voices!");
            return *voices[nb_voice-1];
        }
        else {
            return *voices[n];
        }
    }
};



}
