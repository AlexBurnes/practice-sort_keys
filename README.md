# 🧩 Student Practice: Sorting Keys of an Unordered Map Using Different Container Libraries in C++

**Sort keys of an unordered map using different STL containers in C++**

A lightweight C++ metaprogramming example that demonstrates sorting keys from an `unordered_map` using various standard containers.
Intended for student practice in templates, algorithms, and modern C++ development.

## 🚀 Quick Start

Clone the repository and initialize submodules:
```sh
git clone https://github.com/AlexBurnes/practice-sort_keys.git
cd practice-sort_keys
git submodule update --init
````

### 🐳 Build with Docker

```sh
docker build -t practice_sort_keys .
```

### 🧪 Run Coverage Report

```sh
docker run -d -p 8081:80 practice_sort_keys
```

Then open [http://localhost:8081](http://localhost:8081)

## 📘 About

* Author: **Aleksey Ozhigov** ([AlexBurnes@gmail.com](mailto:AlexBurnes@gmail.com))
* License: [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0)
* Version: **0.2.0**

## 🕓 Change Log

For detailed change history, see [CHANGELOG](CHANGELOG.md).

---
For full build, test, and CI setup details, see the sections below.

## 🏗️ Build

Initialize submodules:

```sh
git submodule init
git submodule update
````

### 🐳 Build in Docker container

```sh
docker build --tag practice_sort_keys:latest --network host --progress=plain .
```

### 💻 Local build (requires `buildfab` utility)

```sh
wget -O - "https://github.com/AlexBurnes/buildfab/releases/latest/download/buildfab-linux-amd64-install.sh" | INSTALL_DIR=./build sh
build/buildfab pre-install
build/buildfab build
build/buildfab check
```

## 🧪 Test Coverage

To view test coverage, run the Docker container:

```sh
docker run -d --rm --name practice_sort_keys --publish 8081:80 practice_sort_keys
```

Then open your browser at [http://localhost:8081](http://localhost:8081).

## 🧹 Code Style Check

Code formatting is verified using `clang-format-19`.
The formatting rules are defined in `style_format.txt`, based on the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

```sh
clang-format-19 --style="file:style_format.txt" source
```

## 🔍 SAST Tools

* [PVS-Studio](https://pvs-studio.com/en/pvs-studio/?utm_source=website&utm_medium=github&utm_campaign=open_source) — Static analyzer for C, C++, C#, and Java code.
* [Cppcheck](https://www.cppcheck.com)

Run SAST tools using `buildfab`:

```sh
build/buildfab pvs-studio-check
build/buildfab cpp-check
```

## 🧰 Development Workflow

To keep the project clean and ensure it passes CI checks, set up the **pre-push** utility as a Git pre-push hook.
This utility is installed along with other build tools via `buildfab`.
Both utilities — `buildfab` and `pre-push` — run the project configuration stage 'pre-push'.
`pre-push` installed as git push hook run it before each push.

### ⚙️ Set up Git hook

```sh
build/pre-push install
```

### 🪶 Automatic Checks on Push

Each time you push changes to a remote repository, `pre-push` will automatically run checks:

```sh
git push origin ...
```

To skip these checks (e.g., for intermediate commits), use the `--no-verify` option:

```sh
git push origin --no-verify ...
```

You can also run the pre-push stage manually:

```sh
build/buildfab pre-push -vv
```

## 📜 License

This project is distributed under the [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0).
See [LICENSE](https://github.com/AlexBurnes/practice-sort_keys/blob/master/LICENSE) for more information.

## 🧭 TODO

* [ ] Implement a benchmark memory class instead of using defines.
