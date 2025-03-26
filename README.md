## Abstract

Sort keys of unordered map

Templated library algorithm for different STL containers tests as an example 
of C++ metaprograming for students practice.

## Copyright

LCC Svyazcom 2025

## Author

Aleksey.Ozhigov <burnes@svyazcom.ru>

## Version

0.1.3

## Change log

- 0.1.0 initial version
- 0.1.1 CI github actions
- 0.1.2 library containers 
- 0.1.3 memory benchmark

## Build

    docker build --tag practice_sort_keys:latest --network host --progress=plain .

## Test coverage

Run docker container to see coverage

    docker run -d --rm --name practice_sort_keys --publish 8081:80 practice_sort_keys

Open in a browser [Coverage](http://localhost:8081)


## TODO

* [%] CI cppcheck trouble