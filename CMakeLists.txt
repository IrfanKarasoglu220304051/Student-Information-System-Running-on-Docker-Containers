cmake_minimum_required(VERSION 3.10)

project(OgrenciBilgiSistemi VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- libpqxx discovery (CI-safe) ---
find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

# Header files
include_directories(include)

# Sources
set(SOURCES
    src/main.cpp
    src/DatabaseManager.cpp
    src/Student.cpp
)

# Executable
add_executable(OBS_App ${SOURCES})

# Link libpqxx (REQUIRED)
target_include_directories(OBS_App PRIVATE ${PQXX_INCLUDE_DIRS})
target_link_libraries(OBS_App PRIVATE ${PQXX_LIBRARIES})

# --- TEST SECTION ---
enable_testing()

find_package(GTest QUIET)
if(GTest_FOUND)
    message(STATUS "GoogleTest found - tests enabled")

    add_executable(UnitTests_Student test/test_student.cpp)
    target_link_libraries(UnitTests_Student PRIVATE GTest::GTest)
    target_include_directories(UnitTests_Student PRIVATE ${CMAKE_SOURCE_DIR}/include)
    add_test(NAME StudentTests COMMAND UnitTests_Student)

    add_executable(UnitTests_Database test/test_database.cpp src/DatabaseManager.cpp)
    target_link_libraries(UnitTests_Database PRIVATE GTest::GTest ${PQXX_LIBRARIES})
    target_include_directories(UnitTests_Database PRIVATE ${CMAKE_SOURCE_DIR}/include)
    add_test(NAME DatabaseTests COMMAND UnitTests_Database)

    add_custom_target(run_all_tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS UnitTests_Student UnitTests_Database
        COMMENT "Running all tests"
    )
else()
    message(WARNING "GoogleTest not found - tests disabled")
endif()
