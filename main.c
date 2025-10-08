#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LINE 256
#define MAX_RECORDS 100

struct Record {
    char id[20];
    char model[50];
    char problem[100];
    int cost;
};





int confirmAction(const char *message) {
    char choice1;

    while (1) {
        printf("%s (y/n): ", message);
        scanf(" %c", &choice1);  // มีช่องว่างหน้า %c เพื่อข้ามช่องว่างหรือ \n
        getchar();
        choice1 = tolower(choice1);  // แปลงเป็นตัวพิมพ์เล็กให้เทียบง่าย

        if (choice1 == 'y') {
            return 1;  // ยืนยัน
        } else if (choice1 == 'n') {
            return 0;  // ยกเลิก
        } else {
            printf("⚠️  กรุณากรอกแค่ y หรือ n เท่านั้น\n");
        }
    }
}
int hasLetterCount(const char *str, int minLetters) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            count++;
        }
    }
    return count >= minLetters;
}
int hasLetter(const char *s) {
    while (*s) {
        if (isalpha(*s)) return 1;
        s++;
    }
    return 0;
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
            printf("⚠️ กรุณากรอกเป็นตัวเลขเท่านั้น!\n");
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
void toUpperStr(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}
void strToLower(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}
void trim(char *str) {  // ตัด space/tab ข้างหน้าและข้างหลัง
    // ตัด space/tab ข้างหน้า
    char *p = str;
    while(*p && isspace(*p)) p++;
    memmove(str, p, strlen(p)+1);

    // ตัด space/tab ข้างหลัง
    int len = strlen(str);
    while(len > 0 && isspace(str[len-1])) {
        str[len-1] = 0;
        len--;
    }
}
int loadData(struct Record records[], const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("ไม่พบไฟล์ข้อมูล\n");
        return 0;
    }

    int count = 0;
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%[^,],%[^,],%[^,],%d",
               records[count].id,
               records[count].model,
               records[count].problem,
               &records[count].cost);
        count++;
    }
    fclose(fp);
    return count;
}
void saveData(struct Record records[], int count, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("ไม่สามารถบันทึกข้อมูลได้\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%d\n",
                records[i].id,
                records[i].model,
                records[i].problem,
                records[i].cost);
    }
    fclose(fp);
}
void printTable(struct Record records[], int count, const char *filename) {
    printf("\n--- ข้อมูลทั้งหมดจากไฟล์ %s ---\n", filename);
    printf("+----------+----------------------+--------------------------+------------+\n");
    printf("| RepairID | Car Model            | Repair Details           | Cost (฿)   |\n");
    printf("+----------+----------------------+--------------------------+------------+\n");
    for (int i = 0; i < count; i++) {
        printf("| %-8s | %-20s | %-24s | %-10d |\n",
               records[i].id,
               records[i].model,
               records[i].problem,
               records[i].cost);
    }
    printf("+----------+----------------------+--------------------------+------------+\n");


}





