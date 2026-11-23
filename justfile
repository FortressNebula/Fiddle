setup:
    cmake -S . -B build

build:
    cmake --build build

run:
    ./build/Fiddle

[default]
dev: build run