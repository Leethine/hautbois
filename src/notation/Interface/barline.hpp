#include "../onebar.hpp"
#include <numeric>
#include <regex>

namespace hautbois {

using BarPtrArray=std::vector<std::unique_ptr<OneBar>>;

using TokenString=std::string;

class BarLine : private OneBar {
    mutable BarPtrArray barline;
    
    bool checkBarComplete() const {
        Duration d;
        for (auto it = begin(notes); it != end(notes); it++) {
            d = d + (*it)->getDuration();
        }
        if (d == meter) { return true; }
        else { return false; }
    }

    NoteType checkType(TokenString& token) const {}
    
    bool checkRestNoteFormatting(TokenString& token) const {}

    bool checkSingleNoteFormatting(TokenString& token) const {}
    
    bool checkGroupNoteFormatting(TokenString& token) const {}

    bool checkFormatting(NoteType type, TokenString& token) const {}

    void strAddSingleNote(TokenString& name, TokenString& duration) {}

    void strAddSingleNote(TokenString& name, TokenString& duration,
                       TokenString& property) {}
    
    void strAddSingleNote(TokenString& name, TokenString& duration,
                       TokenString& property, TokenString& ornament) {}
    
    void strAddRestNote(TokenString& duration) {}
    
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