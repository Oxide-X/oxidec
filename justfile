build:
    cmake --build build

generate-build:
    cmake -B build -S .

clean:
    rm -rf ./build/*
