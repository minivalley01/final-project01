#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "test.h"







int main() {
    

    while(1) {
        printf("\n==== ระบบจัดการข้อมูลการซ่อมแซมรถยนต์ ====\n");
        printf("1) เพิ่มข้อมูลการซ่อมแซมใหม่\n");
        printf("2) ค้นหาข้อมูลการซ่อมเเซม\n");
        printf("3) อัพเดทข้อมูลการซ่อมแซม\n");
        printf("4) ลบ/กู้คืนข้อมูลการซ่อมแซม\n");
        printf("5) แสดงข้อมูลการซ่อมแซมทั้งหมด\n");
        printf("6) รัน Unit Test\n");
        printf("7) รัน E2E Test\n");
        printf("0) ออกจากโปรแกรม\n");
        int choice = getIntegerInput("กรุณาเลือกเมนูที่ต้องการ : ");

        switch (choice) {
            case 1: if (confirmAction("คุณต้องการเพิ่มข้อมูลการซ่อมเเซมใช่ไหม")) {
                        addRepair("data.csv");
                    } else {
                     printf("กำลังกลับไปหน้าเมนู\n");
                    }
            break; 
            case 2: if (confirmAction("คุณต้องการค้นหาข้อมูลการซ่อมเเซมใช่ไหม")) {
                        searchRepair();
                    } else {
                     printf("กำลังกลับไปหน้าเมนู...\n");
                    }
            break; 
            case 3: if (confirmAction("คุณต้องการอัพเดตข้อมูลการซ่อมเเซมใช่ไหม")) {
                        updateRepair("data.csv", NULL, NULL, NULL, -1);    
                    } else {
                     printf("กำลังกลับไปหน้าเมนู...\n");
                    }
            break; 
            case 4: if (confirmAction("คุณต้องการลบ/กู้คืนข้อมูลการซ่อมเเซมใช่ไหม")) {
                        deleteOrRestoreMenu("data.csv");    
                    } else {
                     printf("กำลังกลับไปหน้าเมนู...\n");
                    }
            break;
            case 5:{ struct Record records[MAX_RECORDS];
                    int count = loadData(records,"data.csv");
                    printTable(records,count,"data.csv");
            }
            break;
            case 6: if (confirmAction("คุณต้องการ Run unit_test ใช่ไหม")) {
                        runUnitTests();
                    } else {
                     printf("กำลังกลับไปหน้าเมนู\n");
                    }
            break;
            case 7: if (confirmAction("คุณต้องการ Run E2E_test ใช่ไหม")) {
                        runE2ETests();
                    } else {
                     printf("กำลังกลับไปหน้าเมนู\n");
                    }
            break;       
            case 0:if (confirmAction("คุณต้องการออกจากโปรเเกรมใช่ไหม")) {
                        printf("ออกจากโปรแกรมแล้ว ขอบคุณที่ใช้งาน!\n");
                        exit(0);
                    } else {
                     printf("กำลังกลับไปหน้าเมนู\n");
                    }
            default:
                printf("เลือกเมนูไม่ถูกต้อง กรุณาลองใหม่\n");
        }
    }

    return 0;
}
