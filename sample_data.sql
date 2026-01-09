-- Örnek Veri Ekleme Scripti
-- Bu dosyayı veritabanına uygulamak için:
-- docker exec -i <container_name> psql -U student -d studentdb < sample_data.sql

-- ============================================================================
-- 1. ÖĞRENCİLER (STUDENTS)
-- ============================================================================

INSERT INTO students (student_number, first_name, last_name, email, department) VALUES
('2021001', 'Ahmet', 'Yılmaz', 'ahmet.yilmaz@university.edu', 'Bilgisayar Mühendisliği'),
('2021002', 'Ayşe', 'Demir', 'ayse.demir@university.edu', 'Elektrik Mühendisliği'),
('2021003', 'Mehmet', 'Kaya', 'mehmet.kaya@university.edu', 'Makine Mühendisliği'),
('2021004', 'Fatma', 'Şahin', 'fatma.sahin@university.edu', 'Endüstri Mühendisliği'),
('2021005', 'Ali', 'Çelik', 'ali.celik@university.edu', 'Bilgisayar Mühendisliği'),
('2021006', 'Zeynep', 'Arslan', 'zeynep.arslan@university.edu', 'Yazılım Mühendisliği'),
('2021007', 'Can', 'Öztürk', 'can.ozturk@university.edu', 'Bilgisayar Mühendisliği'),
('2021008', 'Elif', 'Koç', 'elif.koc@university.edu', 'Elektrik Mühendisliği')
ON CONFLICT (student_number) DO NOTHING;

-- ============================================================================
-- 2. DERSLER (COURSES)
-- ============================================================================

INSERT INTO courses (course_code, course_name, credits) VALUES
('CS101', 'Programlamaya Giriş', 4),
('CS201', 'Veri Yapıları', 4),
('CS301', 'Algoritma Analizi', 3),
('MATH101', 'Matematik I', 4),
('MATH201', 'Matematik II', 4),
('PHYS101', 'Fizik I', 3),
('ENG101', 'İngilizce I', 2),
('CS401', 'Veritabanı Sistemleri', 3),
('CS402', 'Yazılım Mühendisliği', 3),
('CS403', 'Web Programlama', 3)
ON CONFLICT (course_code) DO NOTHING;

-- ============================================================================
-- 3. KAYITLAR VE NOTLAR (ENROLLMENTS)
-- ============================================================================

-- Ahmet Yılmaz (2021001) - Bilgisayar Mühendisliği öğrencisi
INSERT INTO enrollments (student_id, course_id, grade) VALUES
((SELECT id FROM students WHERE student_number = '2021001'), (SELECT id FROM courses WHERE course_code = 'CS101'), 85.5),
((SELECT id FROM students WHERE student_number = '2021001'), (SELECT id FROM courses WHERE course_code = 'CS201'), 92.0),
((SELECT id FROM students WHERE student_number = '2021001'), (SELECT id FROM courses WHERE course_code = 'MATH101'), 78.5),
((SELECT id FROM students WHERE student_number = '2021001'), (SELECT id FROM courses WHERE course_code = 'CS401'), 88.0)
ON CONFLICT (student_id, course_id) DO UPDATE SET grade = EXCLUDED.grade;

-- Ayşe Demir (2021002) - Elektrik Mühendisliği öğrencisi
INSERT INTO enrollments (student_id, course_id, grade) VALUES
((SELECT id FROM students WHERE student_number = '2021002'), (SELECT id FROM courses WHERE course_code = 'MATH101'), 95.0),
((SELECT id FROM students WHERE student_number = '2021002'), (SELECT id FROM courses WHERE course_code = 'MATH201'), 90.5),
((SELECT id FROM students WHERE student_number = '2021002'), (SELECT id FROM courses WHERE course_code = 'PHYS101'), 87.0),
((SELECT id FROM students WHERE student_number = '2021002'), (SELECT id FROM courses WHERE course_code = 'ENG101'), 92.5)
ON CONFLICT (student_id, course_id) DO UPDATE SET grade = EXCLUDED.grade;

-- Mehmet Kaya (2021003) - Makine Mühendisliği öğrencisi
INSERT INTO enrollments (student_id, course_id, grade) VALUES
((SELECT id FROM students WHERE student_number = '2021003'), (SELECT id FROM courses WHERE course_code = 'MATH101'), 82.0),
((SELECT id FROM students WHERE student_number = '2021003'), (SELECT id FROM courses WHERE course_code = 'PHYS101'), 75.5),
((SELECT id FROM students WHERE student_number = '2021003'), (SELECT id FROM courses WHERE course_code = 'ENG101'), 88.0)
ON CONFLICT (student_id, course_id) DO UPDATE SET grade = EXCLUDED.grade;

