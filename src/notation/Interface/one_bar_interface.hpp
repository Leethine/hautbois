#pragma once
#include "interface_defs.hpp"

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

    void strAddSingleNote(TokenString& name, TokenString& duration,
                          TokenString& property) {
        appendSingleNote(name, readDurationFromStr(duration));
        // TODO properties
    }
    
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

    void strAddGroupNote(TokenStrVector& names, TokenString& duration,
                         TokenString& property) {
        appendGroupNote(names, readDurationFromStr(duration));
        // TODO properties
    }
    
    void strAddGroupNote(TokenStrVector& names, TokenStrVector& durations, 
                         TokenString& property) {
        appendGroupNote(names, readGroupDurationFromStr(durations));
        // TODO properties
    }

    void tokenAddRestNote(TokenString& token) {}

    void tokenAddSingleNote(TokenString& token) {}

    void tokenAddGroupNote(TokenString& token) {}

    void strAddProperty() {}

    void strAddOrnament() {}
    
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
    
    void addNote(TokenString& token) {}

    OneBar& getNthBar() const {}
    void printBarLine() {}
    void printWholeBar() const {}
    
};

}