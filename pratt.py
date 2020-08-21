#!/usr/bin/python3

from setuptools import setup
#import BytesIO
from tokenize import tokenize, NUMBER, STRING, OP

setup(name='pratt',
      version='0.1',
      description='A Pratt parser',
      #url='http://effbot.org/zone/simple-top-down-parsing.htm',
      author='Keith A. Lewis',
      author_email='kal@kalx.net',
      license='MIT',
      packages=['pratt'],
      zip_safe=False)

"""
def pratt_parse(src):
	tok = tokenize(BytesIO(src.encode('utf-8')).readline)
	for i in tok:
		print (i)
def test_pratt_parse(source):
	#src = cStringIO.StringIO(source).readline
	pratt_parse(source)
test_pratt_parse('a b + c,d')
"""

class Pratt:
	# Give it a token stream
	__self__(next):

	def __repr__(self):
		return f''
		
	def parse(self, rbp = 0)
		left = token.nud() # content of current token
		while (token = next.token).rbp > left.rbp:
			left = token.nud()

		return left
	
