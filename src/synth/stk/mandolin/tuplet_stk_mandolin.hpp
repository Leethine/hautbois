#pragma once

#ifndef TUPLET_STK_MANDOLIN_HPP
#define TUPLET_STK_MANDOLIN_HPP

#include "../../../note/tuplet.hpp"

namespace hautbois {
namespace synth {

class TupletStkMandolin : public Tuplet {

public:

  TupletStkMandolin(const size_t __total, const size_t __value, const std::vector<std::string>& __notes);

  TupletStkMandolin(const Tuplet& __other);

  TupletStkMandolin(const Tuplet&& __other);

  virtual ~TupletStkMandolin();

  virtual void toStream(void * __output, void * __param1, void * __param2, void * __param3) const;

};

} // namespace synth
} // namespace hautbois

#endif
