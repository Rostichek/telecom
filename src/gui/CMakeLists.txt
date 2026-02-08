add_library(TelecomGui STATIC
    MainWindow.cpp
    MainWindow.h
    mobileoperatorswidget.h
    mobileoperatorswidget.cpp
    mobileoperatorsmodel.h
    mobileoperatorsmodel.cpp
    mainwindow.ui
    styles/styleloader.h
    styles/styleloader.cpp
    resources.qrc
)

target_include_directories(TelecomGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(TelecomGui PUBLIC
    TelecomCore
    Qt6::Widgets
)