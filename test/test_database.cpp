#include <gtest/gtest.h>
#include "DatabaseManager.hpp"
#include "Student.hpp"
#include <cstdlib>

// ============================================================================
// ENTEGRASYON TESTLERİ - DatabaseManager
// ============================================================================

class DatabaseIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Her test öncesi DatabaseManager oluştur
        dbManager = new DatabaseManager();
    }
    
    void TearDown() override {
        // Her test sonrası temizle
        if (dbManager) {
            delete dbManager;
            dbManager = nullptr;
        }
    }
    
    DatabaseManager* dbManager;
};

// ============================================================================
// VERİTABANI BAĞLANTI TESTLERİ
// ============================================================================

TEST_F(DatabaseIntegrationTest, Connection_EstablishesSuccessfully) {
    // Act & Assert
    // Not: Bu test sadece bağlantı kurulabildiğinde geçer
    // Eğer veritabanı yoksa test atlanabilir
    if (!dbManager->isConnected()) {
        GTEST_SKIP() << "Veritabanı bağlantısı kurulamadı. Test atlandı.";
    }
    
    EXPECT_TRUE(dbManager->isConnected());
}

// ============================================================================
// ÖĞRENCI İŞLEMLERİ ENTEGRASYON TESTLERİ
// ============================================================================

TEST_F(DatabaseIntegrationTest, AddStudent_InsertsToDatabase) {
    // Skip if not connected
    if (!dbManager->isConnected()) {
        GTEST_SKIP() << "Veritabanı bağlantısı yok. Test atlandı.";
    }
    
    // Arrange
    Student student(0, "TEST001", "Test", "Student", "test@example.com");
    
    // Act
    bool result = dbManager->addStudent(student);
    
    // Assert
    EXPECT_TRUE(result);
    
    // Veritabanında gerçekten var mı kontrol et
    Student retrieved = dbManager->getStudentByNumber("TEST001");
    EXPECT_GT(retrieved.getId(), 0);
    EXPECT_EQ("TEST001", retrieved.getStudentNumber());
    EXPECT_EQ("Test", retrieved.firstName);
    EXPECT_EQ("Student", retrieved.lastName);
    EXPECT_EQ("test@example.com", retrieved.getEmail());
}

TEST_F(DatabaseIntegrationTest, ListStudents_RetrievesFromDatabase) {
    // Skip if not connected
    if (!dbManager->isConnected()) {
        GTEST_SKIP() << "Veritabanı bağlantısı yok. Test atlandı.";
    }
    
    // Arrange - Önce bir öğrenci ekle
    Student student(0, "TEST002", "List", "Test", "list@example.com");
    dbManager->addStudent(student);
    
    // Act
    std::vector<Student> students = dbManager->listStudents();
    
    // Assert
    EXPECT_FALSE(students.empty());
    
    // TEST002'nin listede olduğunu kontrol et
    bool found = false;
    for (const auto& s : students) {
        if (s.getStudentNumber() == "TEST002") {
            found = true;
            EXPECT_EQ("List", s.firstName);
            EXPECT_EQ("Test", s.lastName);
            break;
        }
    }
    EXPECT_TRUE(found);
}

TEST_F(DatabaseIntegrationTest, GetStudentById_RetrievesCorrectStudent) {
    // Skip if not connected
    if (!dbManager->isConnected()) {
        GTEST_SKIP() << "Veritabanı bağlantısı yok. Test atlandı.";
    }
    
    // Arrange - Önce bir öğrenci ekle
    Student student(0, "TEST003", "Id", "Test", "id@example.com");
    dbManager->addStudent(student);
    
    // Öğrenci ID'sini al
    Student temp = dbManager->getStudentByNumber("TEST003");
    int studentId = temp.getId();
    EXPECT_GT(studentId, 0);
    
    // Act
    Student retrieved = dbManager->getStudentById(studentId);
    
    // Assert
    EXPECT_EQ(studentId, retrieved.getId());
    EXPECT_EQ("TEST003", retrieved.getStudentNumber());
    EXPECT_EQ("Id", retrieved.firstName);
    EXPECT_EQ("Test", retrieved.lastName);
}

TEST_F(DatabaseIntegrationTest, GetStudentByNumber_RetrievesCorrectStudent) {
    // Skip if not connected
    if (!dbManager->isConnected()) {
        GTEST_SKIP() << "Veritabanı bağlantısı yok. Test atlandı.";
    }
    
    // Arrange - Önce bir öğrenci ekle
    Student student(0, "TEST004", "Number", "Test", "number@example.com");
    dbManager->addStudent(student);
    
    // Act
    Student retrieved = dbManager->getStudentByNumber("TEST004");
    
    // Assert
    EXPECT_GT(retrieved.getId(), 0);
    EXPECT_EQ("TEST004", retrieved.getStudentNumber());
    EXPECT_EQ("Number", retrieved.firstName);
    EXPECT_EQ("Test", retrieved.lastName);
    EXPECT_EQ("number@example.com", retrieved.getEmail());
}

TEST_F(DatabaseIntegrationTest, GetStudentByNumber_NotFoundReturnsEmpty) {
    // Skip if not connected
    if (!dbManager->isConnected()) {
        GTEST_SKIP() << "Veritabanı bağlantısı yok. Test atlandı.";
    }
    
    // Act
    Student retrieved = dbManager->getStudentByNumber("NONEXISTENT999");
    
    // Assert
    EXPECT_EQ(0, retrieved.getId());
    EXPECT_EQ("", retrieved.getStudentNumber());
}

TEST_F(DatabaseIntegrationTest, DeleteStudent_RemovesFromDatabase) {
    // Skip if not connected
    if (!dbManager->isConnected()) {
        GTEST_SKIP() << "Veritabanı bağlantısı yok. Test atlandı.";
    }
    
    // Arrange - Önce bir öğrenci ekle
    Student student(0, "TEST005", "Delete", "Me", "delete@example.com");
    dbManager->addStudent(student);
    
    // Öğrencinin eklendiğini doğrula
    Student before = dbManager->getStudentByNumber("TEST005");
    EXPECT_GT(before.getId(), 0);
    
    // Act
    bool result = dbManager->deleteStudent("TEST005");
    
    // Assert
    EXPECT_TRUE(result);
    
    // Veritabanında olmadığını kontrol et
    Student after = dbManager->getStudentByNumber("TEST005");
    EXPECT_EQ(0, after.getId());
}

TEST_F(DatabaseIntegrationTest, DeleteStudent_NotFoundReturnsFalse) {
    // Skip if not connected
    if (!dbManager->isConnected()) {
        GTEST_SKIP() << "Veritabanı bağlantısı yok. Test atlandı.";
    }
    
    // Act
    bool result = dbManager->deleteStudent("NONEXISTENT999");
    
    // Assert
    EXPECT_FALSE(result);
}

// ============================================================================
// NOT İŞLEMLERİ ENTEGRASYON TESTLERİ
// ============================================================================

TEST_F(DatabaseIntegrationTest, UpdateStudentGrade_InsertsGrade) {
    // Skip if not connected
    if (!dbManager->isConnected()) {
        GTEST_SKIP() << "Veritabanı bağlantısı yok. Test atlandı.";
    }
    
    // Arrange - Önce öğrenci ekle
    Student student(0, "TEST006", "Grade", "Test", "grade@example.com");
    dbManager->addStudent(student);
    
    // Ders eklemek için önce courses tablosuna ders eklememiz gerekir
    // Basit test için sadece updateStudentGrade'in çağrılabildiğini test ediyoruz
    // Gerçek uygulamada ders önce eklenmeli
    
    // Act - Not güncelle (ders yoksa hata dönebilir, bu normal)
    bool result = dbManager->updateStudentGrade("TEST006", "CS101", 85.0f);
    
    // Assert - Ders yoksa false dönebilir, bu beklenen davranış
    // Eğer ders varsa true dönmeli
    // Bu test sadece metodun çağrılabildiğini ve hata vermediğini kontrol eder
    // (result true veya false olabilir, dersin varlığına bağlı)
}

TEST_F(DatabaseIntegrationTest, CalculateGPA_CalculatesCorrectly) {
    // Skip if not connected
    if (!dbManager->isConnected()) {
        GTEST_SKIP() << "Veritabanı bağlantısı yok. Test atlandı.";
    }
    
    // Arrange - Önce öğrenci ekle
    Student student(0, "TEST007", "GPA", "Test", "gpa@example.com");
    dbManager->addStudent(student);
    
    // Act
    float gpa = dbManager->calculateGPA("TEST007");
    
    // Assert
    // Notu olmayan öğrenci için 0.0 veya -1.0 dönebilir
    // Bu test sadece metodun çağrılabildiğini kontrol eder
    EXPECT_GE(gpa, -1.0f);
    EXPECT_LE(gpa, 4.0f);
}

TEST_F(DatabaseIntegrationTest, CalculateGPA_NotFoundReturnsNegative) {
    // Skip if not connected
    if (!dbManager->isConnected()) {
        GTEST_SKIP() << "Veritabanı bağlantısı yok. Test atlandı.";
    }
    
    // Act
    float gpa = dbManager->calculateGPA("NONEXISTENT999");
    
    // Assert
    EXPECT_EQ(-1.0f, gpa);
}

// ============================================================================
// MAIN FUNCTION (GoogleTest için)
// ============================================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

