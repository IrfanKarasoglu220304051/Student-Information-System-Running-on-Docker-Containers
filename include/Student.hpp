#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
private:
    int id;
    std::string studentNumber;
    std::string firstName;
    std::string lastName;
    std::string email;

public:
    // Constructor (Yapıcı Metot)
    User(int id, std::string sNum, std::string fName, std::string lName, std::string mail);

    // Getter Metotları (Veriyi okumak için)
    int getId() const { return id; }
    std::string getFullName() const { return firstName + " " + lastName; }
    std::string getEmail() const { return email; }
    std::string getStudentNumber() const { return studentNumber; }

    // Setter Metotları (Veriyi güncellemek için - Opsiyonel)
    void setEmail(const std::string& newEmail) { email = newEmail; }
};

#endif