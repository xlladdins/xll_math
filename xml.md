# XML

A (simplified) eXtensible Markup Language _document_ is defined by the
following BNF grammar:

```
	document  ::= prolog element
	prolog    ::= '<?xml version="' version '" encoding="' encoding '"?>'
	element   ::= empty-tag | start-tag content end-tag
	empty-tag ::= '<' name attribute* '/>'
	start-tag ::= '<' name attribute* '>'
	content   ::= (element | string | entity | comment)*
	end-tag   ::= '</' name '>'
	name      ::= name-char+
	name-char ::= (letter | digit | '_' | ':')
	attribute ::= name '=' '"' string '"'
	string    ::= nice-char*
	entity    ::= '&' name ';'
	comment   ::= '<!--' string '-->'
```
where literal tokens are enclose in single quotes (`'`), vertical bar
(`|`) indicates alternatives, parentheses (`()`) are used for grouping
and do not occur in the document, asterisk (`*`) means zero or more
occurences, and plus (`+`) one or more.

The usual prolog version is `1.0` and encoding `UTF-8`.

Content can also have character data and processing instructions.
They can be used to embed additional data and information into
a document. We omit these for simplicity.

Names can't start with digits and sometimes contain a period (`.`).

Note that the characters `<`, `>`, and `&` have
special meaning. We call characters other than these _nice_. (This is non-standard terminology.)
The entities `&lt;`, `&gt;`, and `&amp;` can be used to include
special charaters in content.

Comments cannot be nested and the string must not start or end with the minus (`-`) character.

Strings are messier than what is specified above.

In a _valid_ XML document the name of each start-tag must be the same as
the name of the correponding end-tag.

Documents define a _tree_.
The document element is called the _root_.
Edges connect elements to every element in
its `content`.
These are _children_ of the element.
The order of elements in the text of the document
provide a _tree ordering_. This is called _document order_.

An element is the _parent_ of each of its children.
The children of an element are _siblings_.

The transitive closure of children are _decendents_.The transitive closure of parents are _ancestors_.

## XPath

XPath is an expression language for addressing nodes in an XML tree.
The complete specification is quite complicated but it acts on a
simple _data model_.

### Data Model

An _item_ in the data model is either a _node_, _function_,
or _atomic value_. There are seven kinds of nodes: _document_,
_element_, _attribute_, _text_, _namespace_, _comment_, and _processing instruction_. 
Functions can be _called_ given values for _parameters_
(arguments of the function) belonging to the _domain_ of the function.
The body of the function _implementats_ how the parameter values are
converted to the _result_ of the function call.  Atomic values can have
_type_ string, boolean, integer, floating point number, date, etc.

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

#### Accessor

_Accessors_ return information about content of nodes.

The _attribute_ accessor returns the attributes of a node.
It returns a sequence of zero or more attributes.

The _children_ acc...


Document nodes encapsulate XML documents.

### Path Expression

A _path expression_ consists of a series of one or more _steps_.
Each step specifies successive refinements of nodes to be addressed
and acts in the _context_ selected by the previous steps. A context
is a sequence of nodes.

```
	PathExpr ::= RelativePathExpr | '/' RelativePathExpr? | '//' RelativePathExpr
	RelativePathExpr ::= StepExp (('/' | '//') StepExpr)*
```
where question mark (`?`) indicates exactly zero or one occurence and we use
parenthesis `()` for grouping. They don't show up in expression.

If _E_ is a relative path expression then '_E_', '/',  '/_E_', and '//_E_'
are (the only) valid path expressions. Permissable relative path expressions are
'_S_', '/_S_/_T_', and '//_S_/_T_//_U_' where _S_, _T_, and _U_ are step expressions.

Steps are separated by '/' or '//'.
Path expressions starting with '/' or '//' are abbreviations for one
or more initial steps. A '/' at the beginning of a path expression selects the
document root. A '//' at the beginning of a path
expression selects the root and all decendents.

A relative path expression selects the sequence of nodes that are specified by the
steps in the path.

#### Step

Each step generates a sequence of items from the context provided by the
previous step and then filters the sequence by zero or more predicates.

```
	StepExpr      ::= PostfixExpr | AxisStep
	AxisStep      ::= (ReverseStep | ForwardStep) PredicateList
	ForwardStep   ::= ForwardAxis NodeTest
	ReverseStep   ::= ReverseAxis NodeTest
	PredicateList ::= Predicate*
```

Postfix expressions select primary expressions. These are usually not nodes.

```
	PostfixExpr  ::= PrimaryExpr (Predicate | ArgumentList | Lookup)*
	Predicate    ::= '[' Expr ']'
	ArgumentList ::= '(' (Argument (',' Argument)*)? ')'
```

Primary expressions are the basic primitives of XPath. They can be
_literals_, _variable references_, _context item expressions_, and _function calls_.
They may be enclosed in parentheses to control the order in which they are evaluated.

An _axis step_ selects nodes from the current context, performs a test on
each of the nodes, and optionally filters those based on zero or more predicates.

A _forward axis_ looks a the current node and its attributes, siblings
after the current node (using document order), and decendents. 
A _reverse axis_ looks at siblings before the current node and ancestors
(optionally includng the current node).

The axes have names. For forward axes 'child' specifies all children of the current node,
'descendent' is the transitive closure of all children, 'attribute' is the sequence
of attributes associated with the current node, ...
For reverse axes 'parent' is the (unique) parent of the current node or empty if
the node does not have a parent, ...

There are abbreviations for the most common axes. The 'self' axis is '.', the
'parent' is '..', and '@' selects 'attribute's of the current node.

A node test is a filter acting on the name or kind of a node. They are separated
from the axis name by a '::' token.
```
	NodeTest ::= KindTest | NameTest
	NameTest ::= EQName | Wildcard
	Wildcard ::= '*' | (NCName ':*') | ('*:' NCName) | (BracedURILiteral '*')
	EQName   ::= QName | URIQualifiedName
```

A name test matches the node having the same name or all nodes if the wildcard is '*'.
If no node matches then the result is empty.


Abbreviated syntax...

