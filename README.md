[![Build Status](https://travis-ci.org/simplay/cpptracer.svg?branch=master)](https://travis-ci.org/simplay/cpptracer)
[![Coverage Status](https://coveralls.io/repos/github/simplay/cpptracer/badge.svg?branch=master)](https://coveralls.io/github/simplay/cpptracer?branch=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/a0ebe0868c5e426a8dc723bfbfe1531a)](https://app.codacy.com/app/simplay/cpptracer?utm_source=github.com&utm_medium=referral&utm_content=simplay/cpptracer&utm_campaign=Badge_Grade_Dashboard)

# C++ Raytracer

![alt tag](https://github.com/simplay/cpptracer/blob/master/examples/blinn.bmp)

## Features

+ Recursive raytracing (Whitted Integrator)
+ Can render [Constructive solid geometries](http://en.wikipedia.org/wiki/Constructive_solid_geometry)
+ Can process triangle meshes through the [.obj](https://en.wikipedia.org/wiki/Wavefront_.obj_file) format
+ Multithreaded
+ Supports reflective and refractive materials

## Dependencies

+ `cmake >= 3.1.3`
+ `gcc`

## Setup

1. Clone this repository: `$ git@github.com:simplay/cpptracer.git`
2. Fetch and update all external dependencies: `$ git submodule update --init --recursive`

## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target:

``` bash
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
$ make
```

## Usage

Inside `build/`, execute `./main.x`

Execute `./main --help` to see a list of all available arguments.

## Running the tests

Inside `build/`, execute `./unit_tests.x`

## Running the benchmarks

Inside `build/`, execute `./benchmarks.x`

## Contributing

1. Fork this repository
2. Create your feature branch `git checkout -b my-new-feature`
3. Commit your changes `git commit -am "Add some feature"`
4. Push to the branch `git push origin my-new-feature`
5. Create new Pull Request (in your forked repository)

## References

+ Boilerplate taken from: https://github.com/bsamseth/cpp-project
+ Explosion Rendering was inspired by the work of: https://github.com/ssloy/tinykaboom/wiki
