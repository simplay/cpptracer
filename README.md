[![Build Status](https://travis-ci.org/simplay/cpptracer.svg?branch=master)](https://travis-ci.org/simplay/cpptracer)
[![Coverage Status](https://coveralls.io/repos/github/simplay/cpptracer/badge.svg?branch=master)](https://coveralls.io/github/simplay/cpptracer?branch=master)

# C++ Raytracer

Boilerplate taken from: https://github.com/bsamseth/cpp-project

## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target.

Example:

``` bash
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
$ make
$ ./main.x
$ make gtest     # Makes and runs the tests.
$ make coverage  # Generate a coverage report.
$ make doc       # Generate html documentation.
```