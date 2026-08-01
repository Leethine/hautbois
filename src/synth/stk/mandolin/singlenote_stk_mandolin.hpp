#pragma once

#ifndef SINGLE_NOTE_STK_MANDOLIN_HPP
#define SINGLE_NOTE_STK_MANDOLIN_HPP

#include "../../../note/single_note.hpp"

namespace hautbois {
namespace synth {

class SingleNoteStkMandolin : public SingleNote {

public:

  SingleNoteStkMandolin(const std::string& __pitch, const std::string& __value);

  SingleNoteStkMandolin(const SingleNote& __other);

  SingleNoteStkMandolin(const SingleNote&& __other);

  virtual ~SingleNoteStkMandolin();

  virtual void toStream(void * __output, void * __param1, void * __param2, void * __param3) const;

};

} // namespace synth
} // namespace hautbois

#endif
