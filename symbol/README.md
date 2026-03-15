# Dev note

## Objects
- duration.hpp
- pitch.hpp
- property.hpp
- note.hpp
- note_group.hpp
- note_sequence.hpp
- note_single.hpp
- note_chord.hpp
- note_tuple.hpp
- note_grace.hpp
- note_appoggiatura.hpp
- note_acciaccatura.hpp

## Explanation

| Symbol | File | Explanation | Inherits |
|---|---|---|---|
| Duration | duration.hpp | Duration represents the note value (duration) or meter | Base |
| Pitch | pitch.hpp | Pitch defines the pitch's name and other information / methods | Base |
| Property | property.hpp | Property contains note's property such as ornaments and dynamics, it is stored as free-text (fundamentally, char array) | Base |
| Note | note.hpp | Row 2, Col 2 | Base, Abstract |
| NoteGroup | note_group.hpp | NoteGroup represents note with multiple pitches | NoteGrop : Note, Abstract |
| NoteSequence | note_sequence.hpp | NoteSequence represents note with multiple single notes, or pitches associated with duration | NoteSequence : NoteGroup, Abstract |
| SingleNote | note_single.hpp | Single note, single pitch and duration | SingleNote : Note |
| Chord | note_chord.hpp | Represents a Chord (a group of pitches plus the note value) | Chord : NoteGroup |
| Tuplet | note_tuplet.hpp | Tuplet is a sequence of single notes summing up to a pre-defined note value | Tuple : NoteSequence |
| GraceNote | note_grace.hpp | A main note with some decorative notes | GraceNote : NoteSequence |
| Appoggiatura | note_appoggiatura.hpp | A special type of grace note | Appoggiatura : GraceNote |
| Acciaccatura | note_acciaccatura.hpp | A special type of grace note | Acciaccatura : GraceNote |

## Notes on exception throwing

1. The constructor of Pitch and Duration checks the format and throw exceptions in case of invalid input
2. In Note, `_property` can be `nullptr` (or have `nullptr` in its elements), as a result, the old pointer to `Property` must be freed even if `nullptr` is provided. (That is to say, for _pitch and _duration, `nullptr` should be checked and blocked from adding to the vector).
3. `bool Note::hasXXX(size_t pos) const` methods do not throw exception, if out of rance, false is returned. The logic was simple, if the user provides an out of range index, then naturally there is nothing on that index, and `false` is returned.
4. `T * Note::getXXX(size_t pos) const` methods do not throw exceptions in case of out of range. However, nullptr will be returned.
5. The user must check beforehand, either with `getXXX(pos) == nullptr` or using `hasXXX(pos)`.
6. `void setTied(pos)` and `void isTied(pos)` method do no throw exceptions, if out of range, no action is performed, or false returned.
7. Use `HB_THROW_*` or `HB_NESTED_THROW_*` macros to perform exception handling, must free the memory of objects already allocated.

##### Nested throw example
(e.g. Note calls==> Pitch() 
       |              |
  nested expt     first expt    