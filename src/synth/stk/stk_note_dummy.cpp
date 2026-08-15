#include "stk_note_dummy.hpp"
#include "stk_buffer_writer.hpp"
#include "../../utility/hbexcept.hpp"
#include "../../hbtype/hbdefs.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <stk/Instrmnt.h>
#include <stk/FileWvOut.h>
#include <stk/WvOut.h>

namespace hautbois {
namespace synth {

SingleNoteStkDummy::SingleNoteStkDummy(const std::string& __pitch, const std::string& __value) :
  SingleNote(__pitch, __value) {
  _instr = nullptr;
}

SingleNoteStkDummy::SingleNoteStkDummy(const SingleNote& __other) :
  SingleNote(__other) {
  _instr = nullptr;
}

SingleNoteStkDummy::SingleNoteStkDummy(const SingleNote&& __other) :
  SingleNote(__other) {
  _instr = nullptr;
}

void SingleNoteStkDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  
  int * tempo_ptr = (int *)(__tempo);
  double * amp_ptr = (double *) __amplitude;
  if (!__out || ! tempo_ptr || ! amp_ptr) {
    HB_THROW_MSG(std::runtime_error, 
      "Runtime error, one of the argument is NULL, please check the args.");
  }
  size_t bufferSize;
  stk_buffer::calculateBufferSize(bufferSize, *tempo_ptr, SingleNote::getDuration());
  double buffer[bufferSize + 1];
  stk_buffer::writeToBuffer(buffer, bufferSize, _instr, SingleNote::getPitch(), *amp_ptr);

  for (size_t i = 0; i < bufferSize; i++) {
    __out->tick(buffer[i]);
  }
}


ChordStkDummy::ChordStkDummy(const std::vector<std::string>& __pitch,
                             const std::string& __value) : Chord(__pitch, __value) {
  _instr = nullptr;
}

ChordStkDummy::ChordStkDummy(const Chord&  __other) : Chord(__other) {
  _instr = nullptr;
}

ChordStkDummy::ChordStkDummy(const Chord&& __other) : Chord(__other) {
  _instr = nullptr;
}

void ChordStkDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __tempo;
  double * amp_ptr = (double *) __amplitude;

  if (!(__out && tempo_ptr && amp_ptr)) {
    HB_THROW_MSG(std::runtime_error, 
      "Runtime error, one of the argument is NULL, please check the params.");
  }

  size_t bufferSize;
  stk_buffer::calculateBufferSize(bufferSize, *tempo_ptr, Chord::getDuration());
  double buffer[bufferSize+1];
  stk_buffer::clearBuffer(buffer, bufferSize);
  for (int i = 0; i < Chord::getSize(); i++) {
    stk_buffer::writeToBuffer(buffer, bufferSize, _instr, Chord::getPitch(i), *amp_ptr);
  }

  for (size_t i = 0; i < bufferSize; i++) {
    __out->tick(buffer[i]);
  }
}


GraceNoteStkDummy::GraceNoteStkDummy(
  const std::vector<std::string>& __grace_notes,
  const std::string& __pitch, const std::string& __value) : 
  GraceNote(__grace_notes, __pitch, __value) {
  _instr = nullptr;
}

GraceNoteStkDummy::GraceNoteStkDummy(const GraceNote&  __other) : GraceNote(__other) {
  _instr = nullptr;
}

GraceNoteStkDummy::GraceNoteStkDummy(const GraceNote&& __other) : GraceNote(__other) {
  _instr = nullptr;
}

void GraceNoteStkDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __tempo;
  double * amp_ptr = (double *) __amplitude;

  if (!(__out && tempo_ptr && amp_ptr)) {
    HB_THROW_MSG(std::runtime_error, 
      "Runtime error, one of the argument is NULL, please check the params.");
  }

  // process grace notes
  Duration d_total (0,1);
  for (int n = 0; n < GraceNote::getSize() - 1; n++) {
    if (GraceNote::getNote(n) && GraceNote::getNote(n)->getDuration(0)) {
      Duration duration_mod (0,1);
      duration_mod.plus(GraceNote::getNote(n)->getDuration(0));
      duration_mod.multiply(2);
      duration_mod.divide(3);
      d_total.plus(&duration_mod);

      size_t bufferSize;
      stk_buffer::calculateBufferSize(bufferSize, *tempo_ptr, &duration_mod);
      double buffer[bufferSize+1];
      stk_buffer::clearBuffer(buffer, bufferSize);
      stk_buffer::writeToBuffer(buffer, bufferSize, _instr, GraceNote::getNote(n)->getPitch(0), *amp_ptr);
      for (size_t i = 0; i < bufferSize; i++) {
        __out->tick(buffer[i]);
      }
    }
  }

  // process main note
  const Note * main_note = GraceNote::getNote(GraceNote::getSize()-1);
  if (main_note && main_note->getDuration(0)) {
    Duration duration_main (0,1);
    duration_main.plus(GraceNote::getNote(GraceNote::getSize()-1)->getDuration(0));
    duration_main.minus(&d_total);
    size_t bufferSize;
    stk_buffer::calculateBufferSize(bufferSize, *tempo_ptr, &duration_main);
    double buffer[bufferSize+1];
    stk_buffer::clearBuffer(buffer, bufferSize);
    stk_buffer::writeToBuffer(buffer, bufferSize, _instr,
                              main_note->getPitch(0), *amp_ptr);
    for (size_t i = 0; i < bufferSize; i++) {
      __out->tick(buffer[i]);
    }
  }
}


TupletStkDummy::TupletStkDummy(const size_t __total, const size_t __value,
                               const std::vector<std::string>& __notes) :
  Tuplet(__total, __value, __notes) {
  _instr = nullptr;
}

TupletStkDummy::TupletStkDummy(const Tuplet&  __other) : Tuplet(__other) {
  _instr = nullptr;
}

TupletStkDummy::TupletStkDummy(const Tuplet&& __other) : Tuplet(__other) {
  _instr = nullptr;
}

void TupletStkDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __tempo;
  double * amp_ptr = (double *) __amplitude;

  if (!(__out && tempo_ptr && amp_ptr)) {
    HB_THROW_MSG(std::runtime_error, 
      "Runtime error, one of the argument is NULL, please check the params.");
  }

  std::string tuplet_notevalue;
  if (Tuplet::getDuration(Tuplet::getSize())) {
    // get total value of the tuplet
    tuplet_notevalue = std::to_string(Tuplet::getDuration(Tuplet::getSize())->getDenom());
    std::replace(tuplet_notevalue.begin(), tuplet_notevalue.end(), '0', '.');

    // exit on error (tuplet note value is ill-formed)
    try {
      Duration d_test (tuplet_notevalue);
    }
    catch(std::invalid_argument&) {
      HB_THROW_MSG(std::runtime_error, "Invalid Tuplet format encountered: " + tuplet_notevalue);
    }

    // Fetch duration reshaping info
    Duration tuplet_duration(tuplet_notevalue);
    int tuplet_count = Tuplet::getDuration(Tuplet::getSize())->getNum();
    int mul = 2;
    int div = tuplet_count;
    if (tuplet_notevalue.find('.') != std::string::npos) {
      mul = 3;
    }

    // for each note, write to out buffer
    for (int n = 0; n < Tuplet::getSize(); n++) { 
      const Note * note_ptr = Tuplet::getNote(n);
      // calculate buffer size first, does not matter single note or chord
      size_t bufferSize;
      stk_buffer::calculateBufferSize(bufferSize, *tempo_ptr, note_ptr->getDuration(0), div, mul);
      double buffer[bufferSize + 1];
      stk_buffer::clearBuffer(buffer, bufferSize);

      // Write pitch if single note
      if (note_ptr && note_ptr->isType(CHAR_NOTETYPE_SINGLE)) {
        stk_buffer::writeToBuffer(buffer, bufferSize, _instr, note_ptr->getPitch(0), *amp_ptr);
      }
      // Write pitch if chord note
      else if (note_ptr && note_ptr->isType(CHAR_NOTETYPE_CHORD)) {
        for (int i = 0; i < note_ptr->getSize(); i++) {
          stk_buffer::writeToBuffer(buffer, bufferSize, _instr, note_ptr->getPitch(i), *amp_ptr);
        }
      }

      // write to wav output file
      for (size_t i = 0; i < bufferSize; i++) {
        __out->tick(buffer[i]);
      }
    }
  }
}

} // namespace synth
} // namespace hautbois
