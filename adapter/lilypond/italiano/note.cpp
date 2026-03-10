#include "note.hpp"

namespace hautbois {
namespace ly {

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
  if (__input.size() > 0 && (__input[0] == 'r' || __input[0] == 'R')) {
    return core::NoteType::Rest;
  }
  else if (__input.size() > 0 && (__input[0] == 's' || __input[0] == 'S')) {
    return core::NoteType::Silence;
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
  else if (getType() == core::NoteType::Chord) {
    // TODO
  }
  else if (getType() == core::NoteType::Tuplet) {
    // TODO
  }
  else {
    return true;
  }
  // TODO
}

} // namespace hautbois
} // namespace ly