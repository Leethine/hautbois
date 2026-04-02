#pragma once

#ifndef LY_PROPERTY_H
#define LY_PROPERTY_H

#include "../symbol/property.hpp"

namespace hautbois {
namespace ly {

class LyProperty : public core::Property {

 public:

  LyProperty();

  // LyProperty(const std::string& text);

  LyProperty(const Property& p);

  LyProperty(const Property&& p);

  LyProperty(const LyProperty& p);

  LyProperty(const LyProperty&& p);

  virtual ~LyProperty();

  virtual LyProperty& operator=(const LyProperty& p);

  virtual LyProperty& operator=(const core::Property& p);

  virtual void modify(const char* __context);

  virtual void * convert(const char* __context) const;

  virtual bool hasValue() const;

  virtual std::string toString() const;

  using core::Property::operator==;
  virtual bool operator==(const std::string& s) const;

  virtual const core::PropertyRaw& raw() const;

  virtual core::PropertyRaw getRaw() const;

};

} // namespace ly
} // namespace hautbois

#endif