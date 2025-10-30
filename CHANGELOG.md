# How to add entry for changelog

See documetation [https://common-changelog.org/](common changelog)

## [vX.Y.Z] - YYYY-MM-DD
Short description, optionaly

### Added
- list what added

### Changed
- list what changed

### Fixed
- list what fixed

### Remove
- list what removed

### Required update
- [ ] items required to configure and change to install this version

---
# Change log

## [v0.2.0] - 2025-10-29

### Added
- buildfab .project.yml configuration

### Remove
- scripts catalog and bash scripts, all actions defined in buildfab
  project congfiguration

## [v0.1.7] - 2025-05-06

### Added
- .project files, setup environment for build script, define compiler

### Changed
- build script changed to scripts/build script

## [v0.1.6] - 2025-04-11

### Added
- sparsepp.cmake, remove sparsepp headers, download as 3thd library

## [v0.1.5] - 2025-04-03

### Added
- licence

## [v0.1.4] - 2025-03-27

### Added
- script cpp-check-install
- template sort_keys(vector, map) for simple usage function in code
- tests and bechmarks for sort_keys(vector, map)

### Changed
- github ci uncomment cpp-check and style-check

### Fixed
- cppcheck and style check require one version of tools for all platforms
- style-check use clang-format-19
- cpp-check use cppcheck 2.16.0
- docker-build generate coverage report

## [v0.1.3] - 2025-03-26

Memory benchmark

## [v0.1.2] - 2025-03-26

Library containers

## [v0.1.1] - 2025-03-26

CI github actions

## [v0.1.0] - 2025-03-25

Initial version



