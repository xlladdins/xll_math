#!/usr/bin/python3
# Generate C++ files to be used with the xll library
from cdecl import ccall, cdecl
from ms_cpp_docs import page_html, hrefs, section_function_help, section_syntax, section_parameters

docs_url = 'https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/' 
git_url = 'https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library/reference/'

xll_type = {
	"void": "XLL_VOID",
	"int": "XLL_LONG",
	"unsigned int": "XLL_LONG",
	"int*": "XLL_LONG_",
	"long": "XLL_LONG",
	"unsigned long": "XLL_LONG",
	"long*": "XLL_LONG_",
	"short": "XLL_SHORT",
	"const char": "XLL_USHORT",
	"char": "XLL_USHORT",
	"char*": "XLL_CSTRING",
	"const char*": "XLL_CSTRING",
	"unsigned short": "XLL_USHORT",
	"unsigned char": "XLL_USHORT",
	"double": "XLL_DOUBLE",
	"double*": "XLL_DOUBLE_",
}

def xll_prolog(cat):
	return f'''// xll_{cat.lower()}.cpp - Excel add-in for functions in the {cat} category.
#include <cmath>
#include "xll/xll/xll.h"

using namespace xll;

int xll_math_doc = Documentation("CMATH", R"(
This add-in calls functions from the &lt;cmath&gt; library.
)");

	'''

def add_in(cdecl, params, help, cat, url):
	sep = ',\n\t\t'
	ret = xll_type[cdecl["ret"]]
	fun = cdecl["fun"]
	FUN = fun.upper();
	cat = cat.lower()
	CAT = cat.upper()
	args = cdecl["arg"]
	Arg = ['Arg(' + xll_type[arg[0]] + ', "' + arg[1] + '", "' + params[arg[1]] + '")' for arg in cdecl["arg"]]
	return f'''AddIn xai_{cat}_{fun}(
	Function({ret}, "xll_{cat}_{fun}", "{CAT}.{FUN}")
	.Args({{
		{sep.join(Arg)}
	}})
	.FunctionHelp("{help}")
	.Category("{CAT}")
	.HelpTopic("{url}")
);
{cdecl["ret"]} WINAPI xll_{cat}_{fun}({cdecl["sig"]})
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
	print(add_in(cdecl, params, help, cat, "https://google.com"))

if __name__ == '__main__':
	#test_add_in()
	cat = "math"
	with open('crt_ref.txt') as f:
		hrefs = [line.strip() for line in f if line[0] != '#']

	print(xll_prolog(cat))
	for href in hrefs:
		#print(href)
		page = page_html(git_url + href + '.md')
		syntax = section_syntax(page)
		decl = cdecl(syntax[0])
		#print(decl)
		params = section_parameters(page)
		#print(params)
		help = section_function_help(page)
		print(add_in(decl, params, help, cat, docs_url + href))
