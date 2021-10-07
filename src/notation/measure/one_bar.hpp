#pragma once
#include "../defs.hpp"
#include "../note.hpp"
#include "notation_sys.hpp"
#include <memory>

namespace hautbois {

using std::vector;
using std::unique_ptr;

class OneBar {
protected:
    const NotationSystemType sys;
    vector<unique_ptr<AnyNote>> notes;

    NotationSystemType notationName2Type(NotationSystemName name) const {
        try { return notation_system_table.at(name); }
        catch (std::out_of_range& e) {
            std::cout << "Could not identify notation system: " 
                      << name << " is invalid name." << "\n";
            exit(EXIT_FAILURE);
        }
    }
    
public:
    OneBar()=default;
    ~OneBar()=default;
    
    OneBar() :
    sys { NotationSystemType::SCIENTIFIC }
    {}

    explicit OneBar(NotationSystemName name) :
    sys { notationName2Type(name) }
    {}

    // TODO add methods
    void addSingleNote() {};
    void addRestNote() {};
    void addChord() {};
    void deleteFirstNote() {};
    void deleteLastNote() {};
    void deleteNthNote(int n) {};
};

}