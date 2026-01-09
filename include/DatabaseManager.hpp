#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <vector>
#include "Student.hpp"

class DatabaseManager {
public:
    DatabaseManager();

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
