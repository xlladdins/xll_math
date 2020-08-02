#!/usr/bin/python3
#
# https://github.com/eliben/pycparser
# https://pypi.org/project/pycparser/

import re
import requests
import lxml.etree as etree
from lxml import html
from lxml.html.clean import clean_html

# Excel function category
category = 'cmath'

ref = "https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/"
url = "https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library/reference/"

# simple C function prototype parser
tok = re.compile(r'\s*(\w+)\s*([\( ,\)])')
def parse_cdecl(text):
	cdecl = {}
	cdecl['type'] = []
	cdecl['name'] = []
	iter = tok.finditer(text)

	i = next(iter)
	assert (i[2] == ' ')
	cdecl['return'] = i[1]

	i = next(iter)
	assert (i[2] == '(')
	cdecl['symbol'] = i[1]

	for i in iter:
		assert (i[2] == ' ')
		cdecl['type'].append(i[1])
		i = next(iter)
		assert (i[2] == ',' or i[2] == ')')
		cdecl['name'].append(i[1])
		if (i[2] == ')'):
			break

	return cdecl

#print(parse_cdecl('int foo(double bar, float baz);'))

# strip out html tags
def strip_html(text):
    tree = html.fromstring(text)
	# fix up subsripts and superscripts!!!
    return tree.text_content()

# C to Excel argument codes
xll_args = {
	'short': 'XLL_SHORTX',
	'int': 'XLL_SHORTX',
	'long': 'XLL_LONGX',
	'double': 'XLL_DOUBLEX'
};

def addin(cat, cdecl, args, fh):
	assert (len(cdecl['type']) == len(args))
	argx = ''
	comma = ''
	for type, arg in zip(cdecl['type'], args):
		argx += f'{comma}ArgX({xll_args[type]}, X_("{arg[0]}"), X_("{arg[1]}"))'
		comma = ',\n\t\t'
	
	sym = cdecl['symbol']
	ret = cdecl['return']
	sig = ', '.join(map(' '.join, zip(cdecl['type'], cdecl['name'])))
	arg = ', '.join(cdecl['name'])

	return f'''\
// xll_sym.cpp - Call {sym} from Excel
#include <{category}>
#include "xll/xll/xll.h"

using namespace xll;

AddInX xai_{sym}(
	FunctionX({xll_args[ret]}, X_("?xll_{sym}"), X_("{cat.upper()}.{sym.upper()}"))
	.Args({{
		{argx}
	}})
	.Category(X_("{cat.upper()}"))
	.FunctionHelp(X_("{fh}"))
	.HelpTopic(X_("{ref}{sym}!0"))
);
{ret} WINAPI xll_{sym}({sig})
{{
#pragma XLLEXPORT

	return {sym}({arg});
}}
'''

if __name__ == '__main__':
	#https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/hypot-hypotf-hypotl-hypot-hypotf-hypotl?view=vs-2019
	#req = requests.get(url + "hypot-hypotf-hypotl-hypot-hypotf-hypotl.md")
	req = requests.get(url + "ldexp.md")
	assert (req.status_code == 200)
	# if r.status == 200: ...
	print(req.content.decode('utf-8'))
	parser = etree.HTMLParser(recover=True)
	page = etree.HTML(req.content, parser)
	#print(etree.tostring(page, pretty_print=True).decode('utf-8'))

	args = []
#<p><em>x</em>, <em>y</em><br>
#Floating-point values.</p>

#!!!
#s/<p><em>(.*)</em>, <em>(.*)</em><br>\n(.*)</p>
# /<p><em>\1</em><br>\3\n</p>\n<p><em>\2</em><br>\n\3</p>
#!!! or maybe just parse the html

#<p><em>x</em><br>
#Floating-point value.</p>
#<p><em>exp</em><br>
#Integer exponent.</p>
	are = r"<p><em>(\w+)</em><br/>\n(.*)</p>"
	car = re.compile(are);

	article = page.xpath("//article/h3/following-sibling::p")
	for a in article:
		t = etree.tostring(a).decode('utf-8')
		print (t)
		m = car.match(t)
		if (m):
			args.append(m.groups())
		else:
			fh = strip_html(t)
			break

	syntax = page.xpath('//h2[text()="Syntax"]/following-sibling::div[1]');
	decl = strip_html(etree.tostring(syntax[0]).decode('utf-8'))
	#print (f'decl: {decl}')
	cdecl = parse_cdecl(decl)
	print(cdecl)
	print(args)
	print(addin(category, cdecl, args, fh))
