add_library(TelecomCore STATIC
    db/databasemanager.h
    db/databasemanager.cpp
    idataloader.h
    countryloader.h
    entities.h
    dbcountryloader.h
    dbcountryloader.cpp
    assetsmanager.h
    assetsmanager.cpp
    loaderfactory.h
    db/idatabaseworker.h
    db/idatabaseworker.cpp
    db/types.h
    db/liteworker.h
    db/liteworker.cpp
)

target_include_directories(TelecomCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(TelecomCore PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Sql
    GTest::gtest
)

add_subdirectory(tests)