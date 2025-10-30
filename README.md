# Student Practice: Sort Keys of Unordered Map Using Different Containers Libraries in C++

**Sort keys of unordered map**

A templated library algorithm for testing different STL containers tests as an example of C++ metaprograming for student practice.

## Author

Aleksey.Ozhigov <AlexBurnes@gmail.com>

## Version

0.2.0

## Change log

For detail history changes, see [CHANGELOG](CHANGELOG.md)

## Build

```sh
git submodule init
git submodule update
```

Build in docker container:
```
  docker build --tag practice_sort_keys:latest --network host --progress=plain .
```

Build localhost require install buildfab uitility
```
wget -O - "https://github.com/AlexBurnes/version-go/releases/latest/download/version-linux-amd64-install.sh" | INSTALL_DIR=./build sh
build/buildfab pre-install
build/buildfab build
build/buildfab check
```

## Test Coverage

To view test coverage, run a Docker container:

```sh
docker run -d --rm --name practice_sort_keys --publish 8081:80 practice_sort_keys
```

Then open your browser at [Coverage](http://localhost:8081)

## Code Style Check

For checking code style formatting the clang-format-19 utility is used.
The format is defined in style_format.txt, which is based on [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)

```sh
clang-format-19 --style="file:style_format.txt" source
```

## SAST Tools

* [PVS-Studio](https://pvs-studio.com/en/pvs-studio/?utm_source=website&utm_medium=github&utm_campaign=open_source) - static analyzer for C, C++, C#, and Java code.
* [Cppcheck](https://www.cppcheck.com)

## License

This work is distributed under the [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0), see [LICENSE](https://github.com:AlexBurnes/practice-sort_keys/blob/master/LICENSE) for more information.

## TODO

* [ ] Benchmark memory class instead of defines
