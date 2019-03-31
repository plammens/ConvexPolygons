> **Note:** this Markdown document contains math blocks intended to be parsed 
> with MathJax. To properly view this document, you can either
> use a Markdown viewer like [Typora](https://www.typora.io), or view
> the [exported `html` document](README.html) in this repository. 


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

Start by reading the [features and usage](#Features and usage) section, and then move on to the
[setup and execution](#Setup, testing and execution) section when you're ready!


# Features and usage

The calculator works in a command-line environment. Each line from
`stdin` is interpreted as a single command. Commands follow the classical
`<keyword> [arguments]` structure.

Below you'll find a list of all available commands.


## Commands

### Polygon / ID management

 -  `polygon`

The `polygon` command associates an identifier with a convex polygon made by a
set of zero or more points. If the polygon identifier is new, it will create
it. If it already existed, it will overwrite the previous polygon. New
polygons are black.

 - `delete`

Deletes the polygon with the given identifier (i,e., frees the identifier).


 - `list`

Prints a list of currently defined identifiers, in lexicographical order.

### Polygon-printing commands


 - `print`

The `print` command prints the name and the vertices of a given
polygon. The output contains the vertices in the convex hull of the
polygon, in clockwise order, starting from the vertex will lowest `x` coordinate 
(and the lowest `y` in case of ties). The output is printed in a single line,
with space separated coordinartes.


 - `pretty-print`

 Like `print`, but with slightly nicer format.

### Polygon info commands

- `area`

The `area` command prints the area of the given polygon.

 - `perimeter`

The `perimeter` command prints the perimeter of the given polygon.


 - `vertices`

The `vertices` command prints the number of vertices of the convex hull of the
given polygon.


 - `centroid`

The `centroid` command prints the centroid of the given polygon.

### IO commands


 - `save`

The `save` command saves the given polygons in a file, overwriting it if it
already existed. The format is the same as for `print`.


 -  `load`

The `load` command loads the polygons stored in a file, in the same way as
`polygon`, but retrieving the vertexes and identifiers from the specified file.

### Drawing commands


 - `setcol`

The `setcol` command associates a color to the given polygon.


 - `draw` 

The `draw` command draws a list of polygons in a PNG file, each one with its
associated color. The polygons are scaled to fit nicely in the image.

- `paint`:


 - `intersection`

This command may receive two or three parameters:

- When receiving two parameters `p1`and `p2`, `p1`should be updated to the
- intersection of the original `p1` and `p2`.

- When receiving three parameters `p1`, `p2` and `p3`, `p1`should be updated
- to the intersection of `p2` and `p3`.

Take into account that identifiers may be repeated.


 -  `union`

Just as the `intersection` command, but with the convex union of polygons.


 - `inside`

Given two polygons, the `inside` command prints `yes` or `not` to tell whether
the first is inside the second or not.


 -  `bbox` command

The `bbox` command creates a new polygon with the four vertices corresponding to the
bounding box of the given polygons.


### Commands without answer

As seen in the examples, some commands do not really produce an answer. In
this case `ok` must be printed, unless there was some error.




# Setup, testing and execution instructions

## Build

This project needs `GNU Coreutils` (i.e. the `UNIX`-style commands such as `find`, `rm`, etc.) , 
`GNU make`, and `cmake` (if building the libraries from scratch). So if you're running Linux or
Mac, you probably won't need to install anything. If you're running Windows, installing [`Cygwin`](https://www.cygwin.com) 
with the aforementioned packages should be enough.

No external dependencies need to be installed separately; they come bundled with the project.
To build everything (libraries, main program and test), run the following command.

```bash
make all  # (or just `make`)
```

This should do three things: build the `pngwriter` library from source and install it locally
into `./libs/` (where `./` is the project root), build the main executable, and build the tests.

If for some reason (such as not having `cmake` installed) the installation of `pngwriter` fails, 
you can remove the `libs` prerequisite from the `all` rule in the `Makefile` and proceed to
[installing `pngwriter` manually](<https://github.com/jordi-petit/ap2-imatges>). Don't forget to set the `USER_LIB_DIR` variable in the `Makefile`
to whatever your installation path is. (It should be the path where the `libPNGwriter.a` file is
located.)

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


# Project structure

The most important directories in the project root are:

- `include`: contains all of the project's header files
  - `class`: contains header files dedicated to a single class
  - `details`: contains header files that are intended
    for internal use only.
- `src`: contains all of the main source files
- `libs`: contains all library files (external dependencies)
- `test`: contains test files (test sources, generators, generated tests, etc. )

Other directories that are made on-the-run:

- `build`: directory that stores all build output files, generated
  automatically when building the project (e.g., by running `make all`)
  - `bin`: contains binary files, e.g. `main.x`. It is the output
    directory of the linking stage.
  - `obj`: compiled object files
  - `depend`: auto-generated dependency information files
- `out`: the (optional) output directory. The program will prefix all
  output files it produces with this path. Also, when loading files,
  the program will look for them here. Have a look [here](#Changing the output directory) for customizing
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

## Error handling


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