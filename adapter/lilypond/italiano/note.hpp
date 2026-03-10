#pragma once

#include "adapter/lilypond/duration.hpp"
#include "adapter/lilypond/property.hpp"
#include "adapter/lilypond/italiano/pitch.hpp"
#include "symbol/note.hpp"

#include <string>

namespace hautbois {
namespace ly {

class LyNoteIt : public core::Note {

 protected:

  virtual void setNoteType(core::NoteType __ntype);

  virtual void addPitch(core::Pitch * __p);

  virtual void setPitch(core::Pitch * __p);

  virtual void clearPitch();

  virtual void setDuration(core::Duration * __d);

  virtual void setProperty(core::Property * __p);

  virtual core::NoteType guessNoteType(const std::string& __input) const;

  virtual bool checkFormatThrowExp(const std::string& __pitch) const;

  virtual std::tuple<std::string, std::string, std::string> 
    parseSingleNote(const std::string& __pitch) const;

  virtual std::vector< std::tuple<std::string, std::string, std::string> >
    parseGroupNote(const std::string& __pitch, core::NoteType __type=core::NoteType::Chord) const;

  virtual std::string filterProperty(const std::string& __text) const;

 public:

  LyNoteIt(const std::string& __token);

  LyNoteIt(const std::string& __token, bool flag_singlenote = false);

  LyNoteIt(const LyNoteIt& __n);

  LyNoteIt(const LyNoteIt&& __n);

  virtual ~LyNoteIt();

  virtual LyNoteIt& operator=(const LyNoteIt& __n);

  virtual void updateDuration(const std::string& __context);

  virtual void updatePitch(const std::string& __context);

  virtual void updateProperty(const std::string& __context);

  virtual void setTied();

  virtual void setUntied();

  virtual bool hasProperty() const;

  virtual int pitchSize() const;

  virtual core::NoteType getType() const;

  virtual char getTypeChar() const;

  virtual std::string getTypeStr() const;

  virtual bool isType(core::NoteType iType) const;

  virtual bool isSingle() const;

  virtual bool isChord() const;

  virtual bool isRest() const;

  virtual bool isSilent() const;

  virtual bool isTuplet() const;

  virtual bool isValid() const;

  virtual bool isTied() const;

  virtual const core::Duration * getDuration() const;

  virtual const core::Pitch * getPitch() const;

  virtual const core::Property * getProperty() const;

  virtual const std::vector<const core::Pitch *> getPitchGroup() const;

  virtual std::string getDurationStr() const;

  virtual std::string getPitchStr() const;

  virtual std::vector<std::string> getPitchGroupStr() const;

  virtual std::string getPropertyStr() const;

  virtual std::string toString() const;

  virtual void * toStream(const std::string& __context, void * __ostream) const;

};

} // namespace hautbois
} // namespace ly
