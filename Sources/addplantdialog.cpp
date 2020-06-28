#include "addplantdialog.h"
#include "ui_addplantdialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"

addPlantDialog::addPlantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addPlantDialog)
{
    ui->setupUi(this);
}

addPlantDialog::~addPlantDialog()
{
    delete ui;
}

void addPlantDialog::on_buttonBox_accepted()
{
    QString a = ui->vegCode->text();
    QByteArray b = a.toUtf8();
    char *vegCodee = b.data();
    int vegCode = atoi(vegCodee);


    QString g = ui->plantA->text();
    QByteArray h = g.toUtf8();
    char *plantAA = h.data();
    int plantA = atoi(plantAA);

    QString i = ui->plantW->text();
    QByteArray j = i.toUtf8();
    char *plantWW = j.data();
    float plantW = atof(plantWW);

    QString k = ui->plantY->text();
    QByteArray l = k.toUtf8();
    char *plantY = l.data();

    if(vegCodee[0] == '\0'){
        ui->label_5->setText("蔬菜编号不能为空！");
        return;
    }

    if(plantAA[0] == '\0'){
        ui->label_5->setText("种植面积不能为空！");
        return;
    }

    if(plantWW[0] == '\0'){
        ui->label_5->setText("种植重量不能为空！");
        return;
    }

    if(plantY[0] == '\0'){
        ui->label_5->setText("种植年份不能为空！");
        return;
    }

    category *p = totalHead->next;
    while(p != NULL){
        vegetable *vege = p->vegenext;
        while(vege != NULL){
            if(vege->number == vegCode){//找到对应蔬菜
                plant *pla = vege->plantnext;
                if(pla == NULL){ //种植链为空
                    plant *newnode = (plant*)malloc(sizeof(plant));
                    strcpy(newnode->month,plantY);
                    newnode->next = NULL;
                    newnode->number = plantNumber; plantNumber++;
                    newnode->plantArea = plantA;
                    newnode->vegetableNumber = vegCode;
                    newnode->weight = plantW;
                    vege->plantnext = newnode;
                    ui->label_5->setText("录入成功！");
                    return;
                }

                while(pla->next != NULL){
                    pla = pla->next;
                }
                plant *newnode = (plant*)malloc(sizeof(plant));
                strcpy(newnode->month,plantY);
                newnode->next = NULL;
                newnode->number = plantNumber; plantNumber++;
                newnode->plantArea = plantA;
                newnode->vegetableNumber = vegCode;
                newnode->weight = plantW;
                pla->next = newnode;
                ui->label_5->setText("录入成功！");
                return;

            }
            vege = vege->next;
        }
        p = p->next;
    }

    //没有找到蔬菜
    ui->label_5->setText("没有找到对应蔬菜，录入失败！");
}
