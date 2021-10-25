#include <map>

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

TempoBpmRangeMap tempo_bpm_table {
    { Tempo::LENTISSIMO, {0,0} },
};

}