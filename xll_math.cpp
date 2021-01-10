// xll_math.cpp - Excel add-in for functions in the math category.
#include <cmath>
#include "xll/xll/xll.h"

using namespace xll;

int xll_math_doc = Documentation("MATH", R"(
This add-in calls functions declared in the <math.h> header.
)");

	
AddIn xai_math_abs(
	Function(XLL_LONG, "xll_math_abs", "MATH.ABS")
	.Args({
		Arg(XLL_LONG, "n", "Numeric value.")
	})
	.FunctionHelp("Calculates the absolute value of the argument.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/abs-labs-llabs-abs64")
	.Documentation(R"xyzyx(The abs, labs, llabs, and _abs64 functions return the absolute value of the parameter n. There's no error return.)xyzyx")
);
int WINAPI xll_math_abs(int n)
{
#pragma XLLEXPORT

	return abs(n);
}
	
AddIn xai_math_acos(
	Function(XLL_DOUBLE, "xll_math_acos", "MATH.ACOS")
	.Args({
		Arg(XLL_DOUBLE, "x", "Value between -1 and 1, for which to calculate the arccosine (the inverse cosine).")
	})
	.FunctionHelp("Calculates the arccosine.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/acos-acosf-acosl")
	.Documentation(R"xyzyx(The acos function returns the arccosine of x in the range 0 to π radians.)xyzyx")
);
double WINAPI xll_math_acos(double x)
{
#pragma XLLEXPORT

	return acos(x);
}
	
AddIn xai_math_acosh(
	Function(XLL_DOUBLE, "xll_math_acosh", "MATH.ACOSH")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value.")
	})
	.FunctionHelp("Calculates the inverse hyperbolic cosine.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/acosh-acoshf-acoshl")
	.Documentation(R"xyzyx(The acosh functions return the inverse hyberbolic cosine (arc hyperbolic cosine) of x. These functions are valid over the domain x ≥ 1. If x is less than 1, errno is set to EDOM and the result is a quiet NaN. If x is a quiet NaN, indefinite, or infinity, the same value is returned.)xyzyx")
);
double WINAPI xll_math_acosh(double x)
{
#pragma XLLEXPORT

	return acosh(x);
}
	
AddIn xai_math_asin(
	Function(XLL_DOUBLE, "xll_math_asin", "MATH.ASIN")
	.Args({
		Arg(XLL_DOUBLE, "x", "Value whose arcsine is to be calculated.")
	})
	.FunctionHelp("Calculates the arcsine.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/asin-asinf-asinl")
	.Documentation(R"xyzyx(The asin function returns the arcsine (the inverse sine function) of x in the range -π/2 to π/2 radians.)xyzyx")
);
double WINAPI xll_math_asin(double x)
{
#pragma XLLEXPORT

	return asin(x);
}
	
AddIn xai_math_asinh(
	Function(XLL_DOUBLE, "xll_math_asinh", "MATH.ASINH")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value.")
	})
	.FunctionHelp("Calculates the inverse hyperbolic sine.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/asinh-asinhf-asinhl")
	.Documentation(R"xyzyx(The asinh functions return the inverse hyberbolic sine (arc hyperbolic sine) of x. This function is valid over the floating-point domain. If x is a quiet NaN, indefinite, or infinity, the same value is returned.)xyzyx")
);
double WINAPI xll_math_asinh(double x)
{
#pragma XLLEXPORT

	return asinh(x);
}
	
AddIn xai_math_atan(
	Function(XLL_DOUBLE, "xll_math_atan", "MATH.ATAN")
	.Args({
		Arg(XLL_DOUBLE, "x", "Any numbers.")
	})
	.FunctionHelp("Calculates the arctangent of x (atan, atanf, and atanl) or the arctangent of y/x (atan2, atan2f, and atan2l).")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/atan-atanf-atanl-atan2-atan2f-atan2l")
	.Documentation(R"xyzyx(atan returns the arctangent of x in the range -π/2 to π/2 radians. atan2 returns the arctangent of y/x in the range -π to π radians. If x is 0, atan returns 0. If both parameters of atan2 are 0, the function returns 0. All results are in radians.)xyzyx")
);
double WINAPI xll_math_atan(double x)
{
#pragma XLLEXPORT

	return atan(x);
}
	
