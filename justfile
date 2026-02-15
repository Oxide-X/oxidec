build:
    cmake --build build

enerate-build:
    cmake -B build -S .

clean:
    rm -rf ./build/*
