#include "note_sequence.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "utility/hbexcept.hpp"

#include <vector>
#include <string>
#include <cstring>
#include <initializer_list>

namespace hautbois {
namespace core {

void NoteSequence::addPitch(Pitch *__p) {
  NoteGroup::addPitch(__p);
}

void NoteSequence::setPitch(Pitch * __p) {
  if (__p) {
    delete _pitch;
    _pitch = __p;
    _tied = false;
  }
}

void NoteSequence::addDuration(Duration *__d) {
  if (__d) {
    _durationList.push_back(__d);
  }
}

void NoteSequence::addProperty(Property *__p) {
  if (__p) {
    _propertyList.push_back(__p);
  }
}

void NoteSequence::setProperty(Property *__p) {
  NoteGroup::setProperty(__p);
}

Pitch * NoteSequence::getPitchToModify(int pos) {
  return NoteGroup::getPitchToModify(pos);
}

Duration * NoteSequence::getDurationToModify(int pos) {
  if (pos < 0 || _durationList.empty()) {
    return NoteGroup::getDurationToModify(0);
  }
  else {
    if (pos >= _durationList.size()) {
      return _durationList.back();
    }
    else {
      return _durationList[pos];
    }
  }
}

Property * NoteSequence::getPropertyToModify(int pos) {
  if (pos < 0 || _propertyList.empty()) {
    return NoteGroup::getPropertyToModify(0);
  }
  else {
    if (pos >= _propertyList.size()) {
      return _propertyList.back();
    }
    else {
      return _propertyList[pos];
    }
  }
}

void NoteSequence::clearPitch() {
  delete _pitch;
  _pitch = nullptr;
  _tied = false;
  NoteGroup::clearPitch();
}

void NoteSequence::clearDuration() {
  NoteGroup::clearDuration();
  for (auto it = _durationList.begin(); it != _durationList.end(); it++) {
    delete (*it);
  }
  _durationList.clear();
}

void NoteSequence::clearProperty() {
  NoteGroup::clearProperty();
  for (auto it = _propertyList.begin(); it != _propertyList.end(); it++) {
    delete (*it);
  }
  _propertyList.clear();
}

NoteSequence::NoteSequence(NoteType __type, const unsigned int __count) :
  NoteGroup(__type), _durationList {}, _propertyList {}, 
  _pitch ( nullptr ), _tied ( false ), _noteCount (__count) {  
}

NoteSequence::NoteSequence(const char * __pitch, const char * __duration,
                           const std::initializer_list<const char *> __args,
                           NoteType __type, const unsigned int __count) :
    NoteSequence(__type, __count) {
  //TODO
}

NoteSequence::NoteSequence(const std::string& __pitch, const std::string& __duration,
                           const std::vector<std::string>& __args,
                           NoteType __type, const unsigned int __count) :
    NoteSequence(__type, __count) {
  //TODO
}


} // namespace core
} // namespace hautbois
