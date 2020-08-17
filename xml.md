# XML

A (simplified) eXtensible Markup Language _document_ is defined by the
following BNF grammar:

```
	document  ::= prolog element
	prolog    ::= '<?xml version="' version '" encoding="' encoding '"?>'
	element   ::= empty-tag | start-tag content end-tag
	empty-tag ::= '<' name attribute* '/>'
	start-tag ::= '<' name attribute* '>'
	content   ::= (element | text | entity | comment)*
	end-tag   ::= '</' name '>'
	name      ::= (letter | '_' | ':') name-char*
	name-char ::= (letter | '_' | ':' | digit | '.' | '-')
	attribute ::= name '=' value
	text      ::= nice-char*
	value     ::= '"' text '"'
	entity    ::= '&' name ';'
	comment   ::= '<!--' text '-->'
```
where literal tokens are enclose in single quotes (`'`), vertical bar
(`|`) indicates alternatives, parentheses (`()`) are used for grouping
and do not occur in the document, asterisk (`*`) means zero or more
occurences, and plus (`+`) one or more.

The usual prolog version is `1.0` and encoding `UTF-8`.

Content can also have character data and processing instructions.
They can be used to embed additional data and information into
a document. We omit these for simplicity.

Names for tags specify the element _type_.
If the element is an `empty-tag` it contains no children,
otherwise the content of the element are its _children_.

Note that the characters `<`, `>`, `&`, `'`, and `"` have special
meaning in XML. We call characters other than these _nice_.  (This is
not standard W3 notation. The full story for allowable text is messy.)
The entities `&lt;`, `&gt;`, `&amp;`, `&apos;`, and `&quot;` can be
used to include (_escape_) special characters in text. Text can contain
non-nice characters after the initial character.

Comments cannot be nested and the string must not start or end with the minus (`-`) character.

Text is intermingled character data and _markup_. Markup always starts
with `<` and ends with `>` or starts with `&` and ends with `;`.
Any text that is not markup is character data.

In a _well-formed_ XML document the name of each start-tag must be the same as
the name of the correponding end-tag.

<!--
## Element Content Model

Element content is a list of children of type _choice_ or _sequence_.
A choice has the form `'(' cp ('|' cp)* ')'` and a sequnce has
the form `'(' cp (',' cp)* ')'` where `cp` can be any list
of names, choices, or seqeuences.
-->

## Data Model

The _data model_ is an abstract representation of an XML document.
It is a _tree_ of _items_. An _item_ is a _node_, _function_, or
_atomic value_.

There are seven kinds of nodes: _document_, _element_, _attribute_,
_text_, _namespace_, _comment_, and _processing instruction_.

The document node is the root of the tree. It has a single element
with _edges_ to each item in its _content_. The only items allowed
in content are elements, text, entities (atomic data?), or comments. The elements
have edges to each item in its content while text, entities, and
comments are _leaf_ nodes.

Items in the sequence are children
of the content.

A function ...

An atomic value ...

correspond to XML
element tags or the content of the element.
The _edges_ connect each element
to its content and content its _children_.
Content is a sequence of zero or more elments, text,
entities, or comments.

A _sequence_ is an ordered list of zero or more items. The _empty sequence_
contains no items. A sequence containing
exactly one item is a _singleton_. The data models considers a singleton
to be identical to the item it contains. Sequences **may not** contain sequences.

A _link_ is a special type of edge from one element to another.
If an element has an `id` attribute then its value can be used to
specify the target of a link. Any other element can use
zero or more the `href` attribute with value equal to the
id to create links. In a well-formed document ids are unique.

An _item_ in the data model is either a _node_, _function_,
or _atomic value_. There are seven kinds of nodes: _document_,
_element_, _attribute_, _text_, _namespace_, _comment_, and _processing instruction_. 

<!--
An _item_ in the data model is either a _node_, _function_,
or _atomic value_.
There are seven kinds of nodes: _document_,
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
-->

### Accessors

_Accessors_ return information about content of nodes.

The _attribute_ accessor returns the sequence of attributes of an element node.

The _children_ accessor returns the sequence of nodes of a contend node.


Document nodes encapsulate XML documents.

## XPath

XPath is an expression language for addressing nodes in an XML tree.
The complete specification is quite complicated but it acts on a
simple _data model_.


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

