/* 
  class Voice
  Usage:
    Voice v();
    // Important! Always add new bar before working. 
    v.newBar();
    v.addNote() ...
    v.newTempVoice();
    v.addNoteTV() ...
 */


#pragma once

#ifndef VOICE_H
#define VOICE_H

#include <vector>
#include <string>

namespace hautbois {
namespace core {

class Duration;

class Note;

//! TemporaryVoice
/*!
  TemporaryVoice container that hold the basic information
  needed for processing the temporary voices.
*/
struct TemporaryVoice {

  //! bar number of the temporary voice
  int _bar; 

  //! N-th temporary voice
  int _voice;  

  //! List (vector) of notes
  std::vector<Note *> _noteList;

};

//! Voice (base class)
/*!
  Holds the list of notes, bars numbers and needed methods.
  Built-in GC provided, added note pointer DOES NOT
  need to be freed manually, the class will do the job.
*/
class Voice {

 protected:

  //! currently-processing bar number
  /*! It serves as a "cursor" pointing to the current
      bar number being processed.
      C-style index, starting from 0.
  */
  int _currentBar;

  //! currently-processing temporary voice
  /*! It serves as a "cursor" pointing to the current
      temporary voice being processed.
      C-style index, starting from 0.
  */
  int _currentTV;

  //! new bar position
  /*! The position (the index in _noteList) where each bar starts.
  */
  std::vector<int> _newBarPos;

  //! The meter of this voice
  Duration * _meter;

  //! The meter of each bar within the voice
  std::vector<Duration *> _meterList;

  //! List (vector) of notes of the main voice
  std::vector<Note *> _noteList;

  //! duration pointer logger
  /*! GC mechanism, log all added pointers of duration (meter).
  */
  std::vector<Duration *> _durationPtrLog;

  //! note pointer logger
  /*! GC mechanism, log all added pointers of note.
  */
  std::vector<Note *> _notePtrLog;

  //! List of temporary voices
  std::vector<TemporaryVoice> _temporaryVoiceList;

  //! logDurationPtr
  /*! Save the pointer to GC stack
   * \param pointer of duration, sbould not be nullptr
   */
  virtual void logDurationPtr(Duration * __meter);

  //! logNotePtr
  /*! Save the pointer to GC stack
   * \param pointer of note, should not be nullptr
   */
  virtual void logNotePtr(Note * __note);

  Voice(const Voice&)=delete;

  Voice(const Voice&&)=delete;

  Voice& operator=(const Voice&)=delete;

  Voice& operator=(const Voice&&)=delete;

 public:

  //! Constructor of voice with 4/4 meter
  Voice();

  //! Constructor of voice with meter value provided
  Voice(const int& __num, const int& __denom);

  //! Destructor
  virtual ~Voice();

  //! Get meter
  virtual const Duration * getMeter() const;

  //! Get meter of the N-th bar (starting from 0)
  virtual const Duration * getMeter(const int& __bar) const;

  //! Get total number of bars
  virtual int getTotalBars() const;

  //! Get the size (number of notes) of the Bar
  virtual int getBarSize(const int& __bar) const;

  //! Get the size (number of notes) of the Bar and Voice
  virtual int getBarSize(const int& __bar, const int& __voice) const;

  //! Get the note at the N-th bar and N-th system (both starting from 0)
  virtual const Note * getNote(const int& __bar, const int& __nth) const;

  //! Get the note at the N-th bar and N-th system in temporary voice (all starting from 0)
  virtual const Note * getNoteTV(const int& __bar, const int& __nth, int __voice=0) const;

  //! To stream
  /*! Convert the voice to any out stream, not available in base class
   * \param __instr instruction
   * \param __ostream the out stream pointer (needs pointer casting)
   */
  virtual void * toStream(const std::string& __instr, void * __ostream) const;

  //! barHasTempVoice
  /*! Check if the bar has temporary voice
   */
  virtual bool barHasTempVoice(const int& __bar) const;

  //! getNbrOfTempVoice
  /*! Return the number of temporary voices
   */
  virtual int getNbrOfTempVoice(const int& __bar) const;

  //! barCheck
  /*! Run bar check on both main and temporary voices
   */
  virtual bool barCheck() const;

  //! copyTo
  /*! Copy to another voice
   * \param __ivoice : pointer of the voice to be copied to
   * The input voice will be cleared and filled with everything from 
   * the existing voice. If nullptr was given, not copy will happen.
   */
  virtual void copyTo(Voice * __ivoice) const;

  //! getCurrentBar
  /*! Return the current bar number being processed.
   */
  virtual int getCurrentBar() const;

  //! setCurrentBar
  /*! Set the bar number to be processed (start from 0).
   */
  virtual void setCurrentBar(const int& __bar);

  //! setCurrentTempVoice
  /*! Set the temporary voice to be processed (start from 0).
   */
  virtual void setCurrentTV(const int& __voice=0);

  //! resetNthNote
  /*! Modify the note in the voice.
   * \param __bar : the bar number (counting from 0).
   * \param __nth : the Nth note in the bar (counting from 0).
   * \param __note : the pointer to Note object
   */
  virtual void resetNthNote(const int& __bar, const int& __nth, Note * __note);

  //! resetNthNoteTempVoice
  /*! Modify the note in the voice in temporary voice.
   * \param __bar : the bar number (counting from 0).
   * \param __nth : the Nth note in the bar (counting from 0).
   * \param __voice : the Nth temp voice (counting from 0).
   * \param __note : the pointer to Note object
   */
  virtual void resetNthNoteTV(const int& __bar, const int& __nth, const int& __voice, Note * __note);

  //! addNote
  /*! Add (append) note to the main voice
   * \param __num : the numerator of the note's duration.
   * \param __denom : the denominator of the note's duration.
   * \param __pitch : pitch (or chord, tuplet) as std::string.
   */
  virtual void addNote(const int& __num, const int& __denom,
                       const std::string& __pitch);

  //! addNote
  /*! Add (append) note to the main voice
   * \param __note : the note pointer, cannot be nullptr
   */
  virtual void addNote(Note * __note);

  //! newBar
  /*! Create new bar and move the cursor to new bar.
   * \param __num : the numerator of the new bar's meter.
   * \param __denom : the denominator of the new bar's meter.
   */
  virtual void newBar(const int& __num, const int& __denom);

  //! newBar
  /*! Create new bar and move the cursor to new bar.
   * The meter will be the same as global meter.
   */
  virtual void newBar();

  //! newTempVoice
  /*! Create new temporary voice in the given bar.
   * \param __bar : n-th bar to be added new temp voice
   */
  virtual void newTempVoice(const int& __bar);

  //! newTempVoice
  /*! Create new temporary voice in the current bar.
   */
  virtual void newTempVoice();

  //! addNoteTV
  /*! Add (append) note to the temporary voice currently working on
   * \param __num : the numerator of the note's duration.
   * \param __denom : the denominator of the note's duration.
   * \param __pitch : pitch (or chord, tuplet) as std::string.
   */
  virtual void addNoteTV(const int& __num, const int& __denom,
                         const std::string& __pitch);

  //! addNoteTV
  /*! Add (append) note to the temporary voice currently working on
   * \param __note : the note's pointer.
   */
  virtual void addNoteTV(Note * __note);

  //! deleteBar
  /*! Delete n_th bar and associated notes.
   * \param __bar : the bar number.
   */
  virtual void deleteBar(const int& __bar);

  //! deleteBar
  /*! Delete current working bar and associated notes.
   */
  virtual void deleteBar();

  //! deleteBarTV
  /*! Delete n-th temporary voice on n-th bar.
   * \param __bar : the bar number.
   * \param __voice : the temporary voice number.
   */
  virtual void deleteBarTV(const int& __bar, const int& __voice);

  //! deleteBarTV
  /*! Delete the current working temporary voice in current working bar.
   */
  virtual void deleteBarTV();

  //! deleteBarTV
  /*! Delete all temporary voices on n-th bar.
   * \param __bar : the bar number.
   */
  virtual void deleteBarTV(const int& __bar);
};

} // namespace core
} // namespace hautbois

#endif