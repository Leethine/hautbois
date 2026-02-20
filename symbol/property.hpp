#pragma once

#ifndef PROPERTY_H
#define PROPERTY_H

#include "symbol_raw/property_raw.hpp"
#include <string>

namespace hautbois {
namespace core {

class Property {

 private:
  PropertyRaw _raw;

 public:
  
  Property();
  
  Property(const std::string& text);
  
  Property(const Property& p);
  
  Property(const Property&& p);

  Property(const PropertyRaw& p);
  
  Property(const PropertyRaw&& p);
  
  virtual ~Property();
  
  Property operator=(const Property& p);

  virtual void modify(const char* context);

  virtual void * convert(const char* context);

  virtual bool hasValue() const;

  virtual std::string toString() const;

  virtual const PropertyRaw& raw() const;

  virtual PropertyRaw getRaw() const;

};

} // namespace hautbois
} // namespace core

#endif