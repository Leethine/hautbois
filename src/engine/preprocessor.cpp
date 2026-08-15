#include <cctype>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include "preprocessor.hpp"
#include "../utility/tools.hpp"

#ifndef _VECSTR_
#define _VECSTR_(LST) std::vector<std::string>(LST)
#endif

namespace hautbois {
namespace preprocessor {


void readVoiceFile(const std::string& __fpath, LyConverter& __cvt) {
  std::filesystem::path filepath (__fpath);
  if (!(std::filesystem::exists(filepath) && std::filesystem::is_regular_file(filepath))) {
    throw std::runtime_error("Voice file \'" + __fpath + "\' does not exist or is a directory.");
    return;
  }

  std::ifstream fs (__fpath);
  if (!fs.is_open()) {
    throw std::runtime_error("Failed to open voice file \'" + __fpath + "\'");
    return;
  }

  __cvt.readFromStream(fs);
}

void writeHeader(std::ostream& __ostream) {
  auto& os = __ostream;
  os << "#include <string> \n"
     << "#include <vector> \n"
     << "#include <iostream> \n"
     << "#include \"hautbois/hb_note.hpp\" \n"
     << "#include \"hautbois/basic_voice.hpp\" \n"
     << "#include \"hautbois/hb_defs.hpp\" \n";

  os << "using namespace hautbois; \n\n"
     << "int main() { \n"
     << "try {\n\n"
     << "//////// BEGIN VOICES ////////\n\n";
}

void writeFooter(std::ostream& __ostream) {
  auto& os = __ostream;
  os << "\n//////// END VOICES ////////\n\n}\n"
     << "catch(const std::invalid_argument&) { std::cerr << e.what() << std::endl; }\n"
     << "catch(const std::runtime_error&)    { std::cerr << e.what() << std::endl; }\n"
     << "catch(const std::out_of_range&)     { std::cerr << e.what() << std::endl; }\n";

  os << "} //try \n\n"
     << "return 0;\n} //main";
}

void writeBody(std::ostream& __ostream, const InfoFile& __info, const unsigned int __voice) {
  auto& fs = __ostream;
    
  // voice declaration
  std::string voicename ("voice" + std::to_string(__voice));
  std::string voicename_upper (voicename);
  for (char& c : voicename_upper) { c = std::toupper(c); }
  
  fs << "\n//////// BEGIN " << voicename_upper << "////////\n"
     << "BasicVoice<" << __info._note_types[__voice]
     << "> " << voicename << "("
     << std::to_string(__info._meter_num) << ","
     << std::to_string(__info._meter_num) << ","
     << std::to_string(__info._tempo) + ");\n" ;
  
  // write notes
  LyConverter cvt(__info._lang, __info._init_notes[__voice]);
  readVoiceFile(__info._filenames[__voice], cvt);
  for (size_t i = 0; i < cvt.size(); i++) {
    fs << voicename << ".addnote(" << cvt.getArgs(i) << ");\n";
  }
  fs << "//////// END " << voicename_upper << "////////\n";
}


void writeToFile(const InfoFile& __info) {
    std::filesystem::path filepath ("__PREPROCESSED__.cpp");
    if (std::filesystem::exists(filepath) && !std::filesystem::is_regular_file(filepath)) {
      throw std::runtime_error("File \'__PREPROCESSED__.cpp\' already exist and cannot be overriden.");
      return;
    }
    else if (std::filesystem::exists(filepath) && std::filesystem::is_regular_file(filepath)) {
      std::filesystem::remove(filepath);
    }

    std::ofstream fs (filepath);
    //////////
    writeHeader(fs);

    for (unsigned int i = 0; i < __info._voices; i++) {
      std::cout << "Reading voice file: '" << __info._filenames[i] << "' ..." << std::endl;
      writeBody(fs, __info, i);
    }

    writeFooter(fs);
    //////////
}

void readGlobalFile(const std::string& __fpath, InfoFile& __info) {
  std::cout << "Reading __info file..." << std::endl; 

  std::filesystem::path filepath (__fpath);
  if (!(std::filesystem::exists(filepath) && std::filesystem::is_regular_file(filepath))) {
    throw std::runtime_error("Info file \'" + __fpath + "\' does not exist or is invalid.");
    return;
  }

  std::ifstream fs (__fpath);
  if (!fs.is_open()) {
    throw std::runtime_error("Failed to open info definition file \'" + __fpath + "\'");
    return;
  }

  __info._voices = 0;
  __info._filenames.clear();
  __info._note_types.clear();
  __info._init_notes.clear();
  __info._tempo = 0;
  __info._meter_num = 4;
  __info._meter_denom = 4;
  __info._lang.clear();

  //TODO ugly code
  // temporary solution - need to use flex
  char line[100];
  std::string meter_str;
  std::string tempo_str;
  std::vector<std::string> pair_;
  size_t line_count = 0;
  while (!fs.eof()) {
    fs.getline(line, 100);
    line_count++;
    if (std::strcmp("BEGIN", line) == 0) {
      fs.getline(line, 100);
      line_count++;
      while (std::strcmp("END", line)) {
        tools::splitstring(pair_, std::string(line), ':');
        if (pair_.size() == 2) {
          tools::clean_string(pair_[0]);
          tools::clean_string(pair_[1]);
          if (pair_[0] == "meter") {
            meter_str = pair_[1];
          }
          else if (pair_[0] == "tempo") {
            tempo_str = pair_[1];
          }
          else if (pair_[0] == "lang") {
            __info._lang = pair_[1];
          }
          else if (pair_[0] == "score") {
            __info._filenames.push_back(pair_[1]);
          }
          else if (pair_[0] == "notetype") {
            __info._note_types.push_back(pair_[1]);
          }
          else if (pair_[0] == "initnote") {
            __info._init_notes.push_back(pair_[1]);
          }
        }
        else {
          throw std::invalid_argument("Invalid line: \n At line " + 
            std::to_string(line_count) + " ==> " + std::string(line));
        }
        fs.getline(line, 100);
        line_count++;
      }
    }
  }

  tools::clean_string(tempo_str);
  tools::clean_string(meter_str);
  tools::splitstring(pair_, meter_str, '/');
  if (pair_.size() != 2) {
    throw std::invalid_argument("Invalid meter: " + meter_str);
  }

  try {
    __info._meter_num   = std::stoul(pair_[0]);
    __info._meter_denom = std::stoul(pair_[1]);
    __info._tempo       = std::stoul(tempo_str);
  }
  catch(std::invalid_argument&) {
    throw std::runtime_error("Failed to convert ill-formatted meter or tempo.");
  }
  catch(std::out_of_range&) {
    throw std::runtime_error("Failed to convert ill-formatted meter or tempo.");
  }

  if (!(__info._note_types.size() == __info._filenames.size() && 
        __info._note_types.size() == __info._init_notes.size())) {
    throw std::runtime_error("Error occurred while checking info file.");
  }

  __info._voices = __info._note_types.size();
}

} // namespace preprocessor
} // namespace hautbois

#ifdef __HB_PREPROCESSOR_MAIN__

int main() {
  try {
    hautbois::preprocessor::InfoFile info;
    hautbois::preprocessor::readGlobalFile("__info", info);
    hautbois::preprocessor::writeToFile(info);
  }
  catch(std::invalid_argument& e) {
    std::cerr << "Invalid argument error occurred: \n" << e.what() << "\n"
              << "(!) Please check your info definition file and voice files." << std::endl;
    return 1;
  }
  catch(std::runtime_error& e) {
    std::cerr << "Runtime error occurred: \n" << e.what() << "\n"
              << "(!) Make sure you are running this program in a valid directory." << std::endl;
    return 1;
  }
  catch(std::out_of_range& e) {
    std::cerr << "Out of range error occurred: \n" << e.what() << "\n"
              << "(!) Please check your info definition file." << std::endl;
    return 1;
  }

return 0;
}

#endif