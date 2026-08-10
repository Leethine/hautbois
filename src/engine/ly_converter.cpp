#include "ly_converter.hpp"
#include "../utility/hbexcept.hpp"
#include "../utility/tools.hpp"
#include "../note/duration.hpp"
#include "../hbtype/hbdefs.hpp"

#include <cctype>
#include <cstddef>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <string>

#ifndef STD_VECTOR_STR
#define STD_VECTOR_STR std::string("_VECSTR_")
#endif

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


void LyConverter::parseSingleNote(const std::string& __input, std::string& __o_pitch,
                                  int& __o_octave, std::string& __o_value) const {
  if (__input.empty()) {
    HB_THROW(std::invalid_argument);
  }
  __o_pitch.clear();
  __o_value.clear();
  __o_octave = _relative_mode ? 0 : 4;
  for (const char c: __input) {
    if (c == ',') {
      __o_octave--;
    }
    else if (c == '\'') {
      __o_octave++;
    }
  }
  std::copy_if(__input.begin(), __input.end(),
               std::back_inserter(__o_pitch),
               [](char c) { return std::isalpha(c); });

  std::copy_if(__input.begin(), __input.end(),
               std::back_inserter(__o_value),
               [](char c) { return std::isdigit(c) || c == '.'; });
  if (__o_value.empty()) {
    __o_value = _last_notevalue;
  }

  // validate
  if (!validateSingleNote(__o_pitch, __o_value)) {
    HB_THROW_MSG(std::invalid_argument, "Invalid note: " + __input);
  }
  if (_relative_mode) {
    int abs_oct = findAbsOctaveFromLast(
        _last_pitch, _last_oct_abs, __o_pitch, __o_octave);
    __o_octave = abs_oct;
  }
  if (!validateOctave(__o_octave)) {
    HB_THROW_MSG(std::invalid_argument, "Invalid octave: " + __input);
  }
}


void LyConverter::parseChord(const std::string& __input, std::vector<std::string>& __o_pitch_list,
                             std::vector<int>& __o_abs_octave_list, std::string& __o_note_value) const {
  if (__input.empty()) {
    HB_THROW(std::invalid_argument);
  }
  __o_pitch_list.clear();
  __o_pitch_list.reserve(3);
  __o_abs_octave_list.clear();
  __o_abs_octave_list.reserve(3);
  __o_note_value.clear();
  
  size_t pos1 = __input.find_first_of('<');
  size_t pos2 = __input.find_first_of('>');
  if (pos1 == std::string::npos || pos2 == std::string::npos) {
    HB_THROW_MSG(std::invalid_argument, "Invalid Chord: " + __input);
  }
  std::string chordstr = __input.substr(pos1+1, pos2-pos1-1);
  __o_note_value = __input.substr(pos2+1);
  tools::clean_string(__o_note_value);
  if (__o_note_value.empty()) {
    __o_note_value = _last_notevalue;
  }

  // process pitches in the chord
  std::vector<std::string> pitch_list;
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
  if (!validateSingleNote(pitch, __o_note_value)) {
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
  // add to out list
  __o_pitch_list.push_back(pitch);
  __o_abs_octave_list.push_back(oct);

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
    // add to output list
    __o_pitch_list.push_back(pitch);
    __o_abs_octave_list.push_back(oct);
    
    // update local relative pitch
    lastpitch_local = pitch;
    lastoct_local = oct;
  }
}

std::string LyConverter::convertSingle(const std::string& __input) {
  std::string pitchname;
  int octave;
  std::string notevalue;
  
  HB_NESTED_THROW(std::invalid_argument,
    parseSingleNote(__input, pitchname, octave, notevalue);
  )
  // update previous note
  _last_pitch = pitchname;
  _last_oct_abs = octave;
  _last_notevalue = notevalue;

  return tools::quote_str(_ly_pitch_chart.at(pitchname) + 
    std::to_string(octave))  + "," + tools::quote_str(notevalue);
}


std::string LyConverter::convertChord(const std::string& __input) {
  std::vector<std::string> pitch_list;
  std::vector<int> octave_list;
  std::string note_value;

  HB_NESTED_THROW(std::invalid_argument,
    parseChord(__input, pitch_list, octave_list, note_value);
  )

  if (!(pitch_list.size() == octave_list.size() && octave_list.size() > 1)) {
    HB_THROW_MSG(std::invalid_argument, "Failed to convert invalid chord: " + __input);
  }
  
  // update previous note
  _last_pitch = pitch_list[0];
  _last_oct_abs = octave_list[0];
  _last_notevalue = note_value;

  // write to output
  std::vector<std::string> out_pitch_list;
  out_pitch_list.reserve(octave_list.size());
  for (size_t i = 0; i < octave_list.size(); i++) {
    out_pitch_list.push_back(tools::quote_str(
      _ly_pitch_chart.at(pitch_list[i])+std::to_string(octave_list[i])    
    ));
  }

  return STD_VECTOR_STR + "({" + tools::jointstring(out_pitch_list, ',') + "})," + tools::quote_str(note_value);
}


std::string LyConverter::convertTuplet(const std::string& __input) {
  if (__input.empty()) {
    HB_THROW(std::invalid_argument);
  }

  size_t pos1 = __input.find_first_of('{');
  size_t pos2 = __input.find_first_of('}');

  // parse tuplet size
  std::string tuplet_rat = __input.substr(0,pos1);
  size_t pos_div = tuplet_rat.find_first_of('/');
  std::string tuplet_count = tuplet_rat.substr(0, pos_div);
  std::string tuplet_duration = tuplet_rat.substr(pos_div+1);
  size_t count = 0;

  try {
    // clean
    tools::clean_string(tuplet_count);
    tools::clean_string(tuplet_duration);
    // convert
    count = std::stoul(tuplet_count);
    Duration d_test (tuplet_duration);
  }
  catch(std::invalid_argument&) {
    HB_THROW_MSG(std::invalid_argument, "Failed to convert invalid Tuplet: " + __input + "  At: " + tuplet_rat);
  }
  catch(std::out_of_range&) {
    HB_THROW_MSG(std::invalid_argument, "Failed to convert invalid Tuplet: " + __input + "  At: " + tuplet_rat);
  }

  // parse notes
  std::vector<std::string> note_list;
  tools::splitstring(note_list, __input.substr(pos1+1, pos2 - pos1 - 1), ' ');

  std::vector<std::string> note_list_processed;
  note_list_processed.reserve(6);

  for (size_t i = 0; i < note_list.size(); i++) {
    std::string& current_note = note_list[i];
    if (current_note.find('<') != std::string::npos) { // chord
      std::string chord_str;
      while(i < note_list.size() && current_note.find('>') == std::string::npos) {
        chord_str.append(note_list[i]);
        chord_str.push_back(' ');
        i++;
      }
      std::vector<std::string> pitch_list;
      std::vector<int>         octave_list;
      std::string              note_value;
      HB_NESTED_THROW(std::invalid_argument, 
        parseChord(chord_str, pitch_list, octave_list, note_value);
      )
      if (!(pitch_list.size() == octave_list.size() && octave_list.size() > 1)) {
        HB_THROW_MSG(std::invalid_argument, "Invalid chord within Tuplet: " + __input + " At: " + chord_str);
      }
      // update previous note
      _last_pitch     = pitch_list[0];
      _last_oct_abs   = octave_list[0];
      _last_notevalue = note_value;

      // construct chord string for tuplet
      std::vector<std::string> pitchoctave_list;
      pitchoctave_list.reserve(3);
      for (size_t j = 0 ; j < octave_list.size(); j++) {
        pitchoctave_list.push_back(_ly_pitch_chart.at(pitch_list[j]) + std::to_string(octave_list[j]));
      }
      // add to processed note list
      note_list_processed.push_back(tools::quote_str(tools::jointstring(pitchoctave_list, '+')));
      note_list_processed.push_back(tools::quote_str(note_value));
    }
    else { // process single note
      std::string pitchname;
      int octave;
      std::string notevalue;
      HB_NESTED_THROW(std::invalid_argument, 
        parseSingleNote(current_note, pitchname, octave, notevalue);
      )
      // update previous note
      _last_pitch     = pitchname;
      _last_oct_abs   = octave;
      _last_notevalue = notevalue;

      // add to processed note list
      note_list_processed.push_back(tools::quote_str(
        _ly_pitch_chart.at(pitchname) + std::to_string(octave)
      ));
      note_list_processed.push_back(tools::quote_str(notevalue));
    }
  }

  // convert dots to 0 (as required by hautbois::Tuplet constructor)
  std::replace(tuplet_duration.begin(), tuplet_duration.end(), '.', '0');
  return tuplet_count + "," + tuplet_duration + "," + STD_VECTOR_STR +
    "(" + tools::jointstring(note_list_processed, ',') + ")";
}

std::string LyConverter::convertGrace(const std::string& __input) {
 if (__input.empty()) {
    HB_THROW(std::invalid_argument);
  }

  size_t pos1 = __input.find_first_of('{');
  size_t pos2 = __input.find_first_of('}');

  // parse notes
  std::vector<std::string> note_list;
  tools::splitstring(note_list, __input.substr(pos1+1, pos2 - pos1 - 1), ' ');

  std::vector<std::string> note_list_processed;
  note_list_processed.reserve(4);

  for (size_t i = 0; i < note_list.size(); i++) {
    std::string& current_note = note_list[i];
    
    // process single note
    std::string pitchname;
    int octave;
    std::string notevalue;
    HB_NESTED_THROW(std::invalid_argument, 
      parseSingleNote(current_note, pitchname, octave, notevalue);
    )
    // update previous note
    _last_pitch     = pitchname;
    _last_oct_abs   = octave;
    _last_notevalue = notevalue;

    // add to processed note list
    note_list_processed.push_back(tools::quote_str(
      _ly_pitch_chart.at(pitchname) + std::to_string(octave)
    ));
    note_list_processed.push_back(tools::quote_str(notevalue));
  }

  // must have more then 2 notes in grace note (aka 4 pitch,value pair as list elem) 
  if (note_list_processed.size() < 4) {
    HB_THROW_MSG(std::invalid_argument, "Failed to convert grace notes, too few: " + __input);
  }

  std::string main_value = note_list_processed.back();
  note_list_processed.pop_back();
  std::string main_pitch = note_list_processed.back();
  note_list_processed.pop_back();

  return STD_VECTOR_STR + "(" + tools::jointstring(note_list_processed, ',') + ")," +
    main_pitch + "," + main_value;
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


void LyConverter::readFromStream(std::istream& __stream) {
  std::string input_str;
  std::string additional_str;

  HB_NESTED_THROW(std::invalid_argument, 

  // TODO 
  // this is only a temporary solution, need to be improved (for example use regex, flex/bison)
  while (!__stream.eof()) {
    __stream >> input_str;
    if (input_str.find('<') != std::string::npos) {
      while (!__stream.eof() && input_str.find('>') == std::string::npos) {
        input_str.push_back(' ');
        __stream >> additional_str;
        input_str.append(additional_str);
      }
      _converted_args.push_back(convertChord(input_str));
      _note_types.push_back(CHAR_NOTETYPE_CHORD);
      input_str.clear();
    }
    else if (input_str.find('/') != std::string::npos) {
      while (!__stream.eof() && input_str.find('}') == std::string::npos) {
        input_str.push_back(' ');
        __stream >> additional_str;
        input_str.append(additional_str);
      }
      _converted_args.push_back(convertTuplet(input_str));
      _note_types.push_back(CHAR_NOTETYPE_TUPLET);
      input_str.clear();
    }
    else if (input_str.find('{') != std::string::npos) {
      while (!__stream.eof() && input_str.find('}') == std::string::npos) {
        input_str.push_back(' ');
        __stream >> additional_str;
        input_str.append(additional_str);
      }
      _converted_args.push_back(convertGrace(input_str));
      _note_types.push_back(CHAR_NOTETYPE_GRACE);
      input_str.clear();
    }
    else {
      // defaulted as single note
      _converted_args.push_back(convertSingle(input_str));
      _note_types.push_back(CHAR_NOTETYPE_SINGLE);
      input_str.clear();
    }
  }

  )
}

} // namespace hautbois