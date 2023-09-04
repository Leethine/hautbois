#include "base_bar.hpp"

hautbois::core::BaseBar::BaseBar() :
  _meter { nullptr },
  _main_voice { nullptr }
{}

hautbois::core::BaseBar::~BaseBar() {
  if (_meter != nullptr) {
    delete _meter;
  }
  if (_main_voice != nullptr) {
    delete _main_voice;
  }
}

hautbois::core::BaseDuration hautbois::core::BaseBar::makeDefaultMeter() const {
  return BaseDuration(UInt8(4), UInt8(4));
}

void hautbois::core::BaseBar::setMeter(const UInt8 ivNum, const UInt8 ivDenom) {
  if (_meter != nullptr) {
    delete _meter;
  }
  _meter = new BaseDuration(ivNum, ivDenom);
}

void hautbois::core::BaseBar::setMeter(const BaseDuration& ivMeter) {
  if (_meter != nullptr) {
    delete _meter;
  }
  _meter = new BaseDuration(ivMeter);
}

void hautbois::core::BaseBar::setMeter(BaseDuration* ivMeter) {
  if (_meter != nullptr) {
    delete _meter;
  }
  if (ivMeter != nullptr) {
    _meter = ivMeter;
  }
}

void hautbois::core::BaseBar::setMainVoice(BaseVoice* ivVoice) {
  if (_main_voice != nullptr) {
    delete _main_voice;
  }
  if (ivVoice != nullptr) {
    _main_voice = ivVoice;
  }
}

void hautbois::core::BaseBar::addTempVoice(BaseVoice* ivVoice) {
  if (ivVoice != nullptr) {
    _temp_voices.push_back(ivVoice);
  }
}

hautbois::core::BaseDuration hautbois::core::BaseBar::getMeter() const {
  if (_meter == nullptr) {
    return makeDefaultMeter();
  }
  return * _meter;
}

hautbois::core::BaseDuration * hautbois::core::BaseBar::getMeterPtr() const {
  if (_meter == nullptr) {
    _meter = new BaseDuration(UInt8(4), UInt8(4)); 
  }
  return _meter;
}

hautbois::core::BaseVoice hautbois::core::BaseBar::getMainVoice() const {
  if (_main_voice == nullptr) {
    _main_voice = new BaseVoice();
  }
  return *_main_voice;
}

hautbois::core::BaseVoice hautbois::core::BaseBar::getTempVoice(UInt8 ivNbrVoice) const {
  if (_temp_voices.empty()) {
    return BaseVoice();
  }
  else if (ivNbrVoice >= _temp_voices.size()) {
    return *_temp_voices.back();
  }
  else {
    return *_temp_voices[ivNbrVoice];
  }
}

hautbois::core::BaseVoice * hautbois::core::BaseBar::getMainVoicePtr() const {
  if (_main_voice == nullptr) {
    _main_voice = new BaseVoice();
  }
  return _main_voice;
}

hautbois::core::BaseVoice * hautbois::core::BaseBar::getTempVoicePtr(UInt8 ivNbrVoice) const {
  if (_temp_voices.empty()) {
    return nullptr;
  }
  else if (ivNbrVoice >= _temp_voices.size()) {
    return _temp_voices.back();
  }
  else {
    return _temp_voices[ivNbrVoice];
  }
}

bool hautbois::core::BaseBar::hasTempVoice() const {
  return !_temp_voices.empty();
}
