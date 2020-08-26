#!/usr/bin/python3
# Generate C++ files to be used with the xll library

xll_type = {
	"void": "XLL_VOID",
	"int": "XLL_LONG",
	"long": "XLL_LONG",
	"short": "XLL_SHORT",
	"unsigned short": "XLL_USHORT",
	"char": "XLL_USHORT",
	"unsigned char": "XLL_USHORT",
	"double": "XLL_DOUBLE",
}

def xll_prolog(cat):
	return f'''
// xll_{cat.lower()}.cpp - Excel add-in for functions in the {cat} category.
// Uncomment to build for pre 2007 Excel
//#define XLOPERX XLOPER
#include "xll/xll/xll.h"

using namespace xll;
	'''

def add_in(cdecl, params, help, cat = "XLL"):
	sep = ',\n\t\t'
	return f'''
AddIn xai_{cdecl["fun"]}(
	Function({xll_type[cdecl["ret"]]}, "xll_{cdecl["fun"]}", "{cat}.{cdecl["fun"].upper()}")
	.Args({{
		{sep.join(['Arg(' + xll_type[arg[0]] + ', "' + arg[1] + '", "' + params[arg[1]] + '")' for arg in cdecl["arg"]])}
	}})
	.FunctionHelp("{help}")
	.Category("{cat}")
);
{cdecl["ret"]} WINAPI xll_{cdecl["fun"]}({cdecl["sig"]})
{{
#pragma XLLEXPORT

	return {cdecl["fun"]}({', '.join([a[1] for a in cdecl["arg"]])});
}}
	'''


def test_add_in(cdecl, params, help, cat):
	print(xll_prolog(cat))
	print(add_in(cdecl, params, help, cat))

if __name__ == '__main__':
	cat = "Cmath"
	decl = {
		"ret": "void",
		"fun": "foo",
		"sig": 'int i, unsigned char c',
		"arg": [["int", "i"], ["unsigned char", "c"]]
    }
	params = {
		"i": "is an integer",
		"c": "is a character",
	}
	test_add_in(decl, params, "Function help", "Cmath")
