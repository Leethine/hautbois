#pragma once

#ifndef BASE_NOTE_PROPERTY_H
#define BASE_NOTE_PROPERTY_H

#include "basetypes/base_def_types.hpp"
#include "property/property_enum_types.hpp"
#include "property/property_const.hpp"
#include "property/property_enum_converter.hpp"

#include <vector>

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
  virtual void warnInvalidPropertyName(const std::string& ivFunc) const;

 public:
  BaseNoteProperty();
  virtual ~BaseNoteProperty();

  virtual void setArticulation(const std::string& ivName, UInt8 ivVal);
  virtual void setArticulation(const std::string& ivName);
  virtual void setDynamics(const std::string& ivName, UInt8 ivVal);
  virtual void setDynamics(const std::string& ivName);
  virtual void setOrnament(const std::string& ivName, UInt8 ivVal);
  virtual void setOrnament(const std::string& ivName);
  virtual void set(const std::string& ivName, UInt8 ivVal);
  virtual void set(const std::string& ivName);
  virtual bool hasArticulation() const;
  virtual bool hasDynamics() const;
  virtual bool hasOrnament() const;
  virtual void clearArticulation();
  virtual void clearDynamics();
  virtual void clearOrnament();
  virtual void clear();
  virtual std::pair<std::string, UInt8> getArticulation() const;
  virtual std::pair<std::string, UInt8> getDynamics() const;
  virtual std::pair<std::string, UInt8> getOrnament() const;
};

} // namespace core
} // namespace hautbois

#endif