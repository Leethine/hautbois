#include "flute_dummy.hpp"
#include "stk_note_dummy.hpp"
#include "instrument_singleton.hpp"

#include <stk/Instrmnt.h>
#include <stk/Flute.h>

namespace hautbois {
namespace synth {


SingleNoteFluteDummy::SingleNoteFluteDummy(const std::string& __pitch, const std::string& __value) :
  SingleNoteStkDummy(__pitch, __value) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

SingleNoteFluteDummy::SingleNoteFluteDummy(const SingleNote& __other) :
  SingleNoteStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

SingleNoteFluteDummy::SingleNoteFluteDummy(const SingleNote&& __other) :
  SingleNoteStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

void SingleNoteFluteDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  SingleNoteStkDummy::toStream(__output, __tempo, __amplitude, __freeTxtCtrl);
}


ChordFluteDummy::ChordFluteDummy(const std::vector<std::string>& __pitch,
                                       const std::string& __value) : 
  ChordStkDummy(__pitch, __value) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

ChordFluteDummy::ChordFluteDummy(const Chord& __other) : 
  ChordStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

ChordFluteDummy::ChordFluteDummy(const Chord&& __other) : 
  ChordStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

void ChordFluteDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  ChordStkDummy::toStream(__output, __tempo, __amplitude, __freeTxtCtrl);
}


GraceNoteFluteDummy::GraceNoteFluteDummy(
  const std::vector<std::string>& __grace_notes,
  const std::string& __pitch, const std::string& __value) :
  GraceNoteStkDummy(__grace_notes, __pitch, __value) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

GraceNoteFluteDummy::GraceNoteFluteDummy(const GraceNote& __other) :
  GraceNoteStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

GraceNoteFluteDummy::GraceNoteFluteDummy(const GraceNote&& __other) :
  GraceNoteStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

void GraceNoteFluteDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  GraceNoteStkDummy::toStream(__output, __tempo, __amplitude, __freeTxtCtrl);
}


TupletFluteDummy::TupletFluteDummy(const size_t __total, const size_t __value,
                                         const std::vector<std::string>& __notes) :
  TupletStkDummy(__total, __value, __notes) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

TupletFluteDummy::TupletFluteDummy(const Tuplet& __other) :
  TupletStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

TupletFluteDummy::TupletFluteDummy(const Tuplet&& __other) :
  TupletStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("flute");
}

void TupletFluteDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  TupletStkDummy::toStream(__output, __tempo, __amplitude, __freeTxtCtrl);
}


} // namespace hautbois
} // namespace synth