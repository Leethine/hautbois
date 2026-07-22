#include "property.hpp"
#include "../hbtype/hbconst.hpp"
#include "../utility/tools.hpp"

#include <algorithm>
#include <utility>

namespace hautbois {

void Property::setFreeText(const std::string& __freetext) {
  tools::splitstring(_list_of_marks, __freetext, ' ');
  for (auto it = _list_of_marks.begin(); it != _list_of_marks.end(); it++) {
    if (!isValidMark(*it)) {
      _list_of_marks.erase(it);
      it--;
    }
  }
}

bool Property::isValidMark(const std::string& __mark) const {
  const auto& vld1 = hbconst::VALID_PROPERTY_ARTICULATION;
  const auto& vld2 = hbconst::VALID_PROPERTY_DYNAMIC;
  const auto& vld3 = hbconst::VALID_PROPERTY_ORNAMENT;
  const auto& vld4 = hbconst::VALID_PROPERTY_CONTROL;
  bool isvalid = std::find(vld1.cbegin(), vld1.cend(), __mark) != vld1.cend() ||
                 std::find(vld2.cbegin(), vld2.cend(), __mark) != vld2.cend() ||
                 std::find(vld3.cbegin(), vld3.cend(), __mark) != vld3.cend() ||
                 std::find(vld4.cbegin(), vld4.cend(), __mark) != vld4.cend();

  return isvalid;
}

Property::Property() : _list_of_marks() {
}

Property::Property(const std::string& __freetext) : Property() {
  Property::setFreeText(__freetext);
}
  
Property::Property(const Property& __p) : Property(std::forward<const Property&&>(__p)) {
}

Property::Property(const Property&& __p) : Property(__p.toString()) {
}

Property::~Property() {
}

std::vector<std::string> Property::toList() const {
  return _list_of_marks;
}

std::string Property::toString() const {
  return tools::jointstring(_list_of_marks, ' ');
}

std::string Property::getDynamic() const {
  const auto& vld = hbconst::VALID_PROPERTY_DYNAMIC;
  auto it_target = vld.cend();
  for (auto it = _list_of_marks.cbegin(); it != _list_of_marks.cend(); it++) {
    it_target = std::find(vld.cbegin(), vld.cend(), *it);
    if (it_target != vld.cend()) {
      break;
    }
  }
  if (it_target != vld.cend()) {
    return *it_target;
  }
  else {
    return "";
  }
}

std::string Property::getOrnament() const {
  const auto& vld = hbconst::VALID_PROPERTY_ORNAMENT;
  auto it_target = vld.cend();
  for (auto it = _list_of_marks.cbegin(); it != _list_of_marks.cend(); it++) {
    it_target = std::find(vld.cbegin(), vld.cend(), *it);
    if (it_target != vld.cend()) {
      break;
    }
  }
  if (it_target != vld.cend()) {
    return *it_target;
  }
  else {
    return "";
  }
}

std::string Property::getArticulation() const {
  const auto& vld = hbconst::VALID_PROPERTY_ARTICULATION;
  auto it_target = vld.cend();
  for (auto it = _list_of_marks.cbegin(); it != _list_of_marks.cend(); it++) {
    it_target = std::find(vld.cbegin(), vld.cend(), *it);
    if (it_target != vld.cend()) {
      break;
    }
  }
  if (it_target != vld.cend()) {
    return *it_target;
  }
  else {
    return "";
  }
}

std::string Property::getExprCtrl() const {
  const auto& vld = hbconst::VALID_PROPERTY_CONTROL;
  auto it_target = vld.cend();
  for (auto it = _list_of_marks.cbegin(); it != _list_of_marks.cend(); it++) {
    it_target = std::find(vld.cbegin(), vld.cend(), *it);
    if (it_target != vld.cend()) {
      break;
    }
  }
  if (it_target != vld.cend()) {
    return *it_target;
  }
  else {
    return "";
  }
}

} // namespace hautbois