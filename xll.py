#!/usr/bin/python3
# Generate C++ files to be used with the xll library
from cdecl import ccall
from ms_cpp_docs import page_html, hrefs, section_function_help, section_syntax, section_parameters

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
	return f'''// xll_{cat.lower()}.cpp - Excel add-in for functions in the {cat} category.
// Uncomment to build for pre 2007 Excel
//#define XLOPERX XLOPER
#include "xll/xll/xll.h"

using namespace xll;
	'''

def add_in(cdecl, params, help, cat = "XLL"):
	sep = ',\n\t\t'
	return f'''AddIn xai_{cdecl["fun"]}(
	Function({xll_type[cdecl["ret"]]}, "xll_{cat.lower()}_{cdecl["fun"]}", "{cat.upper()}.{cdecl["fun"].upper()}")
	.Args({{
		{sep.join(['Arg(' + xll_type[arg[0]] + ', "' + arg[1] + '", "' + params[arg[1]] + '")' for arg in cdecl["arg"]])}
	}})
	.FunctionHelp("{help}")
	.Category("{cat.upper()}")
);
{cdecl["ret"]} WINAPI xll_{cat.lower()}_{cdecl["fun"]}({cdecl["sig"]})
{{
#pragma XLLEXPORT

	return {ccall(cdecl)};
}}
	'''

def test_add_in():
	cdecl = {
		"ret": "void",
		"fun": "foo",
		"sig": 'int i, unsigned char c',
		"arg": [["int", "i"], ["unsigned char", "c"]]
    }
	params = {
		"i": "is an integer",
		"c": "is a character",
	}
	help = "Function help"
	cat = "Cmath"
	print(xll_prolog(cat))
	print(add_in(cdecl, params, help, cat))

if __name__ == '__main__':
	#test_add_in()
	for href in hrefs():
		print(href)
		page = page_html(href)
		print(section_parameters(page))
