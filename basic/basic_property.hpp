#pragma once

#ifndef BASIC_PROPERTY_H
#define BASIC_PROPERTY_H

#include "core_types.hpp"
#include <cstring>
#include <cstdlib>

#define PROPERTY_TEXT_MAX_LENGTH 100

namespace hautbois {
namespace core {

class BasicProperty {

 private:

  char * _raw = nullptr;

 protected:

  inline virtual void save(const char* text) {
    if (text && std::strlen(text) < PROPERTY_TEXT_MAX_LENGTH) {
      char * temp_new_text = (char*) std::malloc((std::strlen(text)+1)*sizeof(char));
      if (temp_new_text != NULL) {
        std::free(_raw);
        std::strcpy(temp_new_text, text);
        _raw = temp_new_text;
      }
    }
  }

 public:

  inline BasicProperty() {}
 
  inline virtual ~BasicProperty() {
    std::free(_raw);
  }
 
  inline virtual void update(const char* text) {
    save(text);
  }

  inline virtual bool isValid() const {
    if (_raw) {
      return true;
    }
    return false;
  }

  inline virtual const char * get() const {
    return _raw;
  }

};

} // namespace hautbois
} // namespace core

#endif