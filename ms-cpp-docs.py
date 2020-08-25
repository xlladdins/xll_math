#!/usr/bin/python3
# Microsoft C++ runtime library documentation
import re
import requests
import lxml.etree as etree
from xml.etree import ElementTree
from lxml import html
from lxml.html.clean import clean_html
from lxml.html.clean import Cleaner
# cleaner = Cleaner(page_structure=False)                                          
# cleaner.clean_html(...)

git_url = "https://github.com"
# Microsoft github C runtime libray documentation
crt_url = git_url + "/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library"

# floating point main page
# replace by appropriate docs
fps_item = "/floating-point-support.md"

# parsed HTML from URL
def page_html(item):
	req = requests.get(crt_url + item)
	assert (req.status_code == 200)
	# if r.status == 200: ...
	parser = etree.HTMLParser(recover=True)

	return etree.HTML(req.content, parser)

# user content
section_xpath = '//*[starts-with(@id, "user-content-")]'
# first column of table after matching id
td_xpath = section_xpath + "/following::table/tbody/tr/td[1]"
a_xpath = td_xpath + "/a"

# <a href="url">text</a>
def section_table(page):
	return page.xpath(a_xpath)

# URLs of individual functions without git_url prefix
def section_href(table):
	return [a.attrib['href'] for a in table]

def section_text(table):
	return [a.text for a in table]

# array of urls to floating point functions
# e.g., hrefs("/floating-point-support.md")
def hrefs(item):
	page = page_html(item)
	section = section_table(page)
	return [f'{git_url}{h}' for h in section_href(section)]

fun_item = "/reference/bessel-functions-j0-j1-jn-y0-y1-yn.md"
#fun_url = ref_url + "/ldexp.md"

# user content
user_content_xpath = '//*[starts-with(@id, "user-content-")]/parent::h2'

# array of all function declarations
syntax_xpath = user_content_xpath + '[text()="Syntax"]/following::div[1]'
def section_syntax(page):
	syntax = page.xpath(syntax_xpath)
	text = re.sub(r'\n\s+', '', ''.join(syntax[0].itertext()))
	text = re.sub(r'\n\)', ')', text);

	return text.split(';\n')

if __name__ == '__main__':
	page = page_html(fun_item)
	x = section_syntax(page)
	print (x)
	#for i in x:
		#tostring(i)
		#print(etree.tostring(i, pretty_print=True).decode('utf-8'))
		#print(x)
