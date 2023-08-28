#pragma once

#ifndef TEMPO_ENUM_TYPES_H
#define TEMPO_ENUM_TYPES_H

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

enum class TempoChangeEnum {
  ral, // slow down (rallentando)
  acc, // accelerate (accelerando)
  ral_poco, // slow down little by little
  acc_poco, // accelerate little by little
  UNKNOWN
};

} // namespace core
} // namespace hautbois

#endif
