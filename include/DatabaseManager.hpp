#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <string>
#include <vector>
#include "Student.hpp"
#include <pqxx/pqxx>

class DatabaseManager {
private:
    pqxx::connection* connection;
    std::string connectionString;
    
    std::string buildConnectionString();
    void initializeConnection();

public:
    // Constructor
    DatabaseManager();
    
    // Destructor
    ~DatabaseManager();
    
    // Copy constructor ve assignment operator'ı devre dışı bırak
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    
    // Move constructor ve move assignment
    DatabaseManager(DatabaseManager&&) noexcept;
    DatabaseManager& operator=(DatabaseManager&&) noexcept;
    
    // Bağlantı kontrolü
    bool isConnected() const;
    
    // Öğrenci işlemleri
    bool addStudent(const Student& student);
    std::vector<Student> listStudents();
    Student getStudentById(int id);
    Student getStudentByNumber(const std::string& studentNumber);
    bool deleteStudent(const std::string& studentNumber);
    
    // Not ve GPA işlemleri
    bool updateStudentGrade(const std::string& studentNumber, 
                           const std::string& courseCode, 
                           float grade);
    float calculateGPA(const std::string& studentNumber);
};

#endif // DATABASEMANAGER_HPP

