cmake_minimum_required(VERSION 3.10)

# Proje Adı ve Versiyonu
project(OgrenciBilgiSistemi VERSION 1.0 LANGUAGES CXX)

# C++ Standartı (Modern C++ özellikleri için 17 idealdir)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Bağımlılıkları Bul (libpqxx ve PostgreSQL - Opsiyonel)
# Not: Docker imajında bu paketlerin yüklü olması gerekir.
find_package(PostgreSQL QUIET)
find_package(libpqxx QUIET)

# Header dosyalarının yerini belirt (include/ klasörü)
include_directories(include)

# Uygulama Kaynak Dosyaları
set(SOURCES
    src/main.cpp
    src/DatabaseManager.cpp
)

# Çalıştırılabilir Dosyayı Oluştur (Executable)
add_executable(OBS_App ${SOURCES})

# Kütüphaneleri Projeye Bağla (Linkle - Opsiyonel)
if(PostgreSQL_FOUND AND libpqxx_FOUND)
    target_link_libraries(OBS_App PRIVATE pqxx::pqxx PostgreSQL::PostgreSQL)
endif()

# --- TEST BÖLÜMÜ (Görev Dökümanındaki Unit Test Gereksinimi İçin) ---
enable_testing()

# GoogleTest paketini bul (Eğer yüklüyse)
find_package(GTest QUIET)
if(GTest_FOUND)
    # Unit Tests - Student testleri
    add_executable(UnitTests_Student test/test_student.cpp)
    target_link_libraries(UnitTests_Student PRIVATE GTest::GTest GTest::Main)
    add_test(NAME StudentTests COMMAND UnitTests_Student)
    
    # Integration Tests - DatabaseManager testleri
    add_executable(UnitTests_Database test/test_database.cpp src/DatabaseManager.cpp)
    target_link_libraries(UnitTests_Database PRIVATE GTest::GTest GTest::Main)
    add_test(NAME DatabaseTests COMMAND UnitTests_Database)
    
    # Tüm testleri çalıştırmak için
    add_custom_target(run_all_tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS UnitTests_Student UnitTests_Database
        COMMENT "Running all tests"
    )
endif()