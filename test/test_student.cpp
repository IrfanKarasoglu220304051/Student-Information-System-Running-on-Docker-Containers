#include <gtest/gtest.h>
#include "Student.hpp"

// ============================================================================
// STUDENT STRUCT BİRİM TESTLERİ
// ============================================================================

// TEST: Student Default Initialization Testi
TEST(StudentTest, DefaultInitialization_InitializesCorrectly) {
    // Arrange & Act
    Student student{};
    
    // Assert
    EXPECT_EQ(0, student.id);
    EXPECT_EQ("", student.studentNumber);
    EXPECT_EQ("", student.name);
    EXPECT_EQ("", student.surname);
    EXPECT_EQ(0.0, student.gpa);
}

// TEST: Student Field Assignment Testi
TEST(StudentTest, FieldAssignment_SetsAllFields) {
    // Arrange
    Student student;
    student.id = 1;
    student.studentNumber = "2021001";
    student.name = "Ahmet";
    student.surname = "Yılmaz";
    student.gpa = 3.5;
    
    // Assert
    EXPECT_EQ(1, student.id);
    EXPECT_EQ("2021001", student.studentNumber);
    EXPECT_EQ("Ahmet", student.name);
    EXPECT_EQ("Yılmaz", student.surname);
    EXPECT_DOUBLE_EQ(3.5, student.gpa);
}

// TEST: Student Initialization with Values
TEST(StudentTest, InitializationWithValues_SetsCorrectly) {
    // Arrange & Act
    Student student{1, "2021001", "Ahmet", "Yılmaz", 3.5};
    
    // Assert
    EXPECT_EQ(1, student.id);
    EXPECT_EQ("2021001", student.studentNumber);
    EXPECT_EQ("Ahmet", student.name);
    EXPECT_EQ("Yılmaz", student.surname);
    EXPECT_DOUBLE_EQ(3.5, student.gpa);
}

// ============================================================================
// SINIR DEĞER TESTLERİ
// ============================================================================

TEST(StudentTest, MinimumValues_HandlesCorrectly) {
    // Arrange & Act
    Student student{0, "1", "A", "B", 0.0};
    
    // Assert
    EXPECT_EQ(0, student.id);
    EXPECT_EQ("1", student.studentNumber);
    EXPECT_EQ("A", student.name);
    EXPECT_EQ("B", student.surname);
    EXPECT_DOUBLE_EQ(0.0, student.gpa);
}

TEST(StudentTest, MaximumGPA_HandlesCorrectly) {
    // Arrange & Act
    Student student{1, "2021001", "Test", "User", 4.0};
    
    // Assert
    EXPECT_DOUBLE_EQ(4.0, student.gpa);
}

// ============================================================================
// HATA DURUMLARI TESTLERİ
// ============================================================================

TEST(StudentTest, EmptyFields_HandlesCorrectly) {
    // Arrange & Act
    Student student{0, "", "", "", 0.0};
    
    // Assert
    EXPECT_EQ(0, student.id);
    EXPECT_EQ("", student.studentNumber);
    EXPECT_EQ("", student.name);
    EXPECT_EQ("", student.surname);
    EXPECT_DOUBLE_EQ(0.0, student.gpa);
}

// ============================================================================
// MAIN FUNCTION (GoogleTest için)
// ============================================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
