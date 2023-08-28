#include "base_bar_property.hpp"

hautbois::core::BaseBarProperty::BaseBarProperty() {}
hautbois::core::BaseBarProperty::~BaseBarProperty() {}
bool hautbois::core::BaseBarProperty::setTempo(const std::string& ivName) {}
std::string hautbois::core::BaseBarProperty::getTempo() const {}
bool hautbois::core::BaseBarProperty::setTempoChange(const std::string& ivName) {}
std::string hautbois::core::BaseBarProperty::getTempoChange() const {}
bool hautbois::core::BaseBarProperty::setTempoValue(const UInt16 ivValue) {}
hautbois::UInt16 hautbois::core::BaseBarProperty::getTempoValue() const {}
bool hautbois::core::BaseBarProperty::setTempoChangeStartPoint(const BaseDuration& ivDuration) {}
hautbois::core::BaseDuration hautbois::core::BaseBarProperty::getTempoChangeStartPoint() const {}