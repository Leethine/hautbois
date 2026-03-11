#pragma once

#ifndef NOTE_APPOGGIATURA_H
#define NOTE_APPOGGIATURA_H

#include <vector>
#include <string>

#include "note_grace.hpp"

namespace hautbois {
namespace core {

class Appoggiatura : public GraceNote {

 public:

  Appoggiatura();

  Appoggiatura(Appoggiatura& __note);
  
  Appoggiatura(Appoggiatura&& __note);

  virtual Appoggiatura& operator=(const Appoggiatura& __n);

  virtual ~Appoggiatura();

};

} // namespace core
} // namespace hautbois

#endif