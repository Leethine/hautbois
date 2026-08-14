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
  stk::Instrmnt * _instr;
  SingleNoteStkDummy(const std::string& __pitch, const std::string& __value);
  SingleNoteStkDummy(const SingleNote&  __other);
  SingleNoteStkDummy(const SingleNote&& __other);
public:
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// Chord
class ChordStkDummy : public Chord {
protected:
  stk::Instrmnt * _instr;
  ChordStkDummy(const std::vector<std::string>& __pitch, const std::string& __value);
  ChordStkDummy(const Chord&  __other);
  ChordStkDummy(const Chord&& __other);
public:
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// GraceNote
class GraceNoteStkDummy : public GraceNote {
protected:
  stk::Instrmnt * _instr;
  GraceNoteStkDummy(const std::vector<std::string>& __grace_notes,
                    const std::string& __pitch, const std::string& __value);
  GraceNoteStkDummy(const GraceNote&  __other);
  GraceNoteStkDummy(const GraceNote&& __other);
public:
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// Tuplet
class TupletStkDummy : public Tuplet {
protected:
  stk::Instrmnt * _instr;
  TupletStkDummy(const size_t __total, const size_t __value, const std::vector<std::string>& __notes);
  TupletStkDummy(const Tuplet&  __other);
  TupletStkDummy(const Tuplet&& __other);
public:
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


} // namespace synth
} // namespace hautbois

#endif