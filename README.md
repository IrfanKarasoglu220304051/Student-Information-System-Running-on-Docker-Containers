# Student Information System

Docker + C++ + PostgreSQL based system.

## Branching
- main: stable
- develop: development
- feature/*: features

## Team
- İrfan Karaşoğlu: Project Manager
- Veysel Özaslan: Docker & DevOps
- Berkay Erdoğan: C++ Developer

## Veritabanı Kurulumu (Database Initialization)

### Ön Gereksinimler
- Docker ve Docker Compose yüklü olmalı
- PostgreSQL container'ı çalışıyor olmalı

### Adımlar

1. **Docker Container'ları Başlat:**
   ```bash
   docker-compose up -d
   ```

2. **PostgreSQL Container'ına Bağlan:**
   ```bash
   docker exec -it postgres_db psql -U postgres
   ```

3. **Veritabanını Oluştur (eğer yoksa):**
   ```sql
   CREATE DATABASE studentdb;
   \c studentdb
   ```

4. **Schema'yı Yükle:**
   ```bash
   # Container içinden
   docker exec -i postgres_db psql -U postgres -d studentdb < schema.sql
   
   # VEYA container içinde psql kullanarak
   docker exec -it postgres_db psql -U postgres -d studentdb
   ```
   Sonra `schema.sql` dosyasının içeriğini kopyalayıp yapıştırın.

5. **Ortam Değişkenlerini Ayarla:**
   Uygulama aşağıdaki environment variable'ları kullanır:
   - `DB_HOST`: Veritabanı host adresi (varsayılan: "db")
   - `DB_PORT`: Veritabanı portu (varsayılan: "5432")
   - `DB_NAME`: Veritabanı adı (varsayılan: "studentdb")
   - `DB_USER`: Kullanıcı adı (varsayılan: "postgres")
   - `DB_PASSWORD`: Şifre (varsayılan: "example")

   Docker Compose ile çalışırken bu değişkenler `docker-compose.yml` içinde tanımlanabilir.

### Schema Yapısı

- **students**: Öğrenci bilgileri (id, student_number, first_name, last_name, email)
- **courses**: Ders bilgileri (id, course_code, course_name, credits)
- **enrollments**: Öğrenci-ders kayıtları ve notlar (student_id, course_id, grade)

Detaylı şema tanımı için `schema.sql` dosyasına bakın.

## Kullanım

Uygulama çalıştırıldığında interaktif bir menü sunar:
- 1) Yeni Öğrenci Ekle
- 2) Öğrenci Listele
- 3) Öğrenci Ara (ID ile)
- 4) Öğrenci Ara (Numara ile)
- 5) Öğrenci Sil
- 6) Not Güncelle
- 7) GPA Hesapla
- 0) Çıkış