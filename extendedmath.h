#ifndef __HLS_EXTENDEDMATH_H__
#define __HLS_EXTENDEDMATH_H__

#include "HLS/hls_internal.h"
#include "HLS/math.h"

// iff we're in the Microsoft compilation flow ...
#if defined (_MSC_VER)
  // Pull in CPP Library version information. 
  #include <yvals.h>
  // Check if _CPPLIB_VER is at least 650, the version for
  // Visual Studio 2015 header files, where _finite() and _isnan()
  // are defined.
  #if (_CPPLIB_VER >= 650)
    // if isnan is not defined, define it as _isnan, which is declared in float.h :-)
    // same for isinf/_finite
    #include <float.h>

    #ifndef M_PI
      #define M_PI 3.14159265358979323846
    #endif // #ifndef M_PI

    #ifndef isinf
      #define isinf(x) \
        (sizeof (x) == sizeof (float) ? _finitef (x) :  _finite (x))
    #endif // #ifndef isinf

  #endif // #if (_CPPLIB_VER >= 650)

#endif // #if defined(MSC_VER)

/********* Extended Math Functions ******/

// Mapping powr and pown back to pow with a corner case for powr of x < 0.
double __acl__powr_approx(double x, double y) {
  if (x < 0) {
    unsigned long long res = 0x7fffffffffffffffULL;
    return *((double *) &res);
  } else {
    return pow(x,y);
  }
}

float __acl__powrf_approx(float x, float y) {
  if (x < 0) {
    unsigned int res = 0x7fffffff;
    return *((float *) &res);
  } else {
    return powf(x,y);
  }
}

#if defined(__INTELFPGA_COMPILER__) 
extern "C" {


#if defined(HLS_SYNTHESIS) || defined(_MSC_VER)
// This follows the GNU extension syntax
void sincosf(float arg, float *sinval, float *cosval) {
  *sinval = sinf(arg);
  *cosval = cosf(arg);
}

void sincos(double arg, double *sinval, double *cosval) {
  *sinval = sin(arg);
  *cosval = cos(arg);
}
#endif

#ifdef HLS_SYNTHESIS
// FPGA, remap to current internal names
float __PUREF __acl__rsqrtf(float __x);
#define rsqrtf(__x) __acl__rsqrtf(__x)
double __PUREF __acl__rsqrtfd(double __x);
#define rsqrt(__x) __acl__rsqrtfd(__x)

float __PUREF __acl__sinpif(float __x);
#define sinpif(__x) __acl__sinpif(__x)
double __PUREF __acl__sinpifd(double __x);
#define sinpi(__x) __acl__sinpifd(__x)

float __PUREF __acl__cospif(float __x);
#define cospif(__x) __acl__cospif(__x)
double __PUREF __acl__cospifd(double __x);
#define cospi(__x) __acl__cospifd(__x)

float __acl__tanpif(float __x);
#define tanpif(__x) __acl__tanpif(__x)
#define tanpi(__x) (tan((__x) * (double)M_PI))

float __PUREF __acl__asinpif(float __x);
#define asinpif(__x) __acl__asinpif(__x)
double __PUREF __acl__asinpifd(double __x);
#define asinpi(__x) __acl__asinpifd(__x)

float __PUREF __acl__acospif(float __x);
#define acospif(__x) __acl__acospif(__x)
double __PUREF __acl__acospifd(double __x);
#define acospi(__x) __acl__acospifd(__x)

float __PUREF __acl__atanpif(float __x);
#define atanpif(__x) __acl__atanpif(__x)
double __PUREF __acl__atanpifd(double __x);
#define atanpi(__x) __acl__atanpifd(__x)


float __PUREF __acl__powrf(float __x, float __y);
#define powrf(__x,__y) __acl__powrf(__x, __y)
double __PUREF __acl__powrfd(double __x, double __y);
#define powr(__x,__y) __acl__powrfd(__x, __y)

float __PUREF __acl__pownf(float __x, int __y);
#define pownf(__x,__y) __acl__pownf(__x, __y)
double __PUREF __acl__pownfd(double __x, int __y);
#define pown(__x,__y) __acl__pownfd(__x, __y)

#else // HLS_SYNTHESIS
// Yuck, need to wrap in a function so it can be substituted everywere
float rsqrtf(float __x) {
  return 1.0f/sqrtf(__x);
}
double rsqrt(double __x) {
  return 1.0/sqrt(__x);
}

#define sinpif(__x) (sinf((__x) * (float)M_PI))
#define sinpi(__x) (sin((__x) * (double)M_PI))

#define cospif(__x) (cosf((__x) * (float)M_PI))
#define cospi(__x) (cos((__x) * (double)M_PI))

#define tanpif(__x) (tanf((__x) * (float)M_PI))
#define tanpi(__x) (tan((__x) * (double)M_PI))

#define asinpif(__x) (asinf(__x) / (float)M_PI)
#define asinpi(__x) (asin(__x) / (double)M_PI)

#define acospif(__x) (acosf(__x) / (float)M_PI)
#define acospi(__x) (acos(__x) / (double)M_PI)

#define atanpif(__x) (atanf(__x) / (float)M_PI)
#define atanpi(__x) (atan(__x) / (double)M_PI)

#define powrf(__x,__y) (__acl__powrf_approx(__x,__y))
#define powr(__x,__y) (__acl__powr_approx(__x,__y))

#define pownf(__x,__y) (powf(__x,(float)__y))
#define pown(__x,__y) (pow(__x,(double)__y))

#endif // HLS_SYNTHESIS

#define POPCOUNT32(__x) __builtin_popcount(__x)
#define POPCOUNT64(__x) __builtin_popcountl(__x)

#define popcountc(__x) ((unsigned char) POPCOUNT32((unsigned int) __x))
#define popcounts(__x) ((unsigned short) POPCOUNT32((unsigned int) __x))
#define popcount(__x) POPCOUNT32(__x)

#if defined(_MSC_VER)
//  long is 32 bits on Windows
#define popcountl(__x) POPCOUNT32(__x)
#else
// But it is 64 bits on Linux
#define popcountl(__x) POPCOUNT64(__x)

#endif

#define popcountll(__x) POPCOUNT64(__x)



} //Extern "C"
#endif // __INTELFPGA_COMPILER__
#endif //__HLS_EXTENDEDMATH_H__

