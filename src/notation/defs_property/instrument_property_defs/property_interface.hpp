#pragma once
#include "property_defs.hpp"
#include "instrument_properties.hpp"
#include <memory>

namespace hautbois 
{

// when adding new instrument, add here and instrument_properties.hpp
std::unique_ptr<NoteProperty> makeProperty(InstrumentType instrument) {
    std::unique_ptr<NoteProperty> ptr;
    switch (instrument)
    {
    case InstrumentType::CLAVICEMBALO :
        ptr = std::unique_ptr<NoteProperty> {new HarpsichordNoteProperty()};
        return ptr;
        break;
    case InstrumentType::LIUTO :
        ptr = std::unique_ptr<NoteProperty> {new LuthNoteProperty()};
        return ptr;
        break;
    default:
        ptr = std::unique_ptr<NoteProperty> {new SineWaveNoteProperty()};
        return ptr;
        break;
    }
}

}