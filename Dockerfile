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

RUN apt-get update && \
    apt-get -y install \
    git make cmake ninja-build \
    gcc-12 g++-12 libstdc++-12-dev \
    clang-19 clang-tools-19 clang-format-19 \
    autoconf automake libtool binutils \
    libdigest-sha-perl libipc-run-perl \
    google-perftools glibc-source libgoogle-perftools-dev \
    cppcheck libev-dev libpcre3-dev \
    gettext flex \
    python3 python3-pip \
    lcov wget unzip

RUN pip3 install conan --break-system-packages && \
    mkdir build && \
    cd build && \
    conan profile detect --force 

#RUN cp ~/.conan2/profiles/default ~/.conan2/profiles/debug && sed -i -e 's/Release/Debug/g' ~/.conan2/profiles/debug

RUN apt-get -y install \
    valgrind

WORKDIR build
COPY . . 

RUN bash update-alternatives-clang.sh 19 19

RUN scripts/cpp-check install
RUN scripts/cpp-check 
RUN scripts/style-check
RUN scripts/build
RUN ctest --test-dir .build -T Test -T Coverage -V
RUN scripts/mem-check bin/test_sort_keys
RUN bin/test_bench --benchmark_counters_tabular=true

RUN lcov --directory .build --capture --output-file coverage.info
RUN lcov --extract coverage.info '*src/*' -o coverage.info
RUN genhtml --demangle-cpp -o coverage coverage.info

################################################################################

FROM debian:12.7-slim as runtime

LABEL org.opencontainers.image.author="Aleksey.Ozhigov<AlexBurnes@gmail.com>"
LABEL org.opencontainers.image.source="github.com:AlexBurnes/practice_sort_keys.git"

RUN apt-get update && \
    apt-get install -y libgoogle-perftools4 nginx

COPY --from=builder /build/bin/* /usr/local/bin/*
COPY --from=builder /build/coverage /var/www/html

EXPOSE 80/tcp

CMD ["/usr/sbin/nginx", "-g", "daemon off;"]

