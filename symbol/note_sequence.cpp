#include "note_sequence.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "utility/hbexcept.hpp"

#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cctype>
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

void NoteSequence::addDuration(Duration * __d) {
  if (__d) {
    _durationList.push_back(__d);
  }
}

void NoteSequence::addProperty(Property * __p) {
  _propertyList.push_back(__p);
}

void NoteSequence::setProperty(Property * __p) {
  NoteGroup::setProperty(__p);
}

Pitch * NoteSequence::getPitchToModify(int pos) {
  if (pos < 0) {
    return _pitch;
  }
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


NoteSequence::NoteSequence(const char * __pitch, const char * __duration,
                           NoteType __type, const unsigned int __count) :
    NoteGroup(__type), _durationList {}, _propertyList {}, 
    _pitch ( nullptr ), _tied ( false ), _noteCount (__count) {
  // process const char * __pitch
  if (__pitch != nullptr && std::strlen(__pitch) > 0) {
    char name    = CHAR_PITCHNAME_SILENCE;
    char acc     = CHAR_ACCIDENTAL_NATURAL;
    char oct     = CHAR_OCTAVE_DEFAULT;
    if (std::strlen(__pitch) == 3) {
      name = __pitch[0]; acc = __pitch[1]; oct = __pitch[2]; }
    else if (std::strlen(__pitch) == 2) {
      name = __pitch[0]; oct = __pitch[1]; }
    else if (std::strlen(__pitch) == 1) {
      name = __pitch[0]; }
    else { // pitch must be 1 to 3 length
      HB_THROW_MSG(std::invalid_argument,
                  std::string("Invalid pitch: ") + std::string(__pitch));
    }
    Pitch * p = nullptr;
    HB_NESTED_THROW_MSG(std::invalid_argument,
      std::string("Failed to read pitch: " + std::string(__pitch)),
      p = new Pitch(name, acc, oct - '0');
    )
    NoteSequence::setPitch(p);
  }
  // Process const char * __duration
  if (__duration != nullptr && std::strlen(__duration) > 0) {
    for (int i=0; i<std::strlen(__duration); i++) { // check duration must be digits
      if (!std::isdigit(__duration[i])) {
        HB_THROW_MSG(std::invalid_argument,
        std::string("Duration token must be digits, not: " + std::string(__duration)));
      }
    }
    Duration * d = nullptr;
    HB_NESTED_THROW_MSG(std::invalid_argument,
      std::string("Failed to read duration: " + std::string(__duration)),
      d = new Duration(std::atoi(__duration));
    )
    NoteGroup::setDuration(d);
  }
}


NoteSequence::NoteSequence(const std::string& __pitch, const std::string& __duration,
                           NoteType __type, const unsigned int __count) :
    NoteGroup(__type), _durationList {}, _propertyList {}, 
    _pitch ( nullptr ), _tied ( false ), _noteCount (__count) {
  if (! __pitch.empty()) {
    char name    = CHAR_PITCHNAME_SILENCE;
    char acc     = CHAR_ACCIDENTAL_NATURAL;
    char oct     = CHAR_OCTAVE_DEFAULT;
    if (__pitch.size() == 3) {
      name = __pitch[0]; acc = __pitch[1]; oct = __pitch[2]; }
    else if (__pitch.size() == 2) {
      name = __pitch[0]; oct = __pitch[1]; }
    else if (__pitch.size() == 1) {
      name = __pitch[0]; }      
    else { // __pitch must be 1 to 3 length
      HB_THROW_MSG(std::invalid_argument,
      std::string("Invalid pitch: ") + __pitch);
    }
    Pitch * p = nullptr;
      HB_NESTED_THROW_MSG(std::invalid_argument,
      std::string("Failed to read pitch: " + __pitch),
      p = new Pitch(name, acc, oct - '0');
    )
    NoteSequence::setPitch(p);
  }

  if (! __duration.empty()) {
    int denom = 1;
    HB_NESTED_THROW_MSG(std::invalid_argument,
      std::string("Duration must be digits, not: " + __duration),
      denom = std::stoi(__duration);
    )
    catch(const std::out_of_range&) {
      HB_THROW_MSG(std::invalid_argument,
      std::string("Duration too large: " + __duration));
    }
    Duration * d = nullptr;
    HB_NESTED_THROW_MSG(std::invalid_argument,
      std::string("Failed to read duration from: " + __duration),
      d = new Duration(denom);
    )
    NoteGroup::setDuration(d);
  }
}


NoteSequence::NoteSequence(const char * __pitch, const char * __duration,
                           const std::initializer_list<const char *> __args,
                           NoteType __type, const unsigned int __count) :
    NoteSequence(__pitch, __duration, __type, __count) {
  int count = 0;
  for (auto token : __args) {
    Pitch    * p = nullptr;
    Duration * d = nullptr;
    if (++count % 2 == 1) {
      char name    = CHAR_PITCHNAME_SILENCE;
      char acc     = CHAR_ACCIDENTAL_NATURAL;
      char oct     = CHAR_OCTAVE_DEFAULT;
      if (std::strlen(token) == 3) { name = token[0]; acc = token[1]; oct = token[2]; }
      else if (std::strlen(token) == 2) { name = token[0]; oct = token[1]; }
      else if (std::strlen(token) == 1) { name = token[0]; }      
      else { // check pitch, must be 1 to 3 length
        HB_THROW_MSG(std::invalid_argument,
                     std::string("Invalid pitch token at pos 1: ") + std::string(token));
      }
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string("Failed to read token pos 1: " + std::string(token)),
        p = new Pitch(name, acc, oct - '0');
      )
      NoteSequence::addPitch(p);
      NoteSequence::addProperty(nullptr);
    }
    else {
      for (int i=0; i<std::strlen(token); i++) { // check duration must be digits
        if (!std::isdigit(token[i])) {
          HB_THROW_MSG(std::invalid_argument,
            std::string("Duration token must be digits at pos 2: " + std::string(token))
          );
        }
      }
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string("Failed to read token pos 2: " + std::string(token)),
        d = new Duration(std::atoi(token));
      )
      NoteSequence::addDuration(d);
    }
  }
}


