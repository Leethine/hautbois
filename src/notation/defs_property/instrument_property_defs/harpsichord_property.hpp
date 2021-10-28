#pragma once
#include "AA0_property_defs.hpp"

namespace hautbois 
{
using BoolValue=bool;

struct HarpsichordNoteProperty : NoteProperty {
    boost::optional<bool> delay;

    HarpsichordNoteProperty() {
        delay = boost::none;
    }
};

}
