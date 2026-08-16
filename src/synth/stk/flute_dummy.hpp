#pragma once

#ifndef STK_FLUTE_DUMMY_HPP
#define STK_FLUTE_DUMMY_HPP

#include "stk_note_dummy.hpp"

#define FLUTE_NOTE_TYPES SingleNoteFluteDummy,ChordFluteDummy,GraceNoteFluteDummy,TupletFluteDummy

namespace hautbois {
namespace synth {


class SingleNoteFluteDummy : public SingleNoteStkDummy {
public:
  SingleNoteFluteDummy(const std::string& __pitch, const std::string& __value);
  SingleNoteFluteDummy(const SingleNote&  __other);
  SingleNoteFluteDummy(const SingleNote&& __other);
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// Chord
class ChordFluteDummy : public ChordStkDummy {
public:
  ChordFluteDummy(const std::vector<std::string>& __pitch, const std::string& __value);
  ChordFluteDummy(const Chord&  __other);
  ChordFluteDummy(const Chord&& __other);
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// GraceNote
class GraceNoteFluteDummy : public GraceNoteStkDummy {
public:
  GraceNoteFluteDummy(const std::vector<std::string>& __grace_notes,
                         const std::string& __pitch, const std::string& __value);
  GraceNoteFluteDummy(const GraceNote&  __other);
  GraceNoteFluteDummy(const GraceNote&& __other);
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


// Tuplet
class TupletFluteDummy : public TupletStkDummy {
public:
  TupletFluteDummy(const size_t __total, const size_t __value, const std::vector<std::string>& __notes);
  TupletFluteDummy(const Tuplet&  __other);
  TupletFluteDummy(const Tuplet&& __other);
  virtual void toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const;
};


} // namespace hautbois
} // namespace synth

#endif