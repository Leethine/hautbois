#include "note.hpp"
#include <regex>

namespace hautbois {
namespace ly {


const static std::regex SINGLE_NOTE_REGEX
  ("^[do|re|mi|fa|sol|la|si]{1}[\'|,]*[1|2|4|8|16|32|64|128]{1}(.)*$");

const static std::regex CHORD_REGEX
  ("^<([do|re|mi|fa|sol|la|si][\'|,]*[::blank::]?)+>[1|2|4|8|16|32|64|128]{1}(.)*$");

const static std::regex TUPLE_REGEX ("TODO");
//TODO

void LyNoteIt::setNoteType(core::NoteType __ntype) {
  core::Note::setNoteType(__ntype);
}

void LyNoteIt::addPitch(core::Pitch * __p) {
  core::Note::addPitch(__p);
}

void LyNoteIt::setPitch(core::Pitch * __p) {
  core::Note::setPitch(__p);
}

void LyNoteIt::clearPitch() {
  core::Note::clearPitch();
}

void LyNoteIt::setDuration(core::Duration * __d) {
  core::Note::setDuration(__d);
}

void LyNoteIt::setProperty(core::Property * __p) {
  core::Note::setProperty(__p);
}


core::NoteType LyNoteIt::guessNoteType(const std::string& __input) const {
  if (__input == "r" || __input == "R") {
    return core::NoteType::Rest;
  }
  else if (__input == "s" || __input == "S") {
    return core::NoteType::Rest;
  }
  else if (__input.size() > 5 && __input.substr(__input.size() - 5) == "\\rest") {
    return core::NoteType::Rest;
  }
  else if (__input.find('<') != std::string::npos &&
      __input.find('>') != std::string::npos) {
    return core::NoteType::Chord;
  }
  else if (__input.find('{') != std::string::npos &&
           __input.find('}') != std::string::npos) {
    return core::NoteType::Tuplet;
  }
  else {
    return core::NoteType::SingleNote;
  }
}

bool LyNoteIt::checkFormatThrowExp(const std::string& __pitch) const {
  if (getType() == core::NoteType::SingleNote) {
    // TODO
  }
  // TODO
}

} // namespace hautbois
} // namespace ly