AddIn xai_math_atanh(
	Function(XLL_DOUBLE, "xll_math_atanh", "MATH.ATANH")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value.")
	})
	.FunctionHelp("Calculates the inverse hyperbolic tangent.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/atanh-atanhf-atanhl")
	.Documentation(R"xyzyx(The atanh functions return the inverse hyberbolic tangent (arc hyperbolic tangent) of x. If x is greater than 1, or less than -1, errno is set to EDOM and the result is a quiet NaN. If x is equal to 1 or -1, a positive or negative infinity is returned, respectively, and errno is set to ERANGE.)xyzyx")
);
double WINAPI xll_math_atanh(double x)
{
#pragma XLLEXPORT

	return atanh(x);
}
	
AddIn xai_math_cbrt(
	Function(XLL_DOUBLE, "xll_math_cbrt", "MATH.CBRT")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value")
	})
	.FunctionHelp("Calculates the cube root.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/cbrt-cbrtf-cbrtl")
	.Documentation(R"xyzyx(The cbrt functions return the cube-root of x.)xyzyx")
);
double WINAPI xll_math_cbrt(double x)
{
#pragma XLLEXPORT

	return cbrt(x);
}
	
AddIn xai_math_ceil(
	Function(XLL_DOUBLE, "xll_math_ceil", "MATH.CEIL")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value.")
	})
	.FunctionHelp("Calculates the ceiling of a value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/ceil-ceilf-ceill")
	.Documentation(R"xyzyx(The ceil functions return a floating-point value that represents the smallest integer that is greater than or equal to x. There's no error return.)xyzyx")
);
double WINAPI xll_math_ceil(double x)
{
#pragma XLLEXPORT

	return ceil(x);
}
	
AddIn xai_math__chgsign(
	Function(XLL_DOUBLE, "xll_math__chgsign", "MATH._CHGSIGN")
	.Args({
		Arg(XLL_DOUBLE, "x", "The floating-point value to be changed.")
	})
	.FunctionHelp("Reverses the sign of a floating-point argument.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/chgsign-chgsignf-chgsignl")
	.Documentation(R"xyzyx(The _chgsign functions return a value that's equal to the floating-point argument x, but with its sign reversed. There's no error return.)xyzyx")
);
double WINAPI xll_math__chgsign(double x)
{
#pragma XLLEXPORT

	return _chgsign(x);
}
	
AddIn xai_math_copysign(
	Function(XLL_DOUBLE, "xll_math_copysign", "MATH.COPYSIGN")
	.Args({
		Arg(XLL_DOUBLE, "x", "The floating-point value that's returned as the magnitude of the result."),
		Arg(XLL_DOUBLE, "y", "The floating-point value that's returned as the sign of the result.")
	})
	.FunctionHelp("Returns a value that has the magnitude of one argument and the sign of another.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/copysign-copysignf-copysignl-copysign-copysignf-copysignl")
	.Documentation(R"xyzyx(The copysign functions return a floating-point value that combines the magnitude of x and the sign of y. There's no error return.)xyzyx")
);
double WINAPI xll_math_copysign(double x, double y)
{
#pragma XLLEXPORT

	return copysign(x, y);
}
	
AddIn xai_math_cos(
	Function(XLL_DOUBLE, "xll_math_cos", "MATH.COS")
	.Args({
		Arg(XLL_DOUBLE, "x", "Angle in radians.")
	})
	.FunctionHelp("Calculates the cosine.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/cos-cosf-cosl")
	.Documentation(R"xyzyx(The cosine of x. If x is greater than or equal to 263, or less than or equal to -263, a loss of significance in the result occurs.)xyzyx")
);
double WINAPI xll_math_cos(double x)
{
#pragma XLLEXPORT

	return cos(x);
}
	
AddIn xai_math_cosh(
	Function(XLL_DOUBLE, "xll_math_cosh", "MATH.COSH")
	.Args({
		Arg(XLL_DOUBLE, "x", "Angle in radians.")
	})
	.FunctionHelp("Calculates the hyperbolic cosine.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/cosh-coshf-coshl")
	.Documentation(R"xyzyx(The hyperbolic cosine of x.)xyzyx")
);
double WINAPI xll_math_cosh(double x)
{
#pragma XLLEXPORT

	return cosh(x);
}
	
AddIn xai_math_erf(
	Function(XLL_DOUBLE, "xll_math_erf", "MATH.ERF")
	.Args({
		Arg(XLL_DOUBLE, "x", "A floating-point value.")
	})
	.FunctionHelp("Computes the error function or the complementary error function of a value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/erf-erff-erfl-erfc-erfcf-erfcl")
	.Documentation(R"xyzyx(The erf functions return the Gauss error function of x. The erfc functions return the complementary Gauss error function of x.)xyzyx")
);
double WINAPI xll_math_erf(double x)
{
#pragma XLLEXPORT

	return erf(x);
}
	
