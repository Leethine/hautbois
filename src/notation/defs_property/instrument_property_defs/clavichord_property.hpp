#pragma once
#include "property_defs.hpp"

namespace hautbois 
{

struct ClavichordNoteProperty : NoteProperty {
    ForcePropertyValue force;
    ClavichordNoteProperty() : NoteProperty(InstrumentType::CLAVICORDO)
    {};
};

}