void addRepair() {
    int Expense;
    char ID[10], Car[100], Details[500];
    char choice;

    do {
        printf("\n1) ระบบเพิ่มข้อมูลการซ่อมเเซมใหม่\n");

        FILE *ADD = fopen("data.csv", "a"); 
        if (ADD == NULL) {
            printf("ERROR เปิดไฟล์ไม่สำเร็จ\n");
            return;
        }
        while (1) {
            printf("\nRepairID: "); 
            scanf("%s", ID);
            int c; while ((c = getchar()) != '\n' && c != EOF); 
            if (!hasLetter(ID)) {
                printf("❌ ID ต้องมีตัวอักษรอย่างน้อย 1 ตัว\n");
                continue;
            }
            toUpperStr(ID);

            if (checkID(ID)) {
                break; 
            } else {
                printf("Please try again\n");
            }
        }
        while (1) {
            printf("\nCar model: ");
            fgets(Car, sizeof(Car), stdin);
            Car[strcspn(Car, "\n")] = 0;
            if (!hasLetterCount(Car, 2)) {
                printf("❌ Car model ต้องมีอย่างน้อย 2 ตัวอักษร\n");
                continue;
            }
            break;
        }
        printf("\nRepair details {ใช้ |(vertical bar) ขั้นหากมีหลายกรณี}: ");  
        fgets(Details, sizeof(Details), stdin);
        Details[strcspn(Details, "\n")] = 0;
        while (1) {
            printf("\nCost: ");
            if (scanf("%d", &Expense) == 1) {
                if (Expense >= 0) break;
                else printf("❌ กรุณากรอกจำนวนที่มากกว่าหรือเท่ากับ 0\n");
            } else {
                printf("❌ กรุณากรอกตัวเลขเท่านั้น!\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
        }
        int c; while ((c = getchar()) != '\n' && c != EOF);
        fprintf(ADD, "%s,%s,%s,%d\n", ID, Car, Details, Expense);
        fclose(ADD);
        printf("✅ SUCCESS\n");
        printf("ต้องการเพิ่มข้อมูลอีกหรือไม่?(y/n): ");
        choice = getchar();
        while ((c = getchar()) != '\n' && c != EOF); 

    }while (choice == 'y' || choice == 'Y');
}
void searchRepair() {
    char keyword[50];
    char choice;
    do {
        printf("\n1) ระบบค้นหาข้อมูลการซ่อมเเซม\n");
        while (1) {
        printf("กรอกคีย์เวิร์ดค้นหา(ID/Car) อย่างน้อย 2 ตัว: ");
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = 0; // ตัด \n

        if (strlen(keyword) >= 2) break;  // ผ่านเงื่อนไข
        printf("❌ ต้องกรอกอย่างน้อย 2 ตัวอักษร!\n");
    }

    strToLower(keyword);

    FILE *fp = fopen("data.csv", "r");
    if (fp == NULL) {
        printf("❌ ไม่พบไฟล์ข้อมูล\n");
        return;
    }

    char line[512];
    int found = 0;

    // ANSI สี
    const char *BLUE   = "\033[1;34m";
    const char *YELLOW = "\033[1;33m";
    const char *RED    = "\033[1;31m";
    const char *CYAN   = "\033[1;36m";
    const char *RESET  = "\033[0m";

    // พิมพ์หัวตาราง **ครั้งเดียว**
    printf("%s| %-6s |%s %-15s |%s %-20s |%s %-8s |%s\n",
           BLUE, "RepairID", YELLOW, "Carmodel", RED, "Repairdetails", CYAN, "Cost(Bath)", RESET);
    printf("---------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        char ID[10], Model[50], Problem[200];
        int Cost;

        line[strcspn(line, "\n")] = 0; // ตัด \n

        if (sscanf(line, "%[^,],%[^,],%[^,],%d", ID, Model, Problem, &Cost) != 4)
            continue;

        trim(ID);
        trim(Model);
        trim(Problem);

        char ID_l[10], Model_l[50], Problem_l[200];
        strcpy(ID_l, ID); strToLower(ID_l);
        strcpy(Model_l, Model); strToLower(Model_l);

        if ((hasLetter(ID_l) && strstr(ID_l, keyword) != NULL) || strstr(Model_l, keyword) != NULL) {
            printf("%s| %-6s |%s %-15s |%s %-20s |%s %-8d |%s\n",
                   BLUE, ID, YELLOW, Model, RED, Problem, CYAN, Cost, RESET);
            found = 1;
        }
    }

    if (!found) {
        printf("❌ ไม่พบข้อมูลที่ตรงกับ \"%s\"\n", keyword);
    }

    fclose(fp);
    printf("ต้องการค้นหาต่อหรือไม่?(y/n): ");
    choice = getchar();
    while (getchar() != '\n'); // เคลียร์ buffer

    } while (choice == 'y' || choice == 'Y');
}
void updateRecord(const char *filename) {
    struct Record records[MAX_RECORDS];
    int count = loadData(records, filename);
    int choice;
    int c;
 do {
    if (count == 0) {
        printf("ไม่มีข้อมูลให้อัปเดต\n");
        return;
    }

    printTable(records, count, filename);
    

    // เลือกรายการที่จะอัปเดต
    char targetID[20];
    printf("\nกรอก RepairID ที่ต้องการอัปเดต: ");
    fgets(targetID, sizeof(targetID), stdin);
    targetID[strcspn(targetID, "\n")] = 0;
    toUpperStr(targetID);

    int found = -1;
    for (int i = 0; i < count; i++) {
        char tempID[20];
        strcpy(tempID, records[i].id);
        toUpperStr(tempID);
        if (strcmp(tempID, targetID) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("❌ ไม่พบ ID นี้ในระบบ\n");
        return;
    }

    printf("\n--- อัปเดตรายการ ID: %s ---\n", records[found].id);
    
    do {
        printf("RepairID: ");
        fgets(records[found].id, sizeof(records[found].id), stdin);
        records[found].id[strcspn(records[found].id, "\n")] = 0;
    } while (!hasLetter(records[found].id)&&(checkID(records[found].id)));
        if (checkID(records[found].id)) {
                break; 
            } else {
                printf("Please try again\n");
            }
    toUpperStr(records[found].id);

   
    do {
        printf("Car Model: ");
        fgets(records[found].model, sizeof(records[found].model), stdin);
        records[found].model[strcspn(records[found].model, "\n")] = 0;
    } while (!hasLetterCount(records[found].model,2));

    
    printf("Repair Details : ");
    fgets(records[found].problem, sizeof(records[found].problem), stdin);
    records[found].problem[strcspn(records[found].problem, "\n")] = 0;
    

    //(เฉพาะตัวเลข)
    char costStr[20];
    int validCost;
    do {
        validCost = 1;
        printf("Cost: ");
        fgets(costStr, sizeof(costStr), stdin);
        costStr[strcspn(costStr, "\n")] = 0;
        for (int i = 0; costStr[i]; i++) {
            if (!isdigit(costStr[i])) {
                validCost = 0;
                break;
            }
        }
    } while (!validCost);
    records[found].cost = atoi(costStr);

    saveData(records, count, filename);
    printf("\n✅ อัปเดตข้อมูลเรียบร้อยแล้ว!\n");
    printTable(records, count, filename);
    printf("ต้องการเพิ่มข้อมูลอีกหรือไม่? (y/n): ");
        choice = getchar();
        while ((c = getchar()) != '\n' && c != EOF);
    } while (choice == 'y' || choice == 'Y');
}






int main() {
    

    while(1) {
        printf("\n==== ระบบจัดการข้อมูลการซ่อมแซมรถยนต์ ====\n");
        printf("1) เพิ่มข้อมูลการซ่อมแซมใหม่\n");
        printf("2) ค้นหาข้อมูลการซ่อมเเซม\n");
        printf("3) อัพเดทข้อมูลการซ่อมแซม\n");
        printf("4) ลบข้อมูลการซ่อมแซม\n");
        printf("5) แสดงข้อมูลการซ่อมแซมทั้งหมด\n");
        printf("0) ออกจากโปรแกรม\n");
        int choice = getIntegerInput("กรุณาเลือกเมนูที่ต้องการ : ");

        switch (choice) {
            case 1: if (confirmAction("คุณต้องการเพิ่มข้อมูลการซ่อมเเซมใช่ไหม")) {
                        addRepair();
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
                        updateRecord("data.csv");
                        return 0;
                    } else {
                     printf("กำลังกลับไปหน้าเมนู...\n");
                    }
            break; 
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
