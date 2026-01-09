#include "DatabaseManager.hpp"
#include <cstdlib>
#include <iostream>

DatabaseManager::DatabaseManager() : connection(nullptr) {
    initializeConnection();
}

DatabaseManager::~DatabaseManager() {
    if (connection) {
        delete connection;
        connection = nullptr;
    }
}

DatabaseManager::DatabaseManager(DatabaseManager&& other) noexcept 
    : connection(other.connection), connectionString(std::move(other.connectionString)) {
    other.connection = nullptr;
}

DatabaseManager& DatabaseManager::operator=(DatabaseManager&& other) noexcept {
    if (this != &other) {
        if (connection) {
            delete connection;
        }
        connection = other.connection;
        connectionString = std::move(other.connectionString);
        other.connection = nullptr;
    }
    return *this;
}

std::string DatabaseManager::buildConnectionString() {
    std::string host = std::getenv("DB_HOST") ? std::getenv("DB_HOST") : "localhost";
    std::string port = std::getenv("DB_PORT") ? std::getenv("DB_PORT") : "5432";
    std::string dbname = std::getenv("DB_NAME") ? std::getenv("DB_NAME") : "studentdb";
    std::string user = std::getenv("DB_USER") ? std::getenv("DB_USER") : "student";
    std::string password = std::getenv("DB_PASSWORD") ? std::getenv("DB_PASSWORD") : "student123";
    
    return "host=" + host + 
           " port=" + port + 
           " dbname=" + dbname + 
           " user=" + user + 
           " password=" + password;
}

void DatabaseManager::initializeConnection() {
    try {
        connectionString = buildConnectionString();
        connection = new pqxx::connection(connectionString);
        
        if (connection->is_open()) {
            std::cout << "[INFO] Veritabanı bağlantısı başarılı: " 
                      << connection->dbname() << std::endl;
        } else {
            std::cerr << "[ERROR] Veritabanı bağlantısı açılamadı!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Veritabanı bağlantı hatası: " << e.what() << std::endl;
        connection = nullptr;
    }
}

bool DatabaseManager::isConnected() const {
    return connection != nullptr && connection->is_open();
}

bool DatabaseManager::addStudent(const Student& student) {
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return false;
    }
    
    try {
        pqxx::work txn(*connection);
        
        std::string query = "INSERT INTO students (student_number, first_name, last_name, email) "
                           "VALUES ($1, $2, $3, $4) "
                           "ON CONFLICT (student_number) DO NOTHING";
        
        txn.exec_params(query, 
                       student.studentNumber, 
                       student.firstName, 
                       student.lastName, 
                       student.email);
        
        txn.commit();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Öğrenci ekleme hatası: " << e.what() << std::endl;
        return false;
    }
}

std::vector<Student> DatabaseManager::listStudents() {
    std::vector<Student> students;
    
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return students;
    }
    
    try {
        pqxx::work txn(*connection);
        pqxx::result result = txn.exec("SELECT id, student_number, first_name, last_name, email FROM students ORDER BY id");
        
        for (const auto& row : result) {
            Student student;
            student.id = row[0].as<int>();
            student.studentNumber = row[1].as<std::string>();
            student.firstName = row[2].as<std::string>();
            student.lastName = row[3].as<std::string>();
            student.email = row[4].as<std::string>();
            students.push_back(student);
        }
        
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Öğrenci listeleme hatası: " << e.what() << std::endl;
    }
    
    return students;
}

Student DatabaseManager::getStudentById(int id) {
    Student student;
    student.id = 0; // Bulunamadı durumu
    
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return student;
    }
    
    try {
        pqxx::work txn(*connection);
        pqxx::result result = txn.exec_params(
            "SELECT id, student_number, first_name, last_name, email FROM students WHERE id = $1",
            id
        );
        
        if (!result.empty()) {
            const auto& row = result[0];
            student.id = row[0].as<int>();
            student.studentNumber = row[1].as<std::string>();
            student.firstName = row[2].as<std::string>();
            student.lastName = row[3].as<std::string>();
            student.email = row[4].as<std::string>();
        }
        
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Öğrenci arama hatası: " << e.what() << std::endl;
    }
    
    return student;
}

