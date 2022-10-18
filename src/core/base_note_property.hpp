#pragma once

#ifndef base_property_H
#define base_property_H
#endif

#include "basetypes/base_def_types.hpp"
#include "property/property_enum_types.hpp"
#include "property/property_const.hpp"

namespace hautbois {
namespace core {

class BaseNoteProperty {
 private:
  ArticulationEnum _articulation;
  DynamicsEnum _dynamics;
  OrnamentEnum _ornamant;
  UInt8 _articulationVal;
  UInt8 _dynamicsVal;
  UInt8 _ornamantVal;
 protected:
 public:
  BaseNoteProperty():
  _articulation { ArticulationEnum::UNKNOWN },
  _dynamics { DynamicsEnum::UNKNOWN },
  _ornamant { OrnamentEnum::UNKNOWN },
  _articulationVal { property_values::UNKNOWN_VALUE },
  _dynamicsVal { property_values::UNKNOWN_VALUE },
  _ornamantVal { property_values::UNKNOWN_VALUE }
  {}

};

} // namespace core
} // namespace hautbois

