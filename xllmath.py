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

# Official documentation
ref = "https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/"
# Markdown documentation
url = "https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library/reference/"

# simple C function prototype parser
# parse 'ret sym(t1 n1, ..., tk nk);'
# to {return: ret, symbol: sym, args: "t1 n1, ..., tk nk", type: [t1, ..., tk], name: [n1, ... nk]}

# C comments (does not handle nested comments
cre = re.compile(r"/\*.*?\*/", re.MULTILINE)
# C++ comments
cppre = re.compile(r"//.*$", re.MULTILINE)
def parse_cdecl(text):
	# remove C comments (does not work when nested)
	text = re.sub(cre, "", text)
	# remove C++ comments
	text = re.sub(cppre, "", text)
	text = re.sub(r"\s*([\(,;\)])\s*", r"\1", text)
	s = re.compile(r"[\(\)]").split(text)

	#assert len(s) == 3
	assert s[2][0] == ';'

	cdecl = dict(zip(['return', 'symbol', 'args'], s[0].split() + [s[1]]))
	cdecl['type'] = [x.split(' ')[0] for x in cdecl['args'].split(', ')]
	cdecl['name'] = [x.split(' ')[1] for x in cdecl['args'].split(', ')]

	return cdecl

def test_parse_cdecl():
	c1 = parse_cdecl('int foo(double bar, float baz);')
	c2 = parse_cdecl('int foo(double bar /*a comment*/, float baz) 	;')
	assert (c1 == c2)
	c3 = parse_cdecl('int foo(double bar /*a comment*/, \nfloat // comment\n baz); // inline comment')
	assert (c1 == c3)
	c4 = parse_cdecl('int foo(double bar /*a comment*/, \nfloat // comment\n baz);\n')
	assert (c1 == c4)

test_parse_cdecl()

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
	#print(req.content.decode('utf-8'))
	parser = etree.HTMLParser(recover=True)
	page = etree.HTML(req.content, parser)
	#print(etree.tostring(page, pretty_print=True).decode('utf-8'))

	args = []
#<p><em>x</em>, <em>y</em><br>
#Floating-point values.</p>

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
	print (f'decl: {decl}')
	cdecl = parse_cdecl(decl)
	print(cdecl)
	print(args)
	print(addin(category, cdecl, args, fh))
