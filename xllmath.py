#!/usr/bin/python3

# https://github.com/eliben/pycparser
# https://pypi.org/project/pycparser/

import re
import requests
import lxml.etree as etree

ref = "https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/"
#url = "https://raw.githubusercontent.com/MicrosoftDocs/cpp-docs/master/docs/c-runtime-library/reference/"
url = "https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library/reference/"

# C to Excel argument codes
xll_args = {
	'int': 'XLL_SHORT',
	'double': 'XLL_DOUBLEX'
};

def addin(cat, name, ret, fh, args):
	argx = ''
	comma = ''
	for arg in args:
		argx += f'{comma}ArgX(type, X_("{arg[0]}"), X_("{arg[1]}"))'
		comma = ',\n\t\t'
	
	return f'''\
AddInX xai_{name}(
	FunctionX({xll_args[ret]}, X_("?xll_{name}"), X_("{cat}.{name.upper()}")
	.Args({{
		{argx}
	}})
	.Category(X_("{cat}"))
	.FunctionHelp(X_("{fh}"))
	.HelpTopic(X_("{ref}{name}!0"))
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
	#print(etree.tostring(page, pretty_print=True).decode('utf-8'))
	article = page.xpath("//article/h3/following-sibling::p")
	args = []
	are = r"<p><em>(\w+)</em><br/>\n(.*)</p>"
	#are = r"<p><em>(\w+)</em><br/>\s*(\w+)</p>"
	car = re.compile(are, re.DOTALL);
	for a in article:
		t = etree.tostring(a).decode('utf-8')
		m = car.match(t)
		if (m):
			args.append(m.groups())
		else:
			fh = t
			break
		
	print(args)
	print(addin('CMATH', 'ldexp', 'double', fh, args))
