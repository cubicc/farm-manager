#include "deleteplantdialog.h"
#include "ui_deleteplantdialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"

deletePlantDialog::deletePlantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deletePlantDialog)
{
    ui->setupUi(this);
}

deletePlantDialog::~deletePlantDialog()
{
    delete ui;
}

void deletePlantDialog::on_buttonBox_accepted()
{
    QString a = ui->lineEdit->text();
    QByteArray b = a.toUtf8();
    char *code = b.data();
    int number = atoi(code);

    if(code[0] == '\0'){
        ui->label->setText("种植编号不能为空！");
        return;
    }

    category *p =totalHead->next;
    int flag = 0;
    while(p != NULL){
        vegetable *vege = p->vegenext;
        while(vege != NULL){
            plant *pla = vege->plantnext;
            if(pla == NULL){
                vege = vege->next;
                continue;
            }
            if(pla->number == number){
                flag  = 1;
                vege->plantnext = pla->next;
                break;
            }
            while(pla->next != NULL){
                if(pla->next->number == number){
                    flag = 1;
                    pla->next = pla->next->next;
                    break;
                }
                pla = pla->next;

            }
        vege = vege->next;
        }
    p = p->next;
    }

    if(!flag){
        ui->label->setText("未找到种植编号，删除失败！");
        return;
    }

     ui->label->setText("删除成功！");
}
