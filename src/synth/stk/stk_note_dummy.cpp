#include "stk_note_dummy.hpp"
#include "stk_buffer_writer.hpp"
#include "../../utility/hbexcept.hpp"
#include "../../hbtype/hbdefs.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <stk/FileWvOut.h>
#include <stk/Instrmnt.h>
#include <stk/WvOut.h>

namespace hautbois {
namespace synth {

void SingleNoteStkDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __tempo;
  double * amp_ptr = (double *) __amplitude;
  if (!(__out && tempo_ptr) && ((amp_ptr && !SingleNote::isMute()) || SingleNote::isMute())) {
    HB_THROW_MSG(std::runtime_error, 
      "Runtime error, one of the argument is NULL, please check the args.");
  }

  if (SingleNote::isMute()) {
    stk_wv::writeMuteNoteDummy(__out, *tempo_ptr, SingleNote::getDuration(0));
  }
  else {
    stk_wv::writeSingleNoteDummy(__out, *tempo_ptr, SingleNote::getDuration(0),
      __instr, SingleNote::getPitch(0), *amp_ptr);
  }
}


void ChordStkDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __tempo;
  double * amp_ptr = (double *) __amplitude;

  if (!(__out && tempo_ptr && amp_ptr)) {
    HB_THROW_MSG(std::runtime_error, 
      "Runtime error, one of the argument is NULL, please check the params.");
  }

  std::vector<const Pitch *> pitch_list;
  for (int i = 0; i < Chord::getSize(); i++) {
    pitch_list.push_back(Chord::getPitch(i));
  }

  stk_wv::writeChordDummy(__out, *tempo_ptr, Chord::getDuration(0),
    pitch_list, __instr, *amp_ptr);
}


void GraceNoteStkDummy::toStream(void * __output, void * __tempo, void * __amplitude, void * __freeTxtCtrl) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __tempo;
  double * amp_ptr = (double *) __amplitude;

  if (!(__out && tempo_ptr && amp_ptr)) {
    HB_THROW_MSG(std::runtime_error, 
      "Runtime error, one of the argument is NULL, please check the params.");
  }

  Duration d_total (0,1);
  for (int n = 0; n < GraceNote::getSize() - 1; n++) {
    if (GraceNote::getNote(n) && GraceNote::getNote(n)->getDuration(0)) {
      Duration duration_mod (0,1);
      duration_mod.plus(GraceNote::getNote(n)->getDuration(0));
      duration_mod.multiply(2);
      duration_mod.divide(3);
      d_total.plus(&duration_mod);

      stk_wv::writeSingleNoteDummy(__out, *tempo_ptr, &duration_mod,
        __instr, GraceNote::getNote(n)->getPitch(0), *amp_ptr);
    }
  }

  if (GraceNote::getNote(GraceNote::getSize()-1) &&
      GraceNote::getNote(GraceNote::getSize()-1)->getDuration(0)) {
    Duration duration_main (0,1);
    duration_main.plus(GraceNote::getNote(GraceNote::getSize()-1)->getDuration(0));
    duration_main.minus(&d_total);
    stk_wv::writeSingleNoteDummy(__out, *tempo_ptr, &duration_main, __instr,
      GraceNote::getNote(GraceNote::getSize()-1)->getPitch(0), *amp_ptr);
  }
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

    Duration note_duration(tuplet_notevalue);
    int note_count = Tuplet::getDuration(Tuplet::getSize())->getNum();

    for (int n = 0; n < Tuplet::getSize(); n++) {
      if (Tuplet::getNote(n) && Tuplet::getNote(n)->getDuration(0)) {
        // calculate reshaped note value
        int denom = Tuplet::getNote(n)->getDuration(0)->getDenom();
        int num = Tuplet::getNote(n)->getDuration(0)->getNum();
        Duration duration_mod (num, denom);
        double factor_d = ((double) note_duration.getNum() / note_duration.getDenom()) / ((double) num / denom);
        int factor = int(std::round(factor_d));

        // Tuplet single note
        if (Tuplet::getNote(n)->isType(CHAR_NOTETYPE_SINGLE)) {
          stk_wv::writeSingleNote(__out, *tempo_ptr, &duration_mod,
            __instr, Tuplet::getNote(n)->getPitch(0), *amp_ptr,
            note_count, factor, nullptr, nullptr);
        }
        // Tuplet chord
        else if (Tuplet::getNote(n)->isType(CHAR_NOTETYPE_CHORD)) {
          const Note * note_ptr = Tuplet::getNote(n);

          // save all pitches to a list
          std::vector<const Pitch *> pitch_list;
          for (int i = 0; i < note_ptr->getSize(); i++) {
            pitch_list.push_back(note_ptr->getPitch(i));
          }
          // write to output
          stk_wv::writeChordMonoInstrument(
          __out, *tempo_ptr, &duration_mod, pitch_list,
            __instr, *amp_ptr,
            note_count, factor, nullptr, nullptr);
        }
      }
    }
  }
}

} // namespace synth
} // namespace hautbois
