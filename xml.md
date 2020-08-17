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
_atomic value_. Every item has a _type_ and a _value_.

A _sequence_ is an ordered list of zero or more items. The _empty sequence_
contains no items. A sequence containing
exactly one item is a _singleton_. The data models considers a singleton
to be identical to the item it contains. Sequences **may not** contain sequences.

There are seven types of nodes: _document_, _element_, _attribute_,
_text_, _namespace_, _comment_, and _processing instruction_.
We will ignore namespace and processing instructions for now.

The document node is the root of the tree. It has a single element
with _edges_ to each item in its _content_, the _children_ of the element.
Content is a sequence of zero or more elments, text, entities, or comments.
Elements have edges, in turn, to each item in its content while text, entities, and
comments are _leaf_ nodes. Elemnts can have attributes that are _key_-_value_
pairs.

A _link_ is a special type of edge from one element to another.
If an element has an attribute with key `id` then its value can be used to
specify the target of a link. Any other element can use
an attribute with key `href` and value equal to the
id to create links. In a well-formed document an element can have
exactly zero or one `href` and `id` attribute and `id` values must be unique.

A function has a _name_, _parameters_, and a _body_. It can be called using
its name with parameter values belonging to the _domain_ of the function.
The body is evaluated using the supplied parameter values to return a result.
_Arrays_ and _maps_ are special cases
of functions. 
The domain of an an array is a set of positive integers
_{1,..,n}_ where _n_ is the _size_ of the array.
Arrays are sometimes called vectors, ordered lists, or
sequences. Unlike a sequence in the data model, an array is an item and
can appear as an item in a sequence.
The domain of a map is a set of strings.
Maps are sometimes called associative arrays, dictionaries, hash tables,
keyed lists, or objects (as in JSON).

Atomic values are the lowest level item.
They can have [primitive types](https://www.w3.org/TR/xmlschema-2/#built-in-primitive-datatypes)
number, string, boolean, date, etc.


### [Accessors](https://www.w3.org/TR/query-datamodel/#accessors)

_Accessors_ return information about nodes. They are defined on every
kind of node but may return an empty sequence.

node-kind
  : returns one of the strings "attribute", "comment", "document",
"element", "namespace", "processing-instruction", or "text".

attribute
  : returns the sequence of key-value attributes of an element.

The _node-kind_ accessor returns one of the strings "attribute", "comment", "document",
"element", "namespace", "processing-instruction", or "text".

The _attribute_ accessor returns the sequence of key-value attributes of an element.

The _node-name_ accessor returns the name of the node as a string. If the node is an element it
will be the tag of the element.

The _string-value_ accessor returns the string value of a node. If the node is an element
it returns the content of the element.

The _children_ accessor returns the sequence of child nodes in the content of an element.

The _parent_ accessor returns the parent of a node. If the node does not have a parent
an empty sequence is returned.



## XPath

XPath is an expression language for addressing nodes in an XML tree.
Applying a _path expression_ to a tree satisfying the data model results in a sequence of nodes
contained in the tree. An expression consists of a sequence of _steps_.
Steps select from the _context_ provided by the previous step.
The initial context of the first step is the entire document tree.

### Path Expression

A _path expression_ consists of a series of one or more _steps_.
Each step takes a sequence of nodes, the step _context_, and results
in a sequence of nodes, the context provided to the following step.
The context of the first step is the document provided to the path expression.

```
	PathExpr ::= RelativePathExpr | '/' RelativePathExpr? | '//' RelativePathExpr
	RelativePathExpr ::= StepExp (('/' | '//') StepExpr)*
```
where question mark (`?`) indicates exactly zero or one occurence and we use
parenthesis `()` for grouping. They don't occur in the expression.

If _E_ is a relative path expression then '_E_', '/',  '/_E_', and '//_E_'
are (the only) valid path expressions. Permissable relative path expressions are
'_S_', '/_S_/_T_', and '//_S_/_T_//_U_' where _S_, _T_, and _U_ are step expressions.

Steps are separated by '/' or '//'.
Path expressions starting with '/' or '//' are abbreviations for one
or more initial steps. A '/' at the beginning of a path expression selects the
document root. A '//' at the beginning of a path
expression selects the root and all decendents.

### Step

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