-- Fatma Şahin (2021004) - Endüstri Mühendisliği öğrencisi
INSERT INTO enrollments (student_id, course_id, grade) VALUES
((SELECT id FROM students WHERE student_number = '2021004'), (SELECT id FROM courses WHERE course_code = 'MATH101'), 91.0),
((SELECT id FROM students WHERE student_number = '2021004'), (SELECT id FROM courses WHERE course_code = 'MATH201'), 89.5),
((SELECT id FROM students WHERE student_number = '2021004'), (SELECT id FROM courses WHERE course_code = 'ENG101'), 94.0)
ON CONFLICT (student_id, course_id) DO UPDATE SET grade = EXCLUDED.grade;

-- Ali Çelik (2021005) - Bilgisayar Mühendisliği öğrencisi
INSERT INTO enrollments (student_id, course_id, grade) VALUES
((SELECT id FROM students WHERE student_number = '2021005'), (SELECT id FROM courses WHERE course_code = 'CS101'), 88.5),
((SELECT id FROM students WHERE student_number = '2021005'), (SELECT id FROM courses WHERE course_code = 'CS201'), 85.0),
((SELECT id FROM students WHERE student_number = '2021005'), (SELECT id FROM courses WHERE course_code = 'CS301'), 90.0),
((SELECT id FROM students WHERE student_number = '2021005'), (SELECT id FROM courses WHERE course_code = 'CS401'), 87.5),
((SELECT id FROM students WHERE student_number = '2021005'), (SELECT id FROM courses WHERE course_code = 'CS402'), 92.0)
ON CONFLICT (student_id, course_id) DO UPDATE SET grade = EXCLUDED.grade;

-- Zeynep Arslan (2021006) - Yazılım Mühendisliği öğrencisi
INSERT INTO enrollments (student_id, course_id, grade) VALUES
((SELECT id FROM students WHERE student_number = '2021006'), (SELECT id FROM courses WHERE course_code = 'CS101'), 96.0),
((SELECT id FROM students WHERE student_number = '2021006'), (SELECT id FROM courses WHERE course_code = 'CS201'), 94.5),
((SELECT id FROM students WHERE student_number = '2021006'), (SELECT id FROM courses WHERE course_code = 'CS301'), 93.0),
((SELECT id FROM students WHERE student_number = '2021006'), (SELECT id FROM courses WHERE course_code = 'CS403'), 95.5)
ON CONFLICT (student_id, course_id) DO UPDATE SET grade = EXCLUDED.grade;

-- Can Öztürk (2021007) - Bilgisayar Mühendisliği öğrencisi
INSERT INTO enrollments (student_id, course_id, grade) VALUES
((SELECT id FROM students WHERE student_number = '2021007'), (SELECT id FROM courses WHERE course_code = 'CS101'), 79.0),
((SELECT id FROM students WHERE student_number = '2021007'), (SELECT id FROM courses WHERE course_code = 'MATH101'), 81.5)
ON CONFLICT (student_id, course_id) DO UPDATE SET grade = EXCLUDED.grade;

-- Elif Koç (2021008) - Elektrik Mühendisliği öğrencisi
INSERT INTO enrollments (student_id, course_id, grade) VALUES
((SELECT id FROM students WHERE student_number = '2021008'), (SELECT id FROM courses WHERE course_code = 'MATH101'), 88.0),
((SELECT id FROM students WHERE student_number = '2021008'), (SELECT id FROM courses WHERE course_code = 'PHYS101'), 85.5),
((SELECT id FROM students WHERE student_number = '2021008'), (SELECT id FROM courses WHERE course_code = 'ENG101'), 91.0)
ON CONFLICT (student_id, course_id) DO UPDATE SET grade = EXCLUDED.grade;

-- ============================================================================
-- VERİ KONTROLÜ
-- ============================================================================

-- Öğrenci sayısını kontrol et
SELECT 'Öğrenci Sayısı: ' || COUNT(*) FROM students;

-- Ders sayısını kontrol et
SELECT 'Ders Sayısı: ' || COUNT(*) FROM courses;

-- Kayıt sayısını kontrol et
SELECT 'Kayıt Sayısı: ' || COUNT(*) FROM enrollments;

-- Öğrenci listesi
SELECT id, student_number, first_name, last_name, email, department 
FROM students 
ORDER BY id;

-- Ders listesi
SELECT id, course_code, course_name, credits 
FROM courses 
ORDER BY course_code;

