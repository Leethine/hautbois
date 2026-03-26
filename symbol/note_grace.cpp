#include "note_grace.hpp"
#include "note.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "../utility/hbexcept.hpp"

#include <utility>

namespace hautbois {
namespace core {

void GraceNote::setNoteType(NoteType __ntype) {
  if (__ntype == NoteType::Grace || __ntype == NoteType::Acciaccatura ||
      __ntype == NoteType::Appoggiatura) {
    Note::setNoteType(__ntype);
  }
}

void GraceNote::addPitch(Pitch * __p) {
  if (__p) {
    _pitchList.push_back(__p);
    _tieList.push_back(false);
  }
}

void GraceNote::setPitch(Pitch * __p, int __pos) {
  if (__p) {
    if (__pos < 0) {
      delete _pitch;
      _pitch = __p;
    }
    else if (__pos >= 0 && __pos < _pitchList.size()) {
      delete _pitchList[__pos];
      _pitchList[__pos] = __p;
    }
    else if (_pitchList.empty()) {
      _pitchList.push_back(__p);
    }
  }
}

void GraceNote::addDuration(Duration * __d) {
  if (__d) {
    _durationList.push_back(__d);
  }
}

void GraceNote::setDuration(Duration * __d, int __pos) {
  if (__d) {
    if (__pos < 0) {
      delete _duration;
      _duration = __d;
    }
    else if (__pos >= 0 && __pos < _durationList.size()) {
      delete _durationList[__pos];
      _durationList[__pos] = __d;
    }
    else if (_durationList.empty()) {
      _durationList.push_back(__d);
    }
  }
}

void GraceNote::addProperty(Property * __p) {
  _propertyList.push_back(__p);
}

void GraceNote::setProperty(Property * __p, int __pos) {
  if (__pos < 0) {
    delete _property;
    _property = __p;
  }
  else {
    if (__pos >= 0 && __pos < _propertyList.size()) {
      delete _propertyList[__pos];
      _propertyList[__pos] = __p;
    }
    else if (_propertyList.empty()) {
      _propertyList.push_back(__p);
    }
  }
}

Pitch * GraceNote::getPitchMod(int __pos) {
  if (__pos < 0) {
    return _pitch;
  }
  else if (__pos >= 0 && __pos < _pitchList.size()) {
    return _pitchList[__pos];
  }
  return nullptr;
}

Duration * GraceNote::getDurationMod(int __pos) {
  if (__pos < 0) {
    return _duration;
  }
  else if (__pos < _durationList.size()) {
    return _durationList[__pos];
  }
  else {
    return nullptr;
  }
}

Property * GraceNote::getPropertyMod(int __pos) {
  if (__pos < 0) {
    return _property;
  }
  else if (__pos < _propertyList.size()) {
    return _propertyList[__pos];
  }
  else {
    return nullptr;
  }
}

void GraceNote::clearPitch() {
  delete _pitch;
  _pitch = nullptr;
  for (auto it = _pitchList.begin(); it != _pitchList.end(); it++) {
    delete (*it);
  }
  _pitchList.clear();
  _tieList.clear();
}

void GraceNote::clearDuration() {
  delete _duration;
  _duration = nullptr;
  for (auto it = _durationList.begin(); it != _durationList.end(); it++) {
    delete (*it);
  }
  _durationList.clear();
}

void GraceNote::clearProperty() {
  delete _property;
  _property = nullptr;
  for (auto it = _propertyList.begin(); it != _propertyList.end(); it++) {
    delete (*it);
  }
  _propertyList.clear();
}

void * GraceNote::verify(const char * __context) const {
  return nullptr;
}

std::string GraceNote::filterProperty(const std::string& __text) const {
  std::string s (__text);
  return s;
}

GraceNote::GraceNote(NoteType __type) : Note(__type),
  _pitch (nullptr), _duration (nullptr), _property (nullptr), _tied (false),
  _pitchList {}, _tieList {}, _durationList {}, _propertyList {} {
}

GraceNote::GraceNote(NoteType __type, int __num, int __denom,
                     const char * __pitch) : GraceNote(__type) {
  // process pitch
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
    GraceNote::setPitch(p, -1);
  }
  // process pitch
  Duration * d = nullptr;
  HB_NESTED_THROW_MSG(std::invalid_argument,
    std::string("Failed to read duration: " + 
                 std::to_string(__num) + "/" + std::to_string(__denom)),
    d = new Duration(__num, __denom);
  )
  GraceNote::setDuration(d,-1);
}


GraceNote::GraceNote(NoteType __type, int __num, int __denom, const char * __pitch,
                     const std::initializer_list<const char *> __args) :
    GraceNote(__type, __num, __denom, __pitch) {
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
      GraceNote::addPitch(p);
      GraceNote::addProperty(nullptr);
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
      GraceNote::addDuration(d);
    }
  }
  if (count % 2 != 0) {
    HB_THROW_MSG(std::invalid_argument,
                 std::string("Arg list must be: <pitch1,value1>, <pitch2,value2>, ..."));
  }
}

GraceNote::GraceNote(NoteType __type, int __num, int __denom, const std::string& __pitch,
                     const std::vector<std::string>& __args) :
    GraceNote(__type, __num, __denom, __pitch.c_str()) {
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
      GraceNote::addPitch(p);
      GraceNote::addProperty(nullptr);
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
      GraceNote::addDuration(d);
    }
  }
  if (count % 2 != 0) {
    HB_THROW_MSG(std::invalid_argument,
                 std::string("Arg list must be: <pitch1,value1>, <pitch2,value2>, ..."));
  }
}

GraceNote::GraceNote(int __num, int __denom, const char * __pitch,
                    const std::initializer_list<const char *> __args) :
  GraceNote(NoteType::Grace, __num, __denom, __pitch, __args) {
}

GraceNote::GraceNote(int __num, int __denom, const std::string& __pitch,
                     const std::vector<std::string>& __args) :
  GraceNote(NoteType::Grace, __num, __denom, __pitch, __args) {
}

GraceNote::GraceNote(const GraceNote& __other) :
  GraceNote(std::forward<const GraceNote>(__other)) {
}

GraceNote::GraceNote(const GraceNote&& __other) : GraceNote(NoteType::Grace) {
  if (__other.hasPitch()) {
    Pitch * p = new Pitch(* __other.getPitch());
    GraceNote::setPitch(p, -1);
  }
  if (__other.hasDuration()) {
    Duration * d = new Duration(* __other.getDuration());
    GraceNote::setDuration(d, -1);
  }
  if (__other.hasProperty()) {
    Property * p = new Property(* __other.getProperty());
    GraceNote::setProperty(p, -1);
  }
  for (int i=0; i<__other.getPitchSize(); i++) {
    if (__other.getPitch(i)) {
      Pitch * p = new Pitch(* __other.getPitch(i));
      GraceNote::addPitch(p);
    }
  }
  for (int i=0; i<__other.getDurationSize(); i++) {
    if (__other.getDuration(i)) {
      Duration * d = new Duration(* __other.getDuration(i));
      GraceNote::addDuration(d);
    }
  }
  for (int i=0; i<__other.getPropertySize(); i++) {
    if (__other.getProperty(i)) {
      Property * p = new Property(* __other.getProperty(i));
      GraceNote::addProperty(p);
    }
    else {
      GraceNote::addProperty(nullptr);
    }
  }
  // set Ties
  if (__other.hasPitch() && __other.isTied()) {
    GraceNote::setTied();
  }
  for (int i=0; i < __other.getPitchSize(); i++) {
    if (__other.hasPitch(i) && __other.isTied(i)) {
      GraceNote::setTied(i);
    }
  }
}

GraceNote& GraceNote::operator=(const GraceNote& __other) {
  if (this != &__other) {
    GraceNote::clearDuration();
    GraceNote::clearPitch();
    GraceNote::clearProperty();
    if (__other.hasPitch()) {
      Pitch * p = new Pitch(* __other.getPitch());
      GraceNote::setPitch(p, -1);
    }
    if (__other.hasDuration()) {
      Duration * d = new Duration(* __other.getDuration());
      GraceNote::setDuration(d, -1);
    }
    if (__other.hasProperty()) {
      Property * p = new Property(* __other.getProperty());
      GraceNote::setProperty(p, -1);
    }
    for (int i=0; i<__other.getPitchSize(); i++) {
      if (__other.getPitch(i)) {
        Pitch * p = new Pitch(* __other.getPitch(i));
        GraceNote::addPitch(p);
      }
    }
    for (int i=0; i<__other.getDurationSize(); i++) {
      if (__other.getDuration(i)) {
        Duration * d = new Duration(* __other.getDuration(i));
        GraceNote::addDuration(d);
      }
    }
    for (int i=0; i<__other.getPropertySize(); i++) {
      if (__other.getProperty(i)) {
        Property * p = new Property(* __other.getProperty(i));
        GraceNote::addProperty(p);
      }
      else {
        GraceNote::addProperty(nullptr);
      }
    }
    // set Ties
    if (__other.hasPitch() && __other.isTied()) {
      GraceNote::setTied();
    }
    for (int i=0; i < __other.getPitchSize(); i++) {
      if (__other.hasPitch(i) && __other.isTied(i)) {
        GraceNote::setTied(i);
      }
    }
  }
  return *this;
}

GraceNote::~GraceNote() {
  GraceNote::clearDuration();
  GraceNote::clearPitch();
  GraceNote::clearProperty();
}

void GraceNote::updateDuration(const std::string& __context) {
}

void GraceNote::updateDuration(const std::string& __context, size_t __pos) {
}

void GraceNote::updatePitch(const std::string& __context) {
}

void GraceNote::updatePitch(const std::string& __context, size_t __pos) {
}

void GraceNote::updateProperty(const std::string& __context) {
  if (__context.empty()) {
    GraceNote::setProperty(nullptr, -1);
  }
  else {
    Property * p = new Property(__context);
    GraceNote::setProperty(p, -1);
  }
}

void GraceNote::updateProperty(const std::string& __context, size_t __pos) {
  if (__context.empty()) {
    GraceNote::setProperty(nullptr, __pos);
  }
  else {
    Property * p = new Property(__context);
    GraceNote::setProperty(p, __pos);
  }
}

void GraceNote::setTied() {
  _tied = true;
}

void GraceNote::setTied(size_t __pos) {
  if (__pos < _tieList.size()) {
    _tieList[__pos] = true;
  }
}

void GraceNote::setUntied() {
  _tied = false;
}

void GraceNote::setUntied(size_t __pos) {
  if (__pos < _tieList.size()) {
    _tieList[__pos] = false;
  }
}

int GraceNote::getSize() const {
  return GraceNote::getPitchSize();
}

bool GraceNote::isValid() const {
  if (_durationList.empty() || _pitchList.empty() || _tieList.empty() || 
      _duration == nullptr || _pitch == nullptr ||
      _pitchList.size() != _tieList.size() ||
      _durationList.size() != _propertyList.size() ||
      _durationList.size() != _pitchList.size()) {
    return false;
  }
  for (auto it = _durationList.cbegin(); it != _durationList.cend(); it++) {
    if ((*it) == nullptr) {
      return false;
    }
  }
  for (auto it = _pitchList.cbegin(); it != _pitchList.cend(); it++) {
    if ((*it) == nullptr) {
      return false;
    }
  }
  return true;
}

bool GraceNote::isTied() const {
  return _tied;
}

bool GraceNote::isTied(size_t __pos) const {
  if (__pos >= _tieList.size()) {
    return false;
  }
  else {
    return _tieList[__pos];
  }
}

bool GraceNote::hasDuration() const {
  return _duration != nullptr;
}

bool GraceNote::hasDuration(size_t __pos) const {
  if (__pos >= _durationList.size()) {
    return false;
  }
  else {
    return _durationList[__pos] != nullptr;
  }
}

bool GraceNote::hasPitch() const {
  return _pitch != nullptr;
}

bool GraceNote::hasPitch(size_t __pos) const {
  if (__pos >= _pitchList.size()) {
    return false;
  }
  else {
    return _pitchList[__pos] != nullptr;
  }
}

bool GraceNote::hasProperty() const {
  return _property != nullptr;
}

bool GraceNote::hasProperty(size_t __pos) const {
  if (__pos >= _propertyList.size()) {
    return false;
  }
  else {
    return _propertyList[__pos] != nullptr;
  }
}

const Duration * GraceNote::getDuration() const {
  return _duration;
}

const Duration * GraceNote::getDuration(size_t __pos) const {
  if (__pos >= _durationList.size()) {
    return nullptr;
  }
  else {
    return _durationList[__pos];
  }
}

const Pitch * GraceNote::getPitch() const {
  return _pitch;
}

const Pitch * GraceNote::getPitch(size_t __pos) const {
  if (__pos >= _pitchList.size()) {
    return nullptr;
  }
  else {
    return _pitchList[__pos];
  }
}

const Property * GraceNote::getProperty() const {
  return _property;
}

const Property * GraceNote::getProperty(size_t __pos) const {
  if (__pos >= _propertyList.size()) {
    return nullptr;
  }
  else {
    return _propertyList[__pos];
  }
}

std::string GraceNote::getPropertyStr() const {
  std::string s;
  if (GraceNote::getProperty()) {
    s = GraceNote::getProperty()->toString();
  }
  return s;
}

std::string GraceNote::getPropertyStr(size_t __pos) const {
  std::string s;
  if (GraceNote::getProperty(__pos)) {
    s = GraceNote::getProperty(__pos)->toString();
  }
  return s;
}

int GraceNote::getPitchSize() const {
  return _pitchList.size();
}

int GraceNote::getDurationSize() const {
  return _durationList.size();
}

int GraceNote::getPropertySize() const {
  return _propertyList.size();
}

void GraceNote::modify(const std::string& __context) {
}

std::string GraceNote::toString() const {
  std::string s = "N/A";
  if (GraceNote::isValid()) {
    s = "(";
    for (int i=0; i<GraceNote::getPitchSize(); i++) {
      if (GraceNote::hasPitch(i)) {
        s += GraceNote::getPitch(i)->toString() + ",1/";
      }
      if (GraceNote::hasDuration(i)) {
        s += std::to_string(GraceNote::getDuration(i)->getDenom());
      }
      s += ",";
    }
    s = ") ";
    if (GraceNote::hasPitch()) {
      s += GraceNote::getPitch()->toString() + ",";
    }
    if (GraceNote::hasDuration()) {
      s += GraceNote::getDuration()->toString();
    }
  }
  return s;
}

void * GraceNote::toStream(const std::string& __context, void * __ostream) const {
  return nullptr;
}

} // namespace core
} // namespace hautbois