NoteSequence::NoteSequence(const std::string& __pitch, const std::string& __duration,
                           const std::vector<std::string>& __args,
                           NoteType __type, const unsigned int __count) :
    NoteSequence(__pitch, __duration, __type, __count) {
  int count = 0;
  for (auto token : __args) {
    Pitch    * p = nullptr;
    Duration * d = nullptr;
    if (++count % 2 == 1) {
      char name    = CHAR_PITCHNAME_SILENCE;
      char acc     = CHAR_ACCIDENTAL_NATURAL;
      char oct     = CHAR_OCTAVE_DEFAULT;
      if (token.size() == 3) { name = token[0]; acc = token[1]; oct = token[2]; }
      else if (token.size() == 2) { name = token[0]; oct = token[1]; }
      else if (token.size() == 1) { name = token[0]; }      
      else { // check pitch, must be 1 to 3 length
        HB_THROW_MSG(std::invalid_argument,
                     std::string("Invalid pitch token at pos 1: ") + token);
      }
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string("Failed to read token pos 1: " + token),
        p = new Pitch(name, acc, oct - '0');
      )
      NoteSequence::addPitch(p);
      NoteSequence::addProperty(nullptr);
    }
    else {
      int denom = 1;
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string("Duration token must be digits at pos 2: " + token),
        denom = std::stoi(token);
      )
      catch(const std::out_of_range&) {
        HB_THROW_MSG(std::invalid_argument,
          std::string("Duration token too big at pos 2: " + token));
      }
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string("Failed to read token pos 2: " + token),
        d = new Duration(denom);
      )
      NoteSequence::addDuration(d);
    }
  }
}


void NoteSequence::setTied() {
  _tied = true;  
}

void NoteSequence::setTied(size_t __pos) {
  NoteGroup::setTied(__pos);
}

void NoteSequence::setUntied() {
  _tied = false;
}

void NoteSequence::setUntied(size_t __pos) {
  NoteGroup::setUntied(__pos);
}

int NoteSequence::getSize() const {
  return _noteCount;
}

bool NoteSequence::isValid() const {
  if (NoteGroup::isValid() && ! _durationList.empty() &&
      _durationList.size() == _propertyList.size()) {
    for (auto it = _durationList.cbegin(); it != _durationList.cend(); it++) {
      if ((*it) == nullptr) {
        return false;
      }
    }
    return true;
  }
  else {
    return false;
  }
}

bool NoteSequence::isTied() const {
  return _tied;
}

bool NoteSequence::isTied(size_t __pos) const {
  return NoteGroup::isTied(__pos);
}

bool NoteSequence::hasDuration() const {
  return NoteGroup::hasDuration();
}

bool NoteSequence::hasDuration(size_t __pos) const {
  if (__pos >= _durationList.size() || __pos < 0) {
    return false;
  }
  else {
    return _durationList[__pos] != nullptr;
  }
}

bool NoteSequence::hasPitch() const {
  return _pitch != nullptr;
}

bool NoteSequence::hasPitch(size_t __pos) const {
  return NoteGroup::hasPitch(__pos);
}

bool NoteSequence::hasProperty() const {
  return NoteGroup::hasProperty();
}

bool NoteSequence::hasProperty(size_t __pos) const {
  if (__pos >= _propertyList.size() || __pos < 0) {
    return false;
  }
  else {
    return _propertyList[__pos] != nullptr;
  }
}

const Duration * NoteSequence::getDuration(size_t __pos) {
  if (__pos >= _durationList.size() || __pos < 0) {
    return nullptr;
  }
  else {
    return _durationList[__pos];
  }
}

const Property * NoteSequence::getProperty(size_t __pos) const {
  if (__pos >= _propertyList.size() || __pos < 0) {
    return nullptr;
  }
  else {
    return _propertyList[__pos];
  }
}

int NoteSequence::getPitchSize() const {
  return NoteGroup::getPitchSize();
}

int NoteSequence::getDurationSize() const {
  return _durationList.size();
}

int NoteSequence::getPropertySize() const {
  return _propertyList.size();
}

} // namespace core
} // namespace hautbois
