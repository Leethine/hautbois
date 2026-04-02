#include "ly_property.hpp"

#include <algorithm>
#include <string>
#include <vector>
#include <array>

namespace hautbois {
namespace ly {

const static std::array<std::string, 39> LY_NOTE_PROPERTY {
  // dynamic marks
  "<",">","!","p","pp","ppp","f","ff","fff","mp","mf","fp","pf","cresc","decresc",
  // articulation marks
  "accent", "espressivo", "marcato", "portato", "staccatissimo", "staccato", "tenuto",
  "fermata",
  // Ornament 
  "prall", "prallup", "pralldown", "upprall", "downprall", "prallprall",
  "lineprall", "prallmordent", "mordent", "upmordent", "downmordent",
  "trill", "turn", "reverseturn", "slashturn", "haydnturn"
};

LyProperty::LyProperty() : core::Property() { }

// LyProperty::LyProperty(const std::string& text) :
//  core::Property(text) { }

LyProperty::LyProperty(const core::Property& p) :
  core::Property(p.raw().getStr()) { }
  
LyProperty::LyProperty(const core::Property&& p) :
  core::Property(p.raw().getStr()) { }

LyProperty::LyProperty(const LyProperty& p) :
  core::Property(p.raw().getStr()) { }
  
LyProperty::LyProperty(const LyProperty&& p) :
  core::Property(p.raw().getStr()) { }
  
LyProperty::~LyProperty() {
}

LyProperty& LyProperty::operator=(const LyProperty& p) {
  if (this != &p) {
    _raw.set(p.raw().getStr());
  }
  return *this;
}

LyProperty& LyProperty::operator=(const core::Property& p) {
  if (this != &p) {
    _raw.set(p.raw().getStr());
  }
  return *this;
}

void LyProperty::modify(const char * __context) {
  if (__context == nullptr) {
    return ;
  }
  std::vector<std::string> propertyList;
  for (int i = 0; i<std::strlen(__context); i++) {
    std::string s;
    if (__context[i] == '\\') {
      int j=i+1;
      for (; __context[j] != '\\' && __context[j] != '\0'; j++, i++) {
        s.push_back(__context[j]);
      }
      i = j;
    }
    if (!s.empty()) {
      propertyList.push_back(s);
    }
  }
  std::string newtext;
  for (std::string& s: propertyList) {
    if (std::find(LY_NOTE_PROPERTY.begin(), LY_NOTE_PROPERTY.end(), s) 
        != LY_NOTE_PROPERTY.end()) {
        newtext.push_back('\\');
        newtext.append(s);
    }
  }
  _raw.set(newtext);
}

void * LyProperty::convert(const char* __context) const {
  // Not supported
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