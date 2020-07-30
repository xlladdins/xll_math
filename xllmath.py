#!/usr/bin/python3

import requests
from lxml import html

reference = "https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/"
xmain = "/html/body/div[2]/div/section/div/div[1]/main"

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
	.HelpTopic(X_("{reference}{name}!0"))
);
{ret} WINAPI xll_{name}(args...)
{{
#pragma XLLEXPORT

	return {name}(args...);
}}
'''

if __name__ == '__main__':
	ldexp = requests.get(reference + "ldexp")
	page = html.fromstring(ldexp.content)
	#main = page.xpath('//*[@id="main"]/text()')
	fh = page.xpath(xmain + '/p[1]/text()')
	#/html/body/div[2]/div/section/div/div[1]/main/p[3]
	#decl = page.xpath(xmain + '/pre[1]/code/text()')
	param = page.xpath(xmain + '/p[br]/text()')
	#param = page.xpath(xmain + '//*/text()')
	#/html/body/div[2]/div/section/div/div[1]/main/p[2]/em
	#/html/body/div[2]/div/section/div/div[1]/main/p[2]
	#/html/body/div[2]/div/section/div/div[1]/main/p[3]/em
	#print(fh)
	#print(decl)
	print(param)
	#print(addin('CMATH', 'ldexp', 'double', fh[0]))
