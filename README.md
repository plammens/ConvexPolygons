> **Note:** to properly view this document, you can either use a Markdown viewer 
> like [Typora](https://www.typora.io), or view the [exported `html` document](README.html) in this repository. 


Convex Polygon Calculator
====================

Table of contents:
[TOC]



# Introduction

This project brings to you a Convex Polygon calculator; a small command-line
program that is able to compute the convex hull of a set of points, the
intersection and convex union of convex polygons, the area,
perimeter, and centroid of a polygon... and more! Heck, it can even draw these
polygons! :smile:

The author knows this will be a dream come true for many people...

Start by reading the [features and usage](#features-and-usage) section, and then move on to the
[setup and execution](#setup-testing-and-execution-instructions) section when you're ready! And if you're still documentation-hungry,
pay a visit to the [reference manual](#reference-manual).


# Features and usage

The calculator works in a command-line environment. Each line from
`stdin` is interpreted as a single command. Commands follow a classical
`<keyword> [arguments]` structure.

The whole calculator revolves around 2D convex polygons. You can create, delete,
draw, intersect, unite... convex polygons. Each polygon is stored as an object with
a unique identifier (ID). Identifiers can be composed of almost any combination
of letters, numbers and  symbols.

Jump to the [list of available commands](#commands) to view what you can do with the calculator, or
go to the [examples section](#examples) to take a look at some prepackaged examples.

## Commands

Below you'll find a list of all available commands. `<angle>` brackets indicate
a positional argument, while `[square]` brackets denote an optional argument. 
Ellipses (`[like so...]`) indicate an arbitrary number of arguments.

### Polygon / ID management

 -  `polygon <ID>`

The `polygon` command associates an identifier with a convex polygon made by a
set of zero or more points. If the polygon identifier is new, it will create
it. If it already existed, it will overwrite the previous polygon. New
polygons are black.

 - `delete <ID>`

Deletes the polygon with the given identifier (i,e., frees the identifier).


 - `list`

Prints a list of currently defined identifiers, in lexicographical order.

### Polygon-printing commands


 - `print <polygon ID>`

The `print` command prints the name and the vertices of a given
polygon. The output contains the vertices in the convex hull of the
polygon, in clockwise order, starting from the vertex will lowest `x` coordinate 
(and the lowest `y` in case of ties). The output is printed in a single line,
with space separated coordinartes.


 - `pretty-print <polygon ID>`

 Like `print`, but with slightly nicer format.

### Polygon info commands

- `area <ID>`

The `area` command prints the area of the given polygon.

 - `perimeter <ID>`

The `perimeter` command prints the perimeter of the given polygon.


 - `vertices <ID>`

The `vertices` command prints the number of vertices of the convex hull of the
given polygon.


 - `centroid <ID>` 

The `centroid` command prints the centroid of the given polygon.

### IO commands

Here `<file>` denotes a valid file path.


 - `save <file> [polygon IDs...]`

The `save` command saves the given polygons in a file, overwriting it if it already existed. The format is the same as for `print`.


 -  `load <file>`

The `load` command loads the polygons stored in a file, in the same way as `polygon`, but retrieving the vertexes and identifiers from the specified file.

- `include <file>`

This command parses the contents of `file` as if each line in the file were written directly
to `stdin`. Standard output from the parsing of the commands will be suppressed, although any errors will still be displayed. Useful for scripting and testing.

### Drawing commands


 - `setcol <ID> <R> <G> <B>`

The `setcol` command associates a color to the given polygon. `R`, `G` and `B` are the red,
green, and blue color values respectively; they should all be real numbers in the range 
$[0, 1]$.


 - `draw <file> [polygon IDs...]` 

The `draw` command draws a list of polygons in a PNG file, each one with its
associated color. The polygons are scaled to fit nicely in the image, mantaining
their aspect ratio.

- `paint <file> [polygon IDs...]`

Like `draw`, but fills the interior of polygons instead of just sketching the edges.

### Polygon operations


 - `intersection <ID1> <ID2> [ID3]`

This command may receive two or three parameters:

When receiving two parameters, say,  `p1` and `p2`, `p1` gets updated to 
the intersection of the original `p1` and `p2`.

When receiving three parameters `p1`, `p2` and `p3`, `p1` gets be updated
to the intersection of `p2` and `p3`.


 -  `union <ID1> <ID2> [ID3]`

Just as the `intersection` command, but for the convex union of polygons.


 - `inside <ID1> <ID2>`

Given two polygons, the `inside` command prints `yes` or `no` depending on whether
the first polygon is inside the second polygon.


 -  `bbox <ID1> [polygon IDs...]`

The `bbox` command associates a new polygon to `ID1`, with the four vertices corresponding to the
bounding box of the given polygons. Keep in mind that the bounding box of an empty set is undefined.



## Comments and empty lines

Lines starting with a `#` will be ignored. Likewise, empty lines will be ignored.


## Errors and warnings

Some commands, such as asking for the bounding box of the empty set, will produce an error. In these cases an error message (in bright red, if your console supports ANSI escape codes ​) will be printed to `stderr`. The author has tried to make the error messages as straightforward as
possible.

Other commands will produce warnings. This means that the command finished
its execution correctly, but that some suspicious situation was found that
the user may want to be aware of (to avoid misunderstandings about how
the program is functioning).


## Examples

You can find usage examples under the folder `examples`. Each example has its own sub-folder. Each sub-folder contains an input text file, a shell script to run the example, and any output files the example may have. 

For *example* (get it?), to run the `squares` example, run the following command.

```bash
sh examples/example1/run.sh
```

This very simple example creates two squares and calculates their union and their intersection:

```text
# examples/square/in.txt
# a small example

# setup two overlapping squares:
polygon s1  0 0 2 0 2 2 0 2
polygon s2  1 1 1 3 3 1 3 3

# computations:
intersection s3 s1 s2
union u s1 s2

# output:
setcol s1 0.6 0.1 0
setcol s2 0 0.1 0.6
setcol s3 1 0 1

paint before.png s1 s2
paint intersection.png s1 s2 s3
paint union.png u s1 s2
```

Once it finishes its execution, you should find three pictures in the `examples/squares` directory.

To run all examples, run

```bash
make examples
```

.




# Setup, testing and execution instructions

## Build

This project needs `GNU Coreutils` (i.e. the `UNIX`-style commands such as `find`, `rm`, etc.) , 
`GNU make`, and `cmake` (if building the libraries from scratch). So if you're running Linux or
Mac, you probably won't need to install anything. If you're running Windows, installing [`Cygwin`](https://www.cygwin.com) 
with the aforementioned packages should be enough.

No external dependencies need to be installed separately; they come bundled with the project.
That said, if you don't have [pngwriter](https://github.com/pngwriter/pngwriter) installed, you can build it from source straight from the
project by running

```bash
make libs
```

.

If for some reason (such as not having `cmake` installed) the installation of `pngwriter` fails, 
you can proceed to [installing `pngwriter` manually](<https://github.com/jordi-petit/ap2-imatges>). Don't forget to set the `USER_LIB_DIR` variable in the `Makefile` to whatever your installation path is. (It should be the path where the `libPNGwriter.a` file is located.)

--------------

To build everything (main program and test), run the following command.

```bash
make all  # (or just `make`)
```

This should do three things: build the `pngwriter` library from source and install it locally
into `./libs/` (where `./` is the project root), build the main executable, and build the tests.

Other useful `make` targets:

- To build the main program separately, run
```bash
make build
```

- To build the test program separately, run
```bash
make build-test
```

- To build the libraries separately, run
```bash
make libs
```


## Execution of main program

This is the moment you have been waiting for your whole life...

To run the main program, just execute the command

```bash
make run
```

Or, if you're a do-it-yourself type (and you have already run `make build` or `make all`), you
can execute the program directly like so (from the project root):

```sh
./build/bin/main.x
```

Enjoy!



## Testing the program

This project comes with a few bundled unit tests, made with [`doctest`](https://github.com/onqtam/doctest). To check that the author hasn't been lying, and that this thing actually works as advertised, run

```bash
make test
```

(this is equivalent to

```bash
make build-test
./build/bin/test.x
```

).

If the tests succeed and you want to inspect what's actually going on behind the scenes,
run

```bash
make test ARGS=--success
```

so you'll see in detail every single test assertion. (In fact, you can pass any arguments you
like to the test program by giving the `ARGS` variable a value &mdash; e.g. `ARGS="--foo --bar"`;
refer to [doctest's docs](https://github.com/onqtam/doctest/blob/master/doc/markdown/commandline.md) for all the supported command-line arguments).

If you're still suspicious... well, just dive into the source.

One of the highlights of the test suite is a `Python`-generated file containing the description of
two polygons with 100 000 points each, of which the intersection is calculated! They're two
overlapping slightly rotated circles, so the total number of vertices should be 200 000. In fact,
thats one of the test cases &mdash; check out [`test/src/test_from_file.cc`](./test/src/test_from_file.cc).


# Project structure

The most important directories in the project root are:

- `include`: contains all of the project's header files
  - `class`: contains header files dedicated to a single class
  - `details`: contains header files that are intended
    for internal use only.
- `src`: contains all of the main source files
- `libs`: contains all library files (external dependencies)
- `test`: contains test files (test sources, generators, generated tests, etc. )
- `examples`: some short usage examples

Other directories that are made on-the-run:

- `build`: directory that stores all build output files, generated
  automatically when building the project (e.g., by running `make all`)
  - `bin`: contains binary files, e.g. `main.x`. It is the output
    directory of the linking stage.
  - `obj`: compiled object files
  - `depend`: auto-generated dependency information files
- `out`: the (optional) output directory. The program will prefix all
  output files it produces with this path. Also, when loading files,
  the program will look for them here. Have a look [here](#changing-the-output-directory) for customizing
  this directory.

Finally, the `docs` directory contains additional files needed for the documentation and 
automatically generated documentation files.


## Naming conventions

### Symbols
Constants are named in `SCREAMING_CASE`. Non-constant variables,
functions and methods are named in `camelCase`. Classes, enums and structs are
named in `PascalCase` (including their corresponding header files). Other header/source
files are named in `lisp-case`. Namespaces are named in `lowercase`.

Internal symbols are prefixed with an underscore.

### Files
Header files are given the extension `.h`. Source files are given the extension `.cc`.

# Design choices

Two main design  principles were kept in mind when developing this project: modularity and scalability. Here are some of the consequences:

- Command handlers are grouped into so-called "command handlers": in *very* broad terms, instead of writing something like this,

```c++
void parseCommand(const std::string &kwd, [...]) {
    if (kwd == "polygon") {
        std::string id;
        std::cin >> id;
        newPolygon(id, ...);
    } else if (kwd == "delete") {
        std::string id;
        std::cin >> id;
        delPolygon(id, ...);
    } [...]
}
```

​	one does things like

```c++
void handleIDManagement(const std::string &kwd, [...]) {
    std::string id;
    std::cin >> id;
    
    if (kwd == "polygon") newPolygon(id, [...]);
    else if (kwd == "delete") delPolygon(id, [...]);
    } [...]
}
```

​	by grouping commands together with the same "argument signature".

- No `using namespace::std;` declarations, to avoid name conflicts. The author has learned it the hard way...
- Custom `namespace`s for certain things: all geometric utilities are grouped together under the
  `geom` namespace, for instance
- Usage of [`Boost.Range`](<https://www.boost.org/doc/libs/1_69_0/libs/range/doc/html/index.html>) to allow for lazy-evaluated ranges and range adaptors, and to enhance the flexibility of the algorithms (by taking a `boost::any_range` instead of just a `std::vector`, for instance).


# Additional details

## Changing the output directory
You can customize the output directory for the main program by editing the constant
`OUT_DIR` in the file [`include/consts.h`](include/consts.h), located at line `41`. You should enter
the path relative to the project root.

Keep in mind that if you change the name of the output directory, you will either
have to create that directory before writing/reading files, or configure the `Makefile`'s
`OUT_DIR` variable accordingly.

You can leave it blank if you want to control the path of each file directly (starting at the
project's root directory).

In that last case, be sure *not* to leave the `Makefile`'s `OUT_DIR` variable blank, since
then, upon running `make clean`, all of the files in the project root will be deleted
(since `rm -rf ./` will be called) :wink:.

# Reference manual

This project uses [doxygen](http://www.doxygen.nl) to automatically generate a reference manual with all of the
details of functions, classes, namespaces and more.

To view the manual, you can run `make view-docs`, which by default is equivalent to
`firefox docs/html/index.html`. (You can configure the browser used to open
the docs by editing the `BROWSER` variable in the `Makefile`). You can also open the
[`docs/html/index.html`](./docs/html/index.html) document manually.

If you have `doxygen` installed, you can also run `make docs` to re-build the manual,
if you so wish.