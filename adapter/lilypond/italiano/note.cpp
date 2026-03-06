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

} // namespace hautbois
} // namespace ly