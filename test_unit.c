#include <assert.h>
#include <stdio.h>
#include "main.h"
#include "test.h"



void ensureTestFileExists(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        fp = fopen(filename, "w");
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
void runUnitTests() {
    printf("=== รัน Unit Tests ===\n");
    test_checkID();
    test_addRepair();
    
    printf("✅ Unit Tests เสร็จสิ้น\n");
}

void test_checkID() {
    const char* testFile = "test_data.csv";
    assert(checkID(testFile, "A001") == 1);
    assert(checkID(testFile, "ZZZZ") == 0);
    printf("✅ test_checkID ผ่านแล้ว\n");
}

void test_addRepair() {
    const char* testFile = "test_data.csv";
    addRepairToFile(testFile, "B999", "Honda Jazz", "Replace tires", 3000);
    assert(checkID(testFile, "B999") == 1);
    printf("✅ test_addRepair ผ่านแล้ว\n");
}

int main() {
    const char *testFile = "test_data.csv";
    ensureTestFileExists(testFile); 
    runUnitTests(); 
    return 0;
}