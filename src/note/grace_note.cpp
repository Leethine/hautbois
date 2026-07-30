#include "grace_note.hpp"
#include "../hbtype/hbdefs.hpp"
#include "../utility/hbexcept.hpp"
#include "note.hpp"
#include "single_note.hpp"
#include <stdexcept>
#include <utility>

namespace hautbois {

GraceNote::GraceNote(
  const std::vector<std::string>& __grace_notes, const std::string& __pitch,
  const std::string& __value) : Note(CHAR_NOTETYPE_GRACE) {

  // Process grace notes pitch and duration
  std::vector<std::string> tmp_pitch;
  std::vector<std::string> tmp_duration;
  bool __switch = true;
  for (const auto& str : __grace_notes) {
    if (__switch) {
      tmp_pitch.push_back(str);
      __switch = false;
    }
    else {
      tmp_duration.push_back(str);
      __switch = true;
    }
  }
  // Process main note
  tmp_pitch.push_back(__pitch);
  tmp_duration.push_back(__value);

  // Make sure pitch and duration list is the same length
  if (tmp_pitch.size() != tmp_duration.size()) {
    HB_THROW_MSG(std::invalid_argument,
      std::string("Failed to create grace note, invalid <pitch,value> list!"));
  }

  // Create appended notes
  std::vector<Note *> ptr_notes;
  ptr_notes.reserve(5);
  for (size_t i = 0; i < tmp_pitch.size(); i++) {
    HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
      "Failed to create grace note with <pitch,value>: " + tmp_pitch[i] + "," + tmp_duration[i],
      ptr_notes.push_back(new SingleNote(tmp_pitch[i], tmp_duration[i])); ,
      // clean up previously allocated memory
      for (Note * ptr : ptr_notes) { delete ptr; }
    )
  }

  // Add note ptr to its elements
  for (Note * ptr : ptr_notes) {
    Note::setNote(ptr, NOTE_SETNOTE_APPEND_POS);
  }
}

GraceNote::GraceNote(const GraceNote& __other) : 
  GraceNote(std::forward<const GraceNote&&>(__other)) {
}

GraceNote::GraceNote(const GraceNote&& __other) : Note(__other.getType()) {
  std::vector<Note *> ptr_notes;
  ptr_notes.reserve(5);
  // Copy notes
  for (int i = 0; i < __other.getSize(); i++) {
    // Make sure this is SingleNote type, only SingleNote type is allowed from other GraceNote
    const SingleNote * n_ptr = dynamic_cast<const SingleNote *>(__other.getNote(i));
    if (__other.getNote(i) && __other.getNote(i)->isType(CHAR_NOTETYPE_SINGLE) && n_ptr) {
      ptr_notes.push_back(new SingleNote(* n_ptr));
    }
    else {
      // clean up in case of invalid note type
      for (Note * ptr : ptr_notes) { delete ptr; }
      HB_THROW_MSG(std::runtime_error, std::string("Cannot copy invalid Chord!"));
    }
  }

  // Add note ptr to its elements
  for (Note * ptr : ptr_notes) {
    Note::setNote(ptr, NOTE_SETNOTE_APPEND_POS);
  }
}

void GraceNote::makeTie(const size_t __pos) {
  if (__pos < (size_t) Note::getSize() && Note::getNoteModify(__pos)) {
    Note::getNoteModify(__pos)->makeTie(0);
  }
}

void GraceNote::makeUntie(const size_t __pos) {
  if (__pos < (size_t) Note::getSize() && Note::getNoteModify(__pos)) {
    Note::getNoteModify(__pos)->makeUntie(0);
  }
}

bool GraceNote::isValid() const {
  /* Validity conditions:
   *   Size of Note::_notes must be >= 2
   *   Each note in Note::_notes is SINGLENOTE type and is valid (has pitch and duration)
   */
  if (GraceNote::getSize() < 2) {
    return false;
  }
  for (int i = 0; i < GraceNote::getSize(); i++) {
    if (GraceNote::getNote(i) == nullptr) {
      return false;
    }
    else {
      if (!GraceNote::getNote(i)->isType(CHAR_NOTETYPE_SINGLE) ||
          !GraceNote::getNote(i)->isValid()) {
        return false;
      }
    }
  }
  return true;
}

void GraceNote::addProperty(const std::string& __property, const int __pos) {
  if (__pos < Note::getSize() && Note::getNoteModify(__pos)) {
    Note::getNoteModify(__pos)->addProperty(__property);
  }
}

void GraceNote::transpose(const int __degree, const std::string& __tonality, const std::string& __mode) {
  for (int i = 0; i < GraceNote::getSize(); i++) {
    if (Note::getNoteModify(i)) {
      Note::getNoteModify(i)->transpose(__degree, __tonality, __mode);
    }
  }
}

void GraceNote::enlarge(const int __factor) {
  for (int i = 0; i < GraceNote::getSize(); i++) {
    if (Note::getNoteModify(i)) {
      Note::getNoteModify(i)->enlarge(__factor);
    }
  }
}

void GraceNote::reduce(const int __factor) {
  for (int i = 0; i < GraceNote::getSize(); i++) {
    if (Note::getNoteModify(i)) {
      Note::getNoteModify(i)->reduce(__factor);
    }
  }
}

std::string GraceNote::toString() const {
  std::string out;
  for (int i = 0; i < GraceNote::getSize(); i++) {
    if (GraceNote::getNote(i)) {
      out.append(GraceNote::getNote(i)->toString());
      out.push_back(',');
    }
    else {
      out.append("?,");
    }
  }
  if (!out.empty() && out.back() == ',') {
    out.pop_back();
  }

  return out;
}

void GraceNote::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  // Not implemented in base class
}

void * GraceNote::serialize(const int __version, void * __param) const {
  // TODO
  return nullptr;
}

} // namespace hautbois