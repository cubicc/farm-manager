#include "staticvegdialog.h"
#include "ui_staticvegdialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"

staticVegDialog::staticVegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::staticVegDialog)
{
    ui->setupUi(this);
}

staticVegDialog::~staticVegDialog()
{
    delete ui;
}

void staticVegDialog::on_buttonBox_accepted()
{
    QString a = ui->lineEdit->text();
    QByteArray b = a.toUtf8();
    char *code = b.data();

    if(code[0] == '\0'){
        ui->label->setText("种类编号不能为空！");
        return;
    }

    category *p = totalHead->next;
    int totalA = 0;
    int flag = 0;
    while(p != NULL){
        if(p->code == code[0]){
            flag = 1;
            vegetable *vege = p->vegenext;
            while(vege != NULL){
                totalA ++;
                vege = vege->next;
            }
        }
        p = p->next;
    }
    if(!flag){
        ui->label->setText("种类编号无效！");
        return;
    }

    if(!totalA){
        ui->label->setText("该种蔬菜数量为0！");
        return;
    }
    char c[10];
    itoa(totalA,c,10);
    ui->label->setText("该种蔬菜的数量为" + QString(c));

}
