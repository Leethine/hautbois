#include "single_note.hpp"
#include "../hbtype/hbdefs.hpp"
#include "../utility/hbexcept.hpp"
#include <stdexcept>
#include <utility>

namespace hautbois {
SingleNote::
SingleNote::SingleNote(const std::string& __pitch, const std::string& __value) :
  Note(CHAR_NOTETYPE_SINGLE) {

  Duration * ptr1 = nullptr;
  Pitch    * ptr2 = nullptr;

  // create note value
  HB_NESTED_THROW_MSG(std::invalid_argument ,
    "Failed to create note with Value: " + __value ,
    ptr1 = new Duration(__value);
  )

  // create pitch
  if (__pitch == "R") {
    Note::setNoteType(CHAR_NOTETYPE_REST);
  }
  else if (__pitch == "S") {
    Note::setNoteType(CHAR_NOTETYPE_SILENCE);
  }
  else {
    HB_NESTED_THROW_MSG_ACTION(std::invalid_argument  ,
      "Failed to created note with Pitch: " + __pitch ,
      ptr2 = new Pitch(__pitch); ,
      delete ptr1;
    )
  }

  // set created pitch and duration
  Note::setDuration(ptr1);
  Note::setPitch(ptr2);

  // create empty property
  Note::setProperty(nullptr);
}

SingleNote::SingleNote(const SingleNote& __other) :
  SingleNote(std::forward<const SingleNote&&>(__other)) {
}

SingleNote::SingleNote(const SingleNote&& __other) : Note(CHAR_NOTETYPE_SINGLE) {
  Duration * ptr1 = nullptr;
  Pitch * ptr2 = nullptr;
  Property * ptr3 = nullptr;

  // Copy note type
  if (__other.isType(CHAR_NOTETYPE_REST) || __other.isType(CHAR_NOTETYPE_SILENCE)) {
    Note::setNoteType(__other.getType());
  }

  // Copy note value
  if (__other.getDuration(0)) {
    HB_NESTED_THROW_MSG(std::invalid_argument ,
      std::string("Failed to call copy constructor.") ,
      ptr1 = new Duration(__other.getDuration()->toString());
    )
  }

  // Copy Pitch
  if (__other.getPitch(0)) {
    HB_NESTED_THROW_MSG_ACTION(std::invalid_argument ,
      std::string("Failed to call copy constructor.") ,
      ptr2 = new Pitch(__other.getPitch()->toString()); ,
      delete ptr1;
    )
  }

  // Copy property
  if (__other.getProperty(0)) {
    ptr3 = new Property(__other.getProperty(0)->toString());  
  }

  Note::setDuration(ptr1);
  Note::setPitch(ptr2);
  Note::setProperty(ptr3);

  // Process tie
  if (__other.isTied(0)) {
    SingleNote::makeTie(0);
  }
}

void SingleNote::makeTie(const size_t __pos) {
  Note::setTie(true);
}

void SingleNote::makeUntie(const size_t __pos) {
  Note::setTie(false);
}

bool SingleNote::isValid() const {
  /* Validity conditions:
   * 1. _duration != nullptr
   * 2.
   *   Note type is SINGLE and _pitch != nullptr
   * Or,
   *   Note type is Mute (REST or SILENCE) and _pitch == nullptr
   */
  if (SingleNote::isType(CHAR_NOTETYPE_SINGLE) && 
      SingleNote::getPitch(0) && SingleNote::getDuration(0)) {
    return true;
  }
  else if ((SingleNote::isType(CHAR_NOTETYPE_SILENCE) ||
            SingleNote::isType(CHAR_NOTETYPE_REST)) &&
            SingleNote::getDuration(0)) {
    return true;
  }

  return false;
}

void SingleNote::addProperty(const std::string& __property, const int __pos) {
  if (__property.empty()) {
    // "wipe-off" by setting empty str
    Note::setProperty(nullptr);  
  }
  else {
    Property * ptr = new Property(__property);
    Note::setProperty(ptr);
  }
}

void SingleNote::transpose(const int __degree, const std::string& __tonality, const std::string& __mode) {
  if (Note::getPitchModify()) {
    Note::getPitchModify()->transpose(__degree, __tonality, __mode);
  }
}

void SingleNote::enlarge(const int __factor) {
  if (Note::getDurationModify()) {
    Note::getDurationModify()->multiply(__factor);
  }
}

void SingleNote::reduce(const int __factor) {
  if (Note::getDurationModify()) {
    Note::getDurationModify()->divide(__factor);
  }
}

std::string SingleNote::toString() const {
  std::string out;
  if (SingleNote::isMute()) {
    out.push_back(SingleNote::getType());
  }
  else if (SingleNote::getPitch(0)) {
    out.append(SingleNote::getPitch(0)->toString());
    if (SingleNote::isTied(0)) {
      out.push_back('~');
    }
  }
  else {
    out.push_back('?');
  }
  out.push_back(',');

  if (SingleNote::getDuration(0)) {
    out.append(SingleNote::getDuration(0)->toString());
  }
  else {
    out.push_back('?');
  }

  if (SingleNote::getProperty(0)) {
    out.push_back(',');
    out.push_back('[');
    out.append(SingleNote::getProperty(0)->toString());
    out.push_back(']');
  }

  return out;
}

void SingleNote::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  // not implemented in base class
}

void * SingleNote::serialize(const int __version, void * __param) const {
  // not implemented in base class
  return nullptr;
}

} // namespace hautbois