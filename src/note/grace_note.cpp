#include "grace_note.hpp"
#include "../hbtype/hbdefs.hpp"
#include "../utility/hbexcept.hpp"
#include "note.hpp"
#include <stdexcept>
#include <utility>

namespace hautbois {

GraceNote::GraceNote(
  const std::vector<std::string>& __grace_notes, const std::string& __pitch,
  const std::string& __value) : Note(CHAR_NOTETYPE_GRACE) {

  // Process main pitch and duration
  Pitch * ptr1 = nullptr;
  Duration * ptr2 = nullptr;
  HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
    "Cannot create grace note, bad pitch str: " + __pitch,
    ptr1 = new Pitch(__pitch); ,
    // clean up already allocated memory
    delete ptr1; delete ptr2;
  )
  HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
    "Cannot create grace note, bad note value: " + __value,
    ptr2 = new Duration(__value); ,
    // clean up already allocated memory
    delete ptr1; delete ptr2;
  )

  // Process grace note pitch and duration
  std::vector<Pitch *> ptr_pitch;
  std::vector<Duration *> ptr_duration;
  bool __switch = true;
  for (const auto& str : __grace_notes) {
    if (__switch) {
      HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
        "Cannot create grace note, bad pitch str: " + str,
        ptr_pitch.push_back(new Pitch(str)); ,
        // clean up already allocated memory
        for (Pitch * p : ptr_pitch) { delete p; }
        for (Duration * d : ptr_duration) { delete d; }
        delete ptr1; delete ptr2;
      )
      __switch = false;
    }
    else {
      HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
        "Cannot create grace note, bad note value: " + str,
        ptr_duration.push_back(new Duration(str)); ,
        // clean up already allocated memory
        for (Pitch * p : ptr_pitch) { delete p; }
        for (Duration * d : ptr_duration) { delete d; }
        delete ptr1; delete ptr2;
      )
      __switch = true;
    }
  }

  // call set method add ptr to the object
  for (Pitch * p : ptr_pitch) {
    Note::setPitch(p, NOTE_SET_METHOD_APPEND_POS);
    Note::setProperty(nullptr, NOTE_SET_METHOD_APPEND_POS);
  }
  for (Duration * d : ptr_duration) {
    Note::setDuration(d, NOTE_SET_METHOD_APPEND_POS);
  }
  Note::setPitch(ptr1, NOTE_SET_METHOD_APPEND_POS);
  Note::setDuration(ptr2, NOTE_SET_METHOD_APPEND_POS);
  Note::setProperty(nullptr, NOTE_SET_METHOD_APPEND_POS);
}

GraceNote::GraceNote(const GraceNote& __other) : 
  GraceNote(std::forward<const GraceNote&&>(__other)) {
}

GraceNote::GraceNote(const GraceNote&& __other) : Note(__other.getType()) {

  // Process pitch and duration
  std::vector<Pitch *> ptr_pitch;
  std::vector<Duration *> ptr_duration;
  std::vector<Property *> ptr_property;
  for (int i = 0; i < __other.getSize(); i++) {
    if (__other.getPitch(i)) {
      HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
        "Failed to copy grace note: " + __other.getPitch(i)->toString(),
        ptr_pitch.push_back(new Pitch(__other.getPitch(i)->toString())); ,
        // clean up already allocated memory
        for (Pitch * p : ptr_pitch) { delete p; }
        for (Duration * d : ptr_duration) { delete d; }
      )
    }
    if (__other.getDuration(i)) {
      HB_NESTED_THROW_MSG_ACTION(std::invalid_argument,
        "Failed to copy grace note: " + __other.getDuration(i)->toString(),
        ptr_duration.push_back(new Duration(__other.getDuration(i)->toString())); ,
        // clean up already allocated memory
        for (Pitch * p : ptr_pitch) { delete p; }
        for (Duration * d : ptr_duration) { delete d; }
      )
    }
    // process property
    if (__other.getProperty(i) && !__other.getProperty(i)->toString().empty()) {
      ptr_property.push_back(new Property(__other.getProperty(i)->toString()));
    }
    else {
      ptr_property.push_back(nullptr);
    }
  }

  // call set method add ptr to the object
  for (Pitch * p : ptr_pitch) {
    Note::setPitch(p, NOTE_SET_METHOD_APPEND_POS);
  }
  for (Duration * d : ptr_duration) {
    Note::setDuration(d, NOTE_SET_METHOD_APPEND_POS);
  }
  for (Property * p : ptr_property) {
    Note::setProperty(p, NOTE_SET_METHOD_APPEND_POS);
  }
  
  for (int i = 0; i < __other.getSize(); i++) {
    if (__other.isTied(i)) {
      GraceNote::makeTie(i);
    }
  }
}

void GraceNote::addProperty(const std::string& __property, const int __pos) {
  if (__property == "appoggiatura" || __property == "APPOGGIATURA") {
    Note::setNoteType(CHAR_NOTETYPE_APPOGGIATURA);
  }
  else if (__property == "acciaccatura" || __property == "ACCIACCATURA") {
    Note::setNoteType(CHAR_NOTETYPE_ACCIACCATURA);
  }
  else {
    Property * ptr = new Property(__property);
    Note::setProperty(ptr, __pos);
  }
}

int GraceNote::getSize() const {
  int count = 0;
  while(GraceNote::getPitch(count)) {
    count++;
  }
  return count;
}

bool GraceNote::isValid() const {
  int count = 0;
  while(GraceNote::getDuration(count)) {
    count++;
  }
  return count == GraceNote::getSize();
}

void GraceNote::transpose(const int __degree, const std::string& __tonality, const std::string& __mode) {
  for (int i = 0; i < GraceNote::getSize(); i++) {
    if (Note::getNoteModify(i)) {
      Note::getNoteModify(i)->transpose(__degree, __tonality, __mode);
    }
  }
}

void GraceNote::enlarge(const int __factor) {
  int i = GraceNote::getSize() - 1;
  if (Note::getDurationModify(i)) {
    Note::getDurationModify(i)->multiply(__factor);
  }
}

void GraceNote::reduce(const int __factor) {
  int i = GraceNote::getSize() - 1;
  if (Note::getDurationModify(i)) {
    Note::getDurationModify(i)->divide(__factor);
  }
}

std::string GraceNote::toString() const {
  std::string out;
  std::string propertyStr;
  bool hasProperty = false;
  for (int i = 0; i < GraceNote::getSize(); i++) {
    if (GraceNote::getPitch(i)) {
      out.append(Note::getPitch(i)->toString());
      if (GraceNote::isTied(i)) {
        out.push_back('~');
      }
    }
    else {
      out.push_back('?');
    }
    out.push_back(',');
    // __
    if (GraceNote::getDuration(i)) {
      out.append(Note::getDuration(i)->toString());
    }
    else {
      out.push_back('?');
    }
    out.push_back(',');
    // _
    if (GraceNote::getProperty(i)) {
      hasProperty = true;
      propertyStr.append(GraceNote::getProperty(i)->toString());
    }
    propertyStr.push_back(',');
  }

  if (!out.empty() && out.back() == ',') {
    out.pop_back();
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

void * GraceNote::toStream(void * __output, void * __param) const {
  // TODO
  return nullptr;
}

void * GraceNote::serialize(const int __version, void * __param) const {
  // TODO
  return nullptr;
}


} // namespace hautbois