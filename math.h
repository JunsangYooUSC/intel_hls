#ifndef __HLS_MATH_H__
#define __HLS_MATH_H__

/* This file is used to overlay math.h on linux and windows.
The table below describes what is currently available on each platform
We are currently supporting gcc 4.4.7 and MSVC 10 respectively, so that 
is the versions we are currenlty trying to mimic.
All floating point functions that are available, has an f at the end for 
single precison floating point, so sin(double), but sinf(float)
Y = Supported
N = Not supported yet
- = Not available on that platform with the supported underlying compiler, 
 ****************************************************************
 * Function Name            Linux    Windows  Notes        *
 * abs                          -    N        Integer math *
 * labs                         -    N        Integer math *
 * atof                         -    N                     *
 * cos(float/double)            Y    Y                     *
 * sin(float/double)            Y    Y                     *
 * tan(float/double)            Y    Y                     *
 * acos(float/double)           Y    Y                     *
 * asin(float/double)           Y    Y                     *
 * atan(float/double)           Y    Y                     *
 * atan2(float/double)          Y    Y                     *
 * cosh(float/double)           Y    Y                     *
 * sinh(float/double)           Y    Y                     *
 * tanh(float/double)           Y    Y                     *
 * acosh(float/double)          N    N        C99/C++11    *
 * asinh(float/double)          N    N        C99/C++11    *
 * atanh(float/double)          N    N        C99/C++11    *
 * exp(float/double)            Y    Y                     *
 * frexp(float/double)          Y    Y                     *
 * ldexp(float/double)          Y    Y                     *
 * log(float/double)            Y    Y                     *
 * log10(float/double)          Y    Y                     *
 * modf(float/double)           Y    Y                     *
 * exp2(float/double)           Y    Y        C99/C++11    *
 * exp10(float/double)          Y    -                     *
 * expm1(float/double)          Y    Y        C99/C++11    *
 * ilogb(float/double)          Y    Y        C++11        *
 * log1p(float/double)          D    D        C99/C++11    Only double supported* 
 * log2(float/double)           Y    Y        C99/C++11    *
 * logb(float/double)           N    N        C++11        *
 * scalbn(float/double)         N    N        C99/C++11    *
 * scalbln(float/double)        N    N        C99/C++11    *
 * pow(float/double)            Y    Y                     *
 * sqrt(float/double)           Y    Y                     *
 * cbrt(float/double)           Y    Y        C99/C++11    *
 * hypot(float/double)          Y    Y        C99/C++11    *
 * erf(float/double)            N    N        C99/C++11    *
 * erfc(float/double)           N    N        C99/C++11    *
 * tgamma(float/double)         N    N        C99/C++11    *
 * lgamma(float/double)         N    N        C99/C++11    *
 * ceil(float/double)           Y    Y                     *
 * floor(float/double)          Y    Y                     *
 * fmod(float/double)           Y    Y                     *
 * trunc(float/double)          Y    Y        C++11        *
 * round(float/double)          Y    Y        C++11        *
 * lround(float/double)         N    N        C++11        *
 * llround(float/double)        N    N        C++11        *
 * rint(float/double)           Y    Y        C99/C++11    *
 * lrint(float/double)          N    N        C++11        *
 * llrint(float/double)         N    N        C++11        *
 * nearbyint(float/double)      N    N        C++11        *
 * remainder(float/double)      N    N        C++11        *
 * drem                         N    -        obsolete name for remanider *
 * remquo(float/double)         N    N        C++11        *
 * significand                  N    -        non standard *
 * copysign(float/double)       N    N        C99/C++11    *
 * nan(float/double)            N    N        C99/C++11    *
 * nextafter(float/double)      N    N        C99/C++11    *
 * nexttoward(float/double)     N    N        C99/C++11    *
 * fdim(float/double)           Y    Y        C++11        *
 * fmin(float/double)           Y    Y        C++11        *
 * fmax(float/double)           Y    Y        C++11        *
 * fabs(float/double)           Y    Y                     *
 * fma(float/double)            N    N        C++11        *
 * fpclassify(float/double)     N    N        C++11        *
 * isfinite(float/double)       Y    -        C++11        *
 * finite                       Y    -        BSD name for isfinite _finite for windows    *
 * isinf(float/double)          Y    -        C++11        *
 * isnan(float/double)          Y    Y        C++11        *
 * isnormal(float/double)       N    -        C++11        *
 * signbit(float/double)        N    -        C++11        *
 * isgreater(float/double)      N    -        C++11        *
 * isgreaterequal(float/double) N    -        C++11        *
 * isless(float/double)         N    -        C++11        *
 * islessequal(float/double)    N    -        C++11        *
 * islessgreater(float/double)  N    -        C++11        *
 * isunordered(float/double)    N    -        C++11        *
 ****************************************************************/

#include <math.h>

#if defined(__INTELFPGA_COMPILER__)
#ifdef HLS_SYNTHESIS
#define __PUREF __attribute__((const))

// FPGA, remap to current internal OpenCL names
extern "C" {

/********** Supported trig builtins **********/
double __PUREF __acl__cosfd(double __x);
#define cos(__x) __acl__cosfd(__x)

float __PUREF __acl__flush_denorm_cosf(float __x);
#define cosf(__x) __acl__flush_denorm_cosf(__x)

double __PUREF __acl__sinfd(double __x);
#define sin(__x) __acl__sinfd(__x)

float __PUREF __acl__flush_denorm_sinf(float __x);
#define sinf(__x) __acl__flush_denorm_sinf(__x)

double __PUREF __acl__wrapper_tanfd(double __x);
#define tan(__x) __acl__wrapper_tanfd(__x)

float __PUREF __acl__flush_denorm_tanf(float __x);
#define tanf(__x) __acl__flush_denorm_tanf(__x)

double __PUREF __acl__acosfd(double __x);
#define acos(__x) __acl__acosfd(__x)

float __PUREF __acl__flush_denorm_acosf(float __x);
#define acosf(__x) __acl__flush_denorm_acosf(__x)

double __PUREF __acl__asinfd(double __x);
#define asin(__x) __acl__asinfd(__x)

float __PUREF __acl__flush_denorm_asinf(float __x);
#define asinf(__x) __acl__flush_denorm_asinf(__x)

double __PUREF __acl__atanfd(double __x);
#define atan(__x) __acl__atanfd(__x)

float __PUREF __acl__flush_denorm_atanf(float __x);
#define atanf(__x) __acl__flush_denorm_atanf(__x)

double __PUREF __acl__atan2fd(double __x, double __y);
#define atan2(__x, __y) __acl__atan2fd(__x, __y)

float __PUREF __acl__atan2f(float __x, float __y);
#define atan2f(__x, __y) __acl__atan2f(__x, __y)

double __PUREF __acl__coshfd(double __x);
#define cosh(__x) __acl__coshfd(__x)

float __PUREF __acl__coshf(float __x);
#define coshf(__x) __acl__coshf(__x)

double __PUREF __acl__sinhfd(double __x);
#define sinh(__x) __acl__sinhfd(__x)

float __PUREF __acl__sinhf(float __x);
#define sinhf(__x) __acl__sinhf(__x)

double __PUREF __acl__tanhfd(double __x);
#define tanh(__x) __acl__tanhfd(__x)

float __PUREF __acl__tanhf(float __x);
#define tanhf(__x) __acl__tanhf(__x)

double __PUREF __acl__expfd(double __x);
#define exp(__x) __acl__expfd(__x)

float __PUREF __acl__flush_denorm_expf(float __x);
#define expf(__x) __acl__flush_denorm_expf(__x)

double __PUREF __acl_frexpd(double __x, int* __y);
#define frexp(__x, __y)  __acl_frexpd(__x, __y)

float __PUREF __acl_frexpf(float __x, int* __y);
#define frexpf(__x, __y)  __acl_frexpf(__x, __y)

double __PUREF __acl__ldexpfd(double __x, int __y);
#define ldexp(__x, __y) __acl__ldexpfd(__x, __y)

float __PUREF __acl__ldexpf(float __x, int __y);
#define ldexpf(__x, __y) __acl__ldexpf(__x, __y)
 
double __PUREF __acl__logfd(double __x);
#define log(__x) __acl__logfd(__x)

float __PUREF __acl__flush_denorm_logf(float __x);
#define logf(__x) __acl__flush_denorm_logf(__x)

double __PUREF __acl__log10fd(double __x);
#define log10(__x) __acl__log10fd(__x)

float __PUREF __acl__log10f(float __x);
#define log10f(__x) __acl__log10f(__x)

double __PUREF __acl_modfd(double __x, double * __y);
#define modf(__x, __y) __acl_modfd(__x, __y)

float __PUREF __acl_modff(float __x, float* __y);
#define modff(__x, __y) __acl_modff(__x, __y)

double __PUREF __acl__exp2fd(double __x);
#define exp2(__x) __acl__exp2fd(__x)

float __PUREF __acl__exp2f(float __x);
#define exp2f(__x) __acl__exp2f(__x)

#if defined (__linux__)

double __PUREF __acl__exp10fd(double __x);
#define exp10(__x) __acl__exp10fd(__x)

float __PUREF __acl__exp10f(float __x);
#define exp10f(__x) __acl__exp10f(__x)

#endif //linux

inline double __x_expm1 (double __x) {
  return __acl__expfd(__x) - 1.0;
}
#define expm1(__x) __x_expm1(__x)

float __PUREF __acl__expm1f(float);      
#define expm1f(__x) __acl__expm1f(__x)

int __PUREF __acl__ilogbfd(double __x);
#define ilogb(__x) __acl__ilogbfd(__x)

int __PUREF __acl__ilogbf(float __x);
#define ilogbf(__x) __acl__ilogbf(__x)

double __PUREF __acl__ln1pxfd(double __x);
#define log1p(__x) __acl__ln1pxfd(__x)

double __PUREF __acl__log2fd(double __x);
#define log2(__x) __acl__log2fd(__x)

float __PUREF __acl__log2f(float __x);
#define log2f(__x) __acl__log2f(__x)



double __PUREF __acl__powfd(double __x, double __y);
#define pow(__x,__y) __acl__powfd(__x, __y)

float __PUREF __acl__powf(float __x, float __y);
#define powf(__x,__y) __acl__powf(__x, __y)

double __PUREF __acl__sqrtfd(double  __x);
#define sqrt(__x) __acl__sqrtfd(__x)

float __PUREF __acl__flush_denorm_sqrtf(float __x);
#define sqrtf(__x) __acl__flush_denorm_sqrtf(__x)

// Only have the float version built-in.
inline double __x_cbrt(double __x) {
  return exp(log(__x) / 3.0);
}
#define cbrt(__x) __x_cbrt(__x)

float __PUREF __acl__cbrtf(float);
#define cbrtf(__x) __acl__cbrtf(__x)


inline double __x_hypot(double __x, double __y) {
  return sqrt(__x*__x + __y*__y);
}
#define hypot(__x,__y) __x_hypot(__x,__y)


float __PUREF __acl__hypotf(float, float);
#define hypotf(__x,__y) __acl__hypotf(__x,__y)

/************ Error & Gamma Functions *********/
double __PUREF __acl__ceilfd(double __x);
#define ceil(__x) __acl__ceilfd(__x)

float __PUREF __acl__ceilf(float __x);
#define ceilf(__x) __acl__ceilf(__x)

double __PUREF __acl__floorfd(double __x);
#define floor(__x) __acl__floorfd(__x)

float __PUREF __acl__floorf(float __x);
#define floorf(__x) __acl__floorf(__x)

double __PUREF __acl__fmodfd(double __x, double __y);
#define fmod(__x,__y) __acl__fmodfd(__x, __y)

float __PUREF __acl__fmodf(float __x, float __y);
#define fmodf(__x,__y) __acl__fmodf(__x, __y)

double __PUREF __acl__truncfd(double __x);
#define trunc(__x) __acl__truncfd(__x)

float __PUREF __acl__truncf(float __x);
#define truncf(__x) __acl__truncf(__x)

double __PUREF __acl__roundfd(double __x);
#define round(__x) __acl__roundfd(__x)

float __PUREF __acl__roundf(float __x);
#define roundf(__x) __acl__roundf(__x)

double __PUREF __acl__rintfd(double __x);
#define rint(__x) __acl__rintfd(__x)

float __PUREF __acl__rintf(float __x);
#define rintf(__x) __acl__rintf(__x)

double __PUREF __acl__fdimfd(double __x, double __y);
#define fdim(__x,__y) __acl__fdimfd(__x, __y)

float __PUREF __acl__fdimf(float __x, float __y);
#define fdimf(__x,__y) __acl__fdimf(__x, __y)

double __PUREF __acl__fminfd(double __x, double __y);
#define fmin(__x,__y) __acl__fminfd(__x, __y)

float __PUREF __acl__fminf(float __x, float __y);
#define fminf(__x,__y) __acl__fminf(__x, __y)

double __PUREF __acl__fmaxfd(double __x, double __y);
#define fmax(__x,__y) __acl__fmaxfd(__x, __y)

float __PUREF __acl__fmaxf(float __x, float __y);
#define fmaxf(__x,__y) __acl__fmaxf(__x, __y)

double __PUREF __acl__fabsfd(double __x);
#define fabs(__x) __acl__fabsfd(__x)

float __PUREF __acl__fabsf(float __x);
#define fabsf(__x) __acl__fabsf(__x)

/********** Classification ******************/
#if defined (__linux__)
long __PUREF __acl__isfinitefd(double __x);
#define __finite(__x) __acl__isfinitefd(__x)

int __PUREF __acl__isfinitef(float __x);
#define __finitef(__x) __acl__isfinitef(__x)

#define finite(__x) __acl__isfinitefd(__x)
#define finitef(__x) __acl__isfinitef(__x)

long __PUREF __acl__isinffd(double __x);
#define __isinf(__x) __acl__isinffd(__x)

int __PUREF __acl__isinff(float __x);
#define __isinff(__x) __acl__isinff(__x)

long __PUREF __acl__isnanfd(double __x);
#define __isnan(__x) __acl__isnanfd(__x)

int __PUREF __acl__isnanf(float __x);
#define __isnanf(__x) __acl__isnanf(__x)

#endif //linux

#if defined (_MSC_VER)
  // Pull in CPP Library version information. 
  long __PUREF __acl__isnanfd(double __x);

  int __PUREF __acl__isnanf(float __x);
  
  #if (_CPPLIB_VER >= 650)
    // Support isnan(x) for MSVC 2015+  in fpga components.
    #ifndef isnan 
      #define isnan(x) \
        (sizeof (x) == sizeof (float) ? __acl__isnanf(x) :  __acl__isnanfd(x))
    #endif // #ifndef isnan

  #endif // #if (_CPPLIB_VER >= 650)
  // MSVC handles _isnanf and _isnanfd in 2 different places (math.h and float.h)
  // So it is messy to support them. Use isnan instead.

#endif // #if defined(MSC_VER)



}
#endif //#ifdef HLS_SYNTHESIS
#endif //__INTELFPGA_COMPILER__
#endif //__HLS_MATH_H__

