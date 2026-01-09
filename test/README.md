# Test Planı ve Dokümantasyonu

Bu klasör, Student Information System projesi için test planlarını içerir.

## Dosyalar

1. **unit_tests_plan.cpp** - Birim testler (Unit Tests) planı
2. **integration_tests_plan.cpp** - Entegrasyon testleri (Integration Tests) planı
3. **test_coverage_plan.cpp** - Test kapsamı (Test Coverage) planı
4. **memory_leak_check_plan.cpp** - Bellek sızıntısı kontrolü (Memory Leak Checking) planı

## Test Kategorileri

### 1. Birim Testler (Unit Tests)
- Uygulamanın en küçük parçalarının (fonksiyonlar, metodlar) test edilmesi
- Student sınıfı testleri
- DatabaseManager sınıfı testleri
- Hata durumları testleri
- Sınır değer testleri

### 2. Entegrasyon Testleri (Integration Tests)
- C++ uygulamasının PostgreSQL veritabanı ile uyum içinde çalışması
- Veritabanı bağlantı testleri
- CRUD işlemleri testleri
- Transaction ve veri bütünlüğü testleri
- Performans testleri

### 3. Test Kapsamı (Test Coverage)
- Kodun ne kadarının test edildiğini gösteren rapor
- Satır kapsamı (Line Coverage)
- Fonksiyon kapsamı (Function Coverage)
- Dal kapsamı (Branch Coverage)
- Koşul kapsamı (Condition Coverage)

### 4. Bellek Sızıntısı Kontrolü (Memory Leak Checking)
- C++ uygulamasında bellek yönetimi hatalarının denetlenmesi
- Valgrind kullanımı
- AddressSanitizer kullanımı
- LeakSanitizer kullanımı

## Test Framework

- **GoogleTest (GTest)**: Birim ve entegrasyon testleri için
- **Valgrind**: Bellek sızıntısı kontrolü için
- **gcov/lcov**: Test kapsamı raporu için
- **AddressSanitizer**: Hızlı bellek kontrolü için

## Test Çalıştırma

### Birim Testler
```bash
cd build
cmake ..
make
./UnitTests
```

### Entegrasyon Testleri
```bash
# Önce Docker container'ları başlat
docker compose up -d

# Testleri çalıştır
cd build
cmake ..
make
./IntegrationTests
```

### Test Kapsamı Raporu
```bash
cd build
cmake -DCMAKE_BUILD_TYPE=Coverage ..
make
./UnitTests
gcovr --root . --html --html-details -o coverage_report.html
```

### Bellek Sızıntısı Kontrolü
```bash
# Valgrind ile
valgrind --leak-check=full ./UnitTests

# AddressSanitizer ile
g++ -fsanitize=address -g -O1 -o tests tests.cpp
./tests
```

## Test Hedefleri

- **Birim Test Kapsamı**: %85+
- **Entegrasyon Test Kapsamı**: Tüm CRUD işlemleri
- **Bellek Sızıntısı**: 0 bytes
- **Test Başarı Oranı**: %100

## Notlar

- Tüm test dosyaları yorum satırları içerir
- Test implementasyonu için örnek kodlar mevcuttur
- Her test kategorisi için detaylı açıklamalar bulunmaktadır

