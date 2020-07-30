#!/usr/bin/python3

# https://github.com/eliben/pycparser

import requests
import lxml.etree as etree

#url = "https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/"
#url = "https://raw.githubusercontent.com/MicrosoftDocs/cpp-docs/master/docs/c-runtime-library/reference/"
url = "https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library/reference/"

xll_args = {
	'int': 'XLL_SHORT',
	'double': 'XLL_DOUBLEX'
};

def addin(cat, name, ret, fh):
	return f'''\
AddInX xai_{name}(
	FunctionX({xll_args[ret]}, X_("?xll_{name}"), X_("{cat}.{name.upper()}")
	.Args({{
		ArgX(an, arg, ument)
	}})
	.Category(X_("{cat}"))
	.FunctionHelp(X_("{fh}"))
	.HelpTopic(X_("{url}{name}!0"))
);
{ret} WINAPI xll_{name}(args...)
{{
#pragma XLLEXPORT

	return {name}(args...);
}}
'''

if __name__ == '__main__':
	ldexp = requests.get(url + "ldexp.md")
	# if r.status == 200: ...
	#print(ldexp.content.decode('utf-8'))
	parser = etree.HTMLParser(recover=True)
	page = etree.HTML(ldexp.content, parser)
	article = '//article'
	print(etree.tostring(page, pretty_print=True).decode('utf-8'))
	#/html/body/div[4]/div/main/div[2]/div/div[3]/div[2]/article/h3
	#for i in page.iter():
	#	print(i)
	#print(page)
	#print(fh)
	#print(decl)
	#print(param)
	#print(addin('CMATH', 'ldexp', 'double', fh[0]))
