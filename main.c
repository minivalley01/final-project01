#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  





int confirmAction(const char *message) {
    char choice;

    while (1) {
        printf("%s (y/n): ", message);
        scanf(" %c", &choice);  // มีช่องว่างหน้า %c เพื่อข้ามช่องว่างหรือ \n

        choice = tolower(choice);  // แปลงเป็นตัวพิมพ์เล็กให้เทียบง่าย

        if (choice == 'y') {
            return 1;  // ยืนยัน
        } else if (choice == 'n') {
            return 0;  // ยกเลิก
        } else {
            printf("⚠️  กรุณากรอกแค่ y หรือ n เท่านั้น\n");
        }
    }
}


int getIntegerInput(const char *message) { // ใช้ตรวจสอบว่าเป็นตัวเลขไหม
    char buffer[100];   // เก็บข้อความที่ผู้ใช้พิมพ์
    int isValid = 0;
    int number;

    while (!isValid) {
        printf("%s", message);
        fgets(buffer, sizeof(buffer), stdin);

        // ลบ \n ออกจาก buffer
        buffer[strcspn(buffer, "\n")] = 0;

        // ตรวจสอบว่าเป็นตัวเลขล้วนไหม
        isValid = 1;  // สมมติว่า valid
        for (int i = 0; i < strlen(buffer); i++) {
            if (!isdigit(buffer[i])) {  // ถ้ามีตัวที่ไม่ใช่ตัวเลข
                isValid = 0;
                break;
            }
        }

        if (isValid) {
            sscanf(buffer, "%d", &number);  // แปลงสตริงเป็น int
        } else {
            printf("⚠️ เมนูไม่ถูกต้อง กรุณาเลือกอีกครั้ง!\n");
        }
    }

    return number;
}




int checkID(char *ID) { //  เช็คไอดี
    FILE *fp = fopen("data.csv", "r");
    if (fp == NULL) return 1; // ถ้าไฟล์ยังไม่มี ให้ผ่านไปเลย
    if (strlen(ID) > 4 || strlen(ID) < 4) { //เช็คจำนวนตัวอักษร
        printf("RepairID is incorrect\n");
        return 0;
    }    
    char line[200];  //เช็คว่าซ้ำไหม
    while (fgets(line, sizeof(line), fp)) {
    char existingID[10];
    sscanf(line, "%[^,]", existingID); // อ่านข้อมูลก่อนเครื่องหมาย , 
    if (strcmp(existingID, ID) == 0) {
            printf("RepairID has already been used\n");
            return 0; 
        }
    }
    fclose(fp);
    return 1; // ไม่ซ้ำเเละผ่านการตรวจสอบ
}


void addRepair() {
    int Expense;
    char ID[10],Car[70],Details[200];
    printf("\n1) ระบบเพิ่มข้อมูลการซ่อมเเซมใหม่");
    FILE *ADD = fopen("data.csv","a"); 
    if (ADD == NULL) {
        printf("ERROR\n");
        return ;
    }
    while (1) {
      printf("\nRepairID; "); scanf("%s",ID);
      if (checkID(ID)) {
        break; // ออกจากลูป ID ถูกแล้ว
        } else {
            printf("Please try agin\n");
        }
    }
    printf("\nCar model: ");
    getchar(); // เคลียร์ buffer ก่อนหน้า
    fgets(Car, sizeof(Car), stdin);
    Car[strcspn(Car, "\n")] = 0; //เอา \n ออก
    printf("\nRepair details; ");  
    fgets(Details, sizeof(Details), stdin);
    Details[strcspn(Details, "\n")] = 0;
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
            case 0:
               printf("ออกจากโปรแกรมแล้ว ขอบคุณที่ใช้งาน!\n");
                exit(0);
            default:
                printf("เลือกเมนูไม่ถูกต้อง กรุณาลองใหม่\n");
        }
    }

    return 0;
}
