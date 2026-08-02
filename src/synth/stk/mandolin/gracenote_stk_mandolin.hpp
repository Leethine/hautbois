#pragma once

#ifndef GRACENOTE_STK_MANDOLIN_HPP
#define GRACENOTE_STK_MANDOLIN_HPP

#include "../../../note/grace_note.hpp"

namespace hautbois {
namespace synth {

class GraceNoteStkMandolin : public GraceNote {

public:

  GraceNoteStkMandolin(const std::vector<std::string>& __grace_notes,
                       const std::string& __pitch, const std::string& __value);

  GraceNoteStkMandolin(const GraceNote& __other);

  GraceNoteStkMandolin(const GraceNote&& __other);

  virtual ~GraceNoteStkMandolin();

  virtual void toStream(void * __output, void * __param1, void * __param2, void * __param3) const;

};

} // namespace synth
} // namespace hautbois

#endif
