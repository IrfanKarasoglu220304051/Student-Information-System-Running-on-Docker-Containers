#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <vector>
#include <string>
#include "Student.hpp"
#include <pqxx/pqxx>

// Sıralama kriterleri için enum
enum class SortBy {
    ID,
    STUDENT_NUMBER,
    NAME,
    SURNAME,
    GPA_ASC,
    GPA_DESC
};

// Filtreleme kriterleri için struct
struct FilterCriteria {
    std::string department;
    double minGPA = 0.0;
    double maxGPA = 4.0;
    std::string searchName;  // İsim veya soyisimde arama
};

class DatabaseManager {
private:
    pqxx::connection* connection;
    std::string connectionString;
    
    std::string buildConnectionString();
    void initializeConnection();
    
    // Sıralama için yardımcı metod
    void sortStudents(std::vector<Student>& students, SortBy sortBy) const;

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

    // Temel CRUD işlemleri
    void insertStudent(const Student& student);
    std::vector<Student> getAllStudents();
    Student getStudentById(int id);
    Student getStudentByNumber(const std::string& number);
    void deleteStudent(int id);
    void updateStudentGrade(int id, double gpa);
    double calculateGPA();
    
    // Sıralama ve filtreleme metodları
    std::vector<Student> getStudentsSorted(SortBy sortBy);
    std::vector<Student> getStudentsFiltered(const FilterCriteria& criteria);
    std::vector<Student> getStudentsSortedAndFiltered(SortBy sortBy, const FilterCriteria& criteria);
    
    // Arama metodları
    std::vector<Student> searchStudentsByName(const std::string& searchTerm);
    std::vector<Student> getStudentsByDepartment(const std::string& department);
    std::vector<Student> getStudentsByGPARange(double minGPA, double maxGPA);
    
    // İstatistik metodları
    int getStudentCount();
    double getAverageGPA();
    Student getStudentWithHighestGPA();
    Student getStudentWithLowestGPA();
};

#endif // DATABASE_MANAGER_H
