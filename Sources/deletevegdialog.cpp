#include "deletevegdialog.h"
#include "ui_deletevegdialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"


deleteVegDialog::deleteVegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteVegDialog)
{
    ui->setupUi(this);
}

deleteVegDialog::~deleteVegDialog()
{
    delete ui;
}

void deleteVegDialog::on_buttonBox_accepted()
{
    QString a = ui->lineEdit->text();
    QByteArray b = a.toUtf8();
    char *code = b.data();
    int number = atoi(code);
    if(number == 0){
        ui->label->setText("蔬菜编号不能为空！");
        return;
    }
    int flag = 0;
    category *p = totalHead->next;
    while(p != NULL){
        vegetable *vege = p->vegenext;
        if(vege == NULL){
            p = p->next;
            continue;
        }
        if(vege->number == number){
            p->vegenext = vege->next;
            flag = 1;
            break;
        }

        while(vege->next != NULL){
            if(vege->next->number == number){
                vege->next = vege->next->next;
                flag = 1;
                break;
            }
            vege = vege->next;
        }
    p = p->next;
    }

    if(!flag){
        ui->label->setText("未找到蔬菜编号，修改失败！");
        return;
    }


    ui->label->setText("删除成功！");

}
