#include <assert.h>
#include <stdio.h>
#include "main.h"




void ensureTestFileExists(const char* filename) {
    FILE* fp = fopen(filename, "r"); // ลองเปิดไฟล์อ่าน
    if (fp == NULL) {                // ถ้าเปิดไม่ได้ แปลว่าไฟล์ยังไม่มี
        fp = fopen(filename, "w");   // สร้างไฟล์ใหม่
        if (fp != NULL) {
            printf("สร้างไฟล์ %s สำเร็จ\n", filename);
            
            fclose(fp);
        } else {
            printf("❌ ไม่สามารถสร้างไฟล์ %s ได้\n", filename);
        }
    } else {
        fclose(fp); 
    }
}


void test_checkID() {
    const char* testFile = "test_data.csv";

    
    assert(checkID(testFile, "A001") == 1);

    
    assert(checkID(testFile, "ZZZZ") == 0);

    printf("✅ test_checkID ผ่านแล้ว\n");
}


void test_addRepair() {
    const char* testFile = "test_data.csv";

    
    addRepair(testFile, "B999", "Honda Jazz", "Replace tires", 3000);

    
    assert(checkID(testFile, "B999") == 1);

    printf("✅ test_addRepair ผ่านแล้ว\n");
}

int main() {
    
    const char* testFile = "test_data.csv";
    ensureTestFileExists(testFile);

    test_checkID();
    test_addRepair();
    return 0;

}