Student DatabaseManager::getStudentByNumber(const std::string& studentNumber) {
    Student student;
    student.id = 0; // Bulunamadı durumu
    
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return student;
    }
    
    try {
        pqxx::work txn(*connection);
        pqxx::result result = txn.exec_params(
            "SELECT id, student_number, first_name, last_name, email FROM students WHERE student_number = $1",
            studentNumber
        );
        
        if (!result.empty()) {
            const auto& row = result[0];
            student.id = row[0].as<int>();
            student.studentNumber = row[1].as<std::string>();
            student.firstName = row[2].as<std::string>();
            student.lastName = row[3].as<std::string>();
            student.email = row[4].as<std::string>();
        }
        
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Öğrenci arama hatası: " << e.what() << std::endl;
    }
    
    return student;
}

bool DatabaseManager::deleteStudent(const std::string& studentNumber) {
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return false;
    }
    
    try {
        pqxx::work txn(*connection);
        pqxx::result result = txn.exec_params(
            "DELETE FROM students WHERE student_number = $1",
            studentNumber
        );
        
        txn.commit();
        return result.affected_rows() > 0;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Öğrenci silme hatası: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::updateStudentGrade(const std::string& studentNumber, 
                                         const std::string& courseCode, 
                                         float grade) {
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return false;
    }
    
    try {
        pqxx::work txn(*connection);
        
        // Önce öğrenci ID'sini bul
        pqxx::result studentResult = txn.exec_params(
            "SELECT id FROM students WHERE student_number = $1",
            studentNumber
        );
        
        if (studentResult.empty()) {
            std::cerr << "[ERROR] Öğrenci bulunamadı!" << std::endl;
            return false;
        }
        
        int studentId = studentResult[0][0].as<int>();
        
        // Ders ID'sini bul
        pqxx::result courseResult = txn.exec_params(
            "SELECT id FROM courses WHERE course_code = $1",
            courseCode
        );
        
        if (courseResult.empty()) {
            std::cerr << "[ERROR] Ders bulunamadı!" << std::endl;
            return false;
        }
        
        int courseId = courseResult[0][0].as<int>();
        
        // Notu güncelle veya ekle (UPSERT)
        txn.exec_params(
            "INSERT INTO enrollments (student_id, course_id, grade) "
            "VALUES ($1, $2, $3) "
            "ON CONFLICT (student_id, course_id) "
            "DO UPDATE SET grade = $3",
            studentId, courseId, grade
        );
        
        txn.commit();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Not güncelleme hatası: " << e.what() << std::endl;
        return false;
    }
}

float DatabaseManager::calculateGPA(const std::string& studentNumber) {
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return -1.0f;
    }
    
    try {
        pqxx::work txn(*connection);
        
        // Öğrenci ID'sini bul
        pqxx::result studentResult = txn.exec_params(
            "SELECT id FROM students WHERE student_number = $1",
            studentNumber
        );
        
        if (studentResult.empty()) {
            std::cerr << "[ERROR] Öğrenci bulunamadı!" << std::endl;
            return -1.0f;
        }
        
        int studentId = studentResult[0][0].as<int>();
        
        // GPA hesapla (0-100 arası notları 0-4 arası GPA'ya çevir)
        pqxx::result result = txn.exec_params(
            "SELECT AVG(grade) FROM enrollments WHERE student_id = $1",
            studentId
        );
        
        if (result.empty() || result[0][0].is_null()) {
            return 0.0f;
        }
        
        float avgGrade = result[0][0].as<float>();
        // 0-100 arası notu 0-4 arası GPA'ya çevir
        float gpa = (avgGrade / 100.0f) * 4.0f;
        
        txn.commit();
        return gpa;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] GPA hesaplama hatası: " << e.what() << std::endl;
        return -1.0f;
    }
}