AddIn xai_math_exp(
	Function(XLL_DOUBLE, "xll_math_exp", "MATH.EXP")
	.Args({
		Arg(XLL_DOUBLE, "x", "The floating-point value to exponentiate the natural logarithm base")
	})
	.FunctionHelp("Calculates the exponential.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/exp-expf")
	.Documentation(R"xyzyx(The exp functions return the exponential value of the floating-point parameter, x, if successful. That is, the result is ex, where e is the base of the natural logarithm. On overflow, the function returns INF (infinity) and on underflow, exp returns 0.)xyzyx")
);
double WINAPI xll_math_exp(double x)
{
#pragma XLLEXPORT

	return exp(x);
}
	
AddIn xai_math_exp2(
	Function(XLL_DOUBLE, "xll_math_exp2", "MATH.EXP2")
	.Args({
		Arg(XLL_DOUBLE, "x", "The value of the exponent.")
	})
	.FunctionHelp("Computes 2 raised to the specified value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/exp2-exp2f-exp2l")
	.Documentation(R"xyzyx(If successful, returns the base-2 exponent of x, that is, 2x. Otherwise, it returns one of the following values:)xyzyx")
);
double WINAPI xll_math_exp2(double x)
{
#pragma XLLEXPORT

	return exp2(x);
}
	
AddIn xai_math_expm1(
	Function(XLL_DOUBLE, "xll_math_expm1", "MATH.EXPM1")
	.Args({
		Arg(XLL_DOUBLE, "x", "The floating-point exponential value.")
	})
	.FunctionHelp("Computes the base-e exponential of a value, minus one.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/expm1-expm1f-expm1l")
	.Documentation(R"xyzyx(The expm1 functions return a floating-point value that represents ex - 1, if successful. On overflow, expm1 returns HUGE_VAL, expm1f returns HUGE_VALF, expm1l returns HUGE_VALL, and errno is set to ERANGE. For more information about return codes, see errno, _doserrno, _sys_errlist, and _sys_nerr.)xyzyx")
);
double WINAPI xll_math_expm1(double x)
{
#pragma XLLEXPORT

	return expm1(x);
}
	
AddIn xai_math_fabs(
	Function(XLL_DOUBLE, "xll_math_fabs", "MATH.FABS")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value.")
	})
	.FunctionHelp("Calculates the absolute value of the floating-point argument.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fabs-fabsf-fabsl")
	.Documentation(R"xyzyx(The fabs functions return the absolute value of the argument x. There's no error return.)xyzyx")
);
double WINAPI xll_math_fabs(double x)
{
#pragma XLLEXPORT

	return fabs(x);
}
	
AddIn xai_math_fdim(
	Function(XLL_DOUBLE, "xll_math_fdim", "MATH.FDIM")
	.Args({
		Arg(XLL_DOUBLE, "x", "The first value."),
		Arg(XLL_DOUBLE, "y", "The second value.")
	})
	.FunctionHelp("Determines the positive difference between the first and second values.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fdim-fdimf-fdiml")
	.Documentation(R"xyzyx(Returns the positive difference between x and y:)xyzyx")
);
double WINAPI xll_math_fdim(double x, double y)
{
#pragma XLLEXPORT

	return fdim(x, y);
}
	
AddIn xai_math_floor(
	Function(XLL_DOUBLE, "xll_math_floor", "MATH.FLOOR")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value.")
	})
	.FunctionHelp("Calculates the floor of a value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/floor-floorf-floorl")
	.Documentation(R"xyzyx(The floor functions return a floating-point value that represents the largest integer that is less than or equal to x. There's no error return.)xyzyx")
);
double WINAPI xll_math_floor(double x)
{
#pragma XLLEXPORT

	return floor(x);
}
	
AddIn xai_math_fma(
	Function(XLL_DOUBLE, "xll_math_fma", "MATH.FMA")
	.Args({
		Arg(XLL_DOUBLE, "x", "The first value to multiply."),
		Arg(XLL_DOUBLE, "y", "The second value to multiply."),
		Arg(XLL_DOUBLE, "z", "The value to add.")
	})
	.FunctionHelp("Multiplies two values together, adds a third value, and then rounds the result, without losing any precision due to intermediary rounding.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fma-fmaf-fmal")
	.Documentation(R"xyzyx(Returns (x * y) + z. The return value is then rounded using the current rounding format.)xyzyx")
);
double WINAPI xll_math_fma(double x, double y, double z)
{
#pragma XLLEXPORT

	return fma(x, y, z);
}
	
