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
# set by hand appropriately
fps_item = "/floating-point-support.md"
fps_url = crt_url + fps_item

# parsed HTML from URL
def page_html(url = fps_url):
	req = requests.get(url)
	assert (req.status_code == 200)
	parser = etree.HTMLParser(recover=True)

	return etree.HTML(req.content, parser)

# List of all functions
#
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

def test_section_href():
	page = page_html(fps_url)
	table = section_table(page)
	href = section_href(table)
	for i in href:
		print(i)

def section_text(table):
	return [a.text for a in table]

# array of urls to floating point functions
# e.g., hrefs(fps_url)
def hrefs(url = fps_url):
	page = page_html(url)
	section = section_table(page)
	# exclude /reference/posix-ecvt.md

	return [f'{git_url}{h}' for h in section_href(section)]

def test_hrefs():
	for href in hrefs(fps_url):
		print(href)

#
# Individual functions
#
ref_url = crt_url + "/reference"
#fun_item = "/bessel-functions-j0-j1-jn-y0-y1-yn.md"
fun_item = "/ldexp.md"

def section_function_help(page):
	xhelp = "//h1/following-sibling::p[1]"
	help = page.xpath(xhelp)

	return ''.join(help[0].itertext())

def test_section_function_help():
	page = page_html(ref_url + fun_item)
	ret = section_function_help(page)
	print(ret)

# array of all function declarations
def section_syntax(page):
	xsyntax = '//*[@href="#syntax"]/parent::h2/following::div[1]'
	syntax = page.xpath(xsyntax)
	text = re.sub(r'\n\s+', '', ''.join(syntax[0].itertext()))
	text = re.sub(r'\n\)', ')', text);
	text = re.sub(r'//.*\n', '', text, re.DOTALL)

	return text.split(';\n')

def test_section_syntax():
	page = page_html(ref_url + fun_item)
	ret = section_syntax(page)
	print(ret)

def section_parameters(page):
	xparameters = '//*[@href="#parameters"]/parent::h3/following::p[./em and ./br]'
	params = page.xpath(xparameters)
	print(etree.tostring(params, pretty_print=True).decode('utf-8'))

	# split on em to get key names
	for i in params:
		print(list(i.itertext()))

	return {k:v.strip() for (k,v) in [list(i.itertext()) for i in params]}

def test_section_parameters():
	page = page_html(ref_url + fun_item)
	ret = section_parameters(page)
	print(ret)

test_url = "https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library/reference/atan-atanf-atanl-atan2-atan2f-atan2l.md"

if __name__ == '__main__':
	none = None
	#test_hrefs()
	# all reference to individual functions
	#test_section_href()

	#test_section_function_help()
	#test_section_syntax()
	#test_section_parameters()

	page = page_html(test_url)
	print(section_parameters(page))
	#print(etree.tostring(page, pretty_print=True).decode('utf-8'))
	#print (page)
	#x = section_parameters(page)
	#for i in x:
		#tostring(i)
		#print(etree.tostring(i, pretty_print=True).decode('utf-8'))
		#print(i)
