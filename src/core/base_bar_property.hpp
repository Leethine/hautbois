#pragma once

#ifndef BASE_VOICE_PROPERTY_H
#define BASE_VOICE_PROPERTY_H

#include "basetypes/base_def_types.hpp"
#include "property/property_enum_types.hpp"
#include "property/property_const.hpp"
#include "property/tempo_enum_types.hpp"
#include "base_duration.hpp"
#include <vector>

namespace hautbois {
namespace core {

class BaseBarProperty {
 private:
  TempoEnum _tempo;
  TempoChangeEnum _tempo_change;
  UInt16 _tempo_value;
  BaseDuration * _tempo_change_from;
 protected:
 public:
  BaseBarProperty();
  virtual ~BaseBarProperty();
  virtual bool setTempo(const std::string& ivName);
  virtual std::string getTempo() const;
  virtual bool setTempoChange(const std::string& ivName);
  virtual std::string getTempoChange() const;
  virtual bool setTempoValue(const UInt16 ivValue);
  virtual UInt16 getTempoValue() const;
  virtual bool setTempoChangeStartPoint(const BaseDuration& ivDuration);
  virtual BaseDuration getTempoChangeStartPoint() const;
};

} // namespace core
} // namespace hautbois

#endif