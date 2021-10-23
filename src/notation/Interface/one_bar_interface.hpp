#pragma once
#include "interface_defs.hpp"
#include <cassert>

namespace hautbois {

class OneBarInterface : protected OneBar, protected ParserUtl {
    protected:

    void strAddProperty(const TokenString& property) {

    }
    
    void strAddOrnament(const TokenString& ornament) {
        
    }

    void strAddRestNote(const TokenString& duration) {
        appendRestNote(readDurationFromStr(duration));
    }

    void strAddSingleNote(TokenString& name, TokenString& duration) {
        appendSingleNote(name, readDurationFromStr(duration));
    }


    //MAYBE delete
    void strAddSingleNote(TokenString& name, TokenString& duration,
                          TokenString& property) {
        appendSingleNote(name, readDurationFromStr(duration));
        // TODO properties
    }
    
    //MAYBE delete
    void strAddSingleNote(TokenString& name, TokenString& duration,
                          TokenString& property, TokenString& ornament) {
        appendSingleNote(name, readDurationFromStr(duration));
        // TODO properties
        // TODO ornaments
    }
    
    void strAddGroupNote(TokenStrVector& names, TokenStrVector& durations) {
        appendGroupNote(names, readGroupDurationFromStr(durations));
    }

    void strAddGroupNote(TokenStrVector& names, TokenString& duration) {
        appendGroupNote(names, readDurationFromStr(duration));
    }

    //MAYBE delete
    void strAddGroupNote(TokenStrVector& names, TokenString& duration,
                         TokenString& property) {
        appendGroupNote(names, readDurationFromStr(duration));
        // TODO properties
    }

    //MAYBE delete
    void strAddGroupNote(TokenStrVector& names, TokenStrVector& durations, 
                         TokenString& property) {
        appendGroupNote(names, readGroupDurationFromStr(durations));
        // TODO properties
    }

    //MAYBE delete
    void strAddGroupNote(TokenStrVector& names, TokenString& duration,
                         TokenString& property, TokenString& ornament) {
        appendGroupNote(names, readDurationFromStr(duration));
        // TODO properties
        // TODO ornaments
    }
    
    //MAYBE delete
    void strAddGroupNote(TokenStrVector& names, TokenStrVector& durations, 
                         TokenString& property, TokenString& ornament) {
        appendGroupNote(names, readGroupDurationFromStr(durations));
        // TODO properties
        // TODO ornaments
    }

    void tokenAddRestNote(const TokenString& token_ns) {
        TokenVector token_vec = splitToken(deBracket(token_ns), ",");
        assert(token_vec.size() == 2);
        strAddRestNote(token_vec[1]);
    }

    void tokenAddSingleNote(const TokenString& token_ns) {
        TokenVector token_vec = splitToken(deBracket(token_ns), ",");
        assert(token_vec.size() <= 4 || token_vec.size() >= 2);
        switch (token_vec.size())
        {
        case 2:
            strAddSingleNote(token_vec[0], token_vec[1]);
            break;
        case 3:
            strAddSingleNote(token_vec[0], token_vec[1], token_vec[2]);
            break;
        case 4:
            strAddSingleNote(token_vec[0], token_vec[1], 
                             token_vec[2], token_vec[3]);
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
        
        // clean up remaining bracket 
        for (int i = 0; i < singlenotes.size(); ++i) {
            singlenotes[i] = rmBracket(singlenotes[i]);
        } // now we should have pure note info packed in the vector

        // declare container vectors for group names and durations
        GroupName names;
        TokenStrVector durations;

        // read the first note
        TokenString duration_first;
        TokenVector token_vec = splitToken(singlenotes[0], ",");
        assert(token_vec.size() >= 2 || token_vec.size() <= 4);

        if (token_vec.size() == 2) {
            names.push_back(token_vec[0]);
            duration_first = token_vec[1];
            durations.push_back(duration_first);
        }
        else if (token_vec.size() == 3) {
            names.push_back(token_vec[0]);
            duration_first = token_vec[1];
            durations.push_back(duration_first);
            //TODO parse properties
        }
        else {
            names.push_back(token_vec[0]);
            duration_first = token_vec[1];
            durations.push_back(duration_first);
            //TODO parse properties
            //TODO parse ornaments
        }
        
        // read the following notes
        for (int i = 1; i < singlenotes.size(); ++i) {
            // token_vec.clear(); // no need
            token_vec = splitToken(singlenotes[i], ",");
            assert(token_vec.size() == 1 || token_vec.size() == 2);
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
        // TODO properties
        // TODO ornaments
    }
    
public:
    OneBarInterface() : OneBar ()
    {}
    
    explicit OneBarInterface (NotationSystemName& name, 
    NoteName& scale, Beat num, Beat denom) : 
    OneBar(name, scale, num, denom) 
    {}

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

    }

    void printBarLine() {}
    void printWholeBar() const {}
    

};

}