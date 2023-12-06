# test-task-for-horizont-2023
This is test task for R&amp;D Center Horizont completed in December 2023

## Dependencies
- clang
- cmake
- make [debug build]
- ninja [release build]

## Installing dependencies for Arch Linux
    sudo pacman -S clang cmake make ninja
  
## Clone
    git clone --recurse-submodules https://github.com/HIebyShek/test-task-for-horizont-2023.git test-task-cpp-dev-hleb-yakavinich
    cd test-task-cpp-dev-hleb-yakavinich
    
## Build
    cmake --preset release
    cmake --build --preset release

## Run tests
    ./build/release/tests

## Run
    ./build/release/main [word for deleting] [path to input file] [path to output file]
    
