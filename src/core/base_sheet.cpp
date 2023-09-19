#include "base_sheet.hpp"
hautbois::core::BaseSheet::BaseSheet() {
  _opus_number = 0;

};
  
hautbois::core::BaseSheet::BaseSheet(BaseSheet& ivRh) {
  _title = ivRh._title;
  _subtitle = ivRh._subtitle;
  _subsubtitle = ivRh._subsubtitle;
  _composer = ivRh._composer;

  _opus = ivRh._opus;
  _opus_system = ivRh._opus_system;
  _opus_number = ivRh._opus_number;
  _work_type = ivRh._work_type;
  std::vector<std::string> _tags =std::vector<std::string>(ivRh._tags);
  for (auto it = ivRh._bars.begin(); it != ivRh._bars.end(); it++) {
    _bars.push_back(new BaseBar(*(*it)));
  }
}

void hautbois::core::BaseSheet::setTitle(const std::string& ivTitle) {
  _title = ivTitle;
}

void hautbois::core::BaseSheet::setSubtitle(const std::string& ivTitle) {
  _subtitle = ivTitle;
}

void hautbois::core::BaseSheet::setSubsubTitle(const std::string& ivTitle) {
  _subsubtitle = ivTitle;
}

void hautbois::core::BaseSheet::setComposer(const std::string& ivName) {
  _composer = ivName;
}

void hautbois::core::BaseSheet::setOpus(const std::string& ivOpusSystem, const UInt32 ivOpusNumber) {
  _opus_system = ivOpusSystem;
  _opus_number = ivOpusNumber;
  _opus = ivOpusSystem + " " + std::to_string(ivOpusNumber);
}

std::string hautbois::core::BaseSheet::getTitle() const {
  return _title;
}

std::string hautbois::core::BaseSheet::getSubtitle() const {
  return _subtitle;
}

std::string hautbois::core::BaseSheet::getSubsubtitle() const {
  return _subsubtitle;
}

std::string hautbois::core::BaseSheet::getComposer() const {
  return _composer;
}

std::string hautbois::core::BaseSheet::getOpus() const {
  return _opus;
}

std::string hautbois::core::BaseSheet::getOpusSystem() const {
  return _opus_system;
}

hautbois::UInt32 hautbois::core::BaseSheet::getOpusNumber() const {
  return _opus_number;
}

hautbois::UInt32 hautbois::core::BaseSheet::countBars() const {
  return _bars.size();
}

hautbois::core::BaseBar * hautbois::core::BaseSheet::getBarNumber(const UInt32 ivBarNbr) const {
  if (ivBarNbr >= _bars.size()) {
    return _bars.back();
  }
  else {
    return _bars[ivBarNbr];
  }
}

void hautbois::core::BaseSheet::appendBar(BaseBar * ivNewBar) {
  if (ivNewBar != nullptr) {
    _bars.push_back(ivNewBar);
  }
}
