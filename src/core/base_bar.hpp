#pragma once

#ifndef BASE_BAR_H
#define BASE_BAR_H

#include "base_duration.hpp"
#include "base_note.hpp"
#include "base_voice.hpp"
#include "base_bar_property.hpp"

namespace hautbois {
namespace core {

using TempVoicePair = std::pair<BaseVoice*, BaseDuration*>;
class BaseBar {
  private:
    BaseDuration* _meter;
    BaseVoice* _main_voice;
    std::vector<TempVoicePair> _temp_voices;
    BaseBarProperty* _property;
  public:
    BaseBar();
    virtual ~BaseBar();
};

} // namespace core
} // namespace hautbois

#endif