#pragma once
#include "base_types.hpp"
namespace hautbois 
{
    using InstrumentName=std::string;

    enum class InstrumentType {
        ARPA,
        BASSO_CONTINUOTO,
        CHITARRA,
        CLAVICEMBALO,
        CLAVICORDO,
        CORNETTO,
        CORNO,
        FAGOTTO,
        FLAUTO_DOLCE,
        FLAUTO_TRAVERSO,
        LIRA,
        LIUTO,
        MANDOLINO,
        OBOE,
        OBOE_DAMORE,
        ORGANO,
        VIOLA,
        VIOLA_DA_GAMBA,
        VIOLA_DAMORE,
        VIOLE,
        VIOLINO,
        VIOLONCELLO,
        VIRGINALE,
        TIMPANI,
        TIORBA,
        TROMBA,
        TROMBA_DI_TIRARSI,
        TROMBONE,

    // Abstract field
        NONE,
        SINWAVE,

    };
}
