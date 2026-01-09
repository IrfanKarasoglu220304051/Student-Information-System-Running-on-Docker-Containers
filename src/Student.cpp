#include "Student.hpp"
#include <sstream>
#include <iomanip>

std::string Student::getFullName() const {
    return name + " " + surname;
}

bool Student::isValid() const {
    return id > 0 && !studentNumber.empty() && !name.empty() && !surname.empty();
}

std::string Student::toString() const {
    std::ostringstream oss;
    oss << "ID: " << id 
        << ", Numara: " << studentNumber
        << ", Ad Soyad: " << getFullName()
        << ", GPA: " << std::fixed << std::setprecision(2) << gpa;
    return oss.str();
}
