#include "deletecategorydialog.h"
#include "ui_deletecategorydialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"


deleteCategoryDialog::deleteCategoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deleteCategoryDialog)
{
    ui->setupUi(this);
}

deleteCategoryDialog::~deleteCategoryDialog()
{
    delete ui;
}

void deleteCategoryDialog::on_buttonBox_accepted()
{
    QString a = ui->lineEdit->text();
    QByteArray b = a.toUtf8();
    char *code = b.data();

    if(code[0] == '\0'){
        ui->label->setText("种类编号不能为空！");
        return;
    }

    category *p = totalHead->next;

    if(p->code == code[0]){
        totalHead->next = p->next;
        free(p);
        ui->label->setText("删除成功！");
        return;
    }
    while(p->next != NULL){
        if(p->next->code == code[0]){
            category *q = p->next;
            p->next = p->next->next;
            free(q);
            ui->label->setText("删除成功！");
            return;
        }
        p = p->next;
    }

    ui->label->setText("未找到种类编号，删除失败！");


}
