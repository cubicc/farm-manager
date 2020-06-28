#include "exportcustomdialog.h"
#include "ui_exportcustomdialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"
#include "stdio.h"
#include <QTextCodec>
#include "string"

ExportCustomDialog::ExportCustomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportCustomDialog)
{
    ui->setupUi(this);
}

ExportCustomDialog::~ExportCustomDialog()
{
    delete ui;
}

void ExportCustomDialog::on_buttonBox_accepted()
{
    QString a = ui->year->text();
    QByteArray b = a.toUtf8();
    char *yearr = b.data();

    QString c = ui->plantW->text();
     QByteArray d = c.toUtf8();
    char *plantWW = d.data();
    float plantW = atof(plantWW);

    QString e = ui->vegCode->text();
    QByteArray f = e.toUtf8();
    char *vegCode = f.data();

    QString g = ui->fileName->text();
    QByteArray h = g.toUtf8();
    char *fileName = h.data();

    if(fileName[0] == '\0'){
        ui->label->setText("文件路径不能为空！");
        return;
    }

    int mode = -1; //大于为1，等于为2，小于为3
    if(ui->Bigger->isChecked()){
        mode = 1;
    }
    else if(ui->Equal->isChecked()){
        mode = 2;
    }
    else if(ui->Smaller->isChecked()){
        mode = 3;
    }

    FILE *fp;
    QTextCodec *code = QTextCodec::codecForName("GB2312");
    std::string name = code->fromUnicode(g).data();
    fp = fopen(name.c_str(),"w");
    fputc(0xEF,fp);
     fputc(0xBB,fp);
      fputc(0xBF,fp);
       fputc(0,fp);
    fputs("种植年份,分类名,蔬菜名,种植面积,收获重量,\n",fp);

    category *p = totalHead->next;
    int i = 0;
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(5);
    model->setHeaderData(0,Qt::Horizontal,"种植年份");
    model->setHeaderData(1,Qt::Horizontal,"分类名");
    model->setHeaderData(2,Qt::Horizontal,"蔬菜名");
    model->setHeaderData(3,Qt::Horizontal,"种植面积");
    model->setHeaderData(4,Qt::Horizontal,"收获总重量");
    while(p != NULL){
        if(vegCode[0] == '\0' ||  strcmp(p->name,vegCode) == 0){
            vegetable *vege = p->vegenext;
            while(vege != NULL){
                plant *pla = vege->plantnext;
                int area = 0;
                float weight = 0;
                while(pla != NULL){
                    if(strcmp(yearr,pla->month) == 0){
                            area += pla->plantArea;
                            weight += pla->weight;

                    }
                    pla = pla->next;
                }

                int flag = 0;
                if(mode == 1){
                    if(weight > plantW)
                        flag = 1;
                }
                else if(mode == 2){
                    if(weight == plantW)
                        flag = 1;
                }
                else if(mode == 3){
                    if(weight < plantW)
                        flag = 1;
                }
                else
                    flag = 1;

                if(flag){//输出并保存
                    model->setItem(i,0,new QStandardItem(yearr));
                    fputs(yearr,fp); fputc(',',fp);
                    model->setItem(i,1,new QStandardItem(vegCode));
                    fputs(vegCode,fp); fputc(',',fp);
                    model->setItem(i,2,new QStandardItem(vege->name));
                    fputs(vege->name,fp); fputc(',',fp);
                    char  buf[50];
                    memset(buf,0,sizeof(buf));
                    sprintf(buf,"%d",area);
                     model->setItem(i,3,new QStandardItem(buf));
                     fputs(buf,fp); fputc(',',fp);
                     memset(buf,0,sizeof(buf));
                     sprintf(buf,"%.2f",weight);
                      model->setItem(i,4,new QStandardItem(buf));
                      fputs(buf,fp);fputc('\n',fp);
                      i++;

                }

                vege = vege->next;
            }


        }
        p = p->next;
    }
    fclose(fp);
    ui->tableView->setModel(model);
    ui->label->setText("保存成功！");
}

