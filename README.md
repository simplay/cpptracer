[![Build Status](https://travis-ci.org/simplay/cpptracer.svg?branch=master)](https://travis-ci.org/simplay/cpptracer)
[![Coverage Status](https://coveralls.io/repos/github/simplay/cpptracer/badge.svg?branch=master)](https://coveralls.io/github/simplay/cpptracer?branch=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/a0ebe0868c5e426a8dc723bfbfe1531a)](https://app.codacy.com/app/simplay/cpptracer?utm_source=github.com&utm_medium=referral&utm_content=simplay/cpptracer&utm_campaign=Badge_Grade_Dashboard)

# C++ Raytracer

![alt tag](https://github.com/simplay/cpptracer/blob/master/examples/blinn.bmp)

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
