cmake_minimum_required(VERSION 3.16)
project(Telecom LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql)

qt_standard_project_setup()

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