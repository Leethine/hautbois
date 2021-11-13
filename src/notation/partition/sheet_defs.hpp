#pragma once
#include "../defs/defs.hpp"
#include "../note/any_note.hpp"
#include "../barline_interface/one_bar_interface.hpp"
#include "tempo.hpp"

namespace hautbois 
{

using Clef=char;
using ClefAt=unsigned int;
const Clef G_CLEF { 'G' };
const Clef C_CLEF { 'C' };
const Clef F_CLEF { 'F' };

namespace stave
{
const int LINE1 { 1 };
const int LINE2 { 2 };
const int LINE3 { 3 };
const int LINE4 { 4 };
const int LINE5 { 5 };
}

class myPairClef : public std::pair<Clef,ClefAt> {
    public:
    myPairClef(Clef clef, UIntValue at) {
        first = clef;
        second = at;
    }

    Clef clef() {
        return this->first;
    }
    ClefAt clef_at() {
        return this->second;
    }
};


}
