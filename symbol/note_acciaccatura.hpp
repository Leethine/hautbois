#pragma once

#ifndef NOTE_ACCIACCATURA_H
#define NOTE_ACCIACCATURA_H

#include <vector>
#include <string>

#include "note_grace.hpp"

namespace hautbois {
namespace core {

class Acciaccatura : public GraceNote {

 public:

  Acciaccatura();

  Acciaccatura(Acciaccatura& __note);
  
  Acciaccatura(Acciaccatura&& __note);

  virtual Acciaccatura& operator=(const Acciaccatura& __n);

  virtual ~Acciaccatura();

};

} // namespace core
} // namespace hautbois

#endif