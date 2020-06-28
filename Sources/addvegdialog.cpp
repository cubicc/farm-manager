#include "addvegdialog.h"
#include "ui_addvegdialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"

addVegDialog::addVegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addVegDialog)
{
    ui->setupUi(this);
}

addVegDialog::~addVegDialog()
{
    delete ui;
}

void addVegDialog::on_buttonBox_accepted()
{
    QString a = ui->vegCode->text();
    QByteArray b = a.toUtf8();
    char *vegCode = b.data();

    QString c = ui->vegName->text();
     QByteArray d = c.toUtf8();
    char *vegName = d.data();

    QString e = ui->vegN->text();
    QByteArray f = e.toUtf8();
    char *vegN = f.data();
 /*
    QString g = ui->plantA->text();
    QByteArray h = g.toUtf8();
    char *plantA = h.data();

    QString i = ui->plantW->text();
    QByteArray j = i.toUtf8();
    char *plantW = j.data();

    QString k = ui->plantY->text();
    QByteArray l = k.toUtf8();
    char *plantY = l.data();
 */
    if(vegCode[0] == '\0'){
        ui->label->setText("种类编号不能为空！");
        return;
    }
    if(vegName[0] == '\0'){
        ui->label->setText("蔬菜名不能为空！");
        return;
    }
    if(vegN[0] == '\0'){
        ui->label->setText("营养成分不能为空！");
        return;
    }

        category *p = totalHead->next;
        //遍历链表，查看有没有蔬菜名重复的蔬菜结点
        while(p != NULL){
            vegetable *vege = p->vegenext;
            while(vege != NULL){
                if(strcmp(vege->name,vegName) == 0){
                    ui->label->setText("该蔬菜已在表中，录入失败！");
                    return;
                }
                vege = vege->next;
            }
            p = p->next;
        }
        p = totalHead->next;

        //再次遍历，找到种类编号相同的蔬菜尾，添加结点
        while(p != NULL){
            if(p->code == vegCode[0]){
                vegetable *vege = p->vegenext;
                int flag = 0;
                    while(vege != NULL){
                        flag = 1;
                        if(vege->next == NULL) break; //到链表尾，在其后添加蔬菜信息
                        vege = vege->next;
                    }

                //录入信息
                vegetable *newnode = (vegetable*)malloc(sizeof(vegetable));
                newnode->category = p->code;
                strcpy(newnode->name,vegName);
                strcpy(newnode->nutrientContent,vegN);
                newnode->number = vegNumber; vegNumber++;
                newnode->next = NULL;
                newnode->plantnext = NULL;
                if(flag)
                    vege->next = newnode ;
                else
                    p->vegenext = newnode;
                ui->label->setText("录入成功！");
                return;
            }

            p = p->next;
        }

        ui->label->setText("未找到对应种类编号，录入失败！");
        return;
}
    /*
    //种植信息不为空则必须都不为空
    if(plantA == NULL){
        ui->label_8->setText("种植面积不能为空！");
        return;
    }
    if(plantW == NULL){
        ui->label_8->setText("种植重量不能为空！");
        return;
    }
    if(plantY == NULL){
        ui->label_8->setText("种植年份不能为空！");
        return;
    }
    */


