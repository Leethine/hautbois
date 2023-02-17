#include "base_note_property.hpp"

hautbois::core::BaseNoteProperty::BaseNoteProperty():
  _articulation { ArticulationEnum::UNKNOWN },
  _dynamics { DynamicsEnum::UNKNOWN },
  _ornamant { OrnamentEnum::UNKNOWN },
  _articulationVal { property_values::UNKNOWN_VALUE },
  _dynamicsVal { property_values::UNKNOWN_VALUE },
  _ornamantVal { property_values::UNKNOWN_VALUE } {
}

hautbois::core::BaseNoteProperty::~BaseNoteProperty() {
}

void hautbois::core::BaseNoteProperty::warnInvalidPropertyName(const std::string& ivArg) const {
  throw InvalidArgumentException("InvalidNotePropertyName: " + ivArg);
}

void hautbois::core::BaseNoteProperty::setArticulation(const std::string& ivName, UInt8 ivVal) {
  auto tvMap = &hautbois::core::articulation_str_enum_convert::ARTICULATION_STRING_TO_ENUM;
  if (tvMap->find(ivName) != tvMap->end()) {
    this->_articulation = tvMap->at(ivName);
    this->_articulationVal = ivVal;
  }
  else {
    throw InvalidArgumentException("articulation: " + ivName);
  }
}

void hautbois::core::BaseNoteProperty::setDynamics(const std::string& ivName, UInt8 ivVal) {
  auto tvMap = &hautbois::core::dynamics_str_enum_convert::DYNAMICS_STRING_TO_ENUM;
  if (tvMap->find(ivName) != tvMap->end()) {
    this->_dynamics = tvMap->at(ivName);
    this->_dynamicsVal = ivVal;
  }
  else {
    throw InvalidArgumentException("dynamics: " + ivName);
  }
}

void hautbois::core::BaseNoteProperty::setOrnament(const std::string& ivName, UInt8 ivVal) {
  auto tvMap = &hautbois::core::ornament_str_enum_convert::ORNAMENT_STRING_TO_ENUM;
  if (tvMap->find(ivName) != tvMap->end()) {
    this->_ornamant = tvMap->at(ivName);
    this->_ornamantVal = ivVal;
  }
  else {
    throw InvalidArgumentException("ornament: " + ivName);
  }
}

void hautbois::core::BaseNoteProperty::set(const std::string& ivName, UInt8 ivVal) {
  auto tvMapArt = &hautbois::core::articulation_str_enum_convert::ARTICULATION_STRING_TO_ENUM;
  auto tvMapDyn = &hautbois::core::dynamics_str_enum_convert::DYNAMICS_STRING_TO_ENUM;
  auto tvMapOrn = &hautbois::core::ornament_str_enum_convert::ORNAMENT_STRING_TO_ENUM;
  if (tvMapArt->find(ivName) != tvMapArt->end()) {
    this->setArticulation(ivName, ivVal);
  }
  else if (tvMapDyn->find(ivName) != tvMapDyn->end()) {
    this->setDynamics(ivName, ivVal);
  }
  else if (tvMapOrn->find(ivName) != tvMapOrn->end()) {
    this->setOrnament(ivName, ivVal);
  }
  else {
    throw InvalidArgumentException(ivName);
  }
}

void hautbois::core::BaseNoteProperty::setArticulation(const std::string& ivName) {
  this->setArticulation(ivName, property_values::DEFAULT_VALUE);
}

void hautbois::core::BaseNoteProperty::setDynamics(const std::string& ivName) {
  this->setDynamics(ivName, property_values::DEFAULT_VALUE);
}

void hautbois::core::BaseNoteProperty::setOrnament(const std::string& ivName) {
  this->setOrnament(ivName, property_values::DEFAULT_VALUE);
}

void hautbois::core::BaseNoteProperty::set(const std::string& ivName) {
  this->set(ivName, property_values::DEFAULT_VALUE);
}

bool hautbois::core::BaseNoteProperty::hasArticulation() const {
  if (this->_articulation == ArticulationEnum::UNKNOWN) {
    return true;
  }
  else {
    return false;
  }
}

bool hautbois::core::BaseNoteProperty::hasDynamics() const {
  if (this->_dynamics == DynamicsEnum::UNKNOWN) {
    return true;
  }
  else {
    return false;
  }
}

bool hautbois::core::BaseNoteProperty::hasOrnament() const {
  if (this->_ornamant == OrnamentEnum::UNKNOWN) {
    return true;
  }
  else {
    return false;
  }
}

void hautbois::core::BaseNoteProperty::clearArticulation() {
  this->_articulation = ArticulationEnum::UNKNOWN;
  this->_articulationVal = property_values::UNKNOWN_VALUE;
}

void hautbois::core::BaseNoteProperty::clearDynamics() {
  this->_dynamics = DynamicsEnum::UNKNOWN;
  this->_dynamicsVal = property_values::UNKNOWN_VALUE;
}

void hautbois::core::BaseNoteProperty::clearOrnament() {
  this->_ornamant = OrnamentEnum::UNKNOWN;
  this->_ornamantVal = property_values::UNKNOWN_VALUE;
}

void hautbois::core::BaseNoteProperty::clear() {
  this->clearArticulation();
  this->clearDynamics();
  this->clearOrnament();
}

std::pair<std::string, hautbois::UInt8> hautbois::core::BaseNoteProperty::getArticulation() const {
  if (this->hasArticulation()) {
    auto tvMap = &articulation_str_enum_convert::ARTICULATION_ENUM_TO_STRING;
    return std::make_pair(tvMap->at((this->_articulation)), this->_articulationVal);
  }
  else {
    return std::make_pair("UNKNOWN", property_values::UNKNOWN_VALUE);
  }
}

std::pair<std::string, hautbois::UInt8> hautbois::core::BaseNoteProperty::getDynamics() const {
  if (this->hasArticulation()) {
    auto tvMap = &dynamics_str_enum_convert::DYNAMICS_ENUM_TO_STRING;
    return std::make_pair(tvMap->at((this->_dynamics)), this->_dynamicsVal);
  }
  else {
    return std::make_pair("UNKNOWN", property_values::UNKNOWN_VALUE);
  }
}

std::pair<std::string, hautbois::UInt8> hautbois::core::BaseNoteProperty::getOrnament() const {
  if (this->hasArticulation()) {
    auto tvMap = &ornament_str_enum_convert::ORNAMENT_ENUM_TO_STRING;
    return std::make_pair(tvMap->at((this->_ornamant)), this->_ornamantVal);
  }
  else {
    return std::make_pair("UNKNOWN", property_values::UNKNOWN_VALUE);
  }
}
