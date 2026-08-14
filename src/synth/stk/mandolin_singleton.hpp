#pragma once

#include <stk/Instrmnt.h>
#ifndef INSTR_SINGLETON_HPP
#define INSTR_SINGLETON_HPP

#include <stk/Mandolin.h>

namespace hautbois {
namespace synth {
namespace stk_dummy {

class MandolinSingleton {
public:
    MandolinSingleton(const MandolinSingleton&) = delete;
    MandolinSingleton& operator=(const MandolinSingleton&) = delete;
    MandolinSingleton(MandolinSingleton&&) = delete;
    MandolinSingleton& operator=(MandolinSingleton&&) = delete;

    inline static MandolinSingleton& getInstance() {
        static MandolinSingleton instance;
        return instance;
    }

    inline stk::Instrmnt * getPtr() {
      if (__ptr == nullptr) {
        __ptr = new stk::Mandolin(20.);
      }
      return __ptr;
    }

private:
    stk::Instrmnt * __ptr;
    inline MandolinSingleton() { __ptr = nullptr; }
    inline  ~MandolinSingleton() { delete __ptr; }
};

} // namespace stk_dummy
} // namespace synth
} // namespace hautbois

#endif