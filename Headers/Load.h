#ifndef LOAD_H
#define LOAD_H

#include <QDialog>
#include "stdio.h"
#include "struct.h"
#include "string.h"

char* quitLF(char *result);
vegetable* findVegetableName(char *name,category *head);
vegetable* findVegetableNumber(int number,category *head);
category* load(const char *file1,const char *file2,const char *file3);

extern category *totalHead;
extern int vegNumber;
extern int plantNumber;
extern int cateNumber;



#endif // LOAD_H
