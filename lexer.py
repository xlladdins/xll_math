#!/usr/bin/python3
# lexer.py - scan typical language lines
'''
"aY to yank and @a to execute
:!python3 -m pytest %
'''
import re

# calls lambda on tok = m.group()
# return array of parsed token pairs and the remaining unparsed line
def lexer(line): # and keys array argument
	lex = re.Scanner([
		(r"[a-zA-Z_]\w*", lambda lex, tok: ("IDENTIFIER", tok)),
		(r"0x[0-9]+",     lambda lex, tok: ("HEXIDECIMAL", tok)),
		(r"[+-]?[0-9]+",  lambda lex, tok: ("INTEGER", tok)),
		(r"[\(\)\.,:=;]", lambda lex, tok: ("PUNCTUATION", tok)),
		(r"\s+",          lambda lex, tok: None)
	], flags=re.DOTALL)
	
	return lex.scan(line)

tests = {
	"abc": ([('IDENTIFIER', 'abc')], ''),
	"a$ bc": (),
	"double f(int x);": (),
}
def test_lexer():
	for key in tests:
		print(key)
		print(tests[key])
		print(lexer(key))
		#assert lexer(key) == tests[key]

test_lexer()
