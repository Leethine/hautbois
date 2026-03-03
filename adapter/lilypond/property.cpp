#include "property.hpp"

namespace hautbois {
namespace ly {

LyProperty::LyProperty() : core::Property() { }

LyProperty::LyProperty(const std::string& text) :
  core::Property(text) { }

LyProperty::LyProperty(const core::Property& p) :
  core::Property(p.raw().getStr()) { }
  
LyProperty::LyProperty(const core::Property&& p) :
  core::Property(p.raw().getStr()) { }

LyProperty::LyProperty(const LyProperty& p) :
  core::Property(p.raw().getStr()) { }
  
LyProperty::LyProperty(const LyProperty&& p) :
  core::Property(p.raw().getStr()) { }
  
LyProperty::~LyProperty() {
  core::Property::~Property();
}
  
LyProperty& LyProperty::operator=(const LyProperty& p) {
  if (this != &p) {
    _raw.set(p.raw().getStr());
  }
  return *this;
}

void LyProperty::modify(const char* context) {
  std::string option (context);
  if (option == "filter") {
    //TODO
  }
  _raw.set(context);
}

void * LyProperty::convert(const char* context) {
  // TODO
  return nullptr;
}

bool LyProperty::hasValue() const {
  return core::Property::hasValue();
}

std::string LyProperty::toString() const {
  return _raw.getStr();
}

bool LyProperty::operator==(const std::string& s) const {
  return _raw.getStr() == s;
}

const core::PropertyRaw& LyProperty::raw() const {
  return core::Property::raw();
}

core::PropertyRaw LyProperty::getRaw() const {
  return core::Property::getRaw();
}

} // namespace ly
} // namespace hautbois