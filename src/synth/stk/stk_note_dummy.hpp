#pragma once

#ifndef STK_NOTE_DUMMY_HPP
#define STK_NOTE_DUMMY_HPP

#include "../../note/single_note.hpp"
#include "../../note/chord.hpp"
#include "../../note/grace_note.hpp"
#include "../../note/tuplet.hpp"

namespace stk {
  class Instrmnt;
} // namespace stk

namespace hautbois {
namespace synth {

// SingleNote
class SingleNoteStkDummy : public SingleNote {
protected:
  stk::Instrmnt * __instr = nullptr;
public:
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// Chord
class ChordStkDummy : public Chord {
protected:
  stk::Instrmnt * __instr = nullptr;
public:
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// GraceNote
class GraceNoteStkDummy : public GraceNote {
protected:
  stk::Instrmnt * __instr = nullptr;
public:
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// Tuplet
class TupletStkDummy : public Tuplet {
protected:
  stk::Instrmnt * __instr = nullptr;
public:
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


} // namespace synth
} // namespace hautbois

#endif