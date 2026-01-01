#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "DatabaseManager.hpp"

void printMenu() {
    std::cout << "\n=== Öğrenci Bilgi Sistemi ===" << std::endl;
    std::cout << "1) Yeni Öğrenci Ekle (Insert)" << std::endl;
    std::cout << "2) Öğrenci Listele (List)" << std::endl;
    std::cout << "3) Öğrenci Ara (ID ile)" << std::endl;
    std::cout << "4) Öğrenci Ara (Numara ile)" << std::endl;
    std::cout << "5) Öğrenci Sil (Delete)" << std::endl;
    std::cout << "6) Not Güncelle (Update Grade)" << std::endl;
    std::cout << "7) GPA Hesapla" << std::endl;
    std::cout << "0) Çıkış" << std::endl;
    std::cout << "Seçiminiz: ";
}

Student getStudentInput() {
    Student student;
    student.id = 0; // Yeni öğrenci için 0
    
    std::cout << "Öğrenci Numarası: ";
    std::cin >> student.studentNumber;
    
    std::cout << "Ad: ";
    std::cin >> student.firstName;
    
    std::cout << "Soyad: ";
    std::cin >> student.lastName;
    
    std::cout << "E-posta: ";
    std::cin >> student.email;
    
    return student;
}

void handleInsert(DatabaseManager& dbManager) {
    std::cout << "\n--- Yeni Öğrenci Ekleme ---" << std::endl;
    Student student = getStudentInput();
    
    if (dbManager.addStudent(student)) {
        std::cout << ">> Başarılı!" << std::endl;
    } else {
        std::cout << ">> Hata oluştu!" << std::endl;
    }
}

void handleList(DatabaseManager& dbManager) {
    std::cout << "\n--- Öğrenci Listesi ---" << std::endl;
    std::vector<Student> students = dbManager.listStudents();
    
    if (students.empty()) {
        std::cout << "Kayıtlı öğrenci bulunamadı." << std::endl;
        return;
    }
    
    std::cout << "ID\tNumara\t\tAd\t\tSoyad\t\tE-posta" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    for (const auto& student : students) {
        std::cout << student.id << "\t" 
                  << student.studentNumber << "\t\t"
                  << student.firstName << "\t\t"
                  << student.lastName << "\t\t"
                  << student.email << std::endl;
    }
}

void handleSearchById(DatabaseManager& dbManager) {
    std::cout << "\n--- Öğrenci Ara (ID) ---" << std::endl;
    int id;
    std::cout << "Öğrenci ID: ";
    std::cin >> id;
    
    Student student = dbManager.getStudentById(id);
    
    if (student.id > 0) {
        std::cout << "Bulundu:" << std::endl;
        std::cout << "ID: " << student.id << std::endl;
        std::cout << "Numara: " << student.studentNumber << std::endl;
        std::cout << "Ad: " << student.firstName << std::endl;
        std::cout << "Soyad: " << student.lastName << std::endl;
        std::cout << "E-posta: " << student.email << std::endl;
    } else {
        std::cout << "Öğrenci bulunamadı." << std::endl;
    }
}

void handleSearchByNumber(DatabaseManager& dbManager) {
    std::cout << "\n--- Öğrenci Ara (Numara) ---" << std::endl;
    std::string studentNumber;
    std::cout << "Öğrenci Numarası: ";
    std::cin >> studentNumber;
    
    Student student = dbManager.getStudentByNumber(studentNumber);
    
    if (student.id > 0) {
        std::cout << "Bulundu:" << std::endl;
        std::cout << "ID: " << student.id << std::endl;
        std::cout << "Numara: " << student.studentNumber << std::endl;
        std::cout << "Ad: " << student.firstName << std::endl;
        std::cout << "Soyad: " << student.lastName << std::endl;
        std::cout << "E-posta: " << student.email << std::endl;
    } else {
        std::cout << "Öğrenci bulunamadı." << std::endl;
    }
}

void handleDelete(DatabaseManager& dbManager) {
    std::cout << "\n--- Öğrenci Silme ---" << std::endl;
    std::string studentNumber;
    std::cout << "Silinecek Öğrenci Numarası: ";
    std::cin >> studentNumber;
    
    std::cout << "Emin misiniz? (e/h): ";
    char confirm;
    std::cin >> confirm;
    
    if (confirm == 'e' || confirm == 'E') {
        if (dbManager.deleteStudent(studentNumber)) {
            std::cout << ">> Başarılı!" << std::endl;
        } else {
            std::cout << ">> Hata oluştu!" << std::endl;
        }
    } else {
        std::cout << "İşlem iptal edildi." << std::endl;
    }
}

void handleUpdateGrade(DatabaseManager& dbManager) {
    std::cout << "\n--- Not Güncelleme ---" << std::endl;
    std::string studentNumber, courseCode;
    float grade;
    
    std::cout << "Öğrenci Numarası: ";
    std::cin >> studentNumber;
    
    std::cout << "Ders Kodu: ";
    std::cin >> courseCode;
    
    std::cout << "Not (0-100): ";
    std::cin >> grade;
    
    if (dbManager.updateStudentGrade(studentNumber, courseCode, grade)) {
        std::cout << ">> Başarılı!" << std::endl;
    } else {
        std::cout << ">> Hata oluştu!" << std::endl;
    }
}

void handleCalculateGPA(DatabaseManager& dbManager) {
    std::cout << "\n--- GPA Hesaplama ---" << std::endl;
    std::string studentNumber;
    std::cout << "Öğrenci Numarası: ";
    std::cin >> studentNumber;
    
    float gpa = dbManager.calculateGPA(studentNumber);
    
    if (gpa >= 0) {
        std::cout << "GPA: " << gpa << std::endl;
    } else {
        std::cout << "GPA hesaplanamadı." << std::endl;
    }
}

int main() {
    std::cout << "--- Öğrenci Bilgi Sistemi Başlatılıyor ---" << std::endl;
    
    // ENV değişkenlerinden bağlantı bilgilerini oku
    DatabaseManager dbManager;
    
    // DB bağlantısı kontrolü
    if (!dbManager.isConnected()) {
        std::cerr << "[WARNING] Veritabanı bağlantısı yok! Bazı işlemler çalışmayabilir." << std::endl;
        std::cerr << "[INFO] DB_HOST, DB_PORT, DB_NAME, DB_USER, DB_PASSWORD değişkenlerini kontrol edin." << std::endl;
    }
    
    int choice;
    bool running = true;
    
    while (running) {
        printMenu();
        std::cin >> choice;
        
        // Input buffer temizleme
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                handleInsert(dbManager);
                break;
            case 2:
                handleList(dbManager);
                break;
            case 3:
                handleSearchById(dbManager);
                break;
            case 4:
                handleSearchByNumber(dbManager);
                break;
            case 5:
                handleDelete(dbManager);
                break;
            case 6:
                handleUpdateGrade(dbManager);
                break;
            case 7:
                handleCalculateGPA(dbManager);
                break;
            case 0:
                std::cout << "Çıkılıyor..." << std::endl;
                running = false;
                break;
            default:
                std::cout << "Geçersiz seçim! Lütfen tekrar deneyin." << std::endl;
                break;
        }
    }
    
    std::cout << "\n--- Sistem Kapatılıyor ---" << std::endl;
    return 0;
}
