#include "MathFunctions.h"

// TODO 11: include cmath

// TODO 10: Wrap the mysqrt include in a precompiled ifdef based on USE_MYMATH
#include <cstdio>
#ifdef LQTECH_USE_MYMATH
#  include "mysqrt.h"
#endif
#include <cmath>

namespace mathfunctions {
double sqrt(double x)
{
  // TODO 9: If USE_MYMATH is defined, use detail::mysqrt.
  // Otherwise, use std::sqrt.
  printf("good one");
#ifdef LQTECH_USE_MYMATH
  return detail::mysqrt(x);
#else
  return std::sqrt(x);
#endif
}
}