set(TEST_SOURCES testsTP1.cpp ${PROJECT_SOURCE_DIR}/Regle.cpp ${PROJECT_SOURCE_DIR}/SystemeExpert.cpp)

add_executable(
        testsTP1
        ${TEST_SOURCES}
)

target_include_directories(testsTP1 PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
        testsTP1
        gtest_main
        gtest
        pthread
)

include(GoogleTest)

gtest_discover_tests(testsTP1)