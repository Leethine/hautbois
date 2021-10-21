#pragma once
#include "interface_defs.hpp"

namespace hautbois {

class BarLine : private OneBar, private ParserUtl {
    mutable BarPtrArray barline;

    bool checkBarComplete() const {
        Duration d;
        for (auto it = begin(notes); it != end(notes); it++) {
            d = d + (*it)->getDuration();
        }
        if (d == meter) { return true; }
        else { return false; }
    }
    
    void strAddSingleNote(TokenString& name, TokenString& duration) {}

    void strAddRestNote(const TokenString& duration) {
        //appendRestNote();
    }

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
    BarLine() : OneBar ()
    {}
    
    explicit BarLine (NotationSystemName& name, 
    NoteName& scale, Beat num, Beat denom) : 
    OneBar(name, scale, num, denom) 
    {}

    void addNote(TokenString& token) {}

    OneBar& getNthBar() const {}
    void printBarLine() {}
    void printWholeBar() const {}
    

};

}