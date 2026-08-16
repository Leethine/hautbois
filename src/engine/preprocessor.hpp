#pragma once

#ifndef HB_PREPROCESSOR_HPP
#define HB_PREPROCESSOR_HPP

#include <string>
#include <vector>
#include "ly_converter.hpp"

namespace hautbois {
namespace preprocessor {

struct InfoFile {
  unsigned int _voices;
  std::vector<std::string> _filenames;
  std::vector<std::string> _note_types;
  std::vector<std::string> _init_notes;
  unsigned int _tempo;
  unsigned int _meter_num;
  unsigned int _meter_denom;
  std::string _lang;
};

void readVoiceFile(const std::string& __fpath, LyConverter& __cvt);

void writeHeader(std::ostream& __ostream);

void writeFooter(std::ostream& __ostream, const InfoFile& __info);

void writeBody(std::ostream& __ostream, const InfoFile& __info, const unsigned int __voice);

void writeToFile(const InfoFile& __info);

void readGlobalFile(const std::string& __fpath, InfoFile& __info);

} // namespace preprocessor
} // namespace hautbois

#endif