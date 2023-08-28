#pragma once

#ifndef PROPERTY_ENUM_TYPES_H
#define PROPERTY_ENUM_TYPES_H

#include <string>
#include <map>

namespace hautbois {
namespace core {

enum class ArticulationEnum {
  accento,
  experssivo,
  fermata,
  legato,
  marcato,
  portato,
  spiccato,
  staccatissimo,
  staccato,
  tenuto,
  UNKNOWN
};

enum class DynamicsEnum {
  ppp,   // Pianississimo
  pp,    // Pianissimo
  p,     // Piano
  mp,    // Mezzo piano
  mf,    // Mezzo forte
  f,     // Forte
  ff,    // Fortissimo
  fff,   // Fortississimo
  sfz,   // Sforzando
  fp,    // Fortepiano
  cres,  // Crescendo
  decres,//Decrescendo
  dim,   // Diminuendo
  n,     // Niente
  UNKNOWN
};

enum class OrnamentEnum {
  acciaccatura,
  appoggiatura,
  arpeggio,
  cadenza,
  fioritura,
  glissando,
  gruppetto,
  mordente,
  trillo,
  tremolo,
  UNKNOWN
};

} // namespace core
} // namespace hautbois

#endif