#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "main.h"   // include header ที่ประกาศฟังก์ชัน checkID และ addRepair

void test_checkID() {
    // จำลองไฟล์ทดสอบ (คุณอาจต้องสร้างไฟล์ "test_data.csv" ไว้ก่อน)
    const char *testFile = "test_data.csv";

    // เคส ID ที่มีอยู่
    assert(checkID(testFile, "A001") == 1);

    // เคส ID ที่ไม่มีอยู่
    assert(checkID(testFile, "ZZZZ") == 0);

    printf("✅ test_checkID ผ่านแล้ว\n");
}

void test_addRepair() {
    const char *testFile = "test_data.csv";

    // เพิ่มข้อมูลใหม่
    addRepair(testFile, "B002", "เปลี่ยนยาง");

    // ตรวจสอบว่า ID ที่เพิ่มไปหาเจอหรือไม่
    assert(checkID(testFile, "B002") == 1);

    printf("✅ test_addRepair ผ่านแล้ว\n");
}

int main() {
    printf("===== เริ่มทดสอบ Unit Test =====\n");

    test_checkID();
    test_addRepair();

    printf("===== ✅ การทดสอบเสร็จสมบูรณ์ =====\n");
    return 0;
}
