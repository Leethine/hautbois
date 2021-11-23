#pragma once
#include "facade_defs.hpp"
#include <memory>
#include <cassert>

namespace hautbois {

class OneBarFacade : protected OneBar, protected BarParserUtl {
protected:
    
    void strAddProperty(const TokenString& property_token, 
                        InstrumentType instrument) {
        assert(!property_token.empty());
        assert(isPropertyValid(property_token));
        
        TokenString token = deBracket(property_token);
        auto note_property = makeProperty(instrument);

        // first split into an array of key-val pairs
        TokenVector token_vec = splitToken(token, ";");
        if ( token_vec.size() == 0 ) {
            // second split of key-val pair
            // if only one key-val pair was defined
            TokenVector pair = splitToken(token, ":");
            assert(pair.size() == 2);
            note_property->addEntry(pair[0],pair[1]);
        }
        else {
            for (auto item : token_vec) {
                // second split of each key-val pair
                TokenVector pair = splitToken(item, ":");
                assert(pair.size() == 2);
                note_property->addEntry(pair[0],pair[1]);
            }
        }

        assert(!notes.empty());
        AnyNote& last_note = getLastNote();
        last_note.property = NoteProperty{*note_property};
    }
    
    void strAddOrnament(const TokenString& ornament_token) {
        assert(!ornament_token.empty());
        assert(isOrnamentValid(ornament_token));
        TokenString token = deBracket(ornament_token);
        NoteOrnament note_ornament;
        // check if value is defined
        TokenVector token_vec = splitToken(token, ":");
        if ( token_vec.size() == 2 ) {
            // if size is 2 ==> value is defined
            note_ornament.addOrnament(rmAngleBracket(token_vec[0]), 
                                      rmAngleBracket(token_vec[1]));
        }
        else {
            note_ornament.addOrnament(rmAngleBracket(token), "");
        }
        
        AnyNote& last_note = getLastNote();
        last_note.ornament = NoteOrnament(note_ornament);
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

    void tokenAddSingleNote(const TokenString& token_ns, 
                            InstrumentType instrument) {
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
            // maybe it's ornament rather than property
            if ( token_vec[2].front() == '<' && token_vec[2].back() == '>' ) {
                strAddOrnament(token_vec[2]);
            }
            else {
                strAddProperty(token_vec[2], instrument);
            }
            break;
        case 4:
            strAddSingleNote(token_vec[0], token_vec[1]);
            strAddProperty(token_vec[2], instrument);
            strAddOrnament(token_vec[3]);
            break;
        default:
            break;
        }
    }

    void tokenAddGroupNote(const TokenString& token_ns,
                           InstrumentType instrument) {
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

            // maybe it's ornament rather than property
            if ( token_vec[2].front() == '<' && token_vec[2].back() == '>' ) {
                token_ornament = token_vec[2];
            }
            else {
                token_property = "[" + token_vec[2] + "]";
            }
        }
        else {
            names.push_back(token_vec[0]);
            duration_first = token_vec[1];
            durations.push_back(duration_first);
            token_property = "[" + token_vec[2] + "]";
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
        if ( !token_property.empty() )
            strAddProperty(token_property, instrument);
        if ( !token_ornament.empty() )
            strAddOrnament(token_ornament);
    }
    
public:
    OneBarFacade() : OneBar ()
    {
    }

    explicit OneBarFacade (const NoteName& scale, Beat num, Beat denom) :
    OneBar(scale, num, denom)
    {
    }

    explicit OneBarFacade (NotationSystemName& name, 
    NoteName& scale, Beat num, Beat denom) : 
    OneBar(name, scale, num, denom) 
    {
    }

    bool checkBarComplete() const {
        Duration d;
        for (auto it = begin(notes); it != end(notes); it++) {
            d = d + (*it)->getDuration();
        }
        if (d == meter) { return true; }
        else { return false; }
    }
    
    void addNote(const TokenString& token, InstrumentType instrument) {
        TokenString token_ns = rmSpace(token);
        try {
            NoteType type = checkFormatting(token_ns);
            assert(type != NoteType::TYPE_INVALID);
            switch (type)
            {
            case NoteType::RestNote:
                tokenAddRestNote(token_ns);
                break;
            case NoteType::SingleNote:
                tokenAddSingleNote(token_ns, instrument);
                break;
            case NoteType::GroupNote:
                tokenAddGroupNote(token_ns, instrument);
                break;
            default:
                break;
            }
        } catch (const std::exception &e) {
            std::cout << "Error in addNote(): " << e.what() << "\n";
        }
    }

    void addNote(const TokenString& token) {
        addNote(token, InstrumentType::NONE);
    }

    friend std::ostream& operator<<(std::ostream& o, OneBarFacade& b) {
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
