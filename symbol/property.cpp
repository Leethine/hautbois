#include "property.hpp"

namespace hautbois {
namespace core {

Property::Property() : _raw () {
}

Property::Property(const std::string& text) : _raw () {
  if (!text.empty()) {
    _raw.set(text.c_str());
  }
}

Property::Property(const Property& p) : _raw (p.raw()) {
}


Property::Property(const Property&& p) : _raw (p.raw()) {
}

Property::Property(const PropertyRaw& p) : _raw (p) {  
}

Property::Property(const PropertyRaw&& p) : _raw (p) {  
}

Property::~Property() {}

Property& Property::operator=(const Property& p) {
  if (this != &p) {
    _raw.set(p.raw().get());
  }
  return *this;
}

void Property::modify(const char* context) {
  // not supported
}

void * Property::convert(const char* context) {
  // not supported
  return nullptr;
}

bool Property::hasValue() const {
  return _raw.hasValue();
}

std::string Property::toString() const {
  if (_raw.hasValue()) {
    return _raw.getStr();
  }
  else {
    std::string s;
    return s;
  }
}

bool Property::operator==(const std::string& s) const {
  return toString() == s;
}

const PropertyRaw& Property::raw() const {
  return _raw;
}

PropertyRaw Property::getRaw() const {
  PropertyRaw r(_raw);
  return r;
}


} // namespace hautbois
} // namespace core