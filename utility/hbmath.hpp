#pragma once

#include <numeric>

#if __cplusplus >= 201703L
#define HB_GCD(X, Y) std::gcd((X),(Y))
#else
#define HB_GCD(X, Y)    \
[&](int x_, int y_) {   \
  int a = std::abs(x_); \
  int b = std::abs(y_); \
  int remainder;        \
  while (b != 0) {      \
    remainder = a % b;  \
    a = b;              \
    b = remainder;      \
  }                     \
  return a;             \
}((X),(Y))
#endif