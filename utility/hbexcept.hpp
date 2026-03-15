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

#define HB_NESTED_THROW(EXP,PROC) \
  try { PROC }                    \
  catch(const EXP & e) {          \
    throw EXP(                    \
    std::string("\nFile: ")  +    \
    std::string(__FILE__)    +    \
    "\nLine: "               +    \
    std::to_string(__LINE__) +    \
    "\nUpper-level exception: " + \
    std::string(e.what())) ;      \
  }                               


#define HB_NESTED_THROW_ACTION(EXP,PROC,ACT) \
  try { PROC }                               \
  catch(const EXP & e) {  ACT                \
    throw EXP( std::string("\nFile: ")  +    \
    std::string(__FILE__) + "\nLine: "  +    \
    std::to_string(__LINE__)            +    \
    "\nUpper-level exception: "         +    \
    std::string(e.what())) ;                 \
  }                               


#define HB_NESTED_THROW_MSG(EXP,MSG,PROC) \
  try { PROC } catch(const EXP & e) {     \
    throw EXP(                            \
      std::string("\nFile: ") +           \
      std::string(__FILE__) + "\nLine: "  \
      + std::to_string(__LINE__)          \
      + "\nError: " + std::string( MSG )  \
      + "\nUpper-level exception: "       \
      + e.what() );                       \
}



#define HB_NESTED_THROW_MSG_ACTION(EXP,MSG,PROC,ACT)  \
  try { PROC } catch(const EXP & e) { ACT             \
    throw EXP(                                        \
      std::string("\nFile: ") + std::string(__FILE__) \
      + "\nLine: " + std::to_string(__LINE__)         \
      + "\nError: " + std::string( MSG )              \
      + "\nUpper-level exception: " + e.what() );     \
}

#else

#define HB_THROW_MSG(EXP,MSG)       \
  (throw EXP(std::string("Error: ") \
           + std::string(MSG))      \
)

#define HB_THROW(EXP)(throw EXP( \
  std::string("Error."))         \
)

#define HB_NESTED_THROW(EXP,PROC) \
  try { PROC }                    \
  catch(const EXP & e) {          \
    throw EXP(                    \
    "\nUpper-level exception:\n"+ \
    std::string(e.what())) ;      \
  }                               

#define HB_NESTED_THROW_ACTION(EXP,PROC,ACT) \
  try { PROC }                               \
  catch(const EXP & e) {  ACT                \
    throw EXP("\nUpper-level exception:\n" + \
    std::string(e.what())) ;                 \
  }

#define HB_NESTED_THROW_MSG(EXP,MSG,PROC) \
  try { PROC } catch(const EXP & e) {     \
    throw EXP( "\nError: "+               \
      std::string( MSG )  +               \
      "\nUpper-level exception:\n" +      \
      e.what() ) ;                        \
}

#define HB_NESTED_THROW_MSG_ACTION(EXP,MSG,PROC,ACT) \
  try { PROC } catch(const EXP & e) { ACT            \
    throw EXP( "\nError: " + std::string( MSG ) +    \
      "\nUpper-level exception:\n" + e.what() ) ;    \
}

#endif
