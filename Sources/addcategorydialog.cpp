#include "addcategorydialog.h"
#include "ui_addcategorydialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"

addCategoryDialog::addCategoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addCategoryDialog)
{
    ui->setupUi(this);
}

addCategoryDialog::~addCategoryDialog()
{
    delete ui;
}

void addCategoryDialog::on_buttonBox_accepted()
{
    QString a = ui->code->text();
    QByteArray b = a.toUtf8();
    char *code = b.data();

    QString c = ui->name->text();
     QByteArray d = c.toUtf8();
    char *name = d.data();

    if(code[0] == '\0'){
        ui->label_3->setText("种类编号不能为空！");
        return;
    }

    if(name[0] == '\0'){
        ui->label_3->setText("种类名不能为空！");
        return;
    }
    category *p = totalHead;
    if(p->next == NULL){ //种类为空
        category *newnode = (category*)malloc(sizeof(category));
        newnode->code = code[0];
        strcpy(newnode->name,name);
        newnode->next = NULL;
        newnode->vegenext = NULL;
        p->next = newnode;
        ui->label_3->setText("录入成功！");
        cateNumber++;
        return;
    }
    p = p->next;

    //遍历，查看是否有重复
   while(p != NULL){
       if(p->code == code[0]){
           ui->label_3->setText("种类编号已存在，录入失败！");
           return;
       }
       if(strcmp(p->name,name) == 0){
           ui->label_3->setText("种类名已存在，录入失败！");
           return;
       }
       p = p->next;
   }


   p = totalHead;
    while(p->next != NULL){
        p = p->next;
    }


    category *newnode = (category*)malloc(sizeof(category));
    newnode->code = code[0];
    strcpy(newnode->name,name);
    newnode->next = NULL;
    newnode->vegenext = NULL;
    p->next = newnode;
    ui->label_3->setText("录入成功！");
    cateNumber++;
    return;


}
