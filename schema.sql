-- Student Information System Database Schema
-- P2: Bu dosya veritabanını initialize etmek için kullanılır

-- 1. Öğrenci Tablosu
CREATE TABLE IF NOT EXISTS students (
    id SERIAL PRIMARY KEY,
    student_number VARCHAR(15) UNIQUE NOT NULL,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    department VARCHAR(100),
    email VARCHAR(100) UNIQUE NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 2. Dersler Tablosu
CREATE TABLE IF NOT EXISTS courses (
    id SERIAL PRIMARY KEY,
    course_code VARCHAR(10) UNIQUE NOT NULL,
    course_name VARCHAR(100) NOT NULL,
    credits INT CHECK (credits > 0)
);

-- 3. Kayıt ve Notlar Tablosu (İlişki Tablosu)
CREATE TABLE IF NOT EXISTS enrollments (
    student_id INT REFERENCES students(id) ON DELETE CASCADE,
    course_id INT REFERENCES courses(id) ON DELETE CASCADE,
    grade FLOAT CHECK (grade >= 0 AND grade <= 100),
    PRIMARY KEY (student_id, course_id)
);

-- Index'ler (Performans için)
CREATE INDEX IF NOT EXISTS idx_students_student_number ON students(student_number);
CREATE INDEX IF NOT EXISTS idx_students_email ON students(email);
CREATE INDEX IF NOT EXISTS idx_enrollments_student_id ON enrollments(student_id);
CREATE INDEX IF NOT EXISTS idx_enrollments_course_id ON enrollments(course_id);
