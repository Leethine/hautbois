#pragma once
#include "AA1_property_headers.hpp"

namespace hautbois 
{

template<typename PropertyT>
NoteProperty * newPropertyPtr() {
    return new PropertyT();
}

// when adding new instrument, add here and in the setProperty() func
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

NoteProperty * getPropertyPtr(InstrumentType instrument,
        const std::map<InstrumentType,NoteProperty*>& dict) {
    return dict.at(instrument);
}

// when adding new key, add here
template<typename PropertyT, typename ValueT>
void propertySetterGeneric(PropertyT * ptr, std::string ukey, ValueT val) {
    if      ( ukey == "WAITS" ) {
        ptr->waits = Duration(val);
    }
    else if ( ukey == "LASTS" ) {
        ptr->lasts = Duration(val);
    }
    else if ( ukey == "DELAY" ) {
        ptr->delay = val;
    }
    else if ( ukey == "STRINGNBR" ) {
        ptr->stringnbr = val;
    }
    else if ( ukey == "FORCE" ) {
        ptr->force = val;
    }
    else {
        throw std::domain_error("Not yet implemented.");
    }
}

// when adding new instrument, add here and in the map
template<typename ValueT>
void setProperty(InstrumentType type, 
                 NoteProperty * ptr, std::string ukey, ValueT val) {
    switch (type)
    {
    case InstrumentType::CLAVICEMBALO:
        propertySetterGeneric<HarpsichordNoteProperty,ValueT>(ptr,ukey,val);
        break;
    case InstrumentType::LIUTO:
        propertySetterGeneric<LuthNoteProperty,ValueT>(ptr,ukey,val);
        break;
    default:
        throw std::domain_error("Not yet implemented: unknow instrument.");
        break;
    }
}

}
