## Abstract

Sort keys of unordered map

Templated library algorithm for different STL containers tests as an example 
of C++ metaprograming for students practice.

## Copyright

LCC Svyazcom 2025

## Author

Aleksey.Ozhigov <burnes@svyazcom.ru>

## Version

0.1.0

## Change log

- 0.1.0 initial version

## Build

    docker build --tag practice_sort_keys:latest --network host --progress=plain .

## Test coverage

Run docker container to see coverage

    docker run -d --rm --name practice_sort_keys --publish 8081:80 practice_sort_keys

Open in a browser [Coverage](http://localhost:8081)


## TODO

* [ ] Github CI
* [ ] Benchmark other STL containers
* [ ] Benchmakr memory usage, example https://github.com/google/benchmark/issues/1217