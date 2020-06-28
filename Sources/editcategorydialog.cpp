#include "editcategorydialog.h"
#include "ui_editcategorydialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"


editCategoryDialog::editCategoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editCategoryDialog)
{
    ui->setupUi(this);
}

editCategoryDialog::~editCategoryDialog()
{
    delete ui;
}

void editCategoryDialog::on_buttonBox_accepted()
{
    QString a = ui->Precode->text();
    QByteArray b = a.toUtf8();
    char *Precode = b.data();

    QString c = ui->code->text();
     QByteArray d = c.toUtf8();
    char *code = d.data();

    QString e = ui->name->text();
    QByteArray f = e.toUtf8();
    char *name = f.data();

    category *p = totalHead->next;
    category *q = NULL;

    if(Precode[0] == '\0'){
        ui->label->setText("种类编号不能为空！");
        return;
    }
    if(code[0] == '\0' && name[0] == '\0'){
        ui->label->setText("未提供新修改信息！");
        return;
    }



    while(p != NULL){
        if(Precode[0] == p->code){ //找到种类，保存指针
            q = p;
            p = p->next;
            continue;
        }
        if(code[0] == p->code){
            ui->label->setText("种类编号已存在，修改失败！");
            return;
        }
        if(strcmp(p->name,name) == 0){
            ui->label->setText("种类名已存在，修改失败！");
            return;
        }
        p = p->next;
    }

    if(q == NULL){
        ui->label->setText("未找到种类编号，修改失败！");
        return;
    }

    if(code[0] != '\0')   q->code = code[0];
    if(name[0] != '\0') strcpy(q->name,name);
    ui->label->setText("修改成功！");
}
