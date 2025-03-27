## Abstract

Sort keys of unordered map

Templated library algorithm for different STL containers tests as an example 
of C++ metaprograming for students practice.

## Copyright

LCC Svyazcom 2025

## Author

Aleksey.Ozhigov <burnes@svyazcom.ru>

## Version

0.1.4

## Change log

[CHANGELOG](CHANGELOG.md)

## Build

    docker build --tag practice_sort_keys:latest --network host --progress=plain .

## Test coverage

Run docker container to see coverage

    docker run -d --rm --name practice_sort_keys --publish 8081:80 practice_sort_keys

Open in a browser [Coverage](http://localhost:8081)

## Code style check

For style check used clang-format-19. 
Format described in style_format.txt, based on [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

    clang-format-19 --style="file:style_format.txt" source


## TODO

* [ ] Benchmark memory class instead of defines