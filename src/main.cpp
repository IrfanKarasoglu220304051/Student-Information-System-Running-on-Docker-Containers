#include <iostream>
#include "DatabaseManager.hpp"
#include "Student.hpp"

// ---- Fonksiyon bildirimi (ÖNCE) ----
Student getStudentInput();
void handleInsert(DatabaseManager& dbManager);
void handleList(DatabaseManager& dbManager);

// ---- Implementasyonlar ----
Student getStudentInput() {
    Student s;
    s.id = 1;
    s.studentNumber = "123";
    s.name = "Test";
    s.surname = "User";
    s.gpa = 3.0;
    return s;
}

void handleInsert(DatabaseManager& dbManager) {
    Student s = getStudentInput();
    dbManager.insertStudent(s);
}

void handleList(DatabaseManager& dbManager) {
    auto students = dbManager.getAllStudents();
    std::cout << "Student count: " << students.size() << "\n";
}

int main() {
    DatabaseManager dbManager;

    if (!dbManager.isConnected()) {
        std::cerr << "Database connection failed\n";
        return 1;
    }

    handleInsert(dbManager);
    handleList(dbManager);

    return 0;
}
