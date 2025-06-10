
find_package(GTest CONFIG REQUIRED)

add_executable(unitTest median_filter_tests.cpp)

#target_include_directories(unitTest PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(unitTest GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main MedianLib)