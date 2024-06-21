#ifndef COMMON_DEFINES_IS_DEFINED
#define COMMON_DEFINES_IS_DEFINED

#define ZERO 0

#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

#define FAIL(r)		tX_Error_Description (r)

#define PercentToFloat(x)	(x/100)
#endif