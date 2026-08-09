#include "ly_converter.hpp"
#include "../utility/hbexcept.hpp"
#include "../utility/tools.hpp"
#include "../note/duration.hpp"

#include <cctype>
#include <cstddef>
#include <unordered_map>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>

namespace hautbois {

bool LyConverter::validateSingleNote(const std::string& __pitchname,
                                     const std::string& __duration) const {
  try {
    Duration d_test (__duration);
  }
  catch (const std::invalid_argument&) {
    return false;
  }
  return _ly_pitch_chart.find(__pitchname) != _ly_pitch_chart.end();
}

bool LyConverter::validateOctave(const int __octave) const {
  return __octave >= 0 && __octave < 9;
}

int LyConverter::findAbsOctaveFromLast(const std::string& __pitch_prev, const int __abs_oct_prev,
                                       const std::string& __pitch_next, const int __rel_oct_next) const {
  int diff = _ly_pitch_index.at(__pitch_prev) - _ly_pitch_index.at(__pitch_next) ;
  if (diff < 4 && diff > -4) {
    return __abs_oct_prev + __rel_oct_next;
  }
  else if (diff >= 4) {
    return __abs_oct_prev + __rel_oct_next + 1;
  }
  else if (diff <= -4) {
    return __abs_oct_prev + __rel_oct_next - 1;
  }
  else {
    return -9999;
  }
}

std::string LyConverter::convertSingle(const std::string& __input) {
  if (__input.empty()) {
    HB_THROW(std::invalid_argument);
  }
  std::string pitchname;
  std::string notevalue;
  int oct = _relative_mode ? 0 : 4;
  for (const char c: __input) {
    if (c == ',') {
      oct--;
    }
    else if (c == '\'') {
      oct++;
    }
  }
  std::copy_if(__input.begin(), __input.end(),
               std::back_inserter(pitchname),
               [](char c) { return std::isalpha(c); });

  std::copy_if(__input.begin(), __input.end(),
               std::back_inserter(notevalue),
               [](char c) { return std::isdigit(c) || c == '.'; });
  if (notevalue.empty()) {
    notevalue = _last_notevalue;
  }

  // validate
  if (!validateSingleNote(pitchname, notevalue)) {
    HB_THROW_MSG(std::invalid_argument, "Invalid note: " + __input);
  }
  if (_relative_mode) {
    int abs_oct = findAbsOctaveFromLast(
        _last_pitch, _last_oct_abs,
              pitchname, oct);
    oct = abs_oct;
  }
  if (!validateOctave(oct)) {
    HB_THROW_MSG(std::invalid_argument, "Invalid octave: " + __input);
  }
  
  // update previous
  _last_pitch = pitchname;
  _last_oct_abs = oct;
  _last_notevalue = notevalue;

  return tools::quote_str(_ly_pitch_chart.at(pitchname) +
    std::to_string(oct))  + "," + tools::quote_str(notevalue);
}


std::string LyConverter::convertChord(const std::string& __input) {
  if (__input.empty()) {
    HB_THROW(std::invalid_argument);
  }
  std::vector<std::string> out_pitch;
  out_pitch.reserve(3);

  size_t pos1 = __input.find_first_of('<');
  size_t pos2 = __input.find_first_of('>');
  if (pos1 == std::string::npos || pos2 == std::string::npos) {
    HB_THROW_MSG(std::invalid_argument, "Invalid Chord: " + __input);
  }
  std::string chordstr = __input.substr(pos1+1, pos2-pos1-1);
  std::string notevalue = __input.substr(pos2+1);
  auto ret_ = std::remove(notevalue.begin(), notevalue.end(), ' ');
  if (notevalue.empty()) {
    notevalue = _last_notevalue;
  }

  // process pitches in the chord
  std::vector<std::string> pitch_list;
  pitch_list.reserve(3);
  tools::splitstring(pitch_list, chordstr, ' ');
  if (pitch_list.size() < 2) {
    HB_THROW_MSG(std::invalid_argument, "Invalid Chord, too few notes: " + __input);
  }
  // process the first pitch (it is the main pitch of the chord)
  std::string pitch (pitch_list[0]);
  int oct = _relative_mode ? 0 : 4;
  while (!pitch.empty() && pitch.back() == ',') {
    oct--;
    pitch.pop_back();
  }
  while (!pitch.empty() && pitch.back() == '\'') {
    oct++;
    pitch.pop_back();
  }
  if (!validateSingleNote(pitch, notevalue)) {
    HB_THROW_MSG(std::invalid_argument, "Invalid Chord: " + __input);
  }
  if (_relative_mode) {
    int abs_oct = findAbsOctaveFromLast(
        _last_pitch, _last_oct_abs, pitch, oct);
    oct = abs_oct;
  }
  if (!validateOctave(oct)) {
    HB_THROW_MSG(std::invalid_argument, "Invalid Chord octave: " + __input + " At: " + pitch_list[0]);
  }
  // record the first pitch in chord as previous pitch
  _last_pitch = pitch;
  _last_oct_abs = oct;
  _last_notevalue = notevalue;
  
  out_pitch.push_back("\"" + _ly_pitch_chart.at(pitch) + std::to_string(oct) + "\"");

  // process the rest of the chord
  std::string lastpitch_local = pitch;
  int lastoct_local = oct;
  // relative mode applies locally within the chord 
  for (size_t i = 1; i < pitch_list.size(); i++) {
    pitch = pitch_list[i];
    oct = _relative_mode ? 0 : 4;
    while (!pitch.empty() && pitch.back() == ',') {
      oct--;
      pitch.pop_back();
    }
    while (!pitch.empty() && pitch.back() == '\'') {
      oct++;
      pitch.pop_back();
    }
    if (!validateSingleNote(pitch, "4")) {
      HB_THROW_MSG(std::invalid_argument, "Invalid Chord pitch: " + __input + " At: " + pitch_list[i]);
    }
    if (_relative_mode) {
      int abs_oct = findAbsOctaveFromLast(
          lastpitch_local, lastoct_local, pitch, oct);
      oct = abs_oct;
    }
    if (!validateOctave(oct)) {
      HB_THROW_MSG(std::invalid_argument, "Invalid Chord octave: " + __input + " At: " + pitch_list[i]);
    }
    out_pitch.push_back(tools::quote_str(_ly_pitch_chart.at(pitch) + std::to_string(oct)));
    
    // update local relative pitch
    lastpitch_local = pitch;
    lastoct_local = oct;
  }
  
  return tools::jointstring(out_pitch, ',') + "," + tools::quote_str(notevalue);
}


std::string LyConverter::convertTuplet(const std::string& __input) {
}


std::string LyConverter::convertGrace(const std::string& __input) {
}

LyConverter::LyConverter(const std::string& __lang, const std::string& __init_note, bool __relative_mode) :
  _ly_pitch_chart (), _ly_abs_octave_chart (), _ly_rel_octave_chart (), _ly_pitch_index (),
  _last_pitch (), _last_oct_abs (4), _last_notevalue (), _note_types (), _converted_args (),
  _relative_mode (__relative_mode) {

  std::unordered_map<std::string, std::string> tmp_name_chart;
  std::unordered_map<std::string, int>         tmp_name_index;
  std::unordered_map<std::string, std::string> tmp_acc_chart;
  // set language
  if (__lang == "it") {
    tmp_name_chart = {{"do","C"},{"re","D"},{"mi","E"},{"fa","F"},{"sol","G"},{"la","A"},{"si","B"}};
    tmp_name_index = {{"do",1},{"re",2},{"mi",3},{"fa",4},{"sol",5},{"la",6},{"si",7}};
    tmp_acc_chart = {{"", "n"},{"d","#"},{"b","b"},{"dd","x"},{"bb","B"}};
  }
  else if (__lang == "de") {
    tmp_name_chart = {{"c","C"},{"d","D"},{"e","E"},{"f","F"},{"g","G"},{"a","A"},{"h","B"}};
    tmp_name_index = {{"c",1},{"d",2},{"e",3},{"f",4},{"g",5},{"a",6},{"b",7},{"h",7}};
    tmp_acc_chart = {{"", "n"},{"is","#"},{"es","b"},{"isis","x"},{"eses","B"}};
  }
  else if (__lang == "en") {
    tmp_name_chart = {{"c","C"},{"d","D"},{"e","E"},{"f","F"},{"g","G"},{"a","A"},{"b","B"}};
    tmp_name_index = {{"c",1},{"d",2},{"e",3},{"f",4},{"g",5},{"a",6},{"b",7}};
    tmp_acc_chart = {{"", "n"},{"s","#"},{"f","b"},{"ss","x"}, {"x","x"},{"ff","B"}};
  }
  else {
    HB_THROW_MSG(std::invalid_argument, std::string("Invalid language opion."));
  }

  // construct full pitchname map
  for (auto name_it = tmp_name_chart.begin(); name_it != tmp_name_chart.end(); name_it++) {
    for (auto acc_it = tmp_acc_chart.begin(); acc_it != tmp_acc_chart.end(); acc_it++) {
      std::string key = name_it->first + acc_it->first;
      std::string val = name_it->second + acc_it->second;
      _ly_pitch_chart[key] = val;
      _ly_pitch_index[key] = tmp_name_index.at(name_it->first);
    }
  }
  _ly_pitch_chart["r"] = "R";
  _ly_pitch_chart["s"] = "S";

  if (__lang == "de") { // manually add german note name due to 'B' and 'H' confusion
    _ly_pitch_chart["b"] = "Bb";
    _ly_pitch_chart["bes"] = "BB";
    _ly_pitch_chart["bis"] = "B";
    _ly_pitch_chart["bes"] = "BB";
    _ly_pitch_chart["bisis"] = "B#";
    _ly_pitch_index["b"] = 7;
    _ly_pitch_index["bes"] = 7;
    _ly_pitch_index["bis"] = 7;
    _ly_pitch_index["beses"] = 7;
    _ly_pitch_index["bisis"] = 7;
  }

  // create octave chart
  _ly_abs_octave_chart = {{"'", 5},{"''", 6},{"'''", 7},{"''''", 8},
    {"", 4},{",", 3},{",,", 2},{",,,", 1},{",,,,", 0}};
  _ly_rel_octave_chart = {{"'", 1},{"''", 2},{"'''", 3},{"''''", 4},
    {"", 0},{",", -1},{",,", -2},{",,,", -3},{",,,,", -4}};

  // set initial note
  // process initial note value
  std::copy_if(__init_note.begin(), __init_note.end(),
    std::back_inserter(_last_notevalue),
    [](char c) { return std::isdigit(c) || c == '.'; });
  if (_last_notevalue.empty()) {
    _last_notevalue = "4";
  }

  // process initial octave
  std::string oct_str;
  std::copy_if(__init_note.begin(), __init_note.end(),
    std::back_inserter(oct_str),
    [](char c) { return c == '\'' || c == ','; });
  for (char c : oct_str) {
    if (c == ',') {
      _last_oct_abs--;
    }
    else {
      _last_oct_abs++;
    }
  }

  // process initial pitch name
  std::copy_if(__init_note.begin(), __init_note.end(),
    std::back_inserter(_last_pitch),
    [](char c) { return std::isalpha(c); });
  
  // validate initial pitch
  if (_ly_pitch_chart.find(_last_pitch) == _ly_pitch_chart.end()) {
    HB_THROW_MSG(std::invalid_argument, "Invalid initialization note (pitch) format: " + __init_note);
  }
  // validate initial octave
  if (_last_oct_abs < 0 || _last_oct_abs > 8) {
    HB_THROW_MSG(std::invalid_argument, "Invalid initialization note (pitch octave) format: " + __init_note);
  }
  // validate initial duration
  try {
    Duration d_test (_last_notevalue);
  }
  catch (const std::invalid_argument&) {
    HB_THROW_MSG(std::invalid_argument, "Invalid initialization note (value) format: " + __init_note);
  }
}



} // namespace hautbois