#include "single_note.hpp"
#include "note.hpp"
#include "../hbtype/hbdefs.hpp"
#include "../utility/hbexcept.hpp"
#include <stdexcept>
#include <utility>

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

  // create empty property
  SingleNote::setProperty(nullptr, NOTE_SET_METHOD_APPEND_POS);
}

SingleNote::SingleNote(const SingleNote& __other) :
  SingleNote(std::forward<const SingleNote&&>(__other)) {
}

SingleNote::SingleNote(const SingleNote&& __other) : Note(CHAR_NOTETYPE_SINGLE) {
  // Process note value
  if (__other.getDuration()) {
    Duration * ptr = nullptr;
    HB_NESTED_THROW_MSG(std::invalid_argument ,
      std::string("Failed to call copy constructor.") ,
      ptr = new Duration(__other.getDuration()->toString());
    )
    SingleNote::setDuration(ptr, NOTE_SET_METHOD_APPEND_POS);
  }
  // Process Pitch
  if (__other.getPitch()) {
    Pitch * ptr = nullptr;
    HB_NESTED_THROW_MSG(std::invalid_argument ,
      std::string("Failed to call copy constructor.") ,
      ptr = new Pitch(__other.getPitch()->toString());
    )
    SingleNote::setPitch(ptr, NOTE_SET_METHOD_APPEND_POS);
    if (__other.isTied()) {
      SingleNote::makeTie();
    }
  }
  else if (__other.isType(CHAR_NOTETYPE_REST) || __other.isType(CHAR_NOTETYPE_SILENCE)) {
    SingleNote::setNoteType(__other.getType());
  }
  else {
    HB_THROW_MSG(std::runtime_error, "Error occurred while processing pitch, failed to copy note.");
  }
  // Process property
  Property * ptr = nullptr;
  if (__other.getProperty()) {
    ptr = new Property(__other.getProperty()->toString());  
  }
  SingleNote::setProperty(ptr, NOTE_SET_METHOD_APPEND_POS);
}

void SingleNote::addProperty(const std::string& __property, const int __pos) {
  Property * ptr = new Property(__property);
  SingleNote::setProperty(ptr, 0);
}

int SingleNote::getSize() const {
  return 1;
}

bool SingleNote::isValid() const {
  if (SingleNote::isType(CHAR_NOTETYPE_SINGLE) && 
      SingleNote::getPitch(0) != nullptr && SingleNote::getDuration(0) != nullptr) {
    return true;
  }
  else if ((SingleNote::isType(CHAR_NOTETYPE_SILENCE) || SingleNote::isType(CHAR_NOTETYPE_REST)) &&
            SingleNote::getDuration(0) != nullptr && SingleNote::getPitch(0) != nullptr) {
    return true;
  }

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
  std::string out;
  if (SingleNote::isType(CHAR_NOTETYPE_REST) || SingleNote::isType(CHAR_NOTETYPE_SILENCE)) {
    out.push_back(SingleNote::getType());
  }
  else if (SingleNote::getPitch()) {
    out.append(SingleNote::getPitch()->toString());
    if (SingleNote::isTied()) {
      out.push_back('~');
    }
  }
  else {
    out.push_back('?');
  }
  out.push_back(',');

  if (SingleNote::getDuration()) {
    out.append(SingleNote::getDuration()->toString());
  }
  else {
    out.push_back('?');
  }

  if (SingleNote::getProperty()) {
    out.push_back(',');
    out.push_back('[');
    out.append(SingleNote::getProperty()->toString());
    out.push_back(']');
  }

  return out;
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