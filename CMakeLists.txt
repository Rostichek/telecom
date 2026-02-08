cmake_minimum_required(VERSION 3.16)
project(Telecom LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql)

add_subdirectory(src)

add_executable(TelecomApp main.cpp src/gui/resources.qrc)

target_link_libraries(TelecomApp PRIVATE
    TelecomGui
    TelecomCore
    Qt6::Core
    Qt6::Widgets
)

set(DB_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/assets/system.db")
set(DB_DEST "${CMAKE_CURRENT_BINARY_DIR}/system.db")

if(EXISTS "${DB_SOURCE}")
    configure_file("${DB_SOURCE}" "${DB_DEST}" COPYONLY)
    message(STATUS "Copied system.db to build directory")
else()
    message(WARNING "system.db not found in source dir - App will create a new empty one")
endif()