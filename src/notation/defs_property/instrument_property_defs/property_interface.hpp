#pragma once
#include "property_defs.hpp"
#include "instrument_properties.hpp"

namespace hautbois 
{

template<typename PropertyT>
NoteProperty * newPropertyPtr() {
    return new PropertyT();
}

// when adding new instrument, add here and instrument_properties.hpp
const std::map<InstrumentType,NoteProperty*> property_construction_table {
    //{ InstrumentType::ARPA, },
    //{ InstrumentType::BASSO_CONTINUOTO, },
    //{ InstrumentType::CHITARRA, },
    { InstrumentType::CLAVICEMBALO, newPropertyPtr<HarpsichordNoteProperty>() },
    //{ InstrumentType::CLAVICORDO, newPropertyPtr<ClavichordNoteProperty>() },
    //{ InstrumentType::CORNETTO, },
    //{ InstrumentType::CORNO, },
    //{ InstrumentType::FAGOTTO, },
    //{ InstrumentType::FLAUTO_DOLCE, },
    //{ InstrumentType::FLAUTO_TRAVERSO, },
    { InstrumentType::LIUTO, newPropertyPtr<LuthNoteProperty>() },
    //{ InstrumentType::MANDOLINO, },
    //{ InstrumentType::OBOE, },
    //{ InstrumentType::OBOE_DAMORE, },
    //{ InstrumentType::ORGANO, newPropertyPtr<OrganNoteProperty>() },
    //{ InstrumentType::VIOLA, },
    //{ InstrumentType::VIOLA_DA_GAMBA, },
    //{ InstrumentType::VIOLA_DAMORE, },
    //{ InstrumentType::VIOLINO, },
    //{ InstrumentType::VIOLONCELLO, },
    //{ InstrumentType::TIMPANI, },
    //{ InstrumentType::TIORBA, },
    //{ InstrumentType::TROMBA, },
    //{ InstrumentType::TROMBONE, },
};

}