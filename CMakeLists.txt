cmake_minimum_required(VERSION 3.16)
project(Telecom LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql Test)

qt_standard_project_setup()

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)

qt_add_executable(TelecomApp main.cpp src/gui/resources.qrc)

target_link_libraries(TelecomApp PRIVATE
    TelecomGui
    TelecomCore
    Qt6::Core
    Qt6::Widgets
)

set(DB_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/assets/system.db")

add_custom_command(TARGET TelecomApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${DB_SOURCE}"
        "$<TARGET_FILE_DIR:TelecomApp>/system.db"
    COMMENT "Copying system.db to output directory..."
)