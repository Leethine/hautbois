#pragma once

#define __CXX17

#ifdef __CXX17
#include<optional>
namespace hautbois {
    template<class T>
    class BaseOptional : public std::optional<T> {
        void emplaceValue(T val) {
            std::optional.emplace(val);
        }
        
    };
}

#else

namespace hautbois {
    
}

#endif