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

namespace articulation_str_enum_convert {

const std::map<std::string, ArticulationEnum> ARTICULATION_STRING_TO_ENUM {
  { "accento", ArticulationEnum::accento },
  { "experssivo", ArticulationEnum::experssivo },
  { "fermata", ArticulationEnum::fermata },
  { "legato", ArticulationEnum::legato },
  { "marcato", ArticulationEnum::marcato },
  { "portato", ArticulationEnum::portato },
  { "spiccato", ArticulationEnum::spiccato },
  { "staccatissimo", ArticulationEnum::staccatissimo },
  { "staccato", ArticulationEnum::staccato },
  { "tenuto", ArticulationEnum::tenuto }
};

const std::map<ArticulationEnum, std::string> ARTICULATION_ENUM_TO_STRING {
  { ArticulationEnum::accento, "accento" },
  { ArticulationEnum::experssivo, "experssivo" },
  { ArticulationEnum::fermata, "fermata" },
  { ArticulationEnum::legato, "legato" },
  { ArticulationEnum::marcato, "marcato" },
  { ArticulationEnum::portato, "portato" },
  { ArticulationEnum::spiccato, "spiccato" },
  { ArticulationEnum::staccatissimo, "staccatissimo" },
  { ArticulationEnum::staccato, "staccato" },
  { ArticulationEnum::tenuto, "tenuto" },
  { ArticulationEnum::UNKNOWN, "UNKNOWN" }
};

} // namespace articulation_str_enum_convert

namespace dynamics_str_enum_convert {

const std::map<std::string, DynamicsEnum> DYNAMICS_STRING_TO_ENUM {
  { "ppp", DynamicsEnum::ppp },
  { "pp", DynamicsEnum::pp },
  { "p", DynamicsEnum::p },
  { "mp", DynamicsEnum::mp },
  { "mf", DynamicsEnum::mf },
  { "f", DynamicsEnum::f },
  { "ff", DynamicsEnum::ff },
  { "fff", DynamicsEnum::fff },
  { "sfz", DynamicsEnum::sfz },
  { "fp", DynamicsEnum::ppp },
  { "cres", DynamicsEnum::cres },
  { "dim", DynamicsEnum::dim },
  { "n", DynamicsEnum::n }
};

const std::map<DynamicsEnum, std::string> DYNAMICS_ENUM_TO_STRING {
  { DynamicsEnum::ppp, "ppp" },
  { DynamicsEnum::pp, "pp" },
  { DynamicsEnum::p, "p" },
  { DynamicsEnum::mp, "mp" },
  { DynamicsEnum::mf, "mf" },
  { DynamicsEnum::f, "f" },
  { DynamicsEnum::ff, "ff" },
  { DynamicsEnum::fff, "fff" },
  { DynamicsEnum::sfz, "sfz" },
  { DynamicsEnum::fp, "fp" },
  { DynamicsEnum::cres, "cres" },
  { DynamicsEnum::dim, "dim" },
  { DynamicsEnum::n, "n" },
  { DynamicsEnum::UNKNOWN, "UNKNOWN" }
};

} // namespace dynamics_str_enum_convert

namespace ornament_str_enum_convert {

const std::map<std::string, OrnamentEnum> ORNAMENT_STRING_TO_ENUM {
  { "acciaccatura", OrnamentEnum::acciaccatura },
  { "appoggiatura", OrnamentEnum::appoggiatura },
  { "arpeggio", OrnamentEnum::arpeggio },
  { "cadenza", OrnamentEnum::cadenza },
  { "fioritura", OrnamentEnum::fioritura },
  { "glissando", OrnamentEnum::glissando },
  { "gruppetto", OrnamentEnum::gruppetto },
  { "mordente", OrnamentEnum::mordente },
  { "trillo", OrnamentEnum::trillo },
  { "tremolo", OrnamentEnum::tremolo }
};

const std::map<OrnamentEnum, std::string> ORNAMENT_ENUM_TO_STRING {
  { OrnamentEnum::acciaccatura, "acciaccatura" },
  { OrnamentEnum::appoggiatura, "appoggiatura" },
  { OrnamentEnum::arpeggio, "arpeggio" },
  { OrnamentEnum::cadenza, "cadenza" },
  { OrnamentEnum::fioritura, "fioritura" },
  { OrnamentEnum::glissando, "glissando" },
  { OrnamentEnum::gruppetto, "gruppetto" },
  { OrnamentEnum::mordente, "mordente" },
  { OrnamentEnum::trillo, "trillo" },
  { OrnamentEnum::tremolo, "tremolo" },
  { OrnamentEnum::UNKNOWN, "UNKNOWN" }
};

} // namespace ornament_str_enum_convert

} // namespace core
} // namespace hautbois

#endif