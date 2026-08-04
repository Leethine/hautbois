#pragma once

#ifndef TUNING_HPP
#define TUNING_HPP

#include <unordered_map>
#include <string>
#include <cmath>
#include <cstdint>

namespace hautbois {
namespace tuning {

inline double calculateEqualTemperament(const uint32_t __base_freq, const int __distance) {
  return __base_freq * std::exp2(__distance / 12.0);
}

} //  namespace tuning
} // namespace hautbois


#endif