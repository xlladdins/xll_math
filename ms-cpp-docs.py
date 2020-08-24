#!/usr/bin/python3
# Microsoft C++ runtime library documentation
import re
import requests
import lxml.etree as etree
from lxml import html

git_url = "https://github.com"
crt_url = git_url + "/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library"

# floating point main page
# replace by appropriate docs
fps_docs = "/floating-point-support.md"

def page_html(docs):
	req = requests.get(crt_url + docs)
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

def hrefs(docs):
	page = page_html(docs)
	#print(etree.tostring(page, pretty_print=True).decode('utf-8'))
	section = section_table(page)
	return [f'{git_url}{h}' for h in section_href(section)]

ref_url = git_url + crt_url + "/reference"
#hyp_url = ref_url + "/hypot-hypotf-hypotl-hypot-hypotf-hypotl"
#hyp_url = "https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/hypot-hypotf-hypotl-hypot-hypotf-hypotl"
#git_url = "https://github.com"
#crt_url = git_url + "/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library"
hyp_url = ref_url + "/ldexp.md"

# use .text to extract cdecl
syntax_xpath = "//*[@id='syntax']/following::pre[1]/code"
# sloppy parameter string
parameters_xpath = "//*[@id='parameters']/following::p[1]"
return_value_xpath = "//*[@id='return-value']/following::p[1]"

if __name__ == '__main__':
	href = hrefs(fps_docs)
	for h in href:
		print (h)
