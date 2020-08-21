#!/usr/bin/python3

ret = 'double'
fun = 'exp'
args = ['double', 'int']

def cdecl(ret,fun,args):
	return f'''
	{ret} WINAPI {fun}({', '.join(args)})
	'''

print(cdecl(ret,fun,args))
