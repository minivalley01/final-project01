#include <stdio.h>
#include <stdlib.h>

void addRepair() {
    int Expense;
    char ID[4],Car[50],Details[200];
    printf("\n1) ระบบเพิ่มข้อมูลการซ่อมเเซมใหม่");
    printf("\nRepairID; "); scanf("%s", ID);
    printf("\nCarmodel; "); scanf("%s", Car);
    printf("\nRepairdetails; "); scanf("%s", Details);
    printf("\nCost; "); scanf("%d", Expense);
    



}


int main() {
    int choice;

    while(1) {
        printf("\n==== ระบบจัดการข้อมูลการซ่อมแซมรถยนต์ ====\n");
        printf("1) เพิ่มข้อมูลการซ่อมแซมใหม่\n");
        printf("2) ค้นหาข้อมูลการซ่อมเเซม\n");
        printf("3) อัพเดทข้อมูลการซ่อมแซม\n");
        printf("4) ลบข้อมูลการซ่อมแซม\n");
        printf("5) แสดงข้อมูลการซ่อมแซมทั้งหมด\n");
        printf("0) ออกจากโปรแกรม\n");
        printf("กรุณาเลือกเมนู: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addRepair(); break;
            //case 2: searchRepair(); break;
            //case 3: updateRepair(); break;
            //case 4: deleteRepair(); break;
            //case 5: deleteRepair(); break;
            //case 0:
               // printf("ออกจากโปรแกรมแล้ว ขอบคุณที่ใช้งาน!\n");
                //exit(0);
            //default:
                //printf("เลือกเมนูไม่ถูกต้อง กรุณาลองใหม่\n");
        }
    }

    return 0;
}