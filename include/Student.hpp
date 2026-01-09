#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>

struct Student {
    int id;
    std::string studentNumber;
    std::string name;
    std::string surname;
    double gpa;
    
    // Yardımcı metodlar
    std::string getFullName() const;
    bool isValid() const;
    std::string toString() const;
};

#endif // STUDENT_HPP
