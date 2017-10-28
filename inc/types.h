#ifndef COMMON_CPP_TYPES_H
#define COMMON_CPP_TYPES_H

#if defined(COMMON_CPP_HAS_OPENMP)
#include <omp.h>
#if defined(_WIN32) && defined(_MSC_VER)
#if defined(__INTEL_COMPILER) || defined(__ICC) || defined(__ICL)
typedef size_t omp_size_t;  // MSVC with Intel Compiler has OpenMP >2.0 (support unsigned indexes)
#else
typedef long long omp_size_t;
#endif // Intel Compiler
#else  // Other OS
#include <sys/types.h>
typedef size_t omp_size_t;
#endif // Windows & MSCV
#endif // COMMON_CPP_HAS_OPENMP

#include <vector>

typedef std::vector<double> FeatureVector;

#endif/*COMMON_CPP_TYPES_H*/
