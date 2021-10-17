#include "../onebar.hpp"
#include <regex>

namespace hautbois {

using BarPtrArray=std::vector<std::unique_ptr<OneBar>>;

using TokenString=std::string;

class OneBarFacade : private OneBar {
    mutable BarPtrArray barline;

    bool checkBarComplete() const {}

    NoteType checkType(TokenString& token) const {}
    
    bool checkRestNoteFormatting(TokenString& token) const {}
    bool checkSingleNoteFormatting(TokenString& token) const {}
    bool checkGroupNoteFormatting(TokenString& token) const {}

    bool checkFormatting(NoteType type, TokenString& token) const {}

    void strAddSingleNote(TokenString& name) {}
    void strAddSingleNote(TokenString& name, TokenString& duration) {}
    void strAddSingleNote(TokenString& name, TokenString& duration,
                       TokenString& property) {}
    void strAddSingleNote(TokenString& name, TokenString& duration,
                       TokenString& property, TokenString& ornament) {}
    void strAddRestNote(TokenString& duration) {}
    
    void strAddGroupNote(TokenString& token) {}

    public:
    OneBarFacade() : OneBar ()
    {}
    
    explicit OneBarFacade (NotationSystemName& name, 
    NoteName& scale, Beat num, Beat denom) : 
    OneBar(name, scale, num, denom) 
    {}

    void addNote(TokenString& token) {}

    OneBar& getNthBar() const {}
    void printBarLine() {}
    void printWholeBar() const {}

};

}