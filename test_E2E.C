#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "main.h"

#define E2E_FILE "test_e2e.csv"

void ensureTestFileExists(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fp = fopen(filename, "w");
        if (fp) {
            fclose(fp);
        } else {
            printf("❌ ไม่สามารถสร้างไฟล์ %s\n", filename);
        }
    } else fclose(fp);
}

void runE2ETests() {
    printf("=== รัน E2E Test ===\n");

    // ลบไฟล์เก่า
    remove(E2E_FILE);
    ensureTestFileExists(E2E_FILE);

    // 1️⃣ เพิ่มข้อมูล
    addRepairToFile(E2E_FILE, "R999", "Honda Jazz", "Replace tires", 3000);
    
    // ตรวจสอบ ID ถูกเพิ่ม
    assert(checkID(E2E_FILE, "R999") == 0); // 0 = ใช้ได้แล้ว ID ซ้ำ, อ้างอิง checkID ของคุณ
    printf("✅ Add Repair OK\n");

    // 2️⃣ อัพเดตข้อมูล
    updateRepair(E2E_FILE, "R999", "Honda Jazz", "Replace engine", 5000,1);

    // โหลดไฟล์และเช็คข้อมูล
    struct Record records[MAX_RECORDS];
    int count = loadData(records, E2E_FILE);
    int found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].id, "R999") == 0) {
            found = i;
            break;
        }
    }
    assert(found != -1);
    assert(strcmp(records[found].problem, "Replace engine") == 0);
    printf("✅ Update Repair OK\n");

    // 3️⃣ ลบข้อมูล
    deleteRepair(E2E_FILE, "R999",1);

    count = loadData(records, E2E_FILE);
    found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].id, "R999") == 0) {
            found = i;
            break;
        }
    }
    assert(found != -1);
    assert(records[found].status == 0);
    printf("✅ Delete Repair OK\n");

    // 4️⃣ กู้คืนข้อมูล
    restoreRepair(E2E_FILE, "R999",1);

    count = loadData(records, E2E_FILE);
    found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(records[i].id, "R999") == 0) {
            found = i;
            break;
        }
    }
    assert(found != -1);
    assert(records[found].status == 1);
    printf("✅ Restore Repair OK\n");

    printf("✅ E2E Test ผ่านทั้งหมด\n");
}

int main() {
    runE2ETests();
    return 0;
}
