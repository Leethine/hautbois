#include "chord.hpp"
#include "../hbtype/hbdefs.hpp"
#include "../utility/hbexcept.hpp"
#include "note.hpp"
#include <stdexcept>
#include <utility>

namespace hautbois {

void Chord::setNoteType(const char __note_type) {
  if (__note_type == CHAR_NOTETYPE_CHORD) {
    Note::setNoteType(CHAR_NOTETYPE_CHORD);
  }
}

Chord::Chord(const std::vector<std::string>& __pitch, const std::string& __value) :
  Note(CHAR_NOTETYPE_CHORD) {

  Duration * d_ptr = nullptr;
  HB_NESTED_THROW_MSG(std::invalid_argument,
    std::string("Failed to create chord") ,
    d_ptr = new Duration(__value);
  )
  Chord::setDuration(d_ptr, NOTE_SET_METHOD_APPEND_POS);

  std::vector<Pitch *> temp_pitch;
  for (auto& str: __pitch) {
    HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
      std::string("Failed to create chord.") ,
      temp_pitch.push_back(new Pitch(str)); ,
      for (Pitch * p : temp_pitch) {
        delete p;
      }
    )
  }
  // Call addPitch method
  for (Pitch * p : temp_pitch) {
    Chord::setPitch(p, NOTE_SET_METHOD_APPEND_POS);
    Chord::setProperty(nullptr, NOTE_SET_METHOD_APPEND_POS);
  }
}

Chord::Chord(const Chord& __other) : Chord(std::forward<const Chord&&>(__other)) {
}

Chord::Chord(const Chord&& __other) : Note(CHAR_NOTETYPE_CHORD) {
  // Process note value
  Duration * d_ptr = nullptr;
  if (__other.getDuration()) {
    HB_NESTED_THROW_MSG(std::invalid_argument,
      std::string("Failed to copy construct chord") ,
      d_ptr = new Duration(__other.getDuration()->toString());
    )
    Chord::setDuration(d_ptr, NOTE_SET_METHOD_APPEND_POS);
  }

  // process pitch
  std::vector<Pitch *> temp_pitch;
  for (int i = 0; i < __other.getSize(); i++) {
    if (__other.getPitch(i)) {
      HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
        std::string("Failed to copy construct chord.") ,
        temp_pitch.push_back(new Pitch(__other.getPitch(i)->toString())); ,
        for (Pitch * p : temp_pitch) {
          delete p;
        }
      )
    }
    else {
      HB_THROW_MSG(std::runtime_error,
        std::string("Run time error occurred while calling chord copy constructor."));
    }
  }
  // Call addPitch method
  for (Pitch * p : temp_pitch) {
    Chord::setPitch(p, NOTE_SET_METHOD_APPEND_POS);
  }
  // process ties
  for (int i = 0; i < __other.getSize(); i++) {
    if (__other.isTied(i)) {
      Chord::makeTie(i);
    }
  }

  // Process property
  for (int i = 0; i < Chord::getSize(); i++) {
    if (__other.getProperty(i)) {
      Chord::setProperty(new Property(__other.getProperty(i)->toString()), NOTE_SET_METHOD_APPEND_POS);
    }
    else {
      Chord::setProperty(nullptr, NOTE_SET_METHOD_APPEND_POS);
    }
  }
}

void Chord::addProperty(const std::string& __property, const int __pos) {
  Property * ptr = new Property(__property);
  Chord::setProperty(ptr, __pos);
}

int Chord::getSize() const {
  int count = 0;
  while(Chord::getPitch(count)) {
    count++;
  }
  return count;
}

bool Chord::isValid() const {
  if (Chord::getDuration(0) == nullptr) {
    return false;
  }
  int s = Chord::getSize();
  for (int i = 0; i < s; i++) {
    if (Chord::getPitch(i) == nullptr) {
      return false;
    }
  }
  return true;
}

void Chord::transpose(const int __degree, const std::string& __tonality, const std::string& __mode) {
  int s = Chord::getSize();
  for (int i = 0; i < s; i++) {
    if (Chord::getPitchModify(i)) {
      Chord::getPitchModify(i)->transpose(__degree, __tonality, __mode);
    }
  }
}

void Chord::enlarge(const int __factor) {
  if (Chord::getDurationModify(0)) {
    Chord::getDurationModify(0)->multiply(__factor);
  }
}

void Chord::reduce(const int __factor) {
  if (Chord::getDurationModify(0)) {
    Chord::getDurationModify(0)->divide(__factor);
  }
}

std::string Chord::toString() const {
  std::string out;
  int s = Chord::getSize();
  for (int i = 0; i < s; i++) {
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
  if (!out.empty() && out.back() == '+') {
    out.pop_back();
    out.push_back(',');
  }
  if (Chord::getDuration(0)) {
    out.append(Chord::getDuration(0)->toString());
  }
  else {
    out.push_back('?');
  }

  bool hasProperty = false;
  std::string propertyStr;
  for (int i = 0; i < s; i++) {
    if (Chord::getProperty(i)) {
      propertyStr.append(Chord::getProperty(i)->toString());
      hasProperty = true;
    }
    propertyStr.push_back(',');
  }
  if (!propertyStr.empty() && propertyStr.back() == ',') {
    propertyStr.pop_back();
  }

  if (hasProperty) {
    out.append(",[");
    out.append(propertyStr);
    out.push_back(']');
  }

  return out;
}

void * Chord::toStream(void * __output, void * __param) const {
  // TODO
  return nullptr;
}

void * Chord::serialize(const int __version, void * __param) const {
  // TODO
  return nullptr;
}

} // namespace hautbois