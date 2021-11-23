#pragma once
#include "sheet_defs.hpp"

namespace hautbois 
{

class BarElement : public OneBarFacade {
    Clef clef;
    ClefAt clef_at;
    Tempo tempo;

    public:
    
    explicit BarElement (const NoteName& scale, Beat num, Beat denom) : 
    OneBarFacade(scale, num, denom)
    {
        clef = G_CLEF;
        clef_at = stave::LINE3;
    }

    void setClef(Clef clef, ClefAt line) {
        if ( clef==G_CLEF || clef==F_CLEF || clef==C_CLEF ) {
            this->clef = clef;
        }
        else {
            throw std::domain_error("Invalid Clef name!");
        }
        if ( line >= stave::LINE1 && line <= stave::LINE5 ) {
            this->clef_at = line;
        }
        else {
            throw std::domain_error("Location of the Clef is invalid!");
        }
    }

    void setClef(Clef clef) {
        if ( clef==G_CLEF ) {
            setClef(clef, stave::LINE2);
        }
        else if ( clef==C_CLEF ) {
            setClef(clef, stave::LINE3);
        }
        else if ( clef==F_CLEF ) {
            setClef(clef, stave::LINE4);
        }
        else {
            throw std::domain_error("Invalid Clef name!");
        }
    }

    void setTempo(const std::string& tempostr) {
        std::string tempostr_ns = BarParserUtl::rmSpace(tempostr);
        boost::to_lower(tempostr_ns);
        try {
            tempo = TEMPO_TEXT_TABLE_IT.at(tempostr_ns);
        }
        catch(std::exception& e) {
            std::cout << "Error: invalid tempo: " << tempostr << "!\n";
        }
    }

    void setTempo(Tempo tempo) {
        this->tempo = tempo;
    }

    Tempo getTempo() {
        return tempo;
    }
};

using ListBar=std::list<std::unique_ptr<BarElement>>;
class OneVoice {
    protected:
    const Meter meter;
    mutable ScaleName scale;
    mutable ListBar bars;
    
    InstrumentType instrument;
    Tempo tempo;
    
    public:
    OneVoice()=delete;
    OneVoice(const ScaleName& scale, const Meter& meter) :
    scale { scale },
    meter { meter },
    tempo { Tempo::UNKNOWN },
    instrument { InstrumentType::NONE }
    {
        // create first empty bar
        bars.emplace_back( new BarElement(scale, meter.num, meter.denom) );
    }

    BarElement& getNthBar(size_t n) {
        try {
            if ( n >= bars.size() )  {
               throw std::out_of_range("Index out of range!");
            }
            else {
                auto it = bars.begin(); 
                std::advance(it, n);
                std::unique_ptr<BarElement>& recovered_bar = *it;
                return *recovered_bar;
            }
        }
        catch (std::exception& e) {
            std::cout << "Error at " <<  n << ": " << e.what() << "\n";
            std::unique_ptr<BarElement>& recovered_bar = * bars.end();
            return *recovered_bar;
        }
    }

    BarElement& getLastBar() {
        return getNthBar(bars.size()-1);
    }

    void addNote(const TokenString& token) {
        BarElement& lastbar = getLastBar();
        if (lastbar.checkBarComplete()) {
            // TODO Could modify later
            // e.g. change the tonality in the middle of the music
            // or change the clef position, etc
            bars.emplace_back( new BarElement(scale,meter.num, meter.denom) );
            
            BarElement& lastbar = getLastBar();
            lastbar.addNote(token, this->instrument);
        }
        else {
            lastbar.addNote(token, this->instrument);
        }
    }

    void showBars() {
        for (int i=0; i < bars.size(); i++) {
            BarElement& currentbar = getNthBar(i);
            std::cout << " " << currentbar << " |";
        }
        std::cout << "|;\n";
    }
    
    void setTempo(Tempo tempo) {
        this->tempo = tempo;
    }

    Tempo getTempo() {
        return tempo;
    }

    void setInstrument(InstrumentType instrument) {
        this->instrument = instrument;
    }

    InstrumentType getInstrument() {
        return this->instrument;
    }
};

}
