#include "Load.h"
#include "stdio.h"
#include "struct.h"
#include "string.h"

 category *totalHead = NULL;
int vegNumber = 0;
int plantNumber = 0;
int cateNumber = 0;
char* quitLF(char *result){
    int i = 0;
    if(result == NULL) return result;
    for(;result[i] != '\0';i++){
        if(result[i] == '\n'){
            result[i] = '\0';
            return result;
        }
    }
    return result;
}//消去字符串结尾的回车字符

vegetable* findVegetableName(char *name,category *head){
    head = head->next;
    while(head != NULL){
       vegetable *p = head->vegenext;
       while(p != NULL){
           if(strcmp(p->name,name)==0) return p;
           p = p->next;
       }
       head = head->next;
    }

}//在链表中找到指向对应名字蔬菜的指针

vegetable* findVegetableNumber(int number,category *head){
    head = head->next;
    while(head != NULL){
       vegetable *p = head->vegenext;
       while(p != NULL){
           if(p->number == number) return p;
           p = p->next;
       }
       head = head->next;
    }

}//在链表中找到指向对应编号蔬菜的指针



category* load(const char *file1,const char *file2,const char *file3){
    FILE *fp;
    category *head = (category*)malloc(sizeof(category));
    head->next = NULL;
    category *q = head;

    //蔬菜分类数据的读取写入
    fp = fopen(file1,"r");
    if(!fp) return NULL;
    char buf[200];
    char *result = NULL;
    int i = 0;
    while(fgets(buf,200,fp) != NULL){

        if(i == 0){
            i++;
            continue;
        }
        i = 1;
        result = strtok(buf,","); result = quitLF(result);
        category *p = (category*)malloc(sizeof(category));
        p->next = NULL;
        q->next = p;
        p->code = result[0];
        result = strtok(NULL,","); result = quitLF(result);
        strcpy(p->name,result);
        vegetable *vegepoint = NULL;

        while(result != NULL){
                result = strtok(NULL,",");
                result = quitLF(result);
                if(result == NULL|| result[0] == '\n' ||result[0] == '\0') break;
                vegetable *newnode = (vegetable*)malloc(sizeof(vegetable));
                newnode->category = p->code;
                newnode->next = NULL;
                newnode->plantnext = NULL;
                strcpy(newnode->name,result);
                cateNumber++;
                if(i == 1){
                    p->vegenext = newnode;
                    vegepoint = newnode;
                    i++;
                }
                else{
                    vegepoint->next = newnode;
                    vegepoint = vegepoint->next;
                }
        }

        q = q->next;
    }


    //蔬菜信息的读取写入
    fp = fopen(file2,"r");
    i = 0;
    while(fgets(buf,200,fp) != NULL){
        if(i == 0){
            i++;
            continue;
        }
        result = strtok(buf,","); result = quitLF(result);
        result = strtok(NULL,","); result = quitLF(result);
        vegetable *vegepoint = findVegetableName(result,head);
        vegepoint->number = i;
        i++;
        result = strtok(NULL,","); result = quitLF(result);
        result = strtok(NULL,","); result = quitLF(result);
        strcpy(vegepoint->nutrientContent,result);
    }
    vegNumber = i;


    //菜农种植信息的读取写入
    fp = fopen(file3,"r");
    i = 0;
    while(fgets(buf,200,fp) != NULL){
        if(i == 0){
            i++;
            continue;
        }
        result = strtok(buf,","); result = quitLF(result);
        result = strtok(NULL,","); result = quitLF(result);
        vegetable *vegepoint = findVegetableNumber(atoi(result),head);
        plant *newnode = (plant*)malloc(sizeof(plant));
        //该蔬菜的种植信息链为空,则直接将其连接到该蔬菜指向种植的指针上
        if(vegepoint->plantnext == NULL){
            vegepoint->plantnext = newnode;
        }
        //否则，沿种植信息链寻找最后一个种植信息
        else{
            plant *p = vegepoint->plantnext;
            while(p->next != NULL){
                p = p->next;
            }
            p->next = newnode;
        }
        newnode->next = NULL;
        newnode->number = i; i++;
        newnode->vegetableNumber = vegepoint->number;
        result = strtok(NULL,","); result = quitLF(result);
        newnode->plantArea = atoi(result);
        result = strtok(NULL,","); result = quitLF(result);
        newnode->weight = atof(result);
        result = strtok(NULL,","); result = quitLF(result);
        strcpy(newnode->month,result);
    }
    plantNumber = i;
    fclose(fp);
    return head;
}//从硬盘中读取数据创建链表数据结构






