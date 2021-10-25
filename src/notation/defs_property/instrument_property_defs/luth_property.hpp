#pragma once
#include "property_defs.hpp"

namespace hautbois 
{

struct LuthNoteProperty : NoteProperty {
    StringPropertyValue stringnbr;
    ForcePropertyValue force;
};

}
