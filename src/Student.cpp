#include "User.hpp"

User::User(int id, std::string sNum, std::string fName, std::string lName, std::string mail) 
    : id(id), studentNumber(sNum), firstName(fName), lastName(lName), email(mail) {
    // Burada gerekirse ilk atama kontrolleri yapılabilir
}