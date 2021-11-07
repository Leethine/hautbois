#pragma once
#include "property_defs.hpp"
#include "instrument_properties.hpp"
#include <memory>

namespace hautbois 
{
/*
template<typename PropertyT>
NoteProperty * newPropertyPtr() {
    return dynamic_cast<NoteProperty*> (new PropertyT());
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
    { InstrumentType::SINWAVE, newPropertyPtr<SineWaveNoteProperty>()}
};

NoteProperty * makeProperty(InstrumentType instrument) {
    try {
        return property_construction_table.at(instrument);
    }
    catch(std::exception& e) {
        std::cout << "The specified instrument has not been implemented yet."
                  << "\n" << e.what() << "\n";
        exit(EXIT_FAILURE);
    }
}
*/
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