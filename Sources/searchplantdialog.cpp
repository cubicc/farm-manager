#include "searchplantdialog.h"
#include "ui_searchplantdialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"
#include "string.h"

searchPlantDialog::searchPlantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchPlantDialog)
{
    ui->setupUi(this);
}

searchPlantDialog::~searchPlantDialog()
{
    delete ui;
}

void searchPlantDialog::on_buttonBox_accepted()
{
    QString a = ui->vegYear->text();
    QByteArray b = a.toUtf8();
    char *vegYear = b.data();

    QString c = ui->vegName->text();
    QByteArray d = c.toUtf8();
    char *vegName = d.data();

    category* p = totalHead->next;
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal,"蔬菜编号");
    model->setHeaderData(1,Qt::Horizontal,"蔬菜名称");
    model->setHeaderData(2,Qt::Horizontal,"种植编号");
    model->setHeaderData(3,Qt::Horizontal,"种植面积");
    model->setHeaderData(4,Qt::Horizontal,"收获重量");
    model->setHeaderData(5,Qt::Horizontal,"种植年份");

    int count = 0;
    while(p != NULL){
        vegetable* vege = p->vegenext;
        while(vege != NULL){
            if(vegName != NULL && KMP(vege->name,vegName) == false){
                vege = vege->next;
                continue;
            }
            plant *pla = vege->plantnext;
            while(pla != NULL){
                if(vegYear != NULL && strcmp(vegYear,pla->month) == 0){
                    pla =pla->next;
                    continue;
                }
                model->setItem(count,0,new QStandardItem(QString::number(vege->number,10)));
                model->setItem(count,1,new QStandardItem(vege->name));
                model->setItem(count,2,new QStandardItem(QString::number(pla->number,10)));
                model->setItem(count,3,new QStandardItem(QString::number(pla->plantArea,10)));
                char buffer[50];
                memset(buffer,0,sizeof(buffer));
                sprintf(buffer,"%.2f",pla->weight);
                model->setItem(count,4,new QStandardItem(buffer));
                model->setItem(count,5,new QStandardItem(pla->month));
                count++;
                pla = pla->next;
            }

            vege = vege->next;
        }
        p = p->next;
    }
    if(count) ui->label_3->setText("查找成功！");
    else ui->label_3->setText("查找失败！");
    ui->tableView->setModel(model);
}
