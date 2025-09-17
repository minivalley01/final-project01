#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int checkID(char *ID) { //  เช็คไอดี
    
    if (strlen(ID) > 4 || strlen(ID) < 4) { //เช็คจำนวนตัวอักษร
        printf("RepairID is incorrect\n");
        return 0; 
        
        FILE *fp = fopen("data.csv", "r");
    if (fp == NULL) return 1; // ถ้าไฟล์ยังไม่มี ให้ผ่านไปเลย

    char line[300];                            //เช็คว่าซ้ำไหม
    while (fgets(line, sizeof(line), fp)) {
        char existingID[10];
        sscanf(line, "%d", existingID); // อ่านข้อมูลก่อนเครื่องหมาย , (คือ ID)
        if (strcmp(existingID, id) == 0) {
            printf("RepairID has been used\n");
            fclose(fp);
            return 0; // พบว่า ID ซ้ำ
        }
    }
    fclose(fp);
    return 1; // ไม่ซ้ำ
    }
    return 1; // ผ่านการตรวจสอบ
}




void addRepair() {
    int Expense;
    char ID[4],Car[50],Details[200];
    printf("\n1) ระบบเพิ่มข้อมูลการซ่อมเเซมใหม่");
    FILE *ADD = fopen("data.csv","a"); // เปิดไฟล์
    if (ADD == NULL) {
        printf("ERROR\n");
        return ;
    }
    while (1) {
      printf("\nRepairID; "); scanf("%s",&ID);
      if (checkID(ID)) {
        break; // ออกจากลูปเพราะ ID ถูกต้องแล้ว
        } else {
            printf("Try agin\n");
        }
    }
    printf("\nCarmodel; "); scanf("%s", &Car);
    printf("\nRepairdetails; "); scanf("%s", &Details);
    printf("\nCost; "); scanf("%d", &Expense);

    fprintf(ADD, "%s,%s,%s,%d\n", ID,Car,Details,Expense);
    
    fclose(ADD);
    printf("SUCCESS\n");
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
            //case 5: showRepair(); break;
            //case 0:
               // printf("ออกจากโปรแกรมแล้ว ขอบคุณที่ใช้งาน!\n");
                //exit(0);
            //default:
                //printf("เลือกเมนูไม่ถูกต้อง กรุณาลองใหม่\n");
        }
    }

    return 0;
}