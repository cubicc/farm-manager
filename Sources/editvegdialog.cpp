#include "editvegdialog.h"
#include "ui_editvegdialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"

editVegDialog::editVegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editVegDialog)
{
    ui->setupUi(this);
}

editVegDialog::~editVegDialog()
{
    delete ui;
}

void editVegDialog::on_buttonBox_accepted()
{
    QString a = ui->Prenumber->text();
    QByteArray b = a.toUtf8();
    char *Prenumberr = b.data();
     int Prenumber = atoi(Prenumberr);

    QString c = ui->code->text();
     QByteArray d = c.toUtf8();
    char *code = d.data();

    QString e = ui->name->text();
    QByteArray f = e.toUtf8();
    char *name = f.data();

    QString g = ui->vegN->text();
    QByteArray h = g.toUtf8();
    char *vegN = h.data();

    if(Prenumberr[0] == '\0'){
        ui->label->setText("蔬菜编号不能为空！");
        return;
    }
    if(code[0] == '\0' && name[0] == '\0' && vegN[0] == '\0'){
        ui->label->setText("未提供新修改信息！");
        return;
    }

    category *p = totalHead->next;
    vegetable *q = NULL;    //该蔬菜的位置
    category *ca = NULL;    //新种类
    category *preca = NULL; //该蔬菜之前所在的种类
    while(p != NULL){
        if(code[0] != '\0' && code[0] == p->code) ca = p;
        vegetable *vege = p->vegenext;
        while(vege != NULL){
            if(vege->number == Prenumber){
                q = vege;
                preca = p;
                vege = vege->next;
                continue;
            }
            if(strcmp(vege->name,name) == 0){
                ui->label->setText("蔬菜名已存在，修改失败！");
                return;
            }

            vege = vege->next;
        }
        p = p->next;
    }

    if(q == NULL){
        ui->label->setText("未找到蔬菜编号，修改失败！");
        return;
    }

    //如果分类码不为空，则需要将蔬菜所属分类移动
    if(code[0] != '\0' && ca == NULL){
        ui->label->setText("分类编号不存在，修改失败！");
        return;
    }
    if(code[0] != '\0'){
        vegetable *vege = ca->vegenext;
        if(vege == NULL){
            ca->vegenext = q;
        }
        else{
            while(vege->next != NULL){
                vege = vege->next;
            }
            vege->next = q;
        }

        //将该蔬菜从原来的种类里分离
        vege = preca->vegenext;
        if(vege == q){
            preca->vegenext =  q->next;
        }
        else{
                while(vege->next != q){

                    vege = vege->next;
                }
            vege->next = q->next;
        }

        q->next = NULL;

    }

    q->category = code[0];
   if(name[0] != '\0') strcpy(q->name,name);
   if(vegN[0] != '\0') strcpy(q->nutrientContent,vegN);
    ui->label->setText("修改成功！");


}
