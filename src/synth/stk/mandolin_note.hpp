#pragma once

#ifndef STK_MANDOLIN_NOTE_HPP
#define STK_MANDOLIN_NOTE_HPP

#include "../../note/single_note.hpp"
#include "../../note/chord.hpp"
#include "../../note/grace_note.hpp"
#include "../../note/tuplet.hpp"

#define STK_MANDOLIN_NOTE synth::SingleNoteStkMandolin,synth::ChordStkMandolin,synth::GraceNoteStkMandolin,synth::TupletStkMandolin

namespace hautbois {
namespace synth {

// SingleNote
class SingleNoteStkMandolin : public SingleNote {
public:

  inline SingleNoteStkMandolin(const std::string& __pitch, const std::string& __value) :
    SingleNote(__pitch, __value) {}

  inline SingleNoteStkMandolin(const SingleNote& __other) : SingleNote(__other) {}

  inline SingleNoteStkMandolin(const SingleNote&& __other) : SingleNote(__other) {}

  inline virtual ~SingleNoteStkMandolin() {}

  virtual void toStream(void * __output, void * __param1, void * __param2, void * __param3) const;
};


// Chord
class ChordStkMandolin : public Chord {
public:

  inline ChordStkMandolin(const std::vector<std::string>& __pitch, const std::string& __value) :
    Chord(__pitch, __value) {}

  inline ChordStkMandolin(const Chord& __other) : Chord(__other) {}

  inline ChordStkMandolin(const Chord&& __other) : Chord(__other) {}

  inline virtual ~ChordStkMandolin() {}

  virtual void toStream(void * __output, void * __param1, void * __param2, void * __param3) const;
};


// GraceNote
class GraceNoteStkMandolin : public GraceNote {
public:

  inline GraceNoteStkMandolin(const std::vector<std::string>& __grace_notes,
                              const std::string& __pitch, const std::string& __value) :
    GraceNote(__grace_notes, __pitch, __value) {}

  inline GraceNoteStkMandolin(const GraceNote& __other) : GraceNote(__other) {}

  inline GraceNoteStkMandolin(const GraceNote&& __other) : GraceNote(__other) {}

  inline virtual ~GraceNoteStkMandolin() {}

  virtual void toStream(void * __output, void * __param1, void * __param2, void * __param3) const;
};


// Tuplet
class TupletStkMandolin : public Tuplet {
public:

  inline TupletStkMandolin(const size_t __total, const size_t __value, const std::vector<std::string>& __notes) :
    Tuplet(__total, __value, __notes) {}

  inline TupletStkMandolin(const Tuplet& __other) : Tuplet(__other) {}

  inline TupletStkMandolin(const Tuplet&& __other) : Tuplet(__other) {}

  inline virtual ~TupletStkMandolin() {}

  virtual void toStream(void * __output, void * __param1, void * __param2, void * __param3) const;
};

} // namespace synth
} // namespace hautbois

#endif