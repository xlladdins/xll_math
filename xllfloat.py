#!/usr/bin/python3
import re
import requests
import lxml.etree as etree
from lxml import html

git_url = "https://github.com"
crt_url = git_url + "/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library"
# floating point main page
float_url = crt_url + "/floating-point-support.md"

id_xpath = '//*[@id="user-content-supported-math-and-floating-point-routines"]'
td_xpath = id_xpath + "/parent::h2/following::table/tbody/tr/td[1]"
a_xpath = td_xpath + "/a"

def float_table(page):
	return page.xpath(a_xpath)

def float_href(a_):
	return [a.attrib['href'] for a in a_]

def float_text(a_):
	return [a.text for a in a_]

if __name__ == '__main__':
	req = requests.get(float_url)
	assert (req.status_code == 200)
	# if r.status == 200: ...
	parser = etree.HTMLParser(recover=True)
	page = etree.HTML(req.content, parser)
	#article = float_href(float_table(page))
	table = float_table(page)
	article = float_text(table)
	#print(article)
	s = re.compile(r'\s*,\s*');
	for a in article:
		print(a)
		for c in s.split(a):
			print(f'>{c}<')
		#print(etree.tostring(a.attrib, pretty_print=True).decode('utf-8'))
