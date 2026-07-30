#include "chord.hpp"
#include "../hbtype/hbdefs.hpp"
#include "../utility/hbexcept.hpp"
#include "duration.hpp"
#include "note.hpp"
#include "property.hpp"
#include "single_note.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace hautbois {

Chord::Chord(const std::vector<std::string>& __pitch, const std::string& __value) :
  Note(CHAR_NOTETYPE_CHORD) {

  Duration * d_ptr = nullptr;
  HB_NESTED_THROW_MSG(std::invalid_argument,
    "Failed to create chord from value: " + __value ,
    d_ptr = new Duration(__value);
  )

  std::vector<Note *> tmp_notes;
  tmp_notes.reserve(10);

  for (auto& str: __pitch) {
    HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
      "Failed to create chord note from pitch: " + str
      ,
      tmp_notes.push_back(new SingleNote(str, __value));
      ,
      delete d_ptr;
      for (Note * ptr: tmp_notes) { delete ptr; }
    )
  }
  // Add notes
  for (Note * n_ptr : tmp_notes) {
    Note::setNote(n_ptr, NOTE_SETNOTE_APPEND_POS);
  }
  // Set duration
  Note::setDuration(d_ptr);
}

Chord::Chord(const Chord& __other) : Chord(std::forward<const Chord&&>(__other)) {
}

Chord::Chord(const Chord&& __other) : Note(CHAR_NOTETYPE_CHORD) {
  Duration * d_ptr = nullptr;
  std::vector<Note *> tmp_notes;

  // Copy duration
  if (__other.getDuration(0)) {
    d_ptr = new Duration(__other.getDuration(0)->getValue(), __other.getDuration(0)->getDots());
  }
  else {
    HB_THROW_MSG(std::runtime_error, std::string("Cannot copy chord, duration value missing!"));
  }

  // Copy notes
  for (int i = 0; i < __other.getSize(); i++) {
    // Make sure this is SingleNote type, only SingleNote type is allowed from other Chord
    const SingleNote * n_ptr = dynamic_cast<const SingleNote *>(__other.getNote(i));
    if (__other.getNote(i) && __other.getNote(i)->isType(CHAR_NOTETYPE_SINGLE) && n_ptr) {
      tmp_notes.push_back(new SingleNote(* n_ptr));
    }
    else {
      // clean up in case of invalid note type
      for (Note * ptr : tmp_notes) { delete ptr; }
      delete d_ptr;
      HB_THROW_MSG(std::runtime_error, std::string("Cannot copy invalid Chord!"));
    }
  }

  // set duration and notes
  Note::setDuration(d_ptr);
  for (Note * ptr : tmp_notes) {
    Note::setNote(ptr, NOTE_SETNOTE_APPEND_POS);
  }

  // add property
  if (__other.getProperty(0)) {
    Chord::addProperty(__other.getProperty(0)->toString());
  }
}

void Chord::makeTie(const size_t __pos) {
  if (__pos < (size_t) Note::getSize() && Note::getNoteModify(__pos)) {
    Note::getNoteModify(__pos)->makeTie(0);
  }
}

void Chord::makeUntie(const size_t __pos) {
  if (__pos < (size_t) Note::getSize() && Note::getNoteModify(__pos)) {
    Note::getNoteModify(__pos)->makeUntie(0);
  }
}

bool Chord::isValid() const {
  /* Validity conditions:
   *   Note::_duration != nullptr;
   *  And,
   *   each note in Note::_notes is SINGLENOTE type and is valid (has pitch)
   */
  if (Chord::getDuration(0) == nullptr) {
    return false;
  }
  for (int i = 0; i < Chord::getSize(); i++) {
    if (Chord::getNote(i) == nullptr) {
      return false;
    }
    else {
      if (!Chord::getNote(i)->isType(CHAR_NOTETYPE_SINGLE) ||
          !Chord::getNote(i)->isValid()) {
        return false;
      }
    }
  }
  return true;
}

void Chord::addProperty(const std::string& __property, const int __pos) {
  // Chord only has one global property, not on each each note
  if (__property.empty()) {
    Note::setProperty(nullptr);  
  }
  else {
    Property * ptr = new Property(__property);
    Note::setProperty(ptr);
  }
}

void Chord::transpose(const int __degree, const std::string& __tonality, const std::string& __mode) {
  for (int i = 0; i < Chord::getSize(); i++) {
    if (Note::getNoteModify(i)) {
      Note::getNoteModify(i)->transpose(__degree, __tonality, __mode);
    }
  }
}

void Chord::enlarge(const int __factor) {
  if (Note::getDurationModify()) {
    Note::getDurationModify()->multiply(__factor);
  }
}

void Chord::reduce(const int __factor) {
  if (Note::getDurationModify()) {
    Note::getDurationModify()->divide(__factor);
  }
}

std::string Chord::toString() const {
  std::string out;
  // append each pitch, separated by '+'
  for (int i = 0; i < Chord::getSize(); i++) {
    if (Chord::getPitch(i)) {
      out.append(Chord::getPitch(i)->toString());
      if (Chord::isTied(i)) {
        out.push_back('~');
      }
    }
    else {
      out.push_back('?');
    }
    out.push_back('+');
  }
  // remove excessive '+'
  if (!out.empty() && out.back() == '+') {
    out.pop_back();
    out.push_back(',');
  }
  // append note value
  if (Chord::getDuration(0)) {
    out.append(Chord::getDuration(0)->toString());
  }
  else {
    out.push_back('?');
  }

  // append property, if there is any
  bool hasProperty = false;
  std::string propertyStr;
  if (Chord::getProperty(0)) {
    propertyStr.append(Chord::getProperty(0)->toString());
    hasProperty = true;
  }
  if (hasProperty) {
    out.append(",[");
    out.append(propertyStr);
    out.push_back(']');
  }

  return out;
}

void Chord::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  // Not implemented in base class
}

void * Chord::serialize(const int __version, void * __param) const {
  // TODO
  return nullptr;
}

} // namespace hautbois