#include "Store.h"
#include "ui_store.h"
#include "stdio.h"
#include "struct.h"
#include "string.h"
#include "Load.h"
#include "stdio.h"
#include <QTextCodec>



Store::Store(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Store)
{
    ui->setupUi(this);
    QTextCodec *cate = QTextCodec::codecForName("GB2312");
    std::string cate1 = cate->fromUnicode("蔬菜种类信息表.dat").data();
    QTextCodec *veg = QTextCodec::codecForName("GB2312");
    std::string veg1 = veg->fromUnicode("蔬菜基本信息表.dat").data();
    QTextCodec *pla = QTextCodec::codecForName("GB2312");
    std::string pla1 = pla->fromUnicode("菜农种植信息表.dat").data();
    if(store(totalHead,cate1.c_str(),veg1.c_str(),pla1.c_str()) == 1){
        ui->label->setText("文件保存成功！");

    }
    else{
        ui->label->setText("文件保存失败！");
    }

}

Store::~Store()
{
    delete ui;
}

int  store(category *head,const char *file1,const char *file2,const char *file3){
    FILE *fp;
    category *p = head->next;
    fp = fopen(file1,"w");
    fputc(0xEF,fp);
     fputc(0xBB,fp);
      fputc(0xBF,fp);
       fputc(0,fp);
    fputs("分类编号,分类名称,蔬菜名称\n",fp);
    while(p != NULL){
        vegetable *vegepoint = p->vegenext;
        fputc(p->code,fp);
        fputc(',',fp);
        fputs(p->name,fp);
        fputc(',',fp);
        while(vegepoint != NULL){
            fputs(vegepoint->name,fp);
            fputc(',',fp);
            vegepoint = vegepoint->next;
        }
        fputc('\n',fp);
        p = p->next;
    }
    fclose(fp);


    fp = fopen(file2,"w");
    fputc(0xEF,fp);
     fputc(0xBB,fp);
      fputc(0xBF,fp);
       fputc(0,fp);
    fputs("蔬菜编号,蔬菜名称,分类码,营养成分\n",fp);
    p = head->next;
    while(p != NULL){
        vegetable *vegepoint = p->vegenext;
        while(vegepoint != NULL){
            fputc(vegepoint->number + '0',fp);
            fputc(',',fp);
            fputs(vegepoint->name,fp);
            fputc(',',fp);
            fputc(p->code,fp);
            fputc(',',fp);
            fputs(vegepoint->nutrientContent,fp);
            fputc('\n',fp);
            vegepoint = vegepoint->next;
        }
        p = p->next;
    }
    fclose(fp);

    fp = fopen(file3,"w");
    fputc(0xEF,fp);
     fputc(0xBB,fp);
      fputc(0xBF,fp);
       fputc(0,fp);
    fputs("编号,蔬菜编号,种植面积,收获重量，种植年份\n",fp);
    p = head->next;
    while(p != NULL){
        vegetable *vegepoint = p->vegenext;
        while(vegepoint != NULL){
            plant *plantpoint = vegepoint->plantnext;
            while(plantpoint != NULL){
                fputc(plantpoint->number + '0',fp);
                fputc(',',fp);
                fputc(plantpoint->vegetableNumber + '0',fp);
                fputc(',',fp);
                fputc(plantpoint->plantArea + '0',fp);
                fputc(',',fp);
                char buffer[50];
                memset(buffer,0,sizeof(buffer));
                sprintf(buffer,"%.2f",plantpoint->weight);
                fputs(buffer,fp);

                fputc(',',fp);
                fputs(plantpoint->month,fp);
                fputc('\n',fp);
                plantpoint = plantpoint->next;
            }
            vegepoint = vegepoint->next;
        }
        p = p->next;
    }
    fclose(fp);

    return 1;

}//将数据写入硬盘中

void Store::on_Store_accepted(){

}
