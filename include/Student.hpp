#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>

class Student {
public:
    int id;
    std::string studentNumber;
    std::string firstName;
    std::string lastName;
    std::string email;

    // Default Constructor
    Student() : id(0) {}
    
    // Parametreli Constructor
    Student(int id, std::string sNum, std::string fName, std::string lName, std::string mail);

    // Getter Metotları
    int getId() const { return id; }
    std::string getFullName() const { return firstName + " " + lastName; }
    std::string getEmail() const { return email; }
    std::string getStudentNumber() const { return studentNumber; }

    // Setter Metotları
    void setEmail(const std::string& newEmail) { email = newEmail; }
};

#endif
