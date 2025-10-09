#ifndef MAIN_H
#define MAIN_H

#define MAX_RECORDS 100

struct Record {
    char id[20];
    char model[50];
    char problem[200];
    int cost;
    int status; 

};
int loadData(struct Record records[], const char *filename);
int checkID(const char* filename, const char* id);
void addRepair();

#endif
