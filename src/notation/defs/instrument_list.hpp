#pragma once
#include "base_types.hpp"
namespace hautbois 
{
    using InstrumentName=std::string;

    namespace InstrumentList
    {

    enum class Renaissance{
        //TODO
        CHITARRA,
        CORNETTO,
        FLAUTO_DOLCE,
        FLAUTO_TRAVERSO,
        LIRA,
        LIUTO,
        ORGANO,
        TROMBA,
        TROMBA_DI_TIRARSI,
        VIOLE,
        VIRGINALE
    };

    enum class Baroque {
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
        LIUTO,
        MANDOLINO,
        OBOE,
        OBOE_DAMORE,
        ORGANO,
        VIOLA,
        VIOLA_DA_GAMBA,
        VIOLA_DAMORE,
        VIOLINO,
        VIOLONCELLO,
        TIMPANI,
        TIORBA,
        TROMBA,
        TROMBONE
    };
    
    enum class Classical {
        //TODO
        NA
    };

    }
}
