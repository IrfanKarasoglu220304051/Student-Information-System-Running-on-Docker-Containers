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

void DatabaseManager::insertStudent(const Student& student) {
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return;
    }
    
    try {
        pqxx::work txn(*connection);
        
        std::string query = "INSERT INTO students (student_number, first_name, last_name, email) "
                           "VALUES ($1, $2, $3, $4) "
                           "ON CONFLICT (student_number) DO NOTHING";
        
        // Student struct'ındaki alanları schema'ya göre map et
        // Student struct: id, studentNumber, name, surname, gpa
        // Schema: student_number, first_name, last_name, email
        
        txn.exec_params(query, 
                       student.studentNumber, 
                       student.name,  // first_name
                       student.surname, // last_name
                       student.studentNumber + "@university.edu"); // email (örnek)
        
        txn.commit();
        std::cout << "[INFO] Öğrenci eklendi: " << student.studentNumber << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Öğrenci ekleme hatası: " << e.what() << std::endl;
    }
}

std::vector<Student> DatabaseManager::getAllStudents() {
    std::vector<Student> students;
    
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return students;
    }
    
    try {
        pqxx::work txn(*connection);
        pqxx::result result = txn.exec(
            "SELECT id, student_number, first_name, last_name, email FROM students ORDER BY id"
        );
        
        for (const auto& row : result) {
            Student student;
            student.id = row[0].as<int>();
            student.studentNumber = row[1].as<std::string>();
            student.name = row[2].as<std::string>();  // first_name -> name
            student.surname = row[3].as<std::string>(); // last_name -> surname
            // email'i kullanmıyoruz çünkü Student struct'ında yok
            // gpa'yı enrollments tablosundan hesaplayabiliriz
            student.gpa = 0.0; // Varsayılan
            
            students.push_back(student);
        }
        
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Öğrenci listeleme hatası: " << e.what() << std::endl;
    }
    
    return students;
}

Student DatabaseManager::getStudentById(int id) {
    Student student{};
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
            student.name = row[2].as<std::string>();
            student.surname = row[3].as<std::string>();
            student.gpa = 0.0;
        }
        
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Öğrenci arama hatası: " << e.what() << std::endl;
    }
    
    return student;
}

Student DatabaseManager::getStudentByNumber(const std::string& number) {
    Student student{};
    student.id = 0; // Bulunamadı durumu
    
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return student;
    }
    
    try {
        pqxx::work txn(*connection);
        pqxx::result result = txn.exec_params(
            "SELECT id, student_number, first_name, last_name, email FROM students WHERE student_number = $1",
            number
        );
        
        if (!result.empty()) {
            const auto& row = result[0];
            student.id = row[0].as<int>();
            student.studentNumber = row[1].as<std::string>();
            student.name = row[2].as<std::string>();
            student.surname = row[3].as<std::string>();
            student.gpa = 0.0;
        }
        
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Öğrenci arama hatası: " << e.what() << std::endl;
    }
    
    return student;
}

void DatabaseManager::deleteStudent(int id) {
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return;
    }
    
    try {
        pqxx::work txn(*connection);
        pqxx::result result = txn.exec_params(
            "DELETE FROM students WHERE id = $1",
            id
        );
        
        txn.commit();
        
        if (result.affected_rows() > 0) {
            std::cout << "[INFO] Öğrenci silindi: ID " << id << std::endl;
        } else {
            std::cout << "[WARNING] Silinecek öğrenci bulunamadı: ID " << id << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Öğrenci silme hatası: " << e.what() << std::endl;
    }
}

void DatabaseManager::updateStudentGrade(int id, double gpa) {
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return;
    }
    
    // Not: Schema'da GPA direkt olarak saklanmıyor, enrollments tablosundan hesaplanıyor
    // Bu metod şu an için placeholder, gerçek implementasyon enrollments tablosunu günceller
    std::cerr << "[WARNING] updateStudentGrade() henüz tam implement edilmedi. "
              << "Notlar enrollments tablosunda saklanıyor." << std::endl;
}

double DatabaseManager::calculateGPA() {
    if (!isConnected()) {
        std::cerr << "[ERROR] Veritabanı bağlantısı yok!" << std::endl;
        return -1.0;
    }
    
    // Not: Bu metod tüm öğrenciler için ortalama GPA döndürüyor
    // Belirli bir öğrenci için GPA hesaplamak için parametre eklenebilir
    try {
        pqxx::work txn(*connection);
        pqxx::result result = txn.exec(
            "SELECT AVG(grade) FROM enrollments"
        );
        
        if (result.empty() || result[0][0].is_null()) {
            return 0.0;
        }
        
        double avgGrade = result[0][0].as<double>();
        // 0-100 arası notu 0-4 arası GPA'ya çevir
        double gpa = (avgGrade / 100.0) * 4.0;
        
        txn.commit();
        return gpa;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] GPA hesaplama hatası: " << e.what() << std::endl;
        return -1.0;
    }
}
