#include "mandolin_note.hpp"
#include "stk_buffer_writer.hpp"
#include "../../utility/hbexcept.hpp"
#include "../../hbtype/hbdefs.hpp"

#include <algorithm>
#include <stdexcept>
#include <stk/FileWvOut.h>
#include <stk/Instrmnt.h>
#include <stk/Mandolin.h>
#include <string>
#include <sys/types.h>

#define DEFAULT_AMPLITUDE 0.8

namespace hautbois {
namespace synth {

namespace stk_mandolin {
static stk::Mandolin MandolinContraBass(20.);
static stk::Mandolin MandolinBass(110.);
static stk::Mandolin MandolinTenor(220.);
static stk::Mandolin MandolinAlto(440.);
static stk::Mandolin MandolinSopran(880.);
static stk::Mandolin MandolinSopranissimo(1760.);

static stk::Mandolin * selectInstrument(double __frequency) {
  stk::Mandolin * ptr;
  if (__frequency < 110.) {
    ptr = &MandolinContraBass;
  }
  else if (__frequency > 110. && __frequency < 220.) {
    ptr = &MandolinBass;
  }
  else if (__frequency > 220. && __frequency < 440.) {
    ptr = &MandolinTenor;
  }
  else if (__frequency > 440. && __frequency < 880.) {
    ptr = &MandolinAlto;
  }
  else if (__frequency > 880. && __frequency < 1760.) {
    ptr = &MandolinSopran;
  }
  else if (__frequency > 1760.) {
    ptr = &MandolinSopranissimo;
  }
  else {
    ptr = &MandolinContraBass;
  }
  return ptr;
}
} // namespace mandolin_stk


void SingleNoteStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __param1;
  if (!(__out && tempo_ptr)) {
    HB_THROW_MSG(std::runtime_error, std::string("Runtime error, please check the params."));
  }

  if (SingleNote::isMute()) {
    stk_wav_writer::writeMutedNote(__out, *tempo_ptr, SingleNote::getDuration(0), 1, 1);
  }
  else if (SingleNote::getPitch(0)) {
    stk_wav_writer::writeSingleNote(__out, *tempo_ptr, SingleNote::getDuration(0), 1, 1,
    stk_mandolin::selectInstrument(SingleNote::getPitch(0)->toFrequency()),
    SingleNote::getPitch(0), DEFAULT_AMPLITUDE);
  }
}


void ChordStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __param1;
  if (!(__out && tempo_ptr)) {
    HB_THROW_MSG(std::runtime_error, std::string("Runtime error, please check the params."));
  }

  std::vector<const Pitch *> pitch_list;
  std::vector<double> amplitude_list;
  std::vector<stk::Instrmnt *> instrument_list;

  for (int i = 0; i < Chord::getSize(); i++) {
    if (Chord::getPitch(i)) {
      pitch_list.push_back(Chord::getPitch(i));
      instrument_list.push_back(stk_mandolin::selectInstrument(Chord::getPitch(i)->toFrequency()));
      amplitude_list.push_back(DEFAULT_AMPLITUDE);
    }
  }

  stk_wav_writer::writeChord(__out,
    *tempo_ptr, Chord::getDuration(0), 1, 1,
    pitch_list, instrument_list, amplitude_list);
}


void GraceNoteStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __param1;
  if (!(__out && tempo_ptr)) {
    HB_THROW_MSG(std::runtime_error, std::string("Runtime error, please check the params."));
  }

  Duration d_total (0,1);
  for (int n = 0; n < GraceNote::getSize() - 1; n++) {
    if (GraceNote::getNote(n) && GraceNote::getNote(n)->getDuration(0) && GraceNote::getNote(n)->getPitch(0)) {
      Duration duration_mod (0,1);
      duration_mod.plus(GraceNote::getNote(n)->getDuration(0));
      duration_mod.multiply(2);
      duration_mod.divide(3);
      d_total.plus(&duration_mod);
      stk_wav_writer::writeSingleNote(__out, *tempo_ptr, &duration_mod,
        1, 1,
        stk_mandolin::selectInstrument(GraceNote::getNote(n)->getPitch(0)->toFrequency()),
        GraceNote::getNote(n)->getPitch(0), DEFAULT_AMPLITUDE);
    }
  }
  if (GraceNote::getNote(GraceNote::getSize()-1) && GraceNote::getNote(GraceNote::getSize()-1)->getPitch(0) &&
      GraceNote::getNote(GraceNote::getSize()-1)->getDuration(0)) {
    Duration duration_main (0,1);
    duration_main.plus(GraceNote::getNote(GraceNote::getSize()-1)->getDuration(0));
    duration_main.minus(&d_total);
    stk_wav_writer::writeSingleNote(__out, *tempo_ptr, &duration_main,
    1, 1,
    stk_mandolin::selectInstrument(GraceNote::getNote(GraceNote::getSize()-1)->getPitch(0)->toFrequency()),
    GraceNote::getNote(GraceNote::getSize()-1)->getPitch(0), DEFAULT_AMPLITUDE);
  }
}


void TupletStkMandolin::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  stk::FileWvOut * __out = reinterpret_cast<stk::FileWvOut *>(__output);
  int * tempo_ptr = (int *) __param1;
  if (!(__out && tempo_ptr)) {
    HB_THROW_MSG(std::runtime_error, std::string("Runtime error, please check the params."));
  }

  if (Tuplet::getDuration(Tuplet::getSize())) {
    std::string tuplet_notevalue = std::to_string(Tuplet::getDuration(Tuplet::getSize())->getDenom());
    std::replace(tuplet_notevalue.begin(), tuplet_notevalue.end(), '0', '.');

    // exit on error
    try {
      Duration d_test (tuplet_notevalue);
    }
    catch(std::invalid_argument&) {
      return ;
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
        if (Tuplet::getNote(n)->isType(CHAR_NOTETYPE_SINGLE) && Tuplet::getNote(n)->getPitch(0)) {
          stk_wav_writer::writeSingleNote(__out, *tempo_ptr, &duration_mod,
            note_count, factor,
            stk_mandolin::selectInstrument(Tuplet::getNote(n)->getPitch(0)->toFrequency()),
            Tuplet::getNote(n)->getPitch(0), DEFAULT_AMPLITUDE);
        }
        else if (Tuplet::getNote(n)->isMute()) {
          stk_wav_writer::writeMutedNote(__out, *tempo_ptr,
            &duration_mod, note_count, factor);
        }
        // Tuplet chord
        else if (Tuplet::getNote(n)->isType(CHAR_NOTETYPE_CHORD)) {
          const Note * note_ptr = Tuplet::getNote(n);

          std::vector<const Pitch *> pitch_list;
          std::vector<double> amplitude_list;
          std::vector<stk::Instrmnt *> instrument_list;
          
          // get listed data for each pitch in the chord
          for (int i = 0; i < note_ptr->getSize(); i++) {
            if (note_ptr->getPitch(i)) {
              pitch_list.push_back(note_ptr->getPitch(i));
              instrument_list.push_back(stk_mandolin::selectInstrument(note_ptr->getPitch(i)->toFrequency()));
              amplitude_list.push_back(DEFAULT_AMPLITUDE);
            }
          }
          // write to output
          stk_wav_writer::writeChord(__out,
          *tempo_ptr, &duration_mod, note_count, factor,
            pitch_list, instrument_list, amplitude_list);
        }
      }
    }
  }
}

} // namespace synth
} // namespace hautbois
