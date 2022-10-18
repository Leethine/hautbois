#pragma once

#ifndef tempo_enum_types_H
#define tempo_property_H
#endif

#include <string>
#include <map>


namespace hautbois {
namespace core {

enum class TempoEnum {
  larghissimo,
  adagissimo,
  grave,
  largo,
  lento,
  larghetto,
  adagio,
  adagietto,
  andante,
  andantino,
  marcia_moderato,
  andante_moderato,
  moderato,
  allegretto,
  allegro_moderato,
  allegro,
  molto_allegro,
  vivace,
  vivacissimo,
  vivacissimamente,
  allegrissimo,
  allegro_vivace,
  presto,
  prestissimo,
  UNKNOWN
};

namespace tempo_str_enum_convert {

std::map<std::string, TempoEnum> TEMPO_STRING_TO_ENUM {
  { "larghissimo", TempoEnum::larghissimo },
  { "adagissimo", TempoEnum::adagissimo },
  { "grave", TempoEnum::grave },
  { "largo", TempoEnum::largo },
  { "lento", TempoEnum::lento },
  { "larghetto", TempoEnum::larghetto },
  { "adagio", TempoEnum::adagio },
  { "adagietto", TempoEnum::adagietto },
  { "andante", TempoEnum::andante },
  { "andantino", TempoEnum::andantino },
  { "marcia_moderato", TempoEnum::marcia_moderato },
  { "andante_moderato", TempoEnum::andante_moderato },
  { "moderato", TempoEnum::moderato },
  { "allegretto", TempoEnum::allegretto },
  { "allegro_moderato", TempoEnum::allegro_moderato },
  { "allegro", TempoEnum::allegro },
  { "molto_allegro", TempoEnum::molto_allegro },
  { "vivace", TempoEnum::vivace },
  { "vivacissimo", TempoEnum::vivacissimo },
  { "vivacissimamente", TempoEnum::vivacissimamente },
  { "allegrissimo", TempoEnum::allegrissimo },
  { "allegro_vivace", TempoEnum::allegro_vivace },
  { "presto", TempoEnum::presto },
  { "prestissimo", TempoEnum::prestissimo }
};

std::map<TempoEnum, std::string> TEMPO_ENUM_TO_STRING {
  { TempoEnum::larghissimo, "larghissimo" },
  { TempoEnum::adagissimo, "adagissimo" },
  { TempoEnum::grave, "grave" },
  { TempoEnum::largo, "largo" },
  { TempoEnum::lento, "lento" },
  { TempoEnum::larghetto, "larghetto" },
  { TempoEnum::adagio, "adagio" },
  { TempoEnum::adagietto, "adagietto" },
  { TempoEnum::andante, "andante" },
  { TempoEnum::andantino, "andantino" },
  { TempoEnum::marcia_moderato, "marcia_moderato" },
  { TempoEnum::andante_moderato, "andante_moderato" },
  { TempoEnum::moderato, "moderato" },
  { TempoEnum::allegretto, "allegretto" },
  { TempoEnum::allegro_moderato, "allegro_moderato" },
  { TempoEnum::allegro, "allegro" },
  { TempoEnum::molto_allegro, "molto_allegro" },
  { TempoEnum::vivace, "vivace" },
  { TempoEnum::vivacissimo, "vivacissimo" },
  { TempoEnum::vivacissimamente, "vivacissimamente" },
  { TempoEnum::allegrissimo, "allegrissimo" },
  { TempoEnum::allegro_vivace, "allegro_vivace" },
  { TempoEnum::presto, "presto" },
  { TempoEnum::prestissimo, "prestissimo" }
};

} // namespace tempo_str_enum_convert

} // namespace core
} // namespace hautbois
