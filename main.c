#include <stdio.h>
#include <stdlib.h>

void addRepair() {
    int Cost;
    char RepairID[4],Carmodel[50],RPDetails[200];
    printf("\nรหัสการซ่อมแซม; ");
    scanf("%s", RepairID);
    printf("\nชื่อรถยนต์; ");
    scanf("%s", Carmodel);
    printf("\nรายละเอียดการซ่อม; ");
    scanf("%s", RPDetails);
    printf("\nค่าใช้จ่าย; ");
    scanf("%d", Cost);

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