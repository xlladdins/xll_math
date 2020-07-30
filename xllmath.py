#!/usr/bin/python3

import requests
from html.parser import HTMLParser
from bs4 import BeautifulSoup
from bs4 import SoupStrainer

reference = "https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/"

if __name__ == '__main__':
	ldexp = requests.get(reference + "ldexp")
	nav = SoupStrainer("nav")
	bs = BeautifulSoup(ldexp.text, "lxml", parse_only=nav)
	for nav in bs:
		print(nav)
