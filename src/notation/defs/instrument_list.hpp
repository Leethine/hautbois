#pragma once
#include "base_types.hpp"
#include <map>
namespace hautbois 
{
using InstrumentName=std::string;

enum class InstrumentType
{
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
    VIOLA_DI_BRACCIO,
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

using InstrumentNameTypeTable=std::map<InstrumentName,InstrumentType>;
InstrumentNameTypeTable instrument_name_table_it {
    {"arpa", InstrumentType::ARPA},
    {"basso_continuoto", InstrumentType::BASSO_CONTINUOTO},
    {"chitarra", InstrumentType::CHITARRA},
    {"clavicembalo", InstrumentType::CLAVICEMBALO},
    {"clavicordo", InstrumentType::CLAVICORDO},
    {"cornetto", InstrumentType::CORNETTO},
    {"corno", InstrumentType::CORNO},
    {"fagotto", InstrumentType::FAGOTTO},
    {"flauto_dolce", InstrumentType::FLAUTO_DOLCE},
    {"flauto_traverso", InstrumentType::FLAUTO_TRAVERSO},
    {"lira", InstrumentType::LIRA},
    {"lutio", InstrumentType::LIUTO},
    {"mandolino", InstrumentType::MANDOLINO},
    {"oboe", InstrumentType::OBOE},
    {"oboe_damore",InstrumentType::OBOE_DAMORE},
    {"organo", InstrumentType::ORGANO},
    {"viola", InstrumentType::VIOLA},
    {"viola_da_gamba", InstrumentType::VIOLA_DA_GAMBA},
    {"viola_damore", InstrumentType::VIOLA_DAMORE},
    {"viola_di_braccio", InstrumentType::VIOLA_DI_BRACCIO},
    {"viole", InstrumentType::VIOLE},
    {"violino", InstrumentType::VIOLINO},
    {"violoncello", InstrumentType::VIOLONCELLO},
    {"virginale", InstrumentType::VIRGINALE},
    {"timpani", InstrumentType::TIMPANI},
    {"tiorba", InstrumentType::TIORBA},
    {"tromba", InstrumentType::TROMBA},
    {"tromba_di_tirarsi", InstrumentType::TROMBA_DI_TIRARSI},
    {"trombone", InstrumentType::TROMBONE},
    
};

}
