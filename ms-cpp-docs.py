#!/usr/bin/python3
# Microsoft C++ runtime library documentation
import re
import requests
import lxml.etree as etree
from lxml import html

git_url = "https://github.com"
crt_url = git_url + "/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library"
# floating point main page
section_url = crt_url + "/floating-point-support.md"

section_xpath = '//*[@id="user-content-supported-math-and-floating-point-routines"]'
td_xpath = section_xpath + "/parent::h2/following::table/tbody/tr/td[1]"
a_xpath = td_xpath + "/a"


# first column of table after h2 parent of id
# <a href="url">text</a>
def section_table(page):
	return page.xpath(a_xpath)

# URLs of individual functions without git_url prefix
def section_href(table):
	return [a.attrib['href'] for a in table]

def section_text(table):
	return [a.text for a in table]

ref_url = git_url + crt_url + "/reference"
#hyp_url = ref_url + "/hypot-hypotf-hypotl-hypot-hypotf-hypotl"
#hyp_url = "https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/hypot-hypotf-hypotl-hypot-hypotf-hypotl"
#git_url = "https://github.com"
#crt_url = git_url + "/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library"
hyp_url = ref_url + "/ldexp"

# use .text to extract cdecl
syntax_xpath = "//*[@id='syntax']/following::pre[1]/code"
# sloppy parameter string
parameters_xpath = "//*[@id='parameters']/following::p[1]"
return_value_xpath = "//*[@id='return-value']/following::p[1]"

if __name__ == '__main__':
	req = requests.get(hyp_url)
	assert (req.status_code == 200)
	# if r.status == 200: ...
	parser = etree.HTMLParser(recover=True)
	page = etree.HTML(req.content, parser)
	#print(etree.tostring(page, pretty_print=True).decode('utf-8'))
	#uc = page.xpath(parameters_xpath)
	#uc = page.xpath(syntax_xpath)
	uc = page.xpath(return_value_xpath)
	for u in uc:
		print(etree.tostring(u, pretty_print=True).decode('utf-8'))
		#print(u.text)
		#print(u)
#	table = section_table(page)
#	href = section_href(table)
#	text = section_text(table)
#	for h in href:
#		print(h)
	#print(article)
	#s = re.compile(r'\s*,\s*');
	#for a in article:
	#	print(a)
	#	for c in s.split(a):
	#		print(f'>{c}<')
		#print(etree.tostring(a.attrib, pretty_print=True).decode('utf-8'))
