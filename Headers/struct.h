#ifndef STRUCT_H
#define STRUCT_H


typedef struct category{
    char code;
    char name[20];
    struct category *next;
    struct vegetable *vegenext;
}category;

typedef struct vegetable{
    int number = 0;
    char name[20];
    char category;
    char nutrientContent[100];
    struct vegetable *next;
    struct plant *plantnext;
}vegetable;

typedef struct plant{
    int number;
    int vegetableNumber;
    int plantArea;
    float weight;
    char month[5];
    struct plant *next;
}plant;

#endif // STRUCT_H
