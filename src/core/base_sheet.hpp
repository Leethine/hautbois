#pragma once

#ifndef BASE_SHEET_H
#define BASE_SHEET_H

#include <string>
#include "base_bar.hpp"

namespace hautbois {
namespace core {

class BaseSheet {
 private:
  std::string _title;
 public:
  BaseSheet();
  BaseSheet(BaseSheet& ivRh);
};

} // namespace core
} // namespace hautbois

#endif