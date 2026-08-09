#include "tuplet.hpp"
#include "duration.hpp"
#include "single_note.hpp"
#include "chord.hpp"
#include "../hbtype/hbdefs.hpp"
#include "../utility/hbexcept.hpp"
#include "../utility/tools.hpp"
#include "note.hpp"
#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>

namespace hautbois {

Tuplet::Tuplet(const size_t __total, const size_t __value,
  const std::vector<std::string>& __notes) : Note(CHAR_NOTETYPE_TUPLET) {

  // process notes, put the args in temporary lists
  bool __switch = true;
  std::vector<std::string> tmp_pitch;
  std::vector<std::vector<std::string>> tmp_pitch_list;
  std::vector<std::string> tmp_duration_list;
  for (const auto& str : __notes) {
    if (__switch) {
      tools::splitstring(tmp_pitch, str, '+');
      if (tmp_pitch.empty()) {
        HB_THROW_MSG(
          std::invalid_argument,
          std::string("Failed to create Tuplet: empty input string"));
      }
      else {
        tmp_pitch_list.push_back(tmp_pitch);
        __switch = false;
      }
    }
    else {
      tmp_duration_list.push_back(str);
      __switch = true;
    }
  }

  // check input format corectness
  if (tmp_duration_list.size() != tmp_pitch_list.size()) {
    HB_THROW_MSG(
      std::invalid_argument,
      std::string("Failed to create Tuplet, input must follow this pattern: {PITCH,VALUE,PITCH,VALUE,...}"));
  }

  // create notes and put them in temporary list
  std::vector<Note *> tmp_notes_ptr;
  tmp_notes_ptr.reserve(12);
  for (size_t i = 0; i < tmp_duration_list.size(); i++) {
    std::string& tmp_duration = tmp_duration_list[i];
    std::vector<std::string>& __pitch_list = tmp_pitch_list[i];
    if (tmp_pitch_list[i].size() == 1) {
      std::string& __pitch = tmp_pitch_list[i][0];
      HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
        "Failed to create Tuplet note, invalid note: " + __pitch + "," + tmp_duration,
        tmp_notes_ptr.push_back(new SingleNote(__pitch, tmp_duration)); ,
        for (Note * ptr : tmp_notes_ptr) { delete ptr; } // cleanup in case of error
      )
    }
    else if (tmp_pitch_list[i].size() > 1) {
      HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
        std::string("Failed to create Tuplet note: invalid CHORD"),
        tmp_notes_ptr.push_back(new Chord(__pitch_list, tmp_duration)); ,
        for (Note * ptr : tmp_notes_ptr) { delete ptr; } // cleanup
      )
    }
  }

  // Set Tuplet size (e.g. total note count such as <3,5,7,...> / total note value)
  Note::setDuration(new Duration(__total, __value));
  // call set method to append already-created note ptr
  for (Note * ptr : tmp_notes_ptr) {
    Note::setNote(ptr, NOTE_SETNOTE_APPEND_POS);
  }
}

Tuplet::Tuplet(const Tuplet& __other) :
  Tuplet(std::forward<const Tuplet&&>(__other)) {
}

Tuplet::Tuplet(const Tuplet&& __other) : Note(CHAR_NOTETYPE_TUPLET) {
  std::vector<Note *> ptr_notes;
  ptr_notes.reserve(5);
  std::string __errmsg("Cannot copy invalid Tuplet!");
  // Copy notes
  for (int i = 0; i < __other.getSize(); i++) {
    if ( __other.getNote(i) && 
        (__other.getNote(i)->isType(CHAR_NOTETYPE_SINGLE) ||
         __other.getNote(i)->isType(CHAR_NOTETYPE_REST))) {
      const SingleNote * n_ptr = dynamic_cast<const SingleNote *>(__other.getNote(i));
      if (n_ptr) {
        ptr_notes.push_back(new SingleNote(*n_ptr));
      }
      else {
        // clean up in case of invalid note type
        for (Note * ptr : ptr_notes) { delete ptr; }
        HB_THROW_MSG(std::runtime_error, __errmsg);
      }
    }
    else if (__other.getNote(i) && __other.getNote(i)->isType(CHAR_NOTETYPE_CHORD)) {
      const Chord * n_ptr = dynamic_cast<const Chord *>(__other.getNote(i));
      if (n_ptr) {
        ptr_notes.push_back(new Chord(*n_ptr));
      }
      else {
        // clean up in case of invalid note type
        for (Note * ptr : ptr_notes) { delete ptr; }
        HB_THROW_MSG(std::runtime_error, __errmsg);
      }
    }
    else {
      // clean up in case of invalid note type
      for (Note * ptr : ptr_notes) { delete ptr; }
      HB_THROW_MSG(std::runtime_error, __errmsg);
    }
  }

  // Add note ptr to its elements
  for (Note * ptr : ptr_notes) {
    Note::setNote(ptr, NOTE_SETNOTE_APPEND_POS);
  }

  // Copy duration
  int tuplet_size = __other.getSize();
  if (__other.getDuration(tuplet_size)) {
    Note::setDuration(
      new Duration(
        __other.getDuration(tuplet_size)->getNum(),
      __other.getDuration(tuplet_size)->getDenom())
    );
  }
}

void Tuplet::makeTie(const size_t __pos) {
  if (__pos < (size_t) Note::getSize() && Note::getNoteModify(__pos)) {
    Note::getNoteModify(__pos)->makeTie(0);
  }
}

void Tuplet::makeUntie(const size_t __pos) {
  if (__pos < (size_t) Note::getSize() && Note::getNoteModify(__pos)) {
    Note::getNoteModify(__pos)->makeUntie(0);
  }
}

bool Tuplet::isValid() const {
  /* Validity conditions:
   *   Size of Note::_notes must be >= 2
   *   Note::_duration is not nullptr
   *   Each note in Note::_notes is SINGLENOTE/CHORD type and is valid (has pitch and duration)
   */
  if (Tuplet::getSize() < 2) {
    return false;
  }
  if (Tuplet::getDuration(Tuplet::getSize()) == nullptr) {
    return false;
  }
  else { // validate if the tuplet total value is valid
    std::string tuplet_value = std::to_string(Tuplet::getDuration(Tuplet::getSize())->getDenom());
    std::replace(tuplet_value.begin(), tuplet_value.end(), '0','.');
    try {
      Duration d_test (tuplet_value);
    }
    catch (std::invalid_argument&) {
      return false;
    }
  }

  for (int i = 0; i < Tuplet::getSize(); i++) {
    if (Tuplet::getNote(i) == nullptr) {
      return false;
    }
    else {
      if (!(Tuplet::getNote(i)->isType(CHAR_NOTETYPE_SINGLE) || 
            Tuplet::getNote(i)->isType(CHAR_NOTETYPE_REST)   ||
            Tuplet::getNote(i)->isType(CHAR_NOTETYPE_CHORD)) 
            || !Tuplet::getNote(i)->isValid()) {
        return false;
      }
    }
  }

  return true;
}

void Tuplet::addProperty(const std::string& __property, const int __pos) {
  if (__pos < Note::getSize() && Note::getNoteModify(__pos)) {
    Note::getNoteModify(__pos)->addProperty(__property);
  }
}

void Tuplet::transpose(const int __degree, const std::string& __tonality, const std::string& __mode) {
  for (int i = 0; i < Tuplet::getSize(); i++) {
    if (Note::getNoteModify(i)) {
      Note::getNoteModify(i)->transpose(__degree, __tonality, __mode);
    }
  }
}

void Tuplet::enlarge(const int __factor) {
  // enlarge total note value
  int num = 0;
  int denom = 1;
  if (Note::getDurationModify()) {
    num   = Note::getDurationModify()->getNum();
    denom = Note::getDurationModify()->getDenom();
    denom /= __factor;
    if (denom == 0) {
      denom = 1; // cannot be zero
    }
  }
  Note::setDuration(new Duration(num, denom));

  // enlarge each note
  for (int i = 0; i < Tuplet::getSize(); i++) {
    if (Note::getNoteModify(i)) {
      Note::getNoteModify(i)->reduce(__factor);
    }
  }
}

void Tuplet::reduce(const int __factor) {
  // reduce total note value
  int num = 0;
  int denom = 1;
  if (Note::getDurationModify()) {
    num   = Note::getDurationModify()->getNum();
    denom = Note::getDurationModify()->getDenom();
  }
  Note::setDuration(new Duration(num, denom * __factor));

  // reduce each note
  for (int i = 0; i < Tuplet::getSize(); i++) {
    if (Note::getNoteModify(i)) {
      Note::getNoteModify(i)->enlarge(__factor);
    }
  }
}

std::string Tuplet::toString() const {
  std::string out;
  const int tuplet_size = Tuplet::getSize();
  // Write tuplet size
  if (Tuplet::getDuration(tuplet_size)) {
    out.append(std::to_string(Tuplet::getDuration(tuplet_size)->getNum()));
    out.push_back('/');
    std::string tuplet_value = std::to_string(Tuplet::getDuration(tuplet_size)->getDenom());
    std::replace(tuplet_value.begin(), tuplet_value.end(), '0', '.');
    out.append(tuplet_value);
    out.push_back(',');
  }
  else {
    out.append("?/?,");
  }

  // Write each note
  for (int i = 0; i < tuplet_size; i++) {
    if (Tuplet::getNote(i)) {
      out.append(Tuplet::getNote(i)->toString());
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

void Tuplet::toStream(void * __output, void * __param1, void * __param2, void * __param3) const {
  // Not implemented in base class
}

void * Tuplet::serialize(const int __version, void * __param) const {
  // TODO
  return nullptr;
}

} // namespace hautbois