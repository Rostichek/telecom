# Telecom

Telecom is a desktop application that provides a directory of mobile network operators, organized by country.

## Requirements

To build the project from source, you need a development environment that includes:

- C++ Compiler with C++20 support
- Qt SDK: version 6.9 with Core, Gui, Widgets and Sql modules
- Git LFS

## Getting started

### Get and initialize the repository

    git clone <repository-url>
    cd Telecom
    git lfs install
    git lfs pull
    
### Build

#### Directly with CMake

    mkdir build
    cd build
    cmake ..
    cmake --build .

#### , or in Qt Creator

1. Open CMakeLists.txt as a project.
2. Select your Qt 6.9 kit.
3. Press Build or Run.