#include "note.hpp"
#include "duration.hpp"
#include "pitch.hpp"
#include "property.hpp"

#include <algorithm>
#include <string>
#include <stdexcept>
#include <utility>
#include <boost/algorithm/string.hpp>

namespace hautbois {
namespace core {

void Note::setNoteType(NoteType __ntype) {
  _type = __ntype;
}

void Note::addPitch(Pitch * __p) {
  if (__p) {
    _pitch.push_back(__p);
  }
}

void Note::setPitch(Pitch * __p) {
  clearPitch();
  if (__p) {
    _pitch.push_back(__p);
  }
}

void Note::clearPitch() {
  for (auto it=_pitch.begin(); it != _pitch.end(); it++) {
    delete (*it);
  }
}

void Note::setDuration(Duration * __d) {
  if (_duration && __d) {
    delete _duration;
  }
  _duration = __d;
}

void Note::setProperty(Property * __p) {
  if (_property && __p) {
    delete _property;
  }
  _property = __p;
}

NoteType Note::guessNoteType(const std::string& __input) const {
  if (__input == "S") {
    return NoteType::Silence;
  }
  else if (__input == "R") {
    return NoteType::Rest;
  }
  else {
    size_t pos_plus  = __input.find("+");
    size_t pos_dash = __input.find("-");
    if (pos_plus != std::string::npos) {
      return NoteType::Chord;
    }
    else if (pos_dash != std::string::npos) {
      return NoteType::Tuplet;
    }
    else {
      return NoteType::SingleNote;
    }
  }
}

void Note::checkFormatThrowExp(const std::string& __pitch) const {
  auto is_valid_input = [&] (const std::string& name,
                             const std::string& acc,
                             const std::string& oct) {
    std::string VALIDNAMES = "CDEFGABRS";
    std::string VALIDCTAVE = "0123456789";
    std::vector<std::string> VALIDACCIDENTALS = 
      {"", "n", "s", "ss", "x", "#", "d", "b", "bb"};
    if (VALIDNAMES.find(name) == std::string::npos ||
        VALIDCTAVE.find(oct)  == std::string::npos) {
      return false;
    }
    if (std::find(VALIDACCIDENTALS.begin(), VALIDACCIDENTALS.end(), acc) 
         == VALIDACCIDENTALS.end()) {
      return false;
    }
    return true;
  };

  std::string name;
  std::string accidental;
  std::string octave = "4";

  if (__pitch.length() == 4) {
    name       = __pitch.substr(0,1);
    accidental = __pitch.substr(1,2);
    octave     = __pitch.substr(3,1);
  }
  else if (__pitch.length() == 3) {
    name = __pitch.substr(0,1);
    accidental = __pitch.substr(1,1);
    octave = __pitch.substr(2,1);
  }
  else if (__pitch.length() == 2) {
    name = __pitch.substr(0,1);
    octave = __pitch.substr(1,1);
  }
  else if (__pitch.length() == 1) {
    name = __pitch;
  }
  else {
    throw std::invalid_argument("Cannot parse: " + __pitch);
  }
  if (!is_valid_input(name, accidental, octave)) {
    throw std::invalid_argument("Cannot parse: " + __pitch);
  }
}

std::tuple<std::string, std::string, std::string>
 Note::parseSingleNote(const std::string& __pitch) const {
  checkFormatThrowExp(__pitch);

  std::string name (1, __pitch.front());
  std::string octave (1, __pitch.back());
  std::string accidental(__pitch);
  accidental.pop_back();
  std::reverse(accidental.begin(), accidental.end());
  accidental.pop_back();

  if (accidental == "bb") {
    accidental = "d";
  }
  else if (accidental == "ss") {
    accidental = "x";
  }
  else if (accidental == "#") {
    accidental = "s";
  }

  return { name, accidental, octave };
}

std::vector< std::tuple<std::string, std::string, std::string> >
 Note::parseGroupNote(const std::string& __pitch, NoteType __type) const {
  std::vector< std::tuple<std::string, std::string, std::string> > oResult;

  std::string sep;
  (__type == NoteType::Chord) ? sep = "+" : sep = "-";
  std::vector<std::string> tokens;
  boost::split(tokens, __pitch, boost::is_any_of(sep), boost::token_compress_on);
  if (tokens.empty()) {
    throw std::invalid_argument("Failed to parse \"" + __pitch + "\"");
  }
  for (auto it=tokens.begin(); it != tokens.end(); it++) {
    checkFormatThrowExp(*it);
    auto res = parseSingleNote(*it);
    oResult.push_back(res);
  }

  return oResult;
}

std::string Note::filterProperty(const std::string& __text) const {
  std::string s = __text;
  return s;
}

Note::Note() : _type     ( NoteType::Silence),
               _duration ( new Duration(1,1) ),
               _pitch    ( { new Pitch('S', 'n', 4) } ),
               _property ( nullptr ),
               _tied     ( false )
{}

Note::Note(const int& __num, const int& __denom) :
  _type     ( NoteType::Silence),
  _duration ( new Duration(__num, __denom) ),
  _pitch    ( { new Pitch('S', 'n', 4) } ),
  _property ( nullptr ),
  _tied     ( false )
{}

Note::Note(const int& __num, const int& __denom, const std::string& __pitch) :
  _type     ( NoteType::SingleNote),
  _duration ( nullptr ),
  _pitch    ( {} ),
  _property ( nullptr ),
  _tied     ( false )
{
  _type = guessNoteType(__pitch);
  if (_type == NoteType::SingleNote) {
    std::string name, acc, oct;
    std::tie(name, acc, oct) = parseSingleNote(__pitch);
    setPitch(new Pitch(name, acc, oct));
  }
  else if (_type == NoteType::Rest) {
    setPitch(new Pitch('R', 'n', 4));
  }
  else if (_type == NoteType::Silence) {
    setPitch(new Pitch('S', 'n', 4));
  }
  else if (_type == NoteType::Chord || _type == NoteType::Tuplet) {
    auto args = parseGroupNote(__pitch, _type);
    for (auto it=args.begin(); it != args.end(); it++) {
      std::string name, acc, oct;
      std::tie(name, acc, oct) = (*it);
      addPitch(new Pitch(name, acc, oct));
    }
  }
  _duration = new Duration(__num, __denom);
}

Note::Note(const Note& __n) {
  _type = __n.getType();
  setDuration(new Duration(* __n.getDuration()));

  if (_type == NoteType::SingleNote) {
    setPitch(new Pitch(* __n.getPitch()));
  }
  else if (_type == NoteType::Chord || _type == NoteType::Tuplet) {
    auto group = __n.getPitchGroup();
    for (auto it=group.begin(); it != group.end(); it++) {
      addPitch(new Pitch(*(*it)));
    }
  }
  setProperty(new Property(* __n.getProperty()));
}

Note::Note(const Note&& __n) {
  _type = __n.getType();
  setDuration(new Duration(* __n.getDuration()));

  if (_type == NoteType::SingleNote) {
    setPitch(new Pitch(* __n.getPitch()));
  }
  else if (_type == NoteType::Chord || _type == NoteType::Tuplet) {
    auto group = __n.getPitchGroup();
    for (auto it=group.begin(); it != group.end(); it++) {
      addPitch(new Pitch(*(*it)));
    }
  }
  setProperty(new Property(* __n.getProperty()));
}

Note::~Note() {
  clearPitch();
  if (_duration) {
    delete _duration;
  }
  if (_property) {
    delete _property;
  }
}

Note& Note::operator=(const Note& __n) {
  if (this != &__n) {
    _type = __n.getType();
    setDuration(new Duration(* __n.getDuration()));

    if (_type == NoteType::SingleNote) {
      setPitch(new Pitch(* __n.getPitch()));
    }
    else if (_type == NoteType::Chord || _type == NoteType::Tuplet) {
      auto group = __n.getPitchGroup();
      for (auto it=group.begin(); it != group.end(); it++) {
        addPitch(new Pitch(*(*it)));
      }
    }
    setProperty(new Property(* __n.getProperty()));    
  }
  return *this;
}

void Note::updateDuration(const std::string& __context) {
  // not supported
}
  
void Note::updatePitch(const std::string& __context) {
  // not supported
}

void Note::updateProperty(const std::string& __context) {
  delete _property;
  _property = nullptr;
  if (!__context.empty()) {
    _property = new Property(__context);
  }
}

void Note::setTied() {
  _tied = true;
}

void Note::setUntied() {
  _tied = false;
}

bool Note::hasProperty() const {
  if (_property) {
    return true;
  }
  else {
    return false;
  }
}

int Note::pitchSize() const {
  int s = (int) _pitch.size();
  return s;
}

NoteType Note::getType() const {
  return _type;
}

char Note::getTypeChar() const {
  if (_type == NoteType::SingleNote) {
    return 'N';
  }
  else if (_type == NoteType::Chord) {
    return 'C';
  }
  else if (_type == NoteType::Tuplet) {
    return 'X';
  }
  else if (_type == NoteType::Rest) {
    return 'R';
  }
  else if (_type == NoteType::Silence) {
    return 'S';
  }
  else {
    return '0';
  }
}

std::string Note::getTypeStr() const {
  if (_type == NoteType::SingleNote) {
    return "N";
  }
  else if (_type == NoteType::Chord) {
    return "C";
  }
  else if (_type == NoteType::Tuplet) {
    return "T";
  }
  else if (_type == NoteType::Rest) {
    return "R";
  }
  else if (_type == NoteType::Silence) {
    return "S";
  }
  else {
    return "0";
  }
}

bool Note::isType(NoteType iType) const {
  if (iType == _type) {
    return true;
  }
  else {
    return false;
  }
}

bool Note::isSingle() const {
  return isType(NoteType::SingleNote);
}

bool Note::isChord() const {
  return isType(NoteType::Chord);
}

bool Note::isRest() const {
  return isType(NoteType::Rest);
}

bool Note::isSilent() const {
  return isType(NoteType::Silence);
}

bool Note::isTuplet() const {
  return isType(NoteType::Tuplet);
}

bool Note::isValid() const {
  if (_duration == nullptr) {
    return false;
  }

  if (!_pitch.empty()) {
    for (auto it=_pitch.begin(); it != _pitch.end(); it++) {
      if ((*it) == nullptr) {
        return false;
      }
    }
  }
  if ( (_type == NoteType::Silence || _type == NoteType::Rest)
        && (_pitch.empty() || _pitch.size() == 1) ) {
    return true;
  }
  if (_type == NoteType::SingleNote && _pitch.size() == 1) {
    return true;
  }
  if ((_type == NoteType::Chord || _type == NoteType::Tuplet)
           && _pitch.size() > 1) {
    return true;
  }
  return false;
}

bool Note::isTied() const {
  return _tied;
}

const Duration * Note::getDuration() const {
  if (_duration) {
    return _duration;
  }
  else {
    return nullptr;
  }
}

const Pitch * Note::getPitch() const {
  if (_pitch.size() > 1 && _pitch[0]) {
    return _pitch[0];
  }
  else {
    return nullptr;
  }
}

const Property * Note::getProperty() const {
  if (_property) {
    return _property;
  }
  else {
    return nullptr;
  }
}

const std::vector<const Pitch *> Note::getPitchGroup() const {
  std::vector<const Pitch *> const_pitch;
  for (auto it=_pitch.begin(); it != _pitch.end(); it++) {
    const Pitch * p = (*it);
    const_pitch.push_back(p);
  }
  return const_pitch;
}

std::string Note::getDurationStr() const {
  return _duration->toString();
}

std::string Note::getPitchStr() const {
  if (isRest()) {
    return "R";
  }
  else if (isSilent()) {
    return "S";
  }
  else {
    if (_pitch.size() >= 1) {
      return _pitch[0]->toString();
    }
    else {
      throw std::runtime_error("_pitch.size() < 1");
    }
  }
}

std::vector<std::string> Note::getPitchGroupStr() const {
  std::vector<std::string> res;
  if (isChord() || isTuplet()) {
    if (_pitch.size() < 2) {
      throw std::runtime_error("_pitch.size() < 2");
    }
    for (auto it = _pitch.begin(); it != _pitch.end(); it++) {
      res.push_back((*it)->toString());
    }
  }
  else {
    res.push_back(getPitchStr());
  }
  return res;
}

std::string Note::getPropertyStr() const {
  std::string s;
  if (hasProperty() && _property) {
    s = _property->toString();
  }
  return s;
}

std::string Note::toString() const {
  std::string oString = "(";
  if (isValid()) {
    if (isRest()) {
      oString.append("R ");
    }
    else if (isSilent()) {
      oString.append("S ");
    }
    else if (isSingle()) {
      oString.append(_pitch.front()->toString());
      oString.append(" ");
    }
    else if (isChord()) {
      for (auto it = _pitch.begin(); it != _pitch.end(); it++) {
        oString.append((*it)->toString());
        oString.append("+");
      }
      oString.pop_back();
      oString.append(" ");
    }
    else if (isTuplet()) {
      for (auto it = _pitch.begin(); it != _pitch.end(); it++) {
        oString.append((*it)->toString());
        oString.append("-");
      }
      oString.pop_back();
      oString.append(" ");
    }
    oString.append(_duration->toString());
    oString.append(")");
  }
  else {
    oString = "(Invalid)";
  }
  return oString;
}

void * Note::toStream(const std::string& __context, void * __ostream) const {
  // not supported
  return nullptr;
}

} // namespace core
} // namespace hautbois