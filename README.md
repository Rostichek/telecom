# Telecom

Telecom is a desktop application that provides a directory of mobile network operators, organized by country.

## Usage example

![image](https://drive.google.com/uc?export=view&id=128BcW11-fn3D2LKsYS5iGRGJ_mwaR3Ax)

## Requirements

To build the project from source, you need a development environment that includes:

- C++ Compiler with C++20 support
- Qt SDK: Qt6 with Core, Gui, Widgets and Sql modules (verified with Qt 6.9)
- Git LFS

## Getting started

### Get and initialize the repository

    git clone <repository-url>
    cd Telecom
    git lfs install
    git lfs pull
    
### Build

#### Directly with CMake

Open your **Terminal**

    mkdir build
    cd build 
    cmake .. -DCMAKE_PREFIX_PATH="your_qt_dir"
    cmake --build . --config Release

Open your **Qt Command Prompt**

    windeployqt --release Release/TelecomApp.exe

#### , or in Qt Creator

1. Open CMakeLists.txt as a project.
2. Select your Qt6 kit.
3. Press Build or Run.