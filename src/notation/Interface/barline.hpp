#pragma once
#include "interface_defs.hpp"

namespace hautbois {

class OneBarInterface : protected OneBar, protected ParserUtl {
    mutable BarPtrArray barline;

    bool checkBarComplete() const {
        Duration d;
        for (auto it = begin(notes); it != end(notes); it++) {
            d = d + (*it)->getDuration();
        }
        if (d == meter) { return true; }
        else { return false; }
    }

    // if current bar is full, clear current bar and put in barline
    // otherwise, do nothing
    void packCurrentBar() {
        if ( checkBarComplete() ) {
            barline.emplace_back(  );
            this->clearBar();
        }
    }
    
    void strAddRestNote(const TokenString& duration) {
        appendRestNote(readDurationFromStr(duration));
    }

    void strAddSingleNote(TokenString& name, TokenString& duration) {}

    void strAddSingleNote(TokenString& name, TokenString& duration,
                          TokenString& property) {}
    
    void strAddSingleNote(TokenString& name, TokenString& duration,
                          TokenString& property, TokenString& ornament) {}
    
    void strAddGroupNote(GroupName& names, GroupDuration& durations) {}
    
    void strAddGroupNote(GroupName& names, GroupDuration& durations, 
                         TokenString& property) {}

    void tokenAddRestNote(TokenString& token) {}
    
    void tokenAddSingleNote(TokenString& token) {}
    
    void tokenAddGroupNote(TokenString& token) {}
    
public:
    OneBarInterface() : OneBar ()
    {}
    
    explicit OneBarInterface (NotationSystemName& name, 
    NoteName& scale, Beat num, Beat denom) : 
    OneBar(name, scale, num, denom) 
    {}

    void addNote(TokenString& token) {}

    OneBar& getNthBar() const {}
    void printBarLine() {}
    void printWholeBar() const {}
    
};

}