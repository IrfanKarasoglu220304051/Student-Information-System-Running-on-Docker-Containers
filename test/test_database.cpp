#include <gtest/gtest.h>
#include "DatabaseManager.hpp"
#include "Student.hpp"

// ============================================================================
// DATABASEMANAGER TESTLERİ
// ============================================================================

class DatabaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        dbManager = new DatabaseManager();
    }
    
    void TearDown() override {
        if (dbManager) {
            delete dbManager;
            dbManager = nullptr;
        }
    }
    
    DatabaseManager* dbManager;
};

// ============================================================================
// BAĞLANTI TESTLERİ
// ============================================================================

TEST_F(DatabaseTest, IsConnected_ReturnsTrue) {
    // Act & Assert
    EXPECT_TRUE(dbManager->isConnected());
}

// ============================================================================
// ÖĞRENCI İŞLEMLERİ TESTLERİ
// ============================================================================

TEST_F(DatabaseTest, InsertStudent_DoesNotCrash) {
    // Arrange
    Student student{1, "2021001", "Test", "User", 3.5};
    
    // Act & Assert - Sadece crash olmamasını test ediyoruz
    EXPECT_NO_THROW(dbManager->insertStudent(student));
}

TEST_F(DatabaseTest, GetAllStudents_ReturnsEmptyVector) {
    // Act
    auto students = dbManager->getAllStudents();
    
    // Assert
    EXPECT_TRUE(students.empty());
}

TEST_F(DatabaseTest, GetStudentById_ReturnsEmptyStudent) {
    // Act
    Student student = dbManager->getStudentById(1);
    
    // Assert
    EXPECT_EQ(0, student.id);
    EXPECT_EQ("", student.studentNumber);
}

TEST_F(DatabaseTest, GetStudentByNumber_ReturnsEmptyStudent) {
    // Act
    Student student = dbManager->getStudentByNumber("2021001");
    
    // Assert
    EXPECT_EQ(0, student.id);
    EXPECT_EQ("", student.studentNumber);
}

TEST_F(DatabaseTest, DeleteStudent_DoesNotCrash) {
    // Act & Assert
    EXPECT_NO_THROW(dbManager->deleteStudent(1));
}

TEST_F(DatabaseTest, UpdateStudentGrade_DoesNotCrash) {
    // Act & Assert
    EXPECT_NO_THROW(dbManager->updateStudentGrade(1, 3.5));
}

TEST_F(DatabaseTest, CalculateGPA_ReturnsZero) {
    // Act
    double gpa = dbManager->calculateGPA();
    
    // Assert
    EXPECT_DOUBLE_EQ(0.0, gpa);
}

// ============================================================================
// MAIN FUNCTION (GoogleTest için)
// ============================================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
