#include "DatabaseManager.hpp"
#include <iostream>

DatabaseManager::DatabaseManager() {}

bool DatabaseManager::isConnected() const {
    return true;
}

void DatabaseManager::insertStudent(const Student& student) {
    std::cout << "Student inserted\n";
}

std::vector<Student> DatabaseManager::getAllStudents() {
    return {};
}

Student DatabaseManager::getStudentById(int id) {
    return {};
}

Student DatabaseManager::getStudentByNumber(const std::string& number) {
    return {};
}

void DatabaseManager::deleteStudent(int id) {}

void DatabaseManager::updateStudentGrade(int id, double gpa) {}

double DatabaseManager::calculateGPA() {
    return 0.0;
}
