
# pug

pug is my new programming language project, I guess.

Objectives:

  - jit interpreter (libjit) + aot compiler (llvm)
  - prototype-based, duck typing
  - batteries included: bignum, collections, unicode

Influences: lua, javascript, ruby

Until further notice, this project isn't useful for any purpose - I'm just
trying out new things for fun, we'll see where it leads.

## License

The pug project is released under the terms of the Simplified BSD license
(2-clause) - see the LICENSE file for a copy.

Dependencies are originally licensed as follows:

  - libjit: LGPL-2.1 - must be dynamically linked
  - libcollections: BSD
  - greg: BSD
  - gc: permissive, similar to X11 license
  - jansson: BSD
  - bstring: GPL/BSD dual-licensed (I choose you, BSD!)

## Captain's log

Hint: read it from bottom to top.

### 2014-08-14

After fixing parsing with greg, and managing to store it in a few data
structures, I've started thinking about AST traversal, dumping it for
debug, various transformations, etc.

The problem with 'C-structs-as-first-argument-of-a-bunch-of-functions'-style
is that you don't necessarily have a common, uh, structure for your structs.
ie. your structs aren't tagged with a type, you can't have a visitor pattern
because you have no idea how to dispatch (remember, a `void*` pointer is only
useful if you roughly know what's hiding underneath).

I don't want to go full-ooc where everything has a class, and classes have
metaclasses, and everything is virtual and overrideable and blah, that's
too heavy. I took a look at GLib, even thought of rewriting the whole thing
in Vala or Genie, and then snapped back to reality.

So I'm thinking, something light could do the trick - a pointer to a `class`
field, that's a pointer to a struct of known type, say, `pug_ast_node_interface`.
This struct has pointers to various other structs - if they're non-null, the
interfaces are implemented for that class.

For examples, some nodes might be typed, or have a scope, things like that,
that will make AST traversal easier (at least, possible). It's still very
cumbersome to do anything with C at all, but as I'm learning the hard way,
"it's nothing that a few macros can't fix".

I care more about safety and debuggability than runtime performance at the
moment - already ran into a few bad segfaults that I had to whip out gdb
for (and on OSX, even brew-installed gdb must be codesigned by hand now,
so I wasn't really happy about that).

I added [jansson][jansson] to take care of JSON decoding/encoding. I've
started writing an AST dump to json - this will not only make external
tools easy to write, it'll also make the frontend easy to test: just check
that the JSON structure matches. It might not be ideal for bytecode, for
instance, but I have yet to figure that out completely (with libjit).

I added [bstring][bstring] to manipulate strings. C's stdlib functions are just
too barebones and error-prone for my taste. At least now I can substring,
concatenate, format, replace, and split without worrying about things
exploding.  I had to modify bstring a little to use GC-allocated memory, and
wrote a tiny bridge macro to help jansson deal with bstrings.

[jansson]: http://www.digip.org/jansson/
[bstring]: http://bstring.sourceforge.net/

### 2014-08-13

It was fun to experiment with PackCC, and `packrat` seemed like a fun buzzword,
maybe it would've been faster than Ian Piumarta's peg/leg, maybe allowing left
recursion and memoizing and everything would've been fantastic, but right now:

  - PackCC doesn't support leg grammar, and I really like leg grammar
  - PackCC error reporting isn't the greatest, let's be honest

It's probably a very fine project, but right now I'm more used to [greg][greg]
- I know how to make friendly parsers with it, the leg syntax is nice, and
everything. I reused a bunch of tricks from [nagaqueen][nagaqueen], the ooc
grammar, for reading from memory & file streams, rewinding whitespace, etc.

I still have no idea how I could parse a significant-whitespace language
with a PEG. A quick search turns up [moonscript][moonscript], I should ask
leafo about it - or just muster up the courage to decipher lpeg-using-code.

I adapted gf3/peg.vim to get [leg syntax highlighting in vim][leg.vim].

I've also decided to rely on the [Boehm GC][bdw-gc] for the compiler/interpreter.
I don't really want to deal with manual memory allocation in such a codebase
for now. I might, later, but I have to make the best use of my limited
available brainspace.

[moonscript]: https://github.com/leafo/moonscript/blob/master/moonscript/parse.lua
[greg]: https://github.com/fasterthanlime/greg
[leg.vim]: https://github.com/fasterthanlime/leg.vim
[bdw-gc]: http://www.hboehm.info/gc/ 

### 2014-08-11

Migrated project to CMake - its `ExternalProject` feature makes it easy to
build, well, external projects, whether they are autotools-based, cmake-based,
or god-knows-what-based. Really the only bad thing I can say about it is that
you can't specify environment variables.

As for our own CMakeLists.txt, I'm using `file(GLOB)` directives because I'm
lazy and don't want to list everything by hand - also because I expect the
number of source files to explode over the next few weeks.

[cmake]: http://www.cmake.org/

### 2014-08-07

Fixed libcollections so that it builds on MinGW (win32 gcc) - turns out you
can't use `TYPES_H` as a header guard and expect your stuff to run everywhere
(don't blame me, I'm just using.)

Spent way too long trying to get the whole thing compiling in a win32
environment. While waiting for libjit to try and compile for the 20th time that
evening, tried a cross-compilation from [Debian][debian] out of boredness,
which pretty much worked first time, and much quicker too.

I think I may be done messing with mingw on Windows at all.
[mingw-w64][mingw-w64] on Debian is now my weapon of choice to produce Windows
binaries.

[mingw-w64]: http://mingw-w64.sourceforge.net/
[debian]: http://www.debian.org/

### 2014-08-06

After experimenting with a few JITs, decided to take [libjit][libjit] for a spin.

Set up a minimal project with a hand-written Makefile.

Using [packcc][packcc] to generate a parser from a [PEG][peg] grammar. It seems
old, but works so far.

Using [libcollections][libcollections] so I don't have to write a hash table,
vector, etc. all over again. It seems mostly header-based, but it's kinda good
- it gets you compiler warnings on incompatible types, and your own function
name, I kind of like it so far.

Happy with vendoring (= including the sources of) libs I'm depending on, so
that I can apply fixes if needed. For example, libjit had a codepath that used
deprecated OSX APIs instead of [dlopen/dlsym/dlclose][dlfcn] - I disabled it
(it crashed when dlopening NULL, instead of exposing the global symbol table).

[libjit]: https://www.gnu.org/software/libjit/
[packcc]: http://sourceforge.net/projects/packcc/
[peg]: https://en.wikipedia.org/wiki/Parsing_expression_grammar
[libcollections]: https://bitbucket.org/manvscode/libcollections
[dlfcn]: https://en.wikipedia.org/wiki/Dynamic_loading

