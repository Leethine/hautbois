#include "single_note.hpp"
#include "note.hpp"
#include "../hbtype/hbdefs.hpp"
#include "../utility/hbexcept.hpp"
#include <cstddef>
#include <stdexcept>

namespace hautbois {

void SingleNote::setNoteType(const char __note_type) {
  if (__note_type == CHAR_NOTETYPE_SINGLE ||
      __note_type == CHAR_NOTETYPE_REST ||
      __note_type == CHAR_NOTETYPE_SILENCE) {
    Note::setNoteType(__note_type);
  }
}

SingleNote::SingleNote(const std::string& __pitch, const std::string& __value) :
  Note(CHAR_NOTETYPE_SINGLE) {

  // create note value
  Duration * ptr1 = nullptr;
  HB_NESTED_THROW_MSG(std::invalid_argument ,
    std::string("Failed to create note.") ,
    ptr1 = new Duration(__value);
  )
  SingleNote::setDuration(ptr1, NOTE_SET_METHOD_APPEND_POS);

  // create pitch
  if (__pitch == "R") {
    SingleNote::setNoteType(CHAR_NOTETYPE_REST);
  }
  else if (__pitch == "S") {
    SingleNote::setNoteType(CHAR_NOTETYPE_SILENCE);
  }
  else {
    Pitch * ptr2 = nullptr;
    HB_NESTED_THROW_MSG_ACTION(std::invalid_argument  ,
      std::string("Failed to created note.") ,
      ptr2 = new Pitch(__pitch); ,
      SingleNote::setDuration(nullptr, 0);
    )
    SingleNote::setPitch(ptr2, NOTE_SET_METHOD_APPEND_POS);
  }
}

int SingleNote::getSize() const {
  return 1;
}

bool SingleNote::isValid() const {
  // TODO
  return false;
}

void SingleNote::transpose(const int __degree, const std::string& __tonality, const std::string& __mode) {
  // TODO
}

void SingleNote::enlarge(const int __factor) {
  // TODO
}

void SingleNote::reduce(const int __factor) {
  // TODO
}

void SingleNote::expand(const void * __param) {
  // TODO
}

std::string SingleNote::toString() const {
  // TODO
  return "";
}

void * SingleNote::toStream(void * __output, void * __param) const {
  // TODO
  return nullptr;
}

void * SingleNote::serialize(const int __version, void * __param) const {
  // TODO
  return nullptr;
}

} // namespace hautbois