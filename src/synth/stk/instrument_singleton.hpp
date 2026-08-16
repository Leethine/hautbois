#pragma once

#ifndef INSTR_SINGLETON_HPP
#define INSTR_SINGLETON_HPP

#include <stk/Instrmnt.h>
#include <stk/Mandolin.h>
#include <stk/Flute.h>
#include <string>

namespace hautbois {
namespace synth {
namespace stk_dummy {

class InstrumentSingleton {
public:
    InstrumentSingleton(const InstrumentSingleton&) = delete;
    InstrumentSingleton& operator=(const InstrumentSingleton&) = delete;
    InstrumentSingleton(InstrumentSingleton&&) = delete;
    InstrumentSingleton& operator=(InstrumentSingleton&&) = delete;

    inline static InstrumentSingleton& getInstance() {
        static InstrumentSingleton instance;
        return instance;
    }

    inline stk::Instrmnt * getPtr(const std::string& __instrmnt) {
      if (_ptr_flute == nullptr) {
          _ptr_flute = new stk::Flute(20.);
      }
      if (_ptr_mand == nullptr) {
          _ptr_mand = new stk::Mandolin(20.);
      }

      if (__instrmnt == "flute") {
        return _ptr_flute;
      }
      if (__instrmnt == "mandolin") {
        return _ptr_mand;
      }
      return _ptr_flute;
    }

private:
    stk::Instrmnt * _ptr_mand;
    stk::Instrmnt * _ptr_flute;
    inline InstrumentSingleton() {
      _ptr_mand = nullptr;
      _ptr_flute = nullptr;
    }
    inline ~InstrumentSingleton() {
      delete _ptr_mand;
      delete _ptr_flute;
    }
};

} // namespace stk_dummy
} // namespace synth
} // namespace hautbois

#endif