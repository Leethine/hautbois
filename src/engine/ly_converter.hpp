#pragma once

#include <istream>
#include <tuple>
#ifndef LY_CONVERTER_HPP
#define LY_CONVERTER_HPP

#include <map>
#include <string>
#include <vector>
#include <iostream>

#define _VECSTR_(STR) std::vector<std::string>(STR)

namespace hautbois {

class LyConverter final {
private:
  std::map<std::string, std::string> _ly_pitch_chart;
  std::map<std::string, int> _ly_abs_octave_chart;
  std::map<std::string, int> _ly_rel_octave_chart;
  std::map<std::string, int> _ly_pitch_index;

  std::string _last_pitch;
  int _last_oct_abs;
  std::string _last_notevalue;
  std::vector<char> _note_types;
  std::vector<std::string> _converted_args;
  bool _relative_mode;

//protected:
public:
  bool validateSingleNote(const std::string& __pitchname, const std::string& __duration) const;
  bool validateOctave(const int __octave) const;
  char guessNoteType(const std::string& __input) const;
  int findAbsOctaveFromLast(const std::string& __pitch_prev, const int __abs_oct_prev,
                            const std::string& __pitch_next, const int __rel_oct_next) const;
  void parseSingleNote(const std::string& __input, std::string& __o_pitch, int& __o_octave,
                       std::string& __o_value) const;
  void parseChord(const std::string& __input, std::vector<std::string>& __o_pitch_list,
                  std::vector<int>& __o_abs_octave_list, std::string& __o_note_value) const;
  std::string convertSingle(const std::string& __input);
  std::string convertChord(const std::string& __input);
  std::string convertTuplet(const std::string& __input);
  std::string convertGrace(const std::string& __input);

//public:
  LyConverter(const std::string& __lang, const std::string& __init_note, bool __relative_mode = true);
  LyConverter(LyConverter&) = delete;
  LyConverter(LyConverter&&) = delete;
  inline ~LyConverter() {}

  //void operator<<(const std::string& __iput);
  //void readFromStream(const std::istream& __stream);
  //void readFromFile(const std::string& __fpath);

  /* Return the argument passed to the addNote method in BaseVoice class */
  //std::string getArgs(const size_t __pos) const;
  //size_t size() const;


  /////////////////////
  inline std::string getLastPitch() const {
    return _last_pitch;
  }

  inline int getLastOctave() const {
    return _last_oct_abs;
  }

  inline std::string getLastNoteValue() const {
    return _last_notevalue;
  }

};

} // namespace hautbois

#endif