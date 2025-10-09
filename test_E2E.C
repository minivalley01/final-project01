#include <stdio.h>
#include <assert.h>
#include "main.h"
#include "test.h"

#define TEST_FILE "test_data.csv"

// สร้างไฟล์ test หากยังไม่มี
void ensureTestFileExists(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fp = fopen(filename, "w");
        if (fp) {
            printf("สร้างไฟล์ %s สำเร็จ\n", filename);
            fclose(fp);
        } else {
            printf("❌ ไม่สามารถสร้างไฟล์ %s ได้\n", filename);
        }
    } else {
        fclose(fp);
    }
}

// ฟังก์ชันช่วยเพิ่มข้อมูลโดยไม่ต้องกรอก stdin
void addRepairToFile(const char* filename, const char* ID, const char* Car,
                     const char* Details, int Expense) {
    FILE *fp = fopen(filename, "a");
    fprintf(fp, "%s,%s,%s,%d,1\n", ID, Car, Details, Expense);
    fclose(fp);
}
void runE2ETest() {
    printf("=== รัน E2E Test ===\n");

    // 1️⃣ เพิ่มข้อมูล
    addRepairToFile(TEST_FILE, "R999", "Honda Jazz", "Replace tires", 3000);
    assert(checkID(TEST_FILE, "R999") == 1); // ซ้ำ

    // 2️⃣ อัพเดตข้อมูล
    updateRepair(TEST_FILE, "R999", "Honda Jazz", "Replace engine", 5000);

    // 3️⃣ ลบข้อมูล
    deleteRepair(TEST_FILE, "R999");

    // 4️⃣ ตรวจสอบว่า status = 0
    struct Record records[MAX_RECORDS];
    int count = loadData(records, TEST_FILE);
    int found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].id, "R999") == 0) {
            found = i;
            break;
        }
    }
    assert(found != -1);
    assert(records[found].status == 0);

    // 5️⃣ กู้คืนข้อมูล
    restoreRepair(TEST_FILE, "R999");

    // 6️⃣ ตรวจสอบว่า status = 1
    count = loadData(records, TEST_FILE);
    found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].id, "R999") == 0) {
            found = i;
            break;
        }
    }
    assert(found != -1);
    assert(records[found].status == 1);

    printf("✅ E2E Test ผ่านทั้งหมด\n");
}


int main() {
    ensureTestFileExists(TEST_FILE);
    runE2ETest();

    return 0;
}