#pragma once

#ifndef PROPERTY_RAW_H
#define PROPERTY_RAW_H

#include "core_types.hpp"

#include <string>
#include <cstring>
#include <cstdlib>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/split_member.hpp>

#define PROPERTY_TEXT_MAX_LENGTH 200

namespace hautbois {
namespace core {

class PropertyRaw final {

 private:

  friend class boost::serialization::access;

  template<class Archive>
  inline void save(Archive & ar, const unsigned int version) const {
    if (!_text) {
      ar << false;
    }
    else {
      ar << true;
      std::string text (_text);
      ar << text;
    }
  }
  
  template<class Archive>
  inline void load(Archive & ar, const unsigned int version) {
    bool has_value;
    ar >> has_value;
    if (has_value) {
      std::string text;
      ar >> text;
      set(text);
    }
  }

  BOOST_SERIALIZATION_SPLIT_MEMBER()

  char * _text = nullptr;

 public:

  inline PropertyRaw() {}

  inline PropertyRaw(const PropertyRaw& p) {
    set(p.get());
  }

  inline PropertyRaw(const PropertyRaw&& p) {
    set(p.get());
  }
 
  inline ~PropertyRaw() {
    std::free(_text);
  }

  inline void set(const char* text) noexcept {
    if (text && std::strlen(text) < PROPERTY_TEXT_MAX_LENGTH) {
      char * temp_new_text = (char*) std::malloc((std::strlen(text)+1)*sizeof(char));
      if (temp_new_text != NULL) {
        std::free(_text);
        std::strcpy(temp_new_text, text);
        _text = temp_new_text;
      }
    }
  }

  inline void set(const std::string& text) noexcept {
    if (!text.empty() && text.length() < PROPERTY_TEXT_MAX_LENGTH) {
      char * temp_new_text = (char*) std::malloc((text.length()+1)*sizeof(char));
      if (temp_new_text != NULL) {
        std::free(_text);
        std::strcpy(temp_new_text, text.c_str());
        _text = temp_new_text;
      }
    }
  }

  inline bool hasValue() const {
    if (_text) {
      return true;
    }
    return false;
  }

  inline const char * get() const {
    return _text;
  }

  inline std::string getStr() const {
    std::string s (_text);
    return s;
  }

  inline PropertyRaw& operator=(const PropertyRaw& r) {
    if (this != &r) {
      set(r.get());
    }
    return *this;
  }

};

} // namespace hautbois
} // namespace core

#endif