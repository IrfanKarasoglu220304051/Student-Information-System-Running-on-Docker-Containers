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
- Docker ve Docker Compose (v1 veya v2) yüklü olmalı
- `docker-compose.yml` içindeki `db` servisi Postgres çalıştıracak şekilde yapılandırılmış olmalı

### Otomatik Uygulama (yeni kurulum / önerilen)
Bu repo `schema.sql` dosyasını `db` servisine mount edecek şekilde ayarlanmıştır; init script sadece veritabanı **ilk kez** oluşturulurken çalışır.

1. Varolan container ve volume'leri kaldır (böylece init script çalışacaktır):
   ```bash
   # Docker Compose v2
   docker compose down -v

   # Eğer sisteminizde v1 yüklüyse
   # docker-compose down -v
   ```

2. Container'ları yeniden başlatın:
   ```bash
   docker compose up -d
   # veya docker-compose up -d
   ```

> Not: `docker-entrypoint-initdb.d/schema.sql` içeriği yalnızca volume boşken çalıştırılır; eğer daha önce oluşturulmuş bir volume varsa `down -v` ile silinmelidir.

### Manuel Uygulama (mevcut veritabanı için)
Eğer volume'ü silmek istemiyorsanız veya schema'yı elle uygulamak istiyorsanız:
```bash
# Dockerfile.db'de ayarlı POSTGRES_USER/POSTGRES_DB değerlerini kontrol edin (örnek: student / studentdb)
docker exec -i postgres_db psql -U student -d studentdb < schema.sql
```

### Doğrulama
- Container loglarını kontrol edin:
  ```bash
  docker logs postgres_db --tail 200
  ```
- Veritabanındaki tabloları listeleyin:
  ```bash
  docker exec -i postgres_db psql -U student -d studentdb -c "\dt"
  ```

### Ortam Değişkenleri
- `DB_HOST` (varsayılan: `db`), `DB_PORT` (varsayılan: `5432`), `DB_NAME` (varsayılan: `studentdb`), `DB_USER`, `DB_PASSWORD`
- Ayarlar `docker-compose.yml` veya `Dockerfile.db` içinde kontrol edilebilir.

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