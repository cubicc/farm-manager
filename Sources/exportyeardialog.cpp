#include "exportyeardialog.h"
#include "ui_exportyeardialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"
#include <QTextCodec>
#include "stdio.h"
#include "string"

exportYearDialog::exportYearDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportYearDialog)
{
    ui->setupUi(this);
}

exportYearDialog::~exportYearDialog()
{
    delete ui;
}

void exportYearDialog::on_buttonBox_accepted()
{
    QString e = ui->vegName->text();
    QByteArray f = e.toUtf8();
    char *name = f.data();

    QString a = ui->year->text();
    QByteArray b = a.toUtf8();
    char *yearr = b.data();
    int year = atoi(yearr);

    QString c = ui->endYear->text();
     QByteArray d = c.toUtf8();
    char *endYearr = d.data();
    int endYear = atoi(endYearr);

    if(yearr[0] == '\0'){
        ui->label->setText("起始年份不能为空！");
        return;
    }

    if(endYearr[0] == '\0'){
        ui->label->setText("终止年份不能为空！");
        return;
    }

    if(year > endYear){
        ui->label->setText("年份输入有误！");
        return;
    }

    category *p = totalHead->next;
    category *q = NULL;
    int flag = 0;
    int plantA[endYear-year + 1] = {0};
    float plantW[endYear - year + 1] = {0};
    while(p != NULL){
        vegetable* vege = p->vegenext;
        while(vege != NULL){
            if(strcmp(vege->name,name) == 0){
                flag = 1;
                q = p;
                plant *pla = vege->plantnext;
                while(pla != NULL){
                    if(atoi(pla->month) >= year && atoi(pla->month) <= endYear){
                        plantA[atoi(pla->month) - year] += pla->plantArea;
                        plantW[atoi(pla->month) - year] += pla->weight;
                    }
                    pla = pla->next;
                }

            }
            vege = vege->next;
        }
        p = p->next;
    }

    if(!flag){
        ui->label->setText("输入蔬菜无效！");
        return;
    }

    //显示
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(5);
    model->setHeaderData(0,Qt::Horizontal,"年份");
     model->setHeaderData(1,Qt::Horizontal,"蔬菜名称");
      model->setHeaderData(2,Qt::Horizontal,"分类名称");
       model->setHeaderData(3,Qt::Horizontal,"种植面积");
        model->setHeaderData(4,Qt::Horizontal,"收获总重量");
    for(int i = 0;i < endYear - year + 1;i++){
        char buf[20] = {0};
        sprintf(buf,"%d",i + year);
        model->setItem(i,0,new QStandardItem(buf));
         model->setItem(i,1,new QStandardItem(name));
          model->setItem(i,2,new QStandardItem(q->name));
          memset(buf,0,sizeof(buf));
          sprintf(buf,"%d",plantA[i]);
           model->setItem(i,3,new QStandardItem(buf));
           memset(buf,0,sizeof(buf));
           sprintf(buf,"%.2f",plantW[i]);
            model->setItem(i,4,new QStandardItem(buf));
    }
    ui->tableView->setModel(model);


    //保存
    FILE *fp;
    QTextCodec *code = QTextCodec::codecForName("GB2312");
    std::string file = code->fromUnicode(QString("按蔬菜名称统计信息表.csv")).data();
    fp = fopen(file.c_str(),"w");
    fputc(0xEF,fp);
     fputc(0xBB,fp);
      fputc(0xBF,fp);
       fputc(0,fp);
    fputs("年份,蔬菜名称,分类名称,种植面积,收获总重量\n",fp);
    for(int j = 0;j < endYear - year + 1;j++){
        char buf[20] = {0};
        sprintf(buf,"%d",j + year);
        fputs(buf,fp);
        fputc(',',fp);
        fputs(name,fp);
        fputc(',',fp);
        fputs(q->name,fp);
        fputc(',',fp);
        memset(buf,0,sizeof(buf));
        sprintf(buf,"%d",plantA[j]);
        fputs(buf,fp);

        fputc(',',fp);

        memset(buf,0,sizeof(buf));
        sprintf(buf,"%.2f",plantW[j]);
        fputs(buf,fp);
        fputc('\n',fp);
    }
    fclose(fp);
    ui->label->setText("保存成功！");
}
