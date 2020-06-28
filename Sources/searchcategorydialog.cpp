#include "searchcategorydialog.h"
#include "ui_searchcategorydialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>

searchCategoryDialog::searchCategoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchCategoryDialog)
{
    ui->setupUi(this);
}

searchCategoryDialog::~searchCategoryDialog()
{
    delete ui;
}

void searchCategoryDialog::on_buttonBox_accepted()
{
    QString a = ui->lineEdit->text();
    QByteArray b = a.toUtf8();
    char *result = b.data();
    category* p = totalHead;
    int flag = 0;
    while(p != NULL){
        if(p->code == result[0]){
            flag = 1;
           ui->label_2->setText("查找成功！");
           QStandardItemModel *model = new QStandardItemModel(this);
           model->setItem(0,0,new QStandardItem(p->name));
           vegetable* vege = p->vegenext;
           for(int i = 1;vege != NULL;i++){
               model->setItem(0,i,new QStandardItem(vege->name));
               vege = vege->next;
           }
           ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
           ui->tableView->setModel(model);
           break;
        }
        p = p->next;
    }

    if(!flag){
        ui->label_2->setText("查找失败！");
    }
}
