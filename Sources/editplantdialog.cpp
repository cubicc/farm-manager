#include "editplantdialog.h"
#include "ui_editplantdialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"

editPlantDialog::editPlantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editPlantDialog)
{
    ui->setupUi(this);
}

editPlantDialog::~editPlantDialog()
{
    delete ui;
}

void editPlantDialog::on_buttonBox_accepted()
{
    QString a = ui->prenumber->text();
    QByteArray b = a.toUtf8();
    char *prenumberr = b.data();
    int prenumber = atoi(prenumberr);

    QString c = ui->vegN->text();
     QByteArray d = c.toUtf8();
    char *vegNN = d.data();
    int vegN = atoi(vegNN);

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

    if(prenumberr[0] == '\0'){
        ui->label->setText("种植编号不能为空！");
        return;
    }
    if(vegNN[0] == '\0' && plantAA[0] == '\0' && plantWW[0] == '\0' && plantY[0] == '\0'){
        ui->label->setText("未提供新修改信息！");
        return;
    }

    category *p = totalHead->next;
    vegetable *preVeg = NULL; //种植信息原来的蔬菜位置
    vegetable *Veg = NULL;  //新位置
    plant *q = NULL;
    while(p != NULL){
        vegetable *vege = p->vegenext;
        while(vege != NULL){
            if(vegNN[0] != '\0' && vege->number == vegN){
                Veg = vege;

            }
            plant *pla = vege->plantnext;

            while(pla != NULL){
                if(pla->number == prenumber){
                    preVeg = vege;
                    q = pla;
                    break;
                }
                pla = pla->next;
            }
            vege = vege->next;
        }
        p = p->next;
    }

    if(q == NULL){
        ui->label->setText("未找到种植编号，修改失败！");
    }
    //修改蔬菜编号
    if(vegN != 0 && Veg == NULL){
        ui->label->setText("蔬菜编号无效，修改失败！");
        return;
    }
    if(vegN != 0){
        plant *pla = Veg->plantnext;
        if(pla == NULL){
            Veg->plantnext = q;
        }
        else{
            while(pla->next != NULL)
                pla = pla->next;
            pla->next = q;
        }

        pla = preVeg->plantnext;
        if(pla == q){
            preVeg->plantnext = q->next;
        }
        else{
            while(pla->next != q)
                pla = pla->next;
            pla->next = q->next;
        }
        q->next = NULL;
    }

    if(plantAA[0] != '\0') q->plantArea = plantA;
    if(plantWW[0] != '\0') q->weight = plantW;
    if(plantY[0] != '\0') strcpy(q->month,plantY);
    q->vegetableNumber = vegN;
    ui->label->setText("修改成功！");


}
