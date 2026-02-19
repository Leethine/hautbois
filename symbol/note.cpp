#include "hb_macro.hpp"
#include "note.hpp"
#include "duration.hpp"
#include "pitch.hpp"
#include <algorithm>
#include <string>
#include <stdexcept>
#include <boost/algorithm/string.hpp>

namespace hautbois {
namespace core {

void Note::setDurationPtr(Duration * d) {
  _durationPtrLog.push_back(d);
  _duration = d;
}

NoteType Note::getNoteTypeFromInput(const std::string& iPitch) const {
  if (iPitch == "S") {
    return NoteType::Silence;
  }
  else if (iPitch == "R") {
    return NoteType::Rest;
  }
  else {
    size_t pos_plus  = iPitch.find("+");
    size_t pos_dash = iPitch.find("-");
    if (pos_plus != std::string::npos) {
      return NoteType::Chord;
    }
    else if (pos_dash != std::string::npos) {
      return NoteType::Xuplet;
    }
    else {
      return NoteType::SingleNote;
    }
  }
}

bool Note::checkPitchStrFormat(const std::string& iPitch) const {
  auto keyword_finder = [&] (const std::string& n,
                             const std::string& o,
                             const std::string& a) {
    std::string ALLNAMES = "CDEFGAB";
    std::string ALLOCTAVES = "012345678";
    std::vector<std::string> ALLACCIDENTALS = 
      {"", "n", "s", "ss", "x", "#", "d", "b", "bb"};
    if (ALLNAMES.find(n) == std::string::npos ||
        ALLOCTAVES.find(o) == std::string::npos) {
      return false;
    }
    if (std::find(ALLACCIDENTALS.begin(), ALLACCIDENTALS.end(), a) 
          == ALLACCIDENTALS.end()) {
      return false;
    }
    return true;
  };

  if (iPitch.length() == 4) {
    std::string name = iPitch.substr(0,1);
    std::string octave = iPitch.substr(3,1);
    std::string accidental = iPitch.substr(1,2);
    return keyword_finder(name, octave, accidental);
  }
  else if (iPitch.length() == 3) {
    std::string name = iPitch.substr(0,1);
    std::string octave = iPitch.substr(2,1);
    std::string accidental = iPitch.substr(1,1);
    return keyword_finder(name, octave, accidental);
  }
  else if (iPitch.length() == 2) {
    std::string name = iPitch.substr(0,1);
    std::string octave = iPitch.substr(1,1);
    std::string accidental = "";
    return keyword_finder(name, octave, accidental);
  }
  else {
    return false;
  }
  return true;
}

void Note::parseSingleNote(const std::string& iPitch) {
  if (!checkPitchStrFormat(iPitch)) {
    HB_THROW(std::invalid_argument, "Failed to parse \"" + iPitch + "\"");
    return ;
  }
  std::string name (1, iPitch.front());
  std::string octave (1, iPitch.back());
  std::string accidental(iPitch);
  accidental.pop_back();
  std::reverse(accidental.begin(), accidental.end());
  accidental.pop_back();
  addPitchPtr(new Pitch(name, accidental, octave));
}

void Note::parseGroupNote(const std::string& iPitch, NoteType iType) {
  std::string sep;
  (iType == NoteType::Chord) ? sep = "+" : sep = "-";
  std::vector<std::string> tokens;
  boost::split(tokens, iPitch, boost::is_any_of(sep), boost::token_compress_on);
  if (tokens.empty()) {
    HB_THROW(std::invalid_argument, "Failed to parse \"" + iPitch + "\"");
    return ;
  }
  for (auto it=tokens.begin(); it != tokens.end(); it++) {
    if (!checkPitchStrFormat((*it))) {
      HB_THROW(std::invalid_argument, "Failed to parse \"" + iPitch + "\"");
      return ;
    }
    parseSingleNote(*it);
  }
}

void Note::clearPitch() {
  _pitch.clear();
}

void Note::setNoteType(NoteType iType) {
  _type = iType;
}

void Note::setDuration(const Duration& iDuration) {
  setDurationPtr(new Duration(iDuration));
}

void Note::addPitch(const Pitch * const iPitch) {
  Pitch * p = new Pitch(*iPitch);
  _pitchPtrLog.push_back(p);
  _pitch.push_back(p);
}

void Note::addPitchPtr(Pitch * iPitch) {
  _pitchPtrLog.push_back(iPitch);
  _pitch.push_back(iPitch);
}

std::vector<Pitch *> Note::getPitchPtr() const {
  return _pitch;
}

void Note::filterProperties() {
  return ;
}

Note::Note(const Note& iRhs) {
  _type = iRhs.getType();
  setDurationPtr(new Duration(iRhs.getDuration()));
  if (_type == NoteType::SingleNote) {
    parseSingleNote(iRhs.getPitch());
  }
  else if (_type == NoteType::Chord || _type == NoteType::Xuplet) {
    std::vector<std::string> notegroup = iRhs.getChord();
    for (auto it=notegroup.begin(); it != notegroup.end(); it++) {
      parseSingleNote((*it));
    }
  }
  _noteProperties = iRhs.getProperties();
}

Note::Note() : _type     ( NoteType::Silence),
               _duration ( nullptr ),
               _pitch    ( {} ),
               _pitchPtrLog    ( {} ),
               _noteProperties ( {} ),
               _tied           ( false )
{}

Note::Note(const int iNum, const int iDenom, const std::string& iPitch) {
  setDurationPtr(new Duration(iNum, iDenom));
  _type = getNoteTypeFromInput(iPitch);
  if (_type == NoteType::SingleNote) {
    parseSingleNote(iPitch);
  }
  else if (_type == NoteType::Chord || _type == NoteType::Xuplet) {
    parseGroupNote(iPitch, _type);
  }
}

Note::~Note() {
  for (auto it = _pitchPtrLog.begin(); it != _pitchPtrLog.end(); ++it) {
    HB_DELETE (*it);
  }
  for (auto it = _durationPtrLog.begin(); it != _durationPtrLog.end(); ++it) {
    HB_DELETE (*it);
  }
}

void Note::setTied() {
  _tied = true;
}

void Note::setUntied() {
  _tied = false;
}

void Note::addProperty(const std::string& iFreeTxt) {
  _noteProperties.push_back(iFreeTxt);
}

void Note::deleteProperty(const std::string& iFreeTxt) {
  std::vector<std::string> new_property;
  for (auto it = _noteProperties.begin();
            it != _noteProperties.end(); ++it) {
    if ((*it) != iFreeTxt) {
      new_property.push_back((*it));
    }
  }
  _noteProperties = new_property;
}

void Note::clearProperty() {
  _noteProperties.clear();
}

bool Note::hasProperty() {
  return _noteProperties.empty();
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
  else if (_type == NoteType::Xuplet) {
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
  else if (_type == NoteType::Xuplet) {
    return "X";
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
  return isType(NoteType::Xuplet);
}

bool Note::isValid() const {
  if (!_pitch.empty()) {
    for (auto it=_pitch.begin(); it != _pitch.end(); it++) {
      if ((*it) == nullptr) {
        return false;
      }
    }
  }
  if ((_type == NoteType::Silence || _type == NoteType::Rest)
            && _pitch.empty()) {
    return true;
  }
  if (_type == NoteType::SingleNote && _pitch.size() == 1) {
    return true;
  }
  if ((_type == NoteType::Chord || _type == NoteType::Xuplet)
           && _pitch.size() > 1) {
    return true;
  }
  return false;
}

const Duration Note::getDuration() const {
  const Duration d (*_duration);
  return d;
}

std::string Note::getPitch() const {
  if (_type == NoteType::Rest) {
    return "R";
  }
  else if (_type == NoteType::Silence) {
    return "S";
  }
  else {
    if (_pitch.empty()) {
      HB_THROW(std::runtime_error, "Pitch list is empty!");
      return "";
    }
    return _pitch.front()->toString();
  }
}

std::vector<std::string> Note::getChord() const {
  if (_type == NoteType::Rest || _type == NoteType::Silence) {
    return { };
  }
  else {
    if (_pitch.empty()) {
      HB_THROW(std::runtime_error, "Pitch list is empty!");
      return { };
    }
    std::vector<std::string> ret;
    for (auto it=_pitch.begin(); it != _pitch.end(); it++) {
      ret.push_back((*it)->toString());
    }
    return ret;
  }
}

std::vector<std::string> Note::getTuplet() const {
  return getChord();
}

std::vector<std::string> Note::getProperties() const {
  std::vector<std::string> ret(_noteProperties);
  return ret;
}

void Note::updateNote(void * iGenericPtr) {
  return ;
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

void * Note::toStream(const std::string& iStreamType) const {
  return NULL;
}

} // namespace core
} // namespace hautbois