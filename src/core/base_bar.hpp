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
  BaseNote * _tonality;

 protected:
  //BaseBarProperty * _property;
  BaseDuration makeDefaultMeter() const;

 public:
  BaseBar();
  BaseBar(const BaseBar& ivRhBar);
  virtual ~BaseBar();
  virtual void setMeter(const UInt8 ivNum, const UInt8 ivDenom);
  virtual void setMeter(const BaseDuration& ivMeter);
  virtual void setMeter(BaseDuration* ivMeter);
  virtual void setMainVoice(BaseVoice* ivVoice);
  virtual void addTempVoice(BaseVoice* ivVoice);
  virtual void setTonality(BaseNote* ivNote);
  virtual void setTonality(std::string& ivName, std::string& ivAccidental);

  virtual BaseDuration getMeterCopy() const;
  virtual BaseVoice getMainVoiceCopy() const;
  virtual BaseVoice getTempVoiceCopy(UInt8 ivNbrVoice) const;
  virtual BaseNote getTonalityCopy() const;

  virtual BaseDuration* getMeterPtr() const;
  virtual BaseVoice* getMainVoicePtr() const;
  virtual BaseVoice* getTempVoicePtr(UInt8 ivNbrVoice) const;
  virtual BaseNote* getTonalityPtr() const;

  virtual bool hasTempVoice() const;
  virtual size_t countTempVoice() const;
};

} // namespace core
} // namespace hautbois

#endif