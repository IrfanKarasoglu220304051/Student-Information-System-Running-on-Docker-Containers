#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <vector>
#include <string>
#include "Student.hpp"
#include <pqxx/pqxx>

class DatabaseManager {
private:
    pqxx::connection* connection;
    std::string connectionString;
    
    std::string buildConnectionString();
    void initializeConnection();

public:
    DatabaseManager();
    ~DatabaseManager();
    
    // Copy constructor ve assignment operator'ı devre dışı bırak
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
    
    // Move constructor ve move assignment
    DatabaseManager(DatabaseManager&&) noexcept;
    DatabaseManager& operator=(DatabaseManager&&) noexcept;

    bool isConnected() const;

    void insertStudent(const Student& student);
    std::vector<Student> getAllStudents();
    Student getStudentById(int id);
    Student getStudentByNumber(const std::string& number);
    void deleteStudent(int id);
    void updateStudentGrade(int id, double gpa);
    double calculateGPA();
};

#endif // DATABASE_MANAGER_H
