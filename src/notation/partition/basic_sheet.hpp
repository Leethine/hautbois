#pragma once
#include "sheet_defs.hpp"
#include "one_voice.hpp"

namespace hautbois 
{

//using VoiceVec=std::vector<OneVoice>;
using VoiceVecPtr=std::vector<std::unique_ptr<OneVoice>>;

class BasicSheet {
    protected:

    std::string title;
    std::string author;
    std::string date;

    UIntValue nb_voice;
    Tempo tempo;
    TonalityType tonality;
    ScaleName scale;
    Meter meter;

    std::vector<InstrumentType> instrusment_list;
    std::vector<myPairClef> clefs_list;
    std::vector<ScaleName> scale_list;;

    VoiceVecPtr voices;

    // append clef-at pair from token string, e.g. G-2
    void appendClefs(const std::string& token) {
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

    void checkBasicSetUp() {
        if ( nb_voice == 0 || 
             scale == "unknown" ||
             meter.num == 0 ) {
            throw std::runtime_error("Sheet not yet set up.");
        }
    }

    void checkMiscSetUp() {
        
        if ( instrusment_list.size() != nb_voice ||
             scale_list.size() != nb_voice ||
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

    // fill the vectors with undefined value
    void resetInstruments() {
        instrusment_list.clear();
        for(int i=0; i < nb_voice; i++) {
            instrusment_list.push_back(InstrumentType::NONE);
        }
    }
    
    void resetClefs() {
        clefs_list.clear();
    }

    public:
    BasicSheet(UIntValue nbvoices) :
    nb_voice { nbvoices },
    tempo { Tempo::UNKNOWN },
    tonality { TonalityType::UNKNOWN },
    scale { "unknown" },
    meter { Meter(0,1) }
    {
        resetInstruments();
    }

    void setAuthor(const std::string& author) {
        this->author = author;
    }

    void setTitle(const std::string& title) {
        this->title = title;
    }

    void setDate(const std::string& date) {
        this->date = date;
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

    // Mandatory
    void setScale(const std::string& scalestr) {
        try {
            this->tonality = tonality_str_type_table.at(scalestr);
            this->scale = scalestr;
            // if tonality of each voice is not set, set them now
            scale_list.clear();
            for (int i=0; i < nb_voice; i++) {
                scale_list.emplace_back(this->scale);
            }
        }
        catch(std::exception& e) {
            std::cout << "Error: Invalid tonality format "
                      << scalestr << " - " << e.what() << "\n";
        }
    }

    // Mandatory
    void setMeter(const std::string& meterstr) {
        BarParserUtl parser;
        std::string meterstr_ns = parser.rmSpace(meterstr);
        this->meter = parser.readDurationFromStr(meterstr_ns);
    }

    void setInstruments(const std::vector<std::string>& val_list) {
        assert( val_list.size() == nb_voice );
        assert( instrusment_list.empty() );
        for (auto it = begin(val_list); it != end(val_list); it++ ) {
            instrusment_list.emplace_back( Instrument::str2Type(*it) );
        }
    }
    
    void setClefs(const std::vector<std::string>& val_list) {
        assert( val_list.size() == nb_voice );
        assert( clefs_list.empty() );
        for (auto it : val_list) {
            appendClefs(it);
        }
    }
    
    // set Nth voice tonality
    void setTonalyN(const std::string& scalestr, size_t n) {
        assert( scale_list.size() == nb_voice );
        assert( n < nb_voice );
        if ( scale_list.size() == nb_voice ) {
            throw std::runtime_error("Tonality not set yet!");
        }
        if ( n >= nb_voice ) {
            throw std::range_error("Index N out of range!");
        }
        else {
            scale_list[n] = scalestr;
        }
    }

    void initializeSheet() {
        try {
            checkBasicSetUp();
            for (int i = 0; i < nb_voice; i++) {
                voices.emplace_back( new OneVoice(scale_list[i], meter) );
            }
        }
        catch(std::exception& e) {
            std::cout << "Initialization error: " << e.what() << "\n";
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
