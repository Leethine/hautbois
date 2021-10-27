#pragma once
#include "AA1_property_headers.hpp"

namespace hautbois 
{
namespace property
{

//TODO how to automatically construct the struct into unique_ptr ?

template<typename PropertyT>
NoteProperty * newPropertyPtr() {
    return new PropertyT();
}

std::map<InstrumentType,NoteProperty*> instrument_table {
    //{ InstrumentType::ARPA, },
    //{ InstrumentType::BASSO_CONTINUOTO, },
    //{ InstrumentType::CHITARRA, },
    { InstrumentType::CLAVICEMBALO, newPropertyPtr<HarpsichordNoteProperty>() },
    { InstrumentType::CLAVICORDO, newPropertyPtr<ClavichordNoteProperty>() },
    //{ InstrumentType::CORNETTO, },
    //{ InstrumentType::CORNO, },
    //{ InstrumentType::FAGOTTO, },
    //{ InstrumentType::FLAUTO_DOLCE, },
    //{ InstrumentType::FLAUTO_TRAVERSO, },
    { InstrumentType::LIUTO, newPropertyPtr<LuthNoteProperty>() },
    //{ InstrumentType::MANDOLINO, },
    //{ InstrumentType::OBOE, },
    //{ InstrumentType::OBOE_DAMORE, },
    { InstrumentType::ORGANO, newPropertyPtr<OrganNoteProperty>() },
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

NoteProperty * getPropertyPtr(InstrumentType instrument) {
    return instrument_table.at(instrument);
}

}
}
