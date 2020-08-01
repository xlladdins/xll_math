# XML

A (simplified) eXtensible Markup Language _document_ is defined by the
following BNF grammar:

```
	document  ::= prolog element
	prolog    ::= '<?xml version="1.0" encoding="UTF-8"?>'
	element   ::= empty-tag | start-tag content end-tag
	empty-tag ::= '<' name attribute* '/>'
	start-tag ::= '<' name attribute* '>'
	content   ::= element*
	end-tag   ::= '</' name '>'
	name      ::= char+
	attribute ::= name '=' value
	value     ::= '"' char* '"'
```
where literal tokens are enclose in single quotes (`'`), vertical
bar (`|`) indicates alternatives, asterisk (`*`) means zero or more
occurences, and plus (`+`) one or more.

In a _valid_ XML document the name of each start-tag must be the same as
the name of the correponding end-tag.  This definition ignores (important)
concepts like _reference_, _character data_, _processing instructions_,
and _comments_ that are also valid content of an element.

Not every sequence of characters is a valid name. For example, names starting
with an ampersand (`&`) are called _entities_ and are often used to escape
special characters or to represent non-ASCII characters. For example, the
entity `&amp;` is used to escape the ampersand character.

The top level element is called the _root_ of the document. It is a _tree_
where the elements are the _nodes_ and _edges_ connect each element to
the elements in its content. The order of elements in the content
provide a _tree ordering_.

The (immediate) _children_ of an element are the elements its content.
An element is the (immediate) _parent_ of each of its children.
The children of a node are _siblings_.

## XPath

XPath is an expression language for addressing nodes in an XML tree.
The complete specification is quite complicated but it acts on a
simple _data model_.

### Data Model

An _item_ in the data model is either a _node_, _function_, or _atomic
value_.  Every XML document (or subdocument) is a node. Functions can be
_called_ given values function _parameters_ (arguments of the function)
belonging to the _domain_ of the function.  The body of the function
_implementats_ how the parameter values are converted to the _result_
of the function call.  Atomic values can have _type_ string, boolean,
integer, number, date, etc.

A _sequence_ is an ordered list of zero or more items. The _empty sequence_
contains no items. A sequence containing
exactly one item is a _singleton_. The data models considers a singleton
to be identical to the item it contains. Sequences **may not** contain sequences.

The data model also provides for _arrays_ and _maps_ as special cases
of functions.  Arrays are sometimes called vectors, ordered lists, or
sequences. Unlike a sequence in the data model, an array is an item and
can appear as an item in a sequence.
Maps are sometimes called associative arrays, dictionaries, hash tables,
keyed lists, or objects (as in JSON).

The domain of an an array is a set of positive integers
_{1,..,n}_ where _n_ is the _size_ of the array.
The domain of a map is a set of strings.

### Path Expression

A _path expression_ consists of a series of one or more _steps_.
Each step specifies a successive refinement of nodes to be addressed
and acts in the _context_ selected by the previous steps.

Path expressions can be either _relative_ or _absolute_.
```
	PathExpr ::= RelativePathExpr | "/" RelativePathExpr? | "//" RelativePathExpr
	RelativePathExpr ::= StepExp (('/' | '//') StepExpr)*
```
where question mark (`?`) indicates exactly zero or one occurence and we use
parenthesis `()` for grouping. They are not part of the expression.
If _S_ is a step expression then _S_, /,  /_S_, and are //_S_
are (the only) valid path expressions. Permissable relative path expressions are
_S_, /_S_/_T_, and //_S_/_T_//_U_ where _T_ and _U_ are step expressions.
