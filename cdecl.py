#!/usr/bin/python3
# A makeshift C declaration parser

import re

# "ret fun(type arg, ...)"
# {ret, fun, sig, arg: [[type, name], ...]}
#!!! check for '/* floating-point */'???
def cdecl(text):
	# sig leading and trailing spaces are trimmed
	cre =r'\s*(?P<ret>.*?)\s+(?P<fun>\S+)(?<=\s)*\(\s*(?P<sig>.*?)\s*\)'
	m = re.match(cre, text)
	ret = m.groupdict().copy()
	# normalize sig
	ret["sig"] = re.sub(r'\s+', ' ', ret["sig"])
	ret["sig"] = re.sub(r'\s+\(\s*', '(', ret["sig"])
	ret["sig"] = re.sub(r'\s+\)\s*', ')', ret["sig"])
	ret["sig"] = re.sub(r'\s*,\s*', ', ', ret["sig"])
	ret["sig"] = re.sub(r'\s*\*\s*', '* ', ret["sig"])
	ret['arg'] = [list(re.match(r'(.*)\s+(\S+)|', a).groups()) for a in re.split(r'\s*,\s*', ret['sig'])]

	return ret

# {ret, fun, sig, arg: [[type, name], ...]}
# "fun(arg, ...)"
def ccall(cdecl):
	args = ', '.join([a[1] for a in cdecl["arg"]])

	return f'{cdecl["fun"]}({args})';

def test_cdecl():
	tests = [
		{
			"arg": "void foo()",
			"ret": {
				"ret": "void",
				"fun": "foo",
				"sig": '',
				"arg": [[None,None]]
			}
		},
		{
			"arg": "void foo(int i)",
			"ret": {
				"ret": "void",
				"fun": "foo",
				"sig": 'int i',
				"arg": [["int", "i"]]
			}
		},
		{
			"arg": "void foo(int i, char c)",
			"ret": {
				"ret": "void",
				"fun": "foo",
				"sig": 'int i, char c',
				"arg": [["int", "i"], ["char", "c"]]
			}
		},
		{
			"arg": " void	foo( 	int i ,   char  c )  ",
			"ret": {
				"ret": "void",
				"fun": "foo",
				"sig": 'int i, char c',
				"arg": [["int", "i"], ["char", "c"]]
			}
		},
		{
			"arg": " void	foo( 	int i , unsigned char  c )  ",
			"ret": {
				"ret": "void",
				"fun": "foo",
				"sig": 'int i, unsigned char c',
				"arg": [["int", "i"], ["unsigned char", "c"]]
			}
		},
		#!!! more tests
	]
	for t in tests:
		#print(f'>{t["arg"]}<')
		#print(f'arg: >{cdecl(t["arg"])}<')
		#print(f'ret: >{t["ret"]}<')
		assert(cdecl(t["arg"]) == t["ret"])

if __name__ == '__main__':
	test_cdecl()
