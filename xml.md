# XML

A (simplified) eXtensible Markup Language _document_ is defined by the
following [BNF](https://www.w3.org/TR/REC-xml/#sec-notation) grammar:

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
occurences, and plus (`+`) one or more. We will use question mark (`?`)
to indicate zero or one occurance. When writing about the grammar we
use `inline code` instead of enclosing literals in single quotes.

The usual prolog version is `1.0` and encoding `UTF-8`.

Content can also have character data and processing instructions.
They can be used to embed additional data and information into
a document. We omit these for simplicity.

Elements tags are the _name_ of the element.

Note that the characters `<`, `>`, `&`, `'`, and `"` have special
meaning in XML. We call characters other than these _nice_.  (This is
not standard W3 notation. The full story for allowable text is a bit messy.)
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
_atomic value_. Every item has a _value_ and a _type_.

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

_node-kind_: returns one of the strings "attribute", "comment", "document",
"element", "namespace", "processing-instruction", or "text".

_attribute_: return the sequence of key-value attributes of an element.

_node-name_: return the name of the node as a string. If the node is an element it
will be the tag of the element.

_string-value_: return the string value of a node. If the node is an element
it returns the content of the element.

_children_: return the sequence of child nodes in the content of an element
in _document order_.

_parent_: return the parent of a node. If the node does not have a parent
an empty sequence is returned.

The _decendents_ of a node are its children and their decendents.
They are the _transitive closure_ of the children.
The _ancestors_ of a node is its parent and its ancestors.
They are the transitive closure of the parent.
A collection of children are _siblings_.

## XPath

XPath is an expression language for addressing nodes in an XML tree.
Applying a XPath _expression_ to a document satisfying the data model results in a sequence of nodes.
An expression is a list of one or more comma (`,`) separated _single expressions_.
It results in a concatenation of the node sequences of each single expression.

XPath is an expressive language. It has loops, quantification, and conditionals.
In addition to single expressions that are _value expressions_<sup name="a1">[1](#f1)</sup>
they can also be _for expressions_, _quantified expressions_, or _conditional expressions_.

<span id="f1">[1]</span>. The fact a single expression can be a value expression is well hidden in the XPath
specification. It specifes a single expression
can be an [`OrExpr`](https://www.w3.org/TR/xpath20/#doc-xpath-OrExpr),
which can be a `AndExpr`,
which can be a `ComparisonExpr`,
which can be a `RangeExpr`,
which can be a `AdditiveExpr`,
which can be a `MultiplicativeExpr`,
which can be a `UnionExpr`,
which can be a `IntersectExceptExpr`,
which can be a `InstanceofExpr`,
which can be a `TreatExpr`,
which can be a `CastableExpr`,
which can be a `CastExpr`,
which can be a `UnaryExpr`,
which can be a `ValueExpr`. Whew! [&larrhk;](#a1)

A for expression has the form '`for $`_var_` in `_list_` return `_body_'.
The body is executed once for for each item in the list. The items can be referred to using
var in the body.  A for expression may have multiple `in` clauses
'`for $`_var_` in `_list_ (`, $`_var'_` in `_list'_ )*` return `_body_' which loops over
the cartesian product of the lists.

A quantified expression has the form
'(`some` | `every`) `$`_var_` in `_list_ (`, $`_var'_` in `_list'_)* ` satisfies `_cond_'.
It selects one or all list items that evaluate to true when substituted into the condition.

An conditional expression has the form '`if (`_cond_`) then `_expr_` else `_expr_.
It returns the first expression if the [effective boolean value](https://www.w3.org/TR/xpath20/#id-ebv)
of the condition is true and the second expression otherwise.

XPath has a full complement of set, logical, and arithmetic operators,
as the previous footnote suggests. Recent versions have limited regular
expression functionality.

### Path Expression

A _path expression_ consists of a series of _steps_.
Each step takes a sequence of nodes, the step _context_, and results
in another sequence of nodes: the context provided to the following step.
Steps are separated by a single forward slash (`/`) or double slash (`//`)
to refer to children or ancestors, respectively, of the step context.
The initial context of the first step is the entire document tree.
Subsequent steps select from the _context_ provided by the previous step.

```
	PathExpr ::= RelativePathExpr | '/' RelativePathExpr? | '//' RelativePathExpr
	RelativePathExpr ::= StepExp (('/' | '//') StepExpr)*
```

Steps are separated by '/' or '//'.
Use a single slash to specify ... and double slash to specify ...
Path expressions starting with '/' or '//' are abbreviations for one or more initial steps.
A '/' at the beginning of a path expression selects the document root.
A '//' at the beginning of a path expression selects the root and all decendents.

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

Postfix expressions select primary expressions. These are usually leaf nodes.

```
	PostfixExpr  ::= PrimaryExpr (Predicate | ArgumentList | Lookup)*
	Predicate    ::= '[' Expr ']'
	ArgumentList ::= '(' (Argument (',' Argument)*)? ')'
```

Primary expressions are the basic primitives of XPath. They can be
_literals_, _variable references_, _context item expressions_, and _function calls_.
They may be enclosed in parentheses to control the order in which they are evaluated.

An _axis step_ selects nodes from the current context, performs a test on
each of the nodes, and optionally filters those based on zero or more node test predicates.

The _forward axis_ is the current node and decendents. 
The _reverse axis_ is the current node and its ancestors.

The axes have names.
For forwards axes `self` is the current node,
`child` specifies all children of the current node,
`descendent` is the transitive closure of all children,
`following-sibling` are all siblings after the current node at the same level,
`following` is the transitive closure of all following siblings,
`attribute` is the sequence of attributes associated with the current node.
`descendent-or-self` is what it sounds like.

For reverse axes `parent` is the (unique) parent of the current node or empty,
`ancestor` is the transitive closure of parent, 
`preceding-sibling` are all siblings before the current node at the same level,
`preceding` is the transitive closure of preceding siblings, and
`ancestor-or-self` is what it sounds like.

There are abbreviations for the most common axes. The `self` axis is `.`, the
`parent` is `..`, and `@` selects `attribute`s of the current node.

A node test is a filter acting on the name or kind of a node. They are separated
from the axis name by a '::' token.
```
	NodeTest ::= NameTest | KindTest
	NameTest ::= Name | "*"
```

A name test matches the node having the same name or all nodes if "*".
If no node matches then the result is empty.

A kind test matches node types. These can be
`document-node(`(ElementTest)?`)` where ElementTest is
`element(` NameTest? `)` or `element(` NameTest `,` TypeName `?`? `)`,
an ElementTest, 
`attribute(` NameTest (`,` TypeName)? `)`, 
`text()`,
`comment()`, or `node()`.
The latter selects all nodes, similar to the wildcard `*` for names.


## Remarks

All modern browsers are equipped with a "developer tool" that can be used to inspect documents.
Usually the `F12` key will bring that up. It knows more about XPath, CSS, and DOM structure
than you or I will ever know, so take advantage of that. Right clicking on a node will pop
up a menu that allows you to, among other things, copy its XPath to the clipboard. 
It will give you _an_ XPath that will select the node, but it might not be the most natural one
for you to use. Think of it as a good starting point.

You can also edit anything in the inspector and the changes will be immediately reflected in the document.
