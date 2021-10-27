#pragma once
#include "interface_defs.hpp"
#include <cassert>

namespace hautbois {

class OneBarInterface : protected OneBar, protected ParserUtl {
protected:
    InstrumentType instrument;

    void strAddProperty(const TokenString& property) {
        
    }
    
    void strAddOrnament(const TokenString& ornament) {
        
    }

    void strAddRestNote(const TokenString& duration) {
        OneBar::appendRestNote(readDurationFromStr(duration));
    }

    void strAddSingleNote(TokenString& name, TokenString& duration) {
        OneBar::appendSingleNote(name, readDurationFromStr(duration));
    }
    
    void strAddGroupNote(TokenStrVector& names, TokenStrVector& durations) {
        OneBar::appendGroupNote(names, readGroupDurationFromStr(durations));
    }

    void strAddGroupNote(TokenStrVector& names, TokenString& duration) {
        OneBar::appendGroupNote(names, readDurationFromStr(duration));
    }

    void tokenAddRestNote(const TokenString& token_ns) {
        TokenVector token_vec = splitToken(deBracket(token_ns), ",");
        assert(token_vec.size() == 2);
        if(token_vec.size() != 2) {
            throw std::domain_error("Unable to parse " + token_ns);
        }
        
        strAddRestNote(token_vec[1]);
    }

    void tokenAddSingleNote(const TokenString& token_ns) {
        TokenVector token_vec = splitToken(deBracket(token_ns), ",");
        // pre-cheking
        assert(token_vec.size() >= 2 && token_vec.size() <= 4);
        if(token_vec.size() > 4 || token_vec.size() < 2) {
            throw std::domain_error("Unable to parse " + token_ns);
        }

        switch (token_vec.size())
        {
        case 2:
            strAddSingleNote(token_vec[0], token_vec[1]);
            break;
        case 3:
            strAddSingleNote(token_vec[0], token_vec[1]);
            strAddProperty(token_vec[2]);
            break;
        case 4:
            strAddSingleNote(token_vec[0], token_vec[1]);
            strAddProperty(token_vec[2]);
            strAddOrnament(token_vec[3]);
            break;
        default:
            break;
        }
    }

    void tokenAddGroupNote(const TokenString& token_ns) {
        // remove curley brackets {()()...()} ==> ()()...()
        TokenString token_ns_no_bracket = deBracket(token_ns);
        // remove two round brackets ()()...() ==> )()...(
        token_ns_no_bracket = deBracket(token_ns_no_bracket);
        // then split by ")"
        TokenVector singlenotes = splitToken(token_ns_no_bracket, ")");
        assert(singlenotes.size() >= 2);
        if (singlenotes.size() < 2) {
            throw std::domain_error("Unable to parse " + token_ns
                                    + ". Too few notes in the chord.");
        }
        
        // clean up remaining bracket 
        for (int i = 0; i < singlenotes.size(); ++i) {
            singlenotes[i] = rmBracket(singlenotes[i]);
        } // now we should have pure note info packed in the vector

        // declare container vectors for group names and durations
        GroupName names;
        TokenStrVector durations;

        // read the first note - prechecking
        TokenString duration_first;
        TokenVector token_vec = splitToken(singlenotes[0], ",");
        assert(token_vec.size() >= 2 && token_vec.size() <= 4);
        if (token_vec.size() < 2 || token_vec.size() > 4) {
            throw std::domain_error("Unable to parse " + token_ns
                                    + ". First note failed to parse.");
        }

        TokenString token_property;
        TokenString token_ornament;

        // read the first note
        if (token_vec.size() == 2) {
            names.push_back(token_vec[0]);
            duration_first = token_vec[1];
            durations.push_back(duration_first);
        }
        else if (token_vec.size() == 3) {
            names.push_back(token_vec[0]);
            duration_first = token_vec[1];
            durations.push_back(duration_first);
            token_property = token_vec[2];
        }
        else {
            names.push_back(token_vec[0]);
            duration_first = token_vec[1];
            durations.push_back(duration_first);
            token_property = token_vec[2];
            token_ornament = token_vec[3];
        }
        
        // read the following notes
        for (int i = 1; i < singlenotes.size(); ++i) {
            // token_vec.clear(); // no need
            token_vec = splitToken(singlenotes[i], ",");
            // prechecking
            assert(token_vec.size() == 1 || token_vec.size() == 2);
            if (token_vec.size() != 1 && token_vec.size() != 2) {
                throw std::domain_error("Unable to parse " + token_ns
                                        + ". Notes failed to parse.");
            }
            
            if ( token_vec.size() == 1 ) {
                names.push_back(token_vec[0]);
                durations.push_back(duration_first);
            }
            else {
                names.push_back(token_vec[0]);
                durations.push_back(token_vec[1]);
            }
        }

        // put the contents from the container to barline
        strAddGroupNote(names, durations);
        strAddProperty(token_property);
        strAddOrnament(token_ornament);
    }
    
public:

    OneBarInterface() : OneBar ()
    {
        this->instrument = InstrumentType::NONE;
    }
    
    explicit OneBarInterface (NotationSystemName& name, 
    NoteName& scale, Beat num, Beat denom) : 
    OneBar(name, scale, num, denom) 
    {
        this->instrument = InstrumentType::NONE;
    }

    bool checkBarComplete() const {
        Duration d;
        for (auto it = begin(notes); it != end(notes); it++) {
            d = d + (*it)->getDuration();
        }
        if (d == meter) { return true; }
        else { return false; }
    }
    
    void addNote(const TokenString& token) {
        TokenString token_ns = rmSpace(token);
        try {
            NoteType type = checkType(token_ns);
            checkFormatting(type, token_ns);
            switch (type)
            {
            case NoteType::RestNote:
                tokenAddRestNote(token_ns);
                break;
            case NoteType::SingleNote:
                tokenAddSingleNote(token_ns);
                break;
            case NoteType::GroupNote:
                tokenAddGroupNote(token_ns);
                break;
            default:
                break;
            }
        } catch (const std::exception &e) {
            std::cout << "Error in addNote(): " << e.what() << "\n";
        }
    }

    friend std::ostream& operator<<(std::ostream& o, OneBarInterface& b) {
        o << b.OneBar::printBarLine();
        return o;
    }

    AnyNote& getNthNote(size_t n) {
        return OneBar::getNthNote(n);
    }

    const std::string printNthNote(size_t n) {
        return OneBar::printNthNote(n);
    }

};

}