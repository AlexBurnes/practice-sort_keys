FROM debian:12.7 as builder


ENV DEBIAN_FRONTEND=noninteractive \
    CONAN_PATH=.conan2 

RUN apt-get update && \
    apt-get -y install \
    git gcc-12 g++-12 clang-format make cmake ninja-build \
    autoconf automake libtool binutils \
    libstdc++-12-dev \
    libdigest-sha-perl libipc-run-perl \
    google-perftools glibc-source libgoogle-perftools-dev \
    cppcheck libev-dev libpcre3-dev \
    gettext flex \
    python3 python3-pip \
    lcov

RUN pip3 install conan --break-system-packages && \
    mkdir build && \
    cd build && \
    conan profile detect --force 

RUN cp ~/.conan2/profiles/default ~/.conan2/profiles/debug && sed -i -e 's/Release/Debug/g' ~/.conan2/profiles/debug

RUN apt-get -y install \
    valgrind

WORKDIR build
COPY . . 

RUN scripts/cpp-check
RUN scripts/style-check
RUN conan install . -of .build -pr debug --build missing
RUN cmake -H. -B.build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
RUN cmake --build .build
RUN cmake --install .build
RUN ctest --test-dir .build -T Test -V
RUN ctest --test-dir .build -T Coverage
RUN scripts/mem-check bin/test_sort_keys

RUN cd .build/src/test/CMakeFiles/test_sort_keys.dir && \
    lcov --directory . --capture --output-file coverage.info && \
    genhtml --demangle-cpp -o coverage coverage.info

################################################################################

FROM debian:12.7-slim as runtime

################################################################################

FROM debian:12.7-slim as runtime

LABEL org.opencontainers.image.vendor="LCC Svyazcom"
LABEL org.opencontainers.image.author="Aleksey.Ozhigov<burnes@svyazcom.ru>"
LABEL org.opencontainers.image.source="github.com:AlexBurnes/practice_sort_keys.git"

RUN apt-get update && \
    apt-get install -y libgoogle-perftools4 nginx

COPY --from=builder /build/bin/* /usr/local/bin/*
COPY --from=builder /build/.build/src/test/CMakeFiles/test_sort_keys.dir/coverage /var/www/html

EXPOSE 80/tcp

CMD ["/usr/sbin/nginx", "-g", "daemon off;"]

