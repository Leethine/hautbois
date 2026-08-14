#pragma once

#ifndef STK_MANDOLIN_DUMMY_HPP
#define STK_MANDOLIN_DUMMY_HPP

#include "stk_note_dummy.hpp"

#define MANDOLIN_NOTE_TYPES SingleNoteMandolinDummy,ChordMandolinDummy,GraceNoteMandolinDummy,TupletMandolinDummy

namespace hautbois {
namespace synth {


class SingleNoteMandolinDummy : public SingleNoteStkDummy {
public:
  SingleNoteMandolinDummy(const std::string& __pitch, const std::string& __value);
  SingleNoteMandolinDummy(const SingleNote&  __other);
  SingleNoteMandolinDummy(const SingleNote&& __other);
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// Chord
class ChordMandolinDummy : public ChordStkDummy {
public:
  ChordMandolinDummy(const std::vector<std::string>& __pitch, const std::string& __value);
  ChordMandolinDummy(const Chord&  __other);
  ChordMandolinDummy(const Chord&& __other);
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// GraceNote
class GraceNoteMandolinDummy : public GraceNoteStkDummy {
public:
  GraceNoteMandolinDummy(const std::vector<std::string>& __grace_notes,
                         const std::string& __pitch, const std::string& __value);
  GraceNoteMandolinDummy(const GraceNote&  __other);
  GraceNoteMandolinDummy(const GraceNote&& __other);
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// Tuplet
class TupletMandolinDummy : public TupletStkDummy {
public:
  TupletMandolinDummy(const size_t __total, const size_t __value, const std::vector<std::string>& __notes);
  TupletMandolinDummy(const Tuplet&  __other);
  TupletMandolinDummy(const Tuplet&& __other);
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


} // namespace hautbois
} // namespace synth

#endif