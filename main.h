#ifndef MAIN_H
#define MAIN_H

#define MAX_RECORDS 100
#define MAX_LINE 256


struct Record {
    char id[20];
    char model[50];
    char problem[500];
    int cost;
    int status; // 1=active, 0=deleted
};

int confirmAction(const char *message);
int hasLetterCount(const char *str, int minLetters);
int hasLetter(const char *s);
int getIntegerInput(const char *message);
void toUpperStr(char *str);
void strToLower(char *str);
void trim(char *str);
int loadData(struct Record records[], const char *filename);
void saveData(struct Record records[], int count, const char *filename);
void printTable(struct Record records[], int count, const char *filename);
void printDeletedRecords(struct Record records[], int count);
int checkID(const char *filename, const char *ID);
void addRepairToFile(const char* filename, const char* ID,
                     const char* CarModel, const char* Details, int Cost);
void addRepair();
void searchRepair();
void updateRepair(const char *filename);
void deleteRepair(const char *filename);
void restoreRepair(const char *filename);
void deleteOrRestoreMenu();

#endif
