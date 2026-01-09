#include <gtest/gtest.h>
#include "Student.hpp"

// ============================================================================
// STUDENT SINIFI BİRİM TESTLERİ
// ============================================================================

// TEST: Student Default Constructor Testi
TEST(StudentTest, DefaultConstructor_InitializesCorrectly) {
    // Arrange & Act
    Student student;
    
    // Assert
    EXPECT_EQ(0, student.getId());
    EXPECT_EQ("", student.getStudentNumber());
    EXPECT_EQ("", student.firstName);
    EXPECT_EQ("", student.lastName);
    EXPECT_EQ("", student.getEmail());
    EXPECT_EQ("", student.getFullName());
}

// TEST: Student Parametreli Constructor Testi
TEST(StudentTest, ParameterizedConstructor_SetsAllFields) {
    // Arrange
    int id = 1;
    std::string num = "2021001";
    std::string fName = "Ahmet";
    std::string lName = "Yılmaz";
    std::string email = "ahmet@example.com";
    
    // Act
    Student student(id, num, fName, lName, email);
    
    // Assert
    EXPECT_EQ(id, student.getId());
    EXPECT_EQ(num, student.getStudentNumber());
    EXPECT_EQ(fName, student.firstName);
    EXPECT_EQ(lName, student.lastName);
    EXPECT_EQ(email, student.getEmail());
}

// TEST: Student Getter Metodları Testi
TEST(StudentTest, GetId_ReturnsCorrectValue) {
    // Arrange
    Student student(5, "2021005", "Mehmet", "Demir", "mehmet@example.com");
    
    // Act & Assert
    EXPECT_EQ(5, student.getId());
}

TEST(StudentTest, GetFullName_ReturnsConcatenatedName) {
    // Arrange
    Student student(1, "2021001", "Ahmet", "Yılmaz", "ahmet@example.com");
    
    // Act
    std::string fullName = student.getFullName();
    
    // Assert
    EXPECT_EQ("Ahmet Yılmaz", fullName);
}

TEST(StudentTest, GetEmail_ReturnsCorrectEmail) {
    // Arrange
    Student student(1, "2021001", "Ahmet", "Yılmaz", "ahmet@example.com");
    
    // Act & Assert
    EXPECT_EQ("ahmet@example.com", student.getEmail());
}

TEST(StudentTest, GetStudentNumber_ReturnsCorrectNumber) {
    // Arrange
    Student student(1, "2021001", "Ahmet", "Yılmaz", "ahmet@example.com");
    
    // Act & Assert
    EXPECT_EQ("2021001", student.getStudentNumber());
}

// TEST: Student Setter Metodları Testi
TEST(StudentTest, SetEmail_UpdatesEmail) {
    // Arrange
    Student student(1, "2021001", "Ahmet", "Yılmaz", "old@example.com");
    
    // Act
    student.setEmail("new@example.com");
    
    // Assert
    EXPECT_EQ("new@example.com", student.getEmail());
}

// ============================================================================
// SINIR DEĞER TESTLERİ
// ============================================================================

TEST(StudentTest, MinimumValues_HandlesCorrectly) {
    // Arrange & Act
    Student student(0, "1", "A", "B", "a@b.c");
    
    // Assert
    EXPECT_EQ(0, student.getId());
    EXPECT_EQ("1", student.getStudentNumber());
    EXPECT_EQ("A", student.firstName);
    EXPECT_EQ("B", student.lastName);
    EXPECT_EQ("a@b.c", student.getEmail());
}

TEST(StudentTest, MaxLengthFields_HandlesCorrectly) {
    // Arrange
    std::string longNum(15, '1');      // 15 karakter
    std::string longName(50, 'A');     // 50 karakter
    std::string longEmail(100, 'a');    // 100 karakter
    
    // Act
    Student student(1, longNum, longName, longName, longEmail);
    
    // Assert
    EXPECT_EQ(longNum, student.getStudentNumber());
    EXPECT_EQ(longName, student.firstName);
    EXPECT_EQ(longName, student.lastName);
    EXPECT_EQ(longEmail, student.getEmail());
}

// ============================================================================
// HATA DURUMLARI TESTLERİ
// ============================================================================

TEST(StudentTest, EmptyFields_HandlesCorrectly) {
    // Arrange & Act
    Student student(0, "", "", "", "");
    
    // Assert
    EXPECT_EQ(0, student.getId());
    EXPECT_EQ("", student.getStudentNumber());
    EXPECT_EQ("", student.firstName);
    EXPECT_EQ("", student.lastName);
    EXPECT_EQ("", student.getEmail());
    EXPECT_EQ(" ", student.getFullName()); // Boş string'ler için " " döner (firstName + " " + lastName)
}

// ============================================================================
// MAIN FUNCTION (GoogleTest için)
// ============================================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

