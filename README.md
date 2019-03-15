> **Note:** this Markdown document contains math blocks intended to be parsed 
> with MathJax. To properly view this document, you can either
> use a Markdown viewer like [Typora](https://www.typora.io), or view
> the [exported `html` document](README.html) in this repository. 

# Convex Polygon Calculator

## Project structure

The most important directories in the project root are:

- `include`: contains all project header files
- `src`: contains all source files

In each of those two directories, a `class` subdirectory
contains files (header/source, respectively) that are dedicated to a single class.

Other directories that are made on-the-run:

- `obj`: directory that stores object files produced upon compilation
(e.g. when running `make all`).

- `bin`: contains binary files, e.g. `main`. It is the output
directory of the linking stage. It is used, for instance, when
running `make all`.

- `out`: (optional) output directory. The program will prefix all
output files it produces with this path.

## Naming conventions

### Symbols

Constants are named in `ALL_CAPS_CASE`.
Non-constant variables, functions and methods are named in
`camelCase`. Classes, enums and structs are named in `PascalCase`.

### Files

Header files are given the extension `.h`. Source files are given
the extension `.cc`.

Header files dedicated to a single class reside in a `class`have the
same name as the class (which is in `PascalCase`). The source 
file implementing them also have that same name.

Other header files (and their corresponding implementation files)
are named in `camelCase`.


