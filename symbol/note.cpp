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
  else if (_type == NoteType::Chord) {
    auto chord = __n.getChord();
    for (auto it=chord.begin(); it != chord.end(); it++) {
      addPitch(new Pitch(*(*it)));
    }
  }
  else if (_type == NoteType::Tuplet) {
    auto group = __n.getTuplet();
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
  else if (_type == NoteType::Chord) {
    auto chord = __n.getChord();
    for (auto it=chord.begin(); it != chord.end(); it++) {
      addPitch(new Pitch(*(*it)));
    }
  }
  else if (_type == NoteType::Tuplet) {
    auto group = __n.getTuplet();
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
    else if (_type == NoteType::Chord) {
      auto chord = __n.getChord();
      for (auto it=chord.begin(); it != chord.end(); it++) {
        addPitch(new Pitch(*(*it)));
      }
    }
    else if (_type == NoteType::Tuplet) {
      auto group = __n.getTuplet();
      for (auto it=group.begin(); it != group.end(); it++) {
        addPitch(new Pitch(*(*it)));
      }
    }
    setProperty(new Property(* __n.getProperty()));    
  }
  return *this;
}

} // namespace core
} // namespace hautbois