#include "property_enum_converter.hpp"

const std::map<std::string, hautbois::core::ArticulationEnum> hautbois::core::articulation_str_enum_convert::ARTICULATION_STRING_TO_ENUM {
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

const std::map<hautbois::core::ArticulationEnum, std::string> hautbois::core::articulation_str_enum_convert::ARTICULATION_ENUM_TO_STRING {
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

const std::map<std::string, hautbois::core::DynamicsEnum> hautbois::core::dynamics_str_enum_convert::DYNAMICS_STRING_TO_ENUM {
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

const std::map<hautbois::core::DynamicsEnum, std::string> hautbois::core::dynamics_str_enum_convert::DYNAMICS_ENUM_TO_STRING {
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

const std::map<std::string, hautbois::core::OrnamentEnum> hautbois::core::ornament_str_enum_convert::ORNAMENT_STRING_TO_ENUM {
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

const std::map<hautbois::core::OrnamentEnum, std::string> hautbois::core::ornament_str_enum_convert::ORNAMENT_ENUM_TO_STRING {
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