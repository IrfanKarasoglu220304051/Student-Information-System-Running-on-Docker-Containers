cmake_minimum_required(VERSION 3.10)

# Proje Adı ve Versiyonu
project(OgrenciBilgiSistemi VERSION 1.0 LANGUAGES CXX)

# C++ Standartı (Modern C++ özellikleri için 17 idealdir)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Bağımlılıkları Bul (libpqxx ve PostgreSQL)
# Not: Docker imajında bu paketlerin yüklü olması gerekir.
find_package(PostgreSQL REQUIRED)
find_package(libpqxx REQUIRED)

# Header dosyalarının yerini belirt (include/ klasörü)
include_directories(include)

# Uygulama Kaynak Dosyaları
set(SOURCES
    src/main.cpp
    src/DatabaseManager.cpp
)

# Çalıştırılabilir Dosyayı Oluştur (Executable)
add_executable(OBS_App ${SOURCES})

# Kütüphaneleri Projeye Bağla (Linkle)
target_link_libraries(OBS_App PRIVATE pqxx::pqxx PostgreSQL::PostgreSQL)

# --- TEST BÖLÜMÜ (Görev Dökümanındaki Unit Test Gereksinimi İçin) ---
enable_testing()

# GoogleTest paketini bul (Eğer yüklüyse)
find_package(GTest QUIET)
if(GTest_FOUND)
    add_executable(UnitTests tests/test_db.cpp src/DatabaseManager.cpp)
    target_link_libraries(UnitTests PRIVATE GTest::GTest GTest::Main pqxx::pqxx)
    add_test(NAME AllTests COMMAND UnitTests)
endif()