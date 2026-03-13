#include "note_tuplet.hpp"
#include "note_single.hpp"
#include "pitch.hpp"
#include "duration.hpp"
#include "property.hpp"
#include "utility/hbexcept.hpp"

namespace hautbois {
namespace core {

void Tuplet::addPitch(Pitch * __p) {
  if (__p) {
    _pitch.push_back(__p);
    _tied.push_back(false);
  }
}

void Tuplet::setPitch(Pitch * __p) {
  if (__p) {
    Tuplet::clearPitch();
    _pitch.push_back(__p);
    _tied.push_back(false);
  }
}

void Tuplet::addDuration(Duration * __d) {
  if (__d) {
    _duration.push_back(__d);
  }
}

void Tuplet::setDuration(Duration * __d) {
  if (__d) {
    Tuplet::clearDuration();
    _duration.push_back(__d);
  }
}

void Tuplet::addProperty(Property * __p) {
  _property.push_back(__p);
}

void Tuplet::setProperty(Property * __p) {
  Tuplet::clearProperty();
  _property.push_back(__p);
}

void Tuplet::clearPitch() {
  for (auto it=_pitch.begin(); it != _pitch.end(); it++) {
    delete (*it);
  }
  _pitch.clear();
}

void Tuplet::clearDuration() {
  for (auto it=_duration.begin(); it != _duration.end(); it++) {
    delete (*it);
  }
  _duration.clear();
}

void Tuplet::clearProperty() {
  for (auto it=_property.begin(); it != _property.end(); it++) {
    delete (*it);
  }
  _property.clear();
}

void * Tuplet::verify(const char * __context) const {
  // Verify if all member objects exist and their size are homogeneous
  bool notegroup_ok = false;
  int count_one = 0;
  for (auto it=_duration.cbegin(); it != _duration.cend(); it++) {
    if (*it) {
      count_one++;
    }
  }
  int count_two = 0;
  for (auto it=_pitch.cbegin(); it != _pitch.cend(); it++) {
    if (*it) {
      count_two++;
    }
  }
  // if nbr_of_notes == 0 ==> no need to check nbr of notes, only checking size is enough
  if ((count_one == nbr_of_notes || nbr_of_notes == 0) && count_one == count_two &&
      count_one == _duration.size() && count_one == _pitch.size() &&
      count_one == _property.size() && count_one == _tied.size()) {
    notegroup_ok = true;
  }
  if (!notegroup_ok) {
    std::string msg = std::string("Internal object size mismatch:\n")
     + " _duration counted == " + std::to_string(count_one)
     + "_duration.size() == "   + std::to_string(_duration.size())
     + "_pitch counted == "     + std::to_string(count_two)
     + "_pitch.size() == "      + std::to_string(_pitch.size())
     + "_tied.size() == "       + std::to_string(_tied.size());
    HB_THROW_MSG(std::invalid_argument, msg);
  }
  // Verify if note value in _duration equals _noteValue
  bool notevalue_ok = false;
  Duration v_actual(1,1);
  Duration v_expect(1,1);
  if (_noteValue) {
    v_expect += *_noteValue;
    for (auto it=_duration.cbegin(); it != _duration.cend(); it++) {
      if (*it) {
        v_actual += *(*it);
      }
    }
    if (v_actual == v_expect) {
      notevalue_ok = true;
    }
  }
  if (!notevalue_ok) {
    std::string value_expect = "N/A";
    std::string value_actual = "N/A";
    std::string msg = "Tuplet note value verification failed, total value should be ";
    if (_noteValue) {
      value_expect = _noteValue->toString();
      value_actual = v_actual.toString();
    }
    msg += " but actually is " + value_actual;
    HB_THROW_MSG(std::invalid_argument, msg);
  }
  return nullptr;
}

std::string Tuplet::filterProperty(const std::string& __text) const {
  std::string s (__text);
  return s;
}

Tuplet::Tuplet(const int& __nbr_of_notes) : Note(NoteType::Tuplet),
  _noteValue ( nullptr ), _duration ({}),  _pitch ({}),
  _property ({}), _tied ({}), nbr_of_notes ( 0 ) { }

Tuplet::Tuplet() : Tuplet(0) { }

Tuplet::Tuplet(const std::initializer_list<std::string> __group,
               const int& __nbr_of_notes) : Tuplet(__nbr_of_notes) {
  int count = 0;
  for (auto& token: __group) {
    Pitch * p = nullptr;
    Duration * d = nullptr;
    _property.push_back(nullptr); // add nullptr for no property
    const int note_part = ++count % 2;
    if (note_part == 1) {
      // Read pitch token
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string ("Failed to create Tuplet at token: " + token),
        SingleNote n(token, 1,4);
        HB_NESTED_THROW_MSG(std::out_of_range,
          std::string ("Empty pitch found while processing token: " + token),
          p = new Pitch(*n.getPitch());
        )
      )
      Tuplet::addPitch(p);
    }
    else if (note_part == 0) {
      // Duration
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string ("Failed to create Tuplet at token: " + token),
        d = new Duration(std::stoi(token));
      )
      Tuplet::addDuration(d);
    }
    else {
      HB_THROW(std::runtime_error);
    }
  }
  HB_NESTED_THROW_MSG(std::invalid_argument,
    std::string ("Validation failed"),
    Tuplet::verify(nullptr);
  )
}

Tuplet::Tuplet(const std::vector<std::string>& __group, const int& __nbr_of_notes) : Tuplet(__nbr_of_notes) {
  int count = 0;
  for (auto& token: __group) {
    Pitch * p = nullptr;
    Duration * d = nullptr;
    _property.push_back(nullptr); // add nullptr for no property
    const int note_part = ++count % 2;
    if (note_part == 1) {
      // Read pitch token
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string ("Failed to create Tuplet at token: " + token),
        SingleNote n(token, 1,4);
        HB_NESTED_THROW_MSG(std::out_of_range,
          std::string ("Empty pitch found while processing token: " + token),
          p = new Pitch(*n.getPitch());
        )
      )
      Tuplet::addPitch(p);
    }
    else if (note_part == 0) {
      // Duration
      HB_NESTED_THROW_MSG(std::invalid_argument,
        std::string ("Failed to create Tuplet at token: " + token),
        d = new Duration(std::stoi(token));
      )
      Tuplet::addDuration(d);
    }
    else {
      HB_THROW(std::runtime_error);
    }
  }
  HB_NESTED_THROW_MSG(std::invalid_argument,
    std::string ("Validation failed"),
    Tuplet::verify(nullptr);
  )
}

Tuplet::Tuplet(const std::initializer_list<std::string> __group,
               const int& num, const int& denom,
               const int& __nbr_of_notes) : Tuplet(__group, __nbr_of_notes) {
  HB_NESTED_THROW_MSG(std::invalid_argument,
    std::string ("Failed to create _noteValue with " + 
                 std::to_string(num) + "/" + std::to_string(denom)),
    _noteValue = new Duration(num, denom);
  )
} 

Tuplet::Tuplet(const std::vector<std::string>& __group,
               const int& num, const int& denom,
               const int& __nbr_of_notes) : Tuplet(__group, __nbr_of_notes) {
  HB_NESTED_THROW_MSG(std::invalid_argument,
    std::string ("Failed to create _noteValue with " + 
                 std::to_string(num) + "/" + std::to_string(denom)),
    _noteValue = new Duration(num, denom);
  )
}

Tuplet::Tuplet(const std::initializer_list<std::string> __group,
               const int& denom, const std::string& dots,
               const int& __nbr_of_notes) : Tuplet(__group, __nbr_of_notes) {
  HB_NESTED_THROW_MSG(std::invalid_argument,
    std::string ("Invalid _noteValue: " + std::to_string(denom) + dots),
    _noteValue = new Duration(denom, dots);
  )
}

Tuplet::Tuplet(const std::vector<std::string>& __group,
               const int& denom, const std::string& dots,
               const int& __nbr_of_notes) : Tuplet(__group, __nbr_of_notes) {
  HB_NESTED_THROW_MSG(std::invalid_argument,
    std::string ("Invalid _noteValue: " + std::to_string(denom) + dots),
    _noteValue = new Duration(denom, dots);
  )
}

Tuplet::Tuplet(Tuplet& __note) : Tuplet() {
  if (__note.hasPitch() && __note.hasDuration()) {
    for (int i=0; i < __note.getPitchSize(); i++) {
      Pitch * p = new Pitch(*__note.getPitch(i));
      Tuplet::addPitch(p);
    }
    for (int i=0; i < __note.getDurationSize(); i++) {
      Duration * d = new Duration(*__note.getDuration(i));
      Tuplet::addDuration(d);
    }
    for (int i=0; i < _pitch.size(); i++) {
      if (Tuplet::isTied(i)) {
        Tuplet::setTied(i);
      }
    }
  }
  for (int i=0; i < __note.getPropertySize(); i++) {
    Property * p = nullptr;
    if (__note.hasProperty(i)) {
      p = new Property(*__note.getProperty(i));
    }
    Tuplet::addProperty(p);
  }
}

Tuplet::Tuplet(Tuplet&& __note) : Tuplet() {
  if (__note.hasPitch() && __note.hasDuration()) {
    for (int i=0; i < __note.getPitchSize(); i++) {
      Pitch * p = new Pitch(*__note.getPitch(i));
      Tuplet::addPitch(p);
    }
    for (int i=0; i < __note.getDurationSize(); i++) {
      Duration * d = new Duration(*__note.getDuration(i));
      Tuplet::addDuration(d);
    }
    for (int i=0; i < _pitch.size(); i++) {
      if (Tuplet::isTied(i)) {
        Tuplet::setTied(i);
      }
    }
  }
  for (int i=0; i < __note.getPropertySize(); i++) {
    Property * p = nullptr;
    if (__note.hasProperty(i)) {
      p = new Property(*__note.getProperty(i));
    }
    Tuplet::addProperty(p);
  }
}

Tuplet& Tuplet::operator=(const Tuplet& __n) {
  if (this != &__n) {
    if (__n.hasPitch() && __n.hasDuration()) {
      Tuplet::clearPitch();
      Tuplet::clearDuration();
      for (int i=0; i < __n.getPitchSize(); i++) {
        Pitch * p = new Pitch(*__n.getPitch(i));
        Tuplet::addPitch(p);
      }
      for (int i=0; i < __n.getDurationSize(); i++) {
        Duration * d = new Duration(*__n.getDuration(i));
        Tuplet::addDuration(d);
      }
      for (int i=0; i < _pitch.size(); i++) {
        if (Tuplet::isTied(i)) {
          Tuplet::setTied(i);
        }
      }
    }
    if (__n.hasProperty()) {
      Tuplet::clearProperty();
      for (int i=0; i < __n.getPropertySize(); i++) {
        Property * p = nullptr;
        if (__n.hasProperty(i)) {
          p = new Property(*__n.getProperty(i));
        }
        Tuplet::addProperty(p);
      }
    }
  }
}

Tuplet::~Tuplet() {
  Tuplet::clearPitch();
  Tuplet::clearDuration();
  Tuplet::clearProperty();
  delete _noteValue;
}

void Tuplet::updateDuration(const std::string& __context) { }

void Tuplet::updateDuration(const std::string& __context, size_t __pos) { }
  
void Tuplet::updatePitch(const std::string& __context) { }

void Tuplet::updatePitch(const std::string& __context, size_t __pos) { }

void Tuplet::updateProperty(const std::string& __context) {
  Tuplet::updateProperty(__context, 0);
}

void Tuplet::updateProperty(const std::string& __context, size_t __pos) {
  if (__pos < 0 || __pos >= _property.size()) {
    HB_THROW_MSG(std::out_of_range,
      std::string ("__pos == " + std::to_string(__pos) + 
                   ", _property.size() " + std::to_string(_property.size()))
    );
  }
  else {
    delete _property[__pos];
    _property[__pos] = nullptr;
    if (!__context.empty()) {
      _property[__pos] = new Property(__context);
    }
  }
}

void Tuplet::setTied() {
  for (auto it=_tied.begin(); it != _tied.end(); it++) {
    *it = true;
  }
}

void Tuplet::setTied(size_t __pos) {
  if (__pos >= _tied.size()) {
    _tied[_tied.size() - 1] = true;
  }
  else if (__pos < 0) {
    _tied[0] = true;
  }
  else {
    _tied[__pos] = true;
  }
}

void Tuplet::setUntied() {
  for (auto it=_tied.begin(); it != _tied.end(); it++) {
    *it = false;
  }
}

void Tuplet::setUntied(size_t __pos) {
  if (__pos >= _tied.size()) {
    _tied[_tied.size() - 1] = false;
  }
  else if (__pos < 0) {
    _tied[0] = false;
  }
  else {
    _tied[__pos] = false;
  }
}

int Tuplet::getSize() const {
  return _pitch.size();
}

bool Tuplet::isValid() const {
  if (_pitch.size() == _duration.size() && 
      _pitch.size() == _property.size() &&
      _pitch.size() == _tied.size() &&
      _noteValue != nullptr) {
    for (auto it=_pitch.cbegin(); it != _pitch.cend(); it++) {
      if (*it == nullptr) {
        return false;
      }
    }
    for (auto it=_duration.cbegin(); it != _duration.cend(); it++) {
      if (*it == nullptr) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool Tuplet::isTied() const {
  for (auto it=_tied.cbegin(); it != _tied.cend(); it++) {
    if (*it == false) {
      return false;
    }
  }
  return true;
}

bool Tuplet::isTied(size_t __pos) const {
  if (__pos >= _tied.size()) {
    return _tied[_tied.size() - 1];
  }
  else if (__pos < 0) {
    return _tied[0];
  }
  else {
    return _tied[__pos];
  }
}

bool Tuplet::hasDuration() const {
  if (_noteValue) {
    return true;
  }
  return false;
}
  
bool Tuplet::hasPitch() const {
  if (_pitch.empty()) {
    return false;
  }
  for (auto it=_pitch.cbegin(); it != _pitch.cend(); it++) {
    if (*it == nullptr) {
      return false;
    }
  }
  return true;
}

bool Tuplet::hasProperty() const {
  if (_property.empty()) {
    return false;
  }
  for (auto it=_property.cbegin(); it != _property.cend(); it++) {
    if (*it != nullptr) {
      return true;
    }
  }
  return false;
}

bool Tuplet::hasDuration(size_t __pos) const {
  if (__pos >= _duration.size() || __pos < 0) {
    return false;
  }
  return _duration[__pos] != nullptr;
}
  
bool Tuplet::hasPitch(size_t __pos) const {
  if (__pos >= _pitch.size() || __pos < 0) {
    return false;
  }
  return _pitch[__pos] != nullptr;
}

bool Tuplet::hasProperty(size_t __pos) const {
  if (__pos >= _property.size() || __pos < 0) {
    return false;
  }
  return _property[__pos] != nullptr;
}

const Duration * Tuplet::getDuration() const {
  return _noteValue;
}

const Duration * Tuplet::getDuration(size_t __pos) const {
  if (__pos >= _duration.size() || __pos < 0) {
    std::string msg = "__pos " + std::to_string(__pos) + " exceeds the range";
    HB_THROW_MSG(std::out_of_range, msg);
  }
  else {
    return _duration[__pos];
  }
}

const Pitch * Tuplet::getPitch() const {
  return Tuplet::getPitch(0);
}

const Pitch * Tuplet::getPitch(size_t __pos) const {
  if (__pos >= _pitch.size() || __pos < 0) {
    std::string msg = "__pos " + std::to_string(__pos) + " exceeds the range";
    HB_THROW_MSG(std::out_of_range, msg);
  }
  else {
    return _pitch[__pos];
  }
}

const Property * Tuplet::getProperty() const {
  return Tuplet::getProperty(0);
}

const Property * Tuplet::getProperty(size_t __pos) const {
  if (__pos >= _property.size() || __pos < 0) {
    std::string msg = "__pos " + std::to_string(__pos) + " exceeds the range";
    HB_THROW_MSG(std::out_of_range, msg);
  }
  else {
    return _property[__pos];
  }
}

std::string Tuplet::getPropertyStr() const {
  Tuplet::getPropertyStr(0);
}

std::string Tuplet::getPropertyStr(size_t __pos) const {
  if (__pos >= _property.size() || __pos < 0) {
    std::string msg = "__pos " + std::to_string(__pos) + " exceeds the range";
    HB_THROW_MSG(std::out_of_range, msg);
  }
  else {
    std::string s;
    if (_property[__pos]) {
      s = _property[__pos]->toString();
    }
    return s;
  }
}

int Tuplet::getPitchSize() const {
  return _pitch.size();
}

int Tuplet::getDurationSize() const {
  return _duration.size();
}

int Tuplet::getPropertySize() const {
  return _property.size();
}

void Tuplet::modify(const std::string& __context) {
}

std::string Tuplet::toString() const {
  std::string s;
  if (_noteValue) {
    s += _noteValue->toString();
  }
  else {
    s += "N/A ";
  }
  if (_pitch.size() == _duration.size()) {
    auto it_p = _pitch.cbegin();
    auto it_d = _duration.cbegin();
    for (; it_p != _pitch.end() && it_d != _duration.end(); it_d++, it_p++) {
      s += (*it_p)->toString() + "," + (*it_d)->toString();
    }
  }
  return s;
}

void * Tuplet::toStream(const std::string& __context, void * __ostream) const {
  return nullptr;
}

} // namespace core
} // namespace hautbois