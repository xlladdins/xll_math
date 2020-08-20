#!/usr/bin/python3
import requests
import lxml.etree as etree
from lxml import html

crt_url = "https://github.com/MicrosoftDocs/cpp-docs/blob/master/docs/c-runtime-library"
# floating point main page
float_url = crt_url + "/floating-point-support.md"
id_xpath = '//*[@id="user-content-supported-math-and-floating-point-routines"]'
tbody_xpath = id_xpath + "/parent::h2/following::table/tbody/tr/td[1]"
href_xpath = tbody_xpath + "/a"

def float_table(page):
	return page.xpath(href_xpath)

def float_href(href):
	return [a.attrib['href'] for a in href]

if __name__ == '__main__':
	req = requests.get(float_url)
	assert (req.status_code == 200)
	# if r.status == 200: ...
	parser = etree.HTMLParser(recover=True)
	page = etree.HTML(req.content, parser)
	article = float_href(float_table(page))
	#print(article)
	for a in article:
		print(a)
		#print(etree.tostring(a.attrib, pretty_print=True).decode('utf-8'))
