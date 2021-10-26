#pragma once
#include "../property.hpp"

namespace hautbois 
{
namespace property
{

/*
template<typename PropertyT>
PropertyPtr newPropertyPtr() {
    PropertyPtr ptr { new PropertyT(); }
    return ptr;
}
*/

template<typename PropertyT>
NoteProperty * newPropertyPtr() {
    return new PropertyT();
}

std::map<InstrumentType,NoteProperty*> instrument_table {
    //{ InstrumentType::ARPA, },
    //{ InstrumentType::BASSO_CONTINUOTO, },
    //{ InstrumentType::CHITARRA, },
    //{ InstrumentType::CLAVICEMBALO, },
    { InstrumentType::CLAVICORDO, newPropertyPtr<ClavichordNoteProperty>() },
    //{ InstrumentType::CORNETTO, },
    //{ InstrumentType::CORNO, },
    //{ InstrumentType::FAGOTTO, },
    //{ InstrumentType::FLAUTO_DOLCE, },
    //{ InstrumentType::FLAUTO_TRAVERSO, },
    //{ InstrumentType::LIUTO, },
    //{ InstrumentType::MANDOLINO, },
    //{ InstrumentType::OBOE, },
    //{ InstrumentType::OBOE_DAMORE, },
    //{ InstrumentType::ORGANO, },
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

/*
PropertyPtr getPropertyPtr(InstrumentType instrument) {
    PropertyPtr ptr { &instrument_table.at(instrument) };
    return ptr;
}*/

}
}
