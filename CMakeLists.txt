cmake_minimum_required(VERSION 3.10)

# Proje Adı ve Versiyonu
project(OgrenciBilgiSistemi VERSION 1.0 LANGUAGES CXX)

# C++ Standardı
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# PostgreSQL
find_package(PostgreSQL REQUIRED)

# libpqxx (Portable): pkg-config ile bul
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

# include ve lib pathleri
include_directories(${LIBPQXX_INCLUDE_DIRS})
link_directories(${LIBPQXX_LIBRARY_DIRS})

# Header dosyalarının yerini belirt (include/ klasörü)
include_directories(include)

# Uygulama Kaynak Dosyaları
set(SOURCES
    src/main.cpp
    src/DatabaseManager.cpp
)

# Executable
add_executable(OBS_App ${SOURCES})

# Link
target_link_libraries(OBS_App PRIVATE ${LIBPQXX_LIBRARIES} PostgreSQL::PostgreSQL)

# --- TEST BÖLÜMÜ ---
enable_testing()

find_package(GTest QUIET)
if(GTest_FOUND)
    add_executable(UnitTests tests/test_db.cpp src/DatabaseManager.cpp)

    # UnitTests için de aynı libpqxx link
    target_link_libraries(UnitTests PRIVATE
        GTest::GTest
        GTest::Main
        ${LIBPQXX_LIBRARIES}
        PostgreSQL::PostgreSQL
    )

    add_test(NAME AllTests COMMAND UnitTests)
endif()

