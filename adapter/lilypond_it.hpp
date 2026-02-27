#include <string>

#include "symbol/duration.hpp"
#include "symbol/pitch.hpp"
#include "symbol/property.hpp"
#include "symbol/note.hpp"

namespace hautbois {
namespace ly {

class LyNote_it : public core::Note {

 protected:

  inline virtual void setNoteType(core::NoteType __ntype) {
    Note::setNoteType(__ntype);
  }

  inline virtual void addPitch(core::Pitch * __p) {
    Note::addPitch(__p);
  }

  inline virtual void setPitch(core::Pitch * __p) {
    Note::setPitch(__p);
  }

  inline virtual void clearPitch() {
    Note::clearPitch();
  }

  inline virtual void setDuration(core::Duration * __d) {
    Note::setDuration(__d);
  }

  inline virtual void setProperty(core::Property * __p) {
    Note::setProperty(__p);
  }

  virtual core::NoteType guessNoteType(const std::string& __input) const;

  virtual bool checkFormatThrowExp(const std::string& __pitch) const;

  virtual std::tuple<std::string, std::string, std::string> 
    parseSingleNote(const std::string& __pitch) const;

  virtual std::vector< std::tuple<std::string, std::string, std::string> >
    parseGroupNote(const std::string& __pitch, core::NoteType __type=core::NoteType::Chord) const;

  virtual std::string filterProperty(const std::string& __text) const;

 public:

  LyNote_it(const std::string& __token);

  LyNote_it(const LyNote_it& __n);

  LyNote_it(const LyNote_it&& __n);

  inline virtual ~LyNote_it() {
    Note::~Note();
  } 

  virtual LyNote_it& operator=(const LyNote_it& __n);

  virtual void updateDuration(const std::string& __context);

  virtual void updatePitch(const std::string& __context);

  virtual void updateProperty(const std::string& __context);

  inline virtual void setTied() {
    Note::setTied();
  }

  inline virtual void setUntied() {
    Note::setUntied();
  }

  inline virtual bool hasProperty() const {
    return Note::hasProperty();
  }

  inline virtual int pitchSize() const {
    return Note::pitchSize();
  }

  inline virtual core::NoteType getType() const {
    return Note::getType();
  }

  inline virtual char getTypeChar() const {
    return Note::getTypeChar();
  }

  inline virtual std::string getTypeStr() const {
    return Note::getTypeStr();
  }

  inline virtual bool isType(core::NoteType iType) const {
    return Note::isType(iType);
  }

  inline virtual bool isSingle() const {
    return Note::isSingle();
  }

  inline virtual bool isChord() const {
    return Note::isChord();
  }

  inline virtual bool isRest() const {
    return Note::isRest();
  }

  inline virtual bool isSilent() const {
    return Note::isSilent();
  }

  inline virtual bool isTuplet() const {
    return Note::isTuplet();
  }

  inline virtual bool isValid() const {
    return Note::isValid();
  }

  inline virtual bool isTied() const {
    return Note::isTied();
  }

  inline virtual const core::Duration * getDuration() const {
    return Note::getDuration();
  }

  inline virtual const core::Pitch * getPitch() const {
    return Note::getPitch();
  }

  inline virtual const core::Property * getProperty() const {
    return Note::getProperty();
  }

  inline virtual const std::vector<const core::Pitch *> getPitchGroup() const {
    return Note::getPitchGroup();
  }

  virtual std::string getDurationStr() const;

  virtual std::string getPitchStr() const;

  virtual std::vector<std::string> getPitchGroupStr() const;

  virtual std::string getPropertyStr() const;

  virtual std::string toString() const;

  virtual void * toStream(const std::string& __context, void * __ostream) const;

};

} // namespace hautbois
} // namespace ly