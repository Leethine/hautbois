#include "mandolin_dummy.hpp"
#include "stk_note_dummy.hpp"
#include "instrument_singleton.hpp"

#include <stk/Instrmnt.h>
#include <stk/Mandolin.h>

namespace hautbois {
namespace synth {


SingleNoteMandolinDummy::SingleNoteMandolinDummy(const std::string& __pitch, const std::string& __value) :
  SingleNoteStkDummy(__pitch, __value) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

SingleNoteMandolinDummy::SingleNoteMandolinDummy(const SingleNote& __other) :
  SingleNoteStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

SingleNoteMandolinDummy::SingleNoteMandolinDummy(const SingleNote&& __other) :
  SingleNoteStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

void SingleNoteMandolinDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  SingleNoteStkDummy::toStream(__output, __tempo, __amplitude, __freeTxtCtrl);
}


ChordMandolinDummy::ChordMandolinDummy(const std::vector<std::string>& __pitch,
                                       const std::string& __value) : 
  ChordStkDummy(__pitch, __value) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

ChordMandolinDummy::ChordMandolinDummy(const Chord& __other) : 
  ChordStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

ChordMandolinDummy::ChordMandolinDummy(const Chord&& __other) : 
  ChordStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

void ChordMandolinDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  ChordStkDummy::toStream(__output, __tempo, __amplitude, __freeTxtCtrl);
}


GraceNoteMandolinDummy::GraceNoteMandolinDummy(
  const std::vector<std::string>& __grace_notes,
  const std::string& __pitch, const std::string& __value) :
  GraceNoteStkDummy(__grace_notes, __pitch, __value) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

GraceNoteMandolinDummy::GraceNoteMandolinDummy(const GraceNote& __other) :
  GraceNoteStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

GraceNoteMandolinDummy::GraceNoteMandolinDummy(const GraceNote&& __other) :
  GraceNoteStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

void GraceNoteMandolinDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  GraceNoteStkDummy::toStream(__output, __tempo, __amplitude, __freeTxtCtrl);
}


TupletMandolinDummy::TupletMandolinDummy(const size_t __total, const size_t __value,
                                         const std::vector<std::string>& __notes) :
  TupletStkDummy(__total, __value, __notes) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

TupletMandolinDummy::TupletMandolinDummy(const Tuplet& __other) :
  TupletStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

TupletMandolinDummy::TupletMandolinDummy(const Tuplet&& __other) :
  TupletStkDummy(__other) {
  _instr = stk_dummy::InstrumentSingleton::getInstance().getPtr("mandolin");
}

void TupletMandolinDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  TupletStkDummy::toStream(__output, __tempo, __amplitude, __freeTxtCtrl);
}


} // namespace hautbois
} // namespace synth