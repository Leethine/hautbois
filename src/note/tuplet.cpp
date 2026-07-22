#include "tuplet.hpp"
#include "single_note.hpp"
#include "chord.hpp"
#include "../hbtype/hbdefs.hpp"
#include "../utility/hbexcept.hpp"
#include "../utility/tools.hpp"
#include "note.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>

namespace hautbois {

Tuplet::Tuplet(const size_t __total, const size_t __value,
  const std::vector<std::string>& __notes) : Note(CHAR_NOTETYPE_TUPLET) {

  // set Tuplet size
  Note::setDuration(new Duration(__total, __value), NOTE_SET_METHOD_APPEND_POS);
  // process notes
  bool __switch = true;
  std::vector<std::string> pitch;
  std::vector<std::vector<std::string>> pitch_list;
  std::vector<std::string> notevalue_list;
  for (const auto& str : __notes) {
    if (__switch) {
      tools::splitstring(pitch, str, '+');
      if (pitch.empty()) {
        HB_THROW_MSG(
          std::invalid_argument,
          std::string("Cannot create Tuplet with empty input string"));
      }
      else {
        pitch_list.push_back(pitch);
        __switch = false;
      }
    }
    else {
      notevalue_list.push_back(str);
      __switch = true;
    }
  }

  // call set method
  if (notevalue_list.size() != pitch_list.size()) {
    HB_THROW_MSG(
      std::invalid_argument,
      std::string("Cannot create Tuplet with input string, must follow this pattern: {PITCH,VALUE,PITCH,VALUE,...}"));
  }
  else {
    std::vector<Note *> notes;
    for (size_t i = 0; i < notevalue_list.size(); i++) {
      if (pitch_list[i].size() == 1) {
        HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
          "Failed to create Tuplet, invalid input encountered: " + pitch_list[i][0] ,
          notes.push_back(new SingleNote(pitch_list[i][0], notevalue_list[i])); ,
          for (Note * n : notes) { delete n; }
        )
      }
      else if (pitch_list.size() > 1) {
        HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
          std::string("Failed to create Tuplet, invalid input encountered: CHORD"),
          notes.push_back(new Chord(pitch_list[i], notevalue_list[i])); ,
          for (Note * n : notes) { delete n; }
        )
      }
    }
    for (Note * n : notes) {
      Note::setNote(n, NOTE_SET_METHOD_APPEND_POS);
    }
  }
}

Tuplet::Tuplet(const Tuplet& __other) :
  Tuplet(std::forward<const Tuplet&&>(__other)) {
}

Tuplet::Tuplet(const Tuplet&& __other) : Note(CHAR_NOTETYPE_TUPLET) {
  if (__other.getDuration(0)) {
    Note::setDuration(new Duration(__other.getDuration(0)->getNum(), __other.getDuration(0)->getDenom()),
      NOTE_SET_METHOD_APPEND_POS);
  }
  // process notes
  std::vector<Note *> ptr_notes;
  std::vector<std::string> pitches;
  for (int i = 0; i < __other.getSize(); i++) {
    HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
      std::string("Failed to copy Tuplet.") ,

      if (__other.getNote(i) && __other.getNote(i)->getDuration(0)) {
        if (__other.getNote(i)->isType(CHAR_NOTETYPE_SINGLE) && __other.getNote(i)->getPitch(0)) {
          ptr_notes.push_back(new SingleNote(__other.getNote(i)->getPitch(0)->toString(), 
                                               __other.getNote(i)->getDuration(0)->toString()));
        }
        else if (__other.getNote(i)->isType(CHAR_NOTETYPE_REST)) {
          ptr_notes.push_back(new SingleNote("R", __other.getNote(i)->getDuration(0)->toString()));
        }
        else if (__other.getNote(i)->isType(CHAR_NOTETYPE_SILENCE)) {
          ptr_notes.push_back(new SingleNote("S", __other.getNote(i)->getDuration(0)->toString()));
        }
        else if (__other.getNote(i)->isType(CHAR_NOTETYPE_CHORD)) {
          pitches.clear();
          for (int j = 0; j < __other.getSize(); j++) {
            if (__other.getPitch(j)) {
              pitches.push_back(__other.getPitch(j)->toString());
            }
          }
          ptr_notes.push_back(new Chord(pitches, __other.getNote(i)->getDuration(0)->toString()));
        }
      }
      , // Do not delete this comma
      for (Note * n : ptr_notes) { delete n; }
    )
  }
  for (Note * n : ptr_notes) {
    Note::setNote(n, NOTE_SET_METHOD_APPEND_POS);
  }

  // Process tie and property
  for (int i = 0; i < Tuplet::getSize(); i++) {
    if (__other.getNote(i) && Note::getNoteModify(i)) {
      if (__other.getNote(i)->isTied(0)) {
        Tuplet::getNoteModify(i)->makeTie(0);
      }
      if (__other.getNote(i)->getProperty(0)) {
        Tuplet::addProperty(__other.getNote(i)->getProperty(0)->toString(), i);
      }
    }
  }
}

void Tuplet::addProperty(const std::string& __property, const int __pos) {
  if (!__property.empty() && Note::getNoteModify(__pos)) {
    Note::getNoteModify(__pos)->addProperty(__property, 0);
  }
}

int Tuplet::getSize() const {
  int count = 0;
  while (Tuplet::getNote(count)) {
    count++;
  }
  return count;
}

bool Tuplet::isValid() const {
  int base = 1;
  int factor = 1;
  if (Tuplet::getDuration(0)) {
    factor = Tuplet::getDuration(0)->getNum();
    base = Tuplet::getDuration(0)->getDenom();
  }
  Duration compare(1, base);

  Duration total_value (0,1);
  for (int i = 0; i < Tuplet::getSize(); i++) {
    if (Tuplet::getNote(i) && Tuplet::getNote(i)->getDuration(0)) {
      if (!Tuplet::getNote(i)->isValid()) {
        return false;
      }
      else {
        total_value.plus(Tuplet::getNote(i)->getDuration(0));
      }
    }
  }
  total_value.divide(factor);

  return compare.equals(&total_value);
}

void Tuplet::transpose(const int __degree, const std::string& __tonality, const std::string& __mode) {
  for (int i = 0; i < Tuplet::getSize(); i++) {
    if (Note::getNoteModify(i)) {
      Note::getNoteModify(i)->transpose(__degree, __tonality, __mode);
    }
  }
}

void Tuplet::enlarge(const int __factor) {
  int count = 1;
  int base = 1;
  if (Tuplet::getDuration(0)) {
    count = Tuplet::getDuration(0)->getNum();
    base = Tuplet::getDuration(0)->getDenom();
    base *= __factor;
  }
  if (base) {
    Note::setDuration(new Duration(count, base), 0);
  }
}

void Tuplet::reduce(const int __factor) {
  int count = 1;
  int base = 1;
  if (Tuplet::getDuration(0)) {
    count = Tuplet::getDuration(0)->getNum();
    base = Tuplet::getDuration(0)->getDenom();
    base /= __factor;
  }
  if (base) {
    Note::setDuration(new Duration(count, base), 0);
  }
}

std::string Tuplet::toString() const {
  std::string out;
  if (Tuplet::getDuration(0)) {
    out.append(std::to_string(Tuplet::getDuration(0)->getNum()));
    out.push_back('/');
    out.append(std::to_string(Tuplet::getDuration(0)->getDenom()));
    out.push_back(',');
  }
  else {
    out.append("?/?");
  }
  
  out.push_back('{');
  out.push_back(' ');
  for (int i = 0; i < Tuplet::getSize(); i++) {
    if (Tuplet::getNote(i)) {
      out.append(Tuplet::getNote(i)->toString());
      out.push_back(' ');
    }
  }
  out.push_back('}');

  return out;
}

void * Tuplet::toStream(void * __output, void * __param) const {
  // TODO
  return nullptr;
}

void * Tuplet::serialize(const int __version, void * __param) const {
  // TODO
  return nullptr;
}

} // namespace hautbois