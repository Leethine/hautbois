#pragma once
#include <map>
#include <string>

namespace hautbois 
{

enum class Tempo {
    PRESTISSIMO,
    PRESTO,
    ALLEGRISSIMO,
    ALLEGRO_VIVANCE,
    VIVACISSIMO,
    VIVANCE,
    ALLEGRO_ASSAI,
    ALLEGRO_MOLTO,
    ALLEGRO,
    ALLEGRO_MA_NON_TROPPO,
    ALLEGRO_NON_TROPPO,
    ALLEGRO_MODERATO,
    ALLEGRETTO,
    MODERATO,
    MARCIA_MODERATO,
    ADANTINO,
    ANDANTE,
    ADAGIETTO,
    ADAGIO,
    LARGHETTO,
    LENTO,
    LARGO,
    GRAVE,
    ADAGISSIMO,
    LENTISSIMO,
};

struct Range
{
    int min;
    int max;
};

using TempoBpmRangeMap=std::map<Tempo,Range>;

const TempoBpmRangeMap TEMPO_BPM_TABLE {
    { Tempo::PRESTISSIMO, {0,0} },
    { Tempo::PRESTO, {0,0} },
    { Tempo::ALLEGRISSIMO, {0,0} },
    { Tempo::ALLEGRO_VIVANCE, {0,0} },
    { Tempo::VIVACISSIMO, {0,0} },
    { Tempo::VIVANCE, {0,0} },
    { Tempo::ALLEGRO_ASSAI, {0,0} },
    { Tempo::ALLEGRO_MOLTO, {0,0} },
    { Tempo::ALLEGRO, {0,0} },
    { Tempo::ALLEGRO_MA_NON_TROPPO, {0,0} },
    { Tempo::ALLEGRO_NON_TROPPO, {0,0} },
    { Tempo::ALLEGRO_MODERATO, {0,0} },
    { Tempo::ALLEGRETTO, {0,0} },
    { Tempo::MODERATO, {0,0} },
    { Tempo::MARCIA_MODERATO, {0,0} },
    { Tempo::ADANTINO, {0,0} },
    { Tempo::ANDANTE, {0,0} },
    { Tempo::ADAGIETTO, {0,0} },
    { Tempo::ADAGIO, {0,0} },
    { Tempo::LARGHETTO, {0,0} },
    { Tempo::LENTO, {0,0} },
    { Tempo::LARGO, {0,0} },
    { Tempo::GRAVE, {0,0} },
    { Tempo::ADAGISSIMO, {0,0} },
    { Tempo::LENTISSIMO, {0,0} },
};

using TempoTextTable=std::map<std::string,Tempo>;
const TempoTextTable TEMPO_TEXT_TABLE_IT {
    { "prestissimo", Tempo::PRESTISSIMO},
    { "presto", Tempo::PRESTO},
    { "allegrissimo", Tempo::ALLEGRISSIMO},
    { "allegro_vivance", Tempo::ALLEGRO_VIVANCE},
    { "vivacissimo", Tempo::VIVACISSIMO},
    { "vivance", Tempo::VIVANCE},
    { "allegro_assai", Tempo::ALLEGRO_ASSAI},
    { "allegro_molto", Tempo::ALLEGRO_MOLTO},
    { "allegro", Tempo::ALLEGRO},
    { "allegro_ma_non_troppo", Tempo::ALLEGRO_MA_NON_TROPPO},
    { "allegro_non_troppo", Tempo::ALLEGRO_NON_TROPPO},
    { "allegro_moderato", Tempo::ALLEGRO_MODERATO},
    { "allegretto", Tempo::ALLEGRETTO},
    { "moderato", Tempo::MODERATO},
    { "marcia_moderato", Tempo::MARCIA_MODERATO},
    { "adantino", Tempo::ADANTINO},
    { "adante", Tempo::ANDANTE},
    { "adagietto", Tempo::ADAGIETTO},
    { "adagio", Tempo::ADAGIO},
    { "larghetto", Tempo::LARGHETTO},
    { "lento", Tempo::LENTO},
    { "largo", Tempo::LARGO},
    { "grave", Tempo::GRAVE},
    { "adagissimo", Tempo::ADAGISSIMO},
    { "lentissimo", Tempo::LENTISSIMO},
};

}