AddIn xai_math_fmax(
	Function(XLL_DOUBLE, "xll_math_fmax", "MATH.FMAX")
	.Args({
		Arg(XLL_DOUBLE, "x", "The first value to compare."),
		Arg(XLL_DOUBLE, "y", "The second value to compare.")
	})
	.FunctionHelp("Determine the larger of two specified numeric values.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fmax-fmaxf-fmaxl")
	.Documentation(R"xyzyx(If successful, returns the larger of x or y. The value returned is exact, and does not depend on any form of rounding.)xyzyx")
);
double WINAPI xll_math_fmax(double x, double y)
{
#pragma XLLEXPORT

	return fmax(x, y);
}
	
AddIn xai_math_fmin(
	Function(XLL_DOUBLE, "xll_math_fmin", "MATH.FMIN")
	.Args({
		Arg(XLL_DOUBLE, "x", "The first value to compare."),
		Arg(XLL_DOUBLE, "y", "The second value to compare.")
	})
	.FunctionHelp("Determines the smaller of the two specified values.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fmin-fminf-fminl")
	.Documentation(R"xyzyx(If successful, returns the smaller of x or y.)xyzyx")
);
double WINAPI xll_math_fmin(double x, double y)
{
#pragma XLLEXPORT

	return fmin(x, y);
}
	
AddIn xai_math_fmod(
	Function(XLL_DOUBLE, "xll_math_fmod", "MATH.FMOD")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point values."),
		Arg(XLL_DOUBLE, "y", "Floating-point values.")
	})
	.FunctionHelp("Calculates the floating-point remainder.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fmod-fmodf")
	.Documentation(R"xyzyx(fmod returns the floating-point remainder of x / y. If the value of y is 0.0, fmod returns a quiet NaN. For information about representation of a quiet NaN by the printf family, see printf.)xyzyx")
);
double WINAPI xll_math_fmod(double x, double y)
{
#pragma XLLEXPORT

	return fmod(x, y);
}
	
AddIn xai_math__fpclass(
	Function(XLL_LONG, "xll_math__fpclass", "MATH._FPCLASS")
	.Args({
		Arg(XLL_DOUBLE, "x", "The floating-point value to test.")
	})
	.FunctionHelp("Returns a value indicating the floating-point classification of the argument.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fpclass-fpclassf")
	.Documentation(R"xyzyx(The _fpclass and _fpclassf functions return an integer value that indicates the floating-point classification of the argument x. The classification may have one of the following values, defined in <float.h>.)xyzyx")
);
int WINAPI xll_math__fpclass(double x)
{
#pragma XLLEXPORT

	return _fpclass(x);
}
	
AddIn xai_math_frexp(
	Function(XLL_DOUBLE, "xll_math_frexp", "MATH.FREXP")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value."),
		Arg(XLL_LONG_, "expptr", "Pointer to stored integer exponent.")
	})
	.FunctionHelp("Gets the mantissa and exponent of a floating-point number.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/frexp")
	.Documentation(R"xyzyx(frexp returns the mantissa. If x is 0, the function returns 0 for both the mantissa and the exponent. If expptr is NULL, the invalid parameter handler is invoked as described in Parameter Validation. If execution is allowed to continue, this function sets errno to EINVAL and returns 0.)xyzyx")
);
double WINAPI xll_math_frexp(double x, int* expptr)
{
#pragma XLLEXPORT

	return frexp(x, expptr);
}
	
AddIn xai_math_hypot(
	Function(XLL_DOUBLE, "xll_math_hypot", "MATH.HYPOT")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point values."),
		Arg(XLL_DOUBLE, "y", "Floating-point values.")
	})
	.FunctionHelp("Calculates the hypotenuse.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/hypot-hypotf-hypotl-hypot-hypotf-hypotl")
	.Documentation(R"xyzyx(If successful, hypot returns the length of the hypotenuse; on overflow, hypot returns INF (infinity) and the errno variable is set to ERANGE. You can use _matherr to modify error handling.)xyzyx")
);
double WINAPI xll_math_hypot(double x, double y)
{
#pragma XLLEXPORT

	return hypot(x, y);
}
	
AddIn xai_math_ilogb(
	Function(XLL_LONG, "xll_math_ilogb", "MATH.ILOGB")
	.Args({
		Arg(XLL_DOUBLE, "x", "The specified value.")
	})
	.FunctionHelp("Retrieves an integer that represents the unbiased base-2 exponent of the specified value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/ilogb-ilogbf-ilogbl2")
	.Documentation(R"xyzyx(If successful, return the base-2 exponent of x as a signed int value.)xyzyx")
);
int WINAPI xll_math_ilogb(double x)
{
#pragma XLLEXPORT

	return ilogb(x);
}
	
AddIn xai_math_ldexp(
	Function(XLL_DOUBLE, "xll_math_ldexp", "MATH.LDEXP")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value."),
		Arg(XLL_LONG, "exp", "Integer exponent.")
	})
	.FunctionHelp("Multiplies a floating-point number by an integral power of two.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/ldexp")
	.Documentation(R"xyzyx(The ldexp functions return the value of x * 2exp if successful. On overflow, and depending on the sign of x, ldexp returns +/- HUGE_VAL; the errno value is set to ERANGE.)xyzyx")
);
double WINAPI xll_math_ldexp(double x, int exp)
{
#pragma XLLEXPORT

	return ldexp(x, exp);
}
	
AddIn xai_math_lgamma(
	Function(XLL_DOUBLE, "xll_math_lgamma", "MATH.LGAMMA")
	.Args({
		Arg(XLL_DOUBLE, "x", "The value to compute.")
	})
	.FunctionHelp("Determines the natural logarithm of the absolute value of the gamma function of the specified value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/lgamma-lgammaf-lgammal")
	.Documentation(R"xyzyx(If successful, return the natural logarithm of the absolute value of the gamma function of x.)xyzyx")
);
double WINAPI xll_math_lgamma(double x)
{
#pragma XLLEXPORT

	return lgamma(x);
}
	
AddIn xai_math_log(
	Function(XLL_DOUBLE, "xll_math_log", "MATH.LOG")
	.Args({
		Arg(XLL_DOUBLE, "x", "Value whose logarithm is to be found.")
	})
	.FunctionHelp("Calculates logarithms.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/log-logf-log10-log10f")
	.Documentation(R"xyzyx(The log functions return the natural logarithm (base e) of x if successful. The log10 functions return the base-10 logarithm. If x is negative, these functions return an indefinite (IND), by default. If x is 0, they return infinity (INF).)xyzyx")
);
double WINAPI xll_math_log(double x)
{
#pragma XLLEXPORT

	return log(x);
}
	
AddIn xai_math_log1p(
	Function(XLL_DOUBLE, "xll_math_log1p", "MATH.LOG1P")
	.Args({
		Arg(XLL_DOUBLE, "x", "The floating-point argument.")
	})
	.FunctionHelp("Computes the natural logarithm of 1 plus the specified value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/log1p-log1pf-log1pl2")
	.Documentation(R"xyzyx(If successful, returns the natural (base-e) log of (x + 1).)xyzyx")
);
double WINAPI xll_math_log1p(double x)
{
#pragma XLLEXPORT

	return log1p(x);
}
	
AddIn xai_math_log2(
	Function(XLL_DOUBLE, "xll_math_log2", "MATH.LOG2")
	.Args({
		Arg(XLL_DOUBLE, "x", "The value to determine the base-2 logarithm of.")
	})
	.FunctionHelp("Determines the binary (base-2) logarithm of the specified value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/log2-log2f-log2l")
	.Documentation(R"xyzyx(On success, returns return log2 x.)xyzyx")
);
double WINAPI xll_math_log2(double x)
{
#pragma XLLEXPORT

	return log2(x);
}
	
AddIn xai_math_logb(
	Function(XLL_DOUBLE, "xll_math_logb", "MATH.LOGB")
	.Args({
		Arg(XLL_DOUBLE, "x", "A floating-point value.")
	})
	.FunctionHelp("Extracts the exponent value of a floating-point argument.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/logb-logbf-logbl-logb-logbf")
	.Documentation(R"xyzyx(logb returns the unbiased exponent value of x as a signed integer represented as a floating-point value.)xyzyx")
);
double WINAPI xll_math_logb(double x)
{
#pragma XLLEXPORT

	return logb(x);
}
	
AddIn xai_math_modf(
	Function(XLL_DOUBLE, "xll_math_modf", "MATH.MODF")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value."),
		Arg(XLL_DOUBLE_, "intptr", "Pointer to stored integer portion.")
	})
	.FunctionHelp("Splits a floating-point value into fractional and integer parts.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/modf-modff-modfl")
	.Documentation(R"xyzyx(This function returns the signed fractional portion of x. There's no error return.)xyzyx")
);
double WINAPI xll_math_modf(double x, double* intptr)
{
#pragma XLLEXPORT

	return modf(x, intptr);
}
	
AddIn xai_math_nan(
	Function(XLL_DOUBLE, "xll_math_nan", "MATH.NAN")
	.Args({
		Arg(XLL_CSTRING, "input", "A string value.")
	})
	.FunctionHelp("Returns a quiet NaN value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/nan-nanf-nanl")
	.Documentation(R"xyzyx(The nan functions return a quiet NaN value.)xyzyx")
);
double WINAPI xll_math_nan(const char* input)
{
#pragma XLLEXPORT

	return nan(input);
}
	
AddIn xai_math_nearbyint(
	Function(XLL_DOUBLE, "xll_math_nearbyint", "MATH.NEARBYINT")
	.Args({
		Arg(XLL_DOUBLE, "x", "The value to round.")
	})
	.FunctionHelp("Rounds the specified floating-point value to an integer, and returns that value in a floating-point format.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/nearbyint-nearbyintf-nearbyintl1")
	.Documentation(R"xyzyx(If successful, returns x, rounded to the nearest integer, using the current rounding format as reported by fegetround. Otherwise, the function may return one of the following values:)xyzyx")
);
double WINAPI xll_math_nearbyint(double x)
{
#pragma XLLEXPORT

	return nearbyint(x);
}
	
AddIn xai_math_nextafter(
	Function(XLL_DOUBLE, "xll_math_nextafter", "MATH.NEXTAFTER")
	.Args({
		Arg(XLL_DOUBLE, "x", "The floating-point value to start from."),
		Arg(XLL_DOUBLE, "y", "The floating-point value to go towards.")
	})
	.FunctionHelp("Returns the next representable floating-point value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/nextafter-functions")
	.Documentation(R"xyzyx(Returns the next representable floating-point value of the return type after x in the direction of y. If x and y are equal, the function returns y, converted to the return type, with no exception triggered. If x is not equal to y, and the result is a denormal or zero, the FE_UNDERFLOW and FE_INEXACT floating-point exception states are set, and the correct result is returned. If either x or y is a NAN, then the return value is one of the input NANs. If x is finite and the result is infinite or not representable in the type, a correctly signed infinity or NAN is returned, the FE_OVERFLOW and FE_INEXACT floating-point exception states are set, and errno is set to ERANGE.)xyzyx")
);
double WINAPI xll_math_nextafter(double x, double y)
{
#pragma XLLEXPORT

	return nextafter(x, y);
}
	
AddIn xai_math_pow(
	Function(XLL_DOUBLE, "xll_math_pow", "MATH.POW")
	.Args({
		Arg(XLL_DOUBLE, "x", "Base."),
		Arg(XLL_DOUBLE, "y", "Exponent.")
	})
	.FunctionHelp("Calculates x raised to the power of y.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/pow-powf-powl")
	.Documentation(R"xyzyx(Returns the value of xy. No error message is printed on overflow or underflow.)xyzyx")
);
double WINAPI xll_math_pow(double x, double y)
{
#pragma XLLEXPORT

	return pow(x, y);
}
	
AddIn xai_math_remainder(
	Function(XLL_DOUBLE, "xll_math_remainder", "MATH.REMAINDER")
	.Args({
		Arg(XLL_DOUBLE, "x", "The numerator."),
		Arg(XLL_DOUBLE, "y", "The denominator.")
	})
	.FunctionHelp("Computes the remainder of the quotient of two floating-point values, rounded to the nearest integral value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/remainder-remainderf-remainderl")
	.Documentation(R"xyzyx(The floating-point remainder of x / y. If the value of y is 0.0, remainder returns a quiet NaN. For information about the representation of a quiet NaN by the printf family, see printf, _printf_l, wprintf, _wprintf_l.)xyzyx")
);
double WINAPI xll_math_remainder(double x, double y)
{
#pragma XLLEXPORT

	return remainder(x, y);
}
	
AddIn xai_math_remquo(
	Function(XLL_DOUBLE, "xll_math_remquo", "MATH.REMQUO")
	.Args({
		Arg(XLL_DOUBLE, "numer", "The numerator."),
		Arg(XLL_DOUBLE, "denom", "The denominator."),
		Arg(XLL_LONG_, "quo", "A pointer to an integer to store a value that has the sign and approximate magnitude of the quotient.")
	})
	.FunctionHelp("Computes the remainder of two integer values, and stores an integer value with the sign and approximate magnitude of the quotient in a location that's specified in a parameter.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/remquo-remquof-remquol")
	.Documentation(R"xyzyx(remquo returns the floating-point remainder of x / y. If the value of y is 0.0, remquo returns a quiet NaN. For information about the representation of a quiet NaN by the printf family, see printf, _printf_l, wprintf, _wprintf_l.)xyzyx")
);
double WINAPI xll_math_remquo(double numer, double denom, int* quo)
{
#pragma XLLEXPORT

	return remquo(numer, denom, quo);
}
	
AddIn xai_math_rint(
	Function(XLL_DOUBLE, "xll_math_rint", "MATH.RINT")
	.Args({
		Arg(XLL_DOUBLE, "x", "The floating-point value to round.")
	})
	.FunctionHelp("Rounds a floating-point value to the nearest integer in floating-point format.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/rint-rintf-rintl")
	.Documentation(R"xyzyx(The rint functions return a floating-point value that represents the nearest integer to x. Halfway values are rounded according to the current setting of the floating-point rounding mode, the same as the nearbyint functions. Unlike the nearbyint functions, the rint functions may raise the FE_INEXACT floating-point exception if the result differs in value from the argument. There's no error return.)xyzyx")
);
double WINAPI xll_math_rint(double x)
{
#pragma XLLEXPORT

	return rint(x);
}
	
AddIn xai_math__rotl(
	Function(XLL_LONG, "xll_math__rotl", "MATH._ROTL")
	.Args({
		Arg(XLL_LONG, "value", "Value to be rotated."),
		Arg(XLL_LONG, "shift", "Number of bits to shift.")
	})
	.FunctionHelp("Rotates bits to the left (_rotl) or right (_rotr).")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/rotl-rotl64-rotr-rotr64")
	.Documentation(R"xyzyx(The rotated value. There's no error return.)xyzyx")
);
unsigned int WINAPI xll_math__rotl(unsigned int value, int shift)
{
#pragma XLLEXPORT

	return _rotl(value, shift);
}
	
AddIn xai_math_round(
	Function(XLL_DOUBLE, "xll_math_round", "MATH.ROUND")
	.Args({
		Arg(XLL_DOUBLE, "x", "The floating-point value to round.")
	})
	.FunctionHelp("Rounds a floating-point value to the nearest integer value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/round-roundf-roundl")
	.Documentation(R"xyzyx(The round functions return a floating-point value that represents the nearest integer to x. Halfway values are rounded away from zero, regardless of the setting of the floating-point rounding mode. There's no error return.)xyzyx")
);
double WINAPI xll_math_round(double x)
{
#pragma XLLEXPORT

	return round(x);
}
	
AddIn xai_math__scalb(
	Function(XLL_DOUBLE, "xll_math__scalb", "MATH._SCALB")
	.Args({
		Arg(XLL_DOUBLE, "x", "Double-precision, floating-point value."),
		Arg(XLL_LONG, "exp", "Long integer exponent.")
	})
	.FunctionHelp("Scales argument by a power of 2.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/scalb")
	.Documentation(R"xyzyx(Returns an exponential value if successful. On overflow (depending on the sign of x), _scalb returns +/- HUGE_VAL; the errno variable is set to ERANGE.)xyzyx")
);
double WINAPI xll_math__scalb(double x, long exp)
{
#pragma XLLEXPORT

	return _scalb(x, exp);
}
	
AddIn xai_math_scalbn(
	Function(XLL_DOUBLE, "xll_math_scalbn", "MATH.SCALBN")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value."),
		Arg(XLL_LONG, "exp", "Integer exponent.")
	})
	.FunctionHelp("Multiplies a floating-point number by an integral power of FLT_RADIX.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/scalbn-scalbnf-scalbnl-scalbln-scalblnf-scalblnl")
	.Documentation(R"xyzyx(The scalbn functions return the value of x * FLT_RADIXexp when successful. On overflow (depending on the sign of x), scalbn returns +/- HUGE_VAL; the errno value is set to ERANGE.)xyzyx")
);
double WINAPI xll_math_scalbn(double x, int exp)
{
#pragma XLLEXPORT

	return scalbn(x, exp);
}
	
AddIn xai_math_sin(
	Function(XLL_DOUBLE, "xll_math_sin", "MATH.SIN")
	.Args({
		Arg(XLL_DOUBLE, "x", "Angle in radians.")
	})
	.FunctionHelp("Calculates the sine of a floating-point value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/sin-sinf-sinl")
	.Documentation(R"xyzyx(The sin functions return the sine of x. If x is greater than or equal to 263, or less than or equal to -263, a loss of significance in the result occurs.)xyzyx")
);
double WINAPI xll_math_sin(double x)
{
#pragma XLLEXPORT

	return sin(x);
}
	
AddIn xai_math_sinh(
	Function(XLL_DOUBLE, "xll_math_sinh", "MATH.SINH")
	.Args({
		Arg(XLL_DOUBLE, "x", "Angle in radians.")
	})
	.FunctionHelp("Calculates the hyperbolic sine.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/sinh-sinhf-sinhl")
	.Documentation(R"xyzyx(The sinh functions return the hyperbolic sine of x. By default, if the result is too large, sinh sets errno to ERANGE and returns ±HUGE_VAL.)xyzyx")
);
double WINAPI xll_math_sinh(double x)
{
#pragma XLLEXPORT

	return sinh(x);
}
	
AddIn xai_math_sqrt(
	Function(XLL_DOUBLE, "xll_math_sqrt", "MATH.SQRT")
	.Args({
		Arg(XLL_DOUBLE, "x", "Non-negative floating-point value")
	})
	.FunctionHelp("Calculates the square root.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/sqrt-sqrtf-sqrtl")
	.Documentation(R"xyzyx(The sqrt functions return the square-root of x. By default, if x is negative, sqrt returns an indefinite NaN.)xyzyx")
);
double WINAPI xll_math_sqrt(double x)
{
#pragma XLLEXPORT

	return sqrt(x);
}
	
AddIn xai_math_tan(
	Function(XLL_DOUBLE, "xll_math_tan", "MATH.TAN")
	.Args({
		Arg(XLL_DOUBLE, "x", "Angle in radians.")
	})
	.FunctionHelp("Calculates the tangent.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/tan-tanf-tanl")
	.Documentation(R"xyzyx(The tan functions return the tangent of x. If x is greater than or equal to 263, or less than or equal to -263, a loss of significance in the result occurs.)xyzyx")
);
double WINAPI xll_math_tan(double x)
{
#pragma XLLEXPORT

	return tan(x);
}
	
AddIn xai_math_tanh(
	Function(XLL_DOUBLE, "xll_math_tanh", "MATH.TANH")
	.Args({
		Arg(XLL_DOUBLE, "x", "Angle in radians.")
	})
	.FunctionHelp("Calculates the hyperbolic tangent.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/tanh-tanhf-tanhl")
	.Documentation(R"xyzyx(The tanh functions return the hyperbolic tangent of x. There's no error return.)xyzyx")
);
double WINAPI xll_math_tanh(double x)
{
#pragma XLLEXPORT

	return tanh(x);
}
	
AddIn xai_math_tgamma(
	Function(XLL_DOUBLE, "xll_math_tgamma", "MATH.TGAMMA")
	.Args({
		Arg(XLL_DOUBLE, "x", "The value to find the gamma of.")
	})
	.FunctionHelp("Determines the gamma function of the specified value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/tgamma-tgammaf-tgammal")
	.Documentation(R"xyzyx(If successful, returns the gamma of x.)xyzyx")
);
double WINAPI xll_math_tgamma(double x)
{
#pragma XLLEXPORT

	return tgamma(x);
}
	
AddIn xai_math_trunc(
	Function(XLL_DOUBLE, "xll_math_trunc", "MATH.TRUNC")
	.Args({
		Arg(XLL_DOUBLE, "x", "The value to truncate.")
	})
	.FunctionHelp("Determines the nearest integer that is less than or equal to the specified floating-point value.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/trunc-truncf-truncl")
	.Documentation(R"xyzyx(If successful, returns an integer value of x, rounded towards zero.)xyzyx")
);
double WINAPI xll_math_trunc(double x)
{
#pragma XLLEXPORT

	return trunc(x);
}
	
AddIn xai_math__j0(
	Function(XLL_DOUBLE, "xll_math__j0", "MATH._J0")
	.Args({
		Arg(XLL_DOUBLE, "x", "Floating-point value.")
	})
	.FunctionHelp("Computes the Bessel function of the first or second kind, of orders 0, 1, or n. The Bessel functions are commonly used in the mathematics of electromagnetic wave theory.")
	.Category("MATH")
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/bessel-functions-j0-j1-jn-y0-y1-yn")
	.Documentation(R"xyzyx(Each of these routines returns a Bessel function of x. If x is negative in the _y0, _y1, or _yn functions, the routine sets errno to EDOM, prints a _DOMAIN error message to stderr, and returns _HUGE_VAL. You can modify error handling by using _matherr.)xyzyx")
);
double WINAPI xll_math__j0(double x)
{
#pragma XLLEXPORT

	return _j0(x);
}
	
