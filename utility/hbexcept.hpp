#pragma once

#include <stdexcept>
#include <string>

#if defined(__FILE__) && defined(__LINE__)

#define HB_THROW_MSG(EXP,MSG)  \
  (throw EXP(                  \
    std::string("\nFile: ")  + \
    std::string(__FILE__)    + \
    "\nLine: "               + \
    std::to_string(__LINE__) + \
    "\nError: " +              \
    std::string(MSG))          \
)

#define HB_THROW(EXP)(throw EXP( \
    std::string("\nFile: ") +    \
    std::string(__FILE__)   +    \
    "\nLine: "              +    \
    std::to_string(__LINE__))    \
)

#else

#define HB_THROW_MSG(EXP,MSG)       \
  (throw EXP(std::string("Error: ") \
           + std::string(MSG))      \
)

#define HB_THROW(EXP)(throw EXP( \
  std::string("Error."))         \
)

#endif
