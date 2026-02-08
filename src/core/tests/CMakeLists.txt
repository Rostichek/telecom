add_executable(CoreTests
    main.cpp
    assetsmanagertest.cpp
    mock/mockresources.qrc
    dbcountryloadertest.cpp
    mock/databaseworkermock.h
)

target_link_libraries(CoreTests PRIVATE
    TelecomCore
    GTest::gtest_main
    Qt6::Core
    Qt6::Test
)

include(GoogleTest)
gtest_discover_tests(CoreTests DISCOVERY_MODE PRE_TEST)