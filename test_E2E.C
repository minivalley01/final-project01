#include <stdio.h>
#include <assert.h>
#include "main.h"
#include "test.h"

#define E2E_FILE "test_e2e.csv"

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
void runE2ETests() {
    printf("=== รัน E2E Test ===\n");
    remove(E2E_FILE);
    // 1️⃣ เพิ่มข้อมูล
    addRepairToFile(E2E_FILE, "R999", "Honda Jazz", "Replace tires", 3000);
    assert(checkID(E2E_FILE, "R999") == 0); // ซ้ำ
    printf("✅ Add Repair OK\n");


    // 2️⃣ อัพเดตข้อมูล
    updateRepair(E2E_FILE, "R999", "Honda Jazz", "Replace engine", 5000);
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
    deleteRepair(E2E_FILE, "R999");
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

    
    // 5️⃣ กู้คืนข้อมูล
    restoreRepair(E2E_FILE, "R999");
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
    ensureTestFileExists(E2E_FILE);
    runE2ETests();
    

    return 0;
}