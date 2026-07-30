#ifndef CHORD_STK_MANDOLIN_HPP
#define CHORD_STK_MANDOLIN_HPP

#include "../../../note/chord.hpp"

namespace hautbois {
namespace synth {

class ChordStkMandolin : public Chord {

public:

  ChordStkMandolin(const std::vector<std::string>& __pitch, const std::string& __value);

  ChordStkMandolin(const Chord& __other);

  ChordStkMandolin(const Chord&& __other);

  virtual ~ChordStkMandolin();

  virtual void toStream(void * __output, void * __param1, void * __param2, void * __param3) const;

};

} // namespace synth
} // namespace hautbois

#endif
