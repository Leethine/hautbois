#pragma once

#ifndef BASE_BAR_H
#define BASE_BAR_H

#include "base_duration.hpp"
#include "base_note.hpp"
#include "base_voice.hpp"

namespace hautbois {
namespace core {

class BaseBar {
 private:
  mutable BaseDuration* _meter;
  mutable BaseVoice* _main_voice;
  std::vector<BaseVoice*> _temp_voices;


 protected:
  BaseDuration makeDefaultMeter() const;

 public:
  BaseBar();
  virtual ~BaseBar();
  virtual void setMeter(const UInt8 ivNum, const UInt8 ivDenom);
  virtual void setMeter(const BaseDuration& ivMeter);
  virtual void setMeter(BaseDuration* ivMeter);
  virtual void setMainVoice(BaseVoice* ivVoice);
  virtual void addTempVoice(BaseVoice* ivVoice);
  virtual BaseDuration getMeter() const;
  virtual BaseDuration * getMeterPtr() const;
  virtual BaseVoice getMainVoice() const;
  virtual BaseVoice getTempVoice(UInt8 ivNbrVoice) const;
  virtual BaseVoice * getMainVoicePtr() const;
  virtual BaseVoice * getTempVoicePtr(UInt8 ivNbrVoice) const;
  virtual bool hasTempVoice() const;
};

} // namespace core
} // namespace hautbois

#endif