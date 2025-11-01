# Student practice C++ sort keys of unordered map on different containers libraries
# Copyright 2025 AlexBurnes@gmail.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

FROM debian:12.7 as builder

ENV DEBIAN_FRONTEND=noninteractive \
    CONAN_PATH=.conan2

RUN apt-get update && apt-get -y install wget which && apt clean

RUN wget -O - "https://github.com/AlexBurnes/buildfab/releases/latest/download/buildfab-linux-amd64-install.sh" | sh

WORKDIR build
COPY . .

# Install system build packages
RUN buildfab ci-pre-install

# Install buildfab build tools
RUN buildfab pre-install

# Install cppcheck from tarball
RUN buildfab cppcheck-install

# PVS-Studio install, uncomment if require
# RUN buildfab install-pvs-studio

# Static analyze of source code
RUN buildfab cpp-check

# Check code style
RUN buildfab style-check

# Build and test code
RUN buildfab build -vv

# PVS-Studio analyze of source code on compile commands log
# Init Free PVS-Studio License for Students and Teachers: https://pvs-studio.com/en/order/for-students/
# RUN buildfab pvs-studio-check

# Check build binary on memory leaks
RUN buildfab mem-check

# Generate coverage report
RUN lcov --directory .build --capture --output-file coverage.info
RUN lcov --extract coverage.info '*src/*' -o coverage.info
RUN genhtml --demangle-cpp -o coverage coverage.info

################################################################################

FROM debian:12.7-slim as runtime

LABEL org.opencontainers.image.author="Aleksey.Ozhigov<AlexBurnes@gmail.com>"
LABEL org.opencontainers.image.source="github.com:AlexBurnes/practice_sort_keys.git"

RUN apt-get update && \
    apt-get install -y libgoogle-perftools4 nginx && \
    apt-get clean

COPY --from=builder /build/bin/* /usr/local/bin/*
COPY --from=builder /build/coverage /var/www/html

EXPOSE 80/tcp

CMD ["/usr/sbin/nginx", "-g", "daemon off;"]

