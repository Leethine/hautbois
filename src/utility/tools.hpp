#pragma once

#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <string>
#include <vector>

namespace hautbois {
namespace tools {

inline void splitstring(std::vector<std::string>& __out, std::string __in, const char __delim, bool __remove_empty = true) {
  __out.clear();
  size_t pos = __in.find(__delim);
  if (pos == std::string::npos && !__in.empty()) {
    __out.push_back(__in);
    return ;
  }
  while (pos != std::string::npos) {
    __out.push_back(__in.substr(0, pos));
    if (__remove_empty && __out.back().empty()) {
      __out.pop_back();
    }
    __in = __in.substr(pos + 1);
    pos = __in.find(__delim);
  }
  __out.push_back(__in);
  if (__remove_empty && __out.back().empty()) {
    __out.pop_back();
  }
}

inline std::string jointstring(const std::vector<std::string>& __in, const char __delim, bool __ignore_empty = true) {
  std::string out;
  if (__in.empty()) {
    return out;
  }
  for (auto it = __in.cbegin(); it != __in.cend(); it++) {
    if (__ignore_empty && it->empty()) {
      continue;
    }
    else {
      out.append(*it);
      out.push_back(__delim);
    }
  }
  out.pop_back();
  return out;
}

} // namespace hautbois
} // namespace tools

#endif