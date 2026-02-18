# Default build type (override: just build type=Release)

type := "Debug"
builddir := "build"

# Number of cores

jobs := `nproc`

default: run

# ---------------------------------------------------------

configure:
    cmake -S . -B {{ builddir }} -DCMAKE_BUILD_TYPE={{ type }} -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build: configure
    cmake --build {{ builddir }} --parallel {{ jobs }}

rebuild:
    rm -rf {{ builddir }}
    just build type={{ type }}

run: build
    ./{{ builddir }}/oxidec -v examples/main.ox

install: build
    cmake --install {{ builddir }}

clean:
    cmake --build {{ builddir }} --target clean 2>/dev/null || true

distclean:
    rm -rf {{ builddir }}

release:
    just build type=Release

debug:
    just build type=Debug

verbose: configure
    cmake --build {{ builddir }} --verbose
