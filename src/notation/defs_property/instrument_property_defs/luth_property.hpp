#pragma once
#include "AA0_property_defs.hpp"

namespace hautbois 
{

using StringNbrValue=int;
using ForceValue=int;
using BoolValue=bool;

struct LuthNoteProperty : NoteProperty {
    boost::optional<StringNbrValue> stringnbr;
    boost::optional<ForceValue> force;
    boost::optional<bool> delay;

    LuthNoteProperty() {
        stringnbr = boost::none;
        force = boost::none;
        delay = boost::none;
    }
};

}
