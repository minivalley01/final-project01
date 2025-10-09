#ifndef MAIN_H
#define MAIN_H

#define MAX_RECORDS 100

struct Record {
    char id[20];
    char model[50];
    char problem[500];
    int cost;
    int status; // 1=active, 0=deleted
};

int loadData(struct Record records[], const char *filename);
int checkID(const char *filename, const char *ID);
void addRepair();

#endif
