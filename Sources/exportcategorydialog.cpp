#include "exportcategorydialog.h"
#include "ui_exportcategorydialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "searchvegedialog.h"
#include "stdio.h"
#include <QTextCodec>
#include "string"

exportCategoryDialog::exportCategoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportCategoryDialog)
{
    ui->setupUi(this);
}

exportCategoryDialog::~exportCategoryDialog()
{
    delete ui;
}

void exportCategoryDialog::on_buttonBox_accepted()
{
    QString a = ui->lineEdit->text();
    QByteArray b = a.toUtf8();
    char *yearr = b.data();
     int year = atoi(yearr);
     if(yearr[0] == '\0'){
         ui->label->setText("年份不能为空！");
         return;
     }
     struct totaldata{
       category *ca = NULL;
       int plantA = 0;
       float plantW = 0;
     };

     struct totaldata data[10];
     int i = 0;
     int flag = 0;
     category *p = totalHead->next;
     while(p != NULL){
         data[i].ca = p;
         vegetable *vege = p->vegenext;
         while(vege != NULL){
             plant *pla = vege->plantnext;
             while(pla != NULL){
                 if(atoi(pla->month) == year){
                     flag = 1;

                     data[i].plantA += pla->plantArea;
                     data[i].plantW += pla->weight;
                 }
                 pla =pla->next;
             }
             vege = vege->next;
         }
         p = p->next;
         i++;
     }

     if(!flag){
         ui->label->setText("年份无效！");
         return;
     }

     //保存到文件中
     FILE *fp;
     QTextCodec *code = QTextCodec::codecForName("GB2312");
     std::string name = code->fromUnicode(QString("按年份各类蔬菜信息统计表.csv")).data();
     fp = fopen(name.c_str(),"w");
     fputc(0xEF,fp);
      fputc(0xBB,fp);
       fputc(0xBF,fp);
        fputc(0,fp);
     fputs("年份,分类名称,种植面积,收获重量,\n",fp);
     for(int j = 0; j < i;j++){
         fputs(yearr,fp);
         fputc(',',fp);
         fputs(data[j].ca->name,fp);
         fputc(',',fp);
         char buf[20] = {0};
         sprintf(buf,"%d",data[j].plantA);
         fputs(buf,fp);
         fputc(',',fp);
         memset(buf,0,sizeof(buf));
         sprintf(buf,"%.2f",data[j].plantW);
         fputs(buf,fp);
         fputc('\n',fp);
     }

    fclose(fp);
     //显示
     QStandardItemModel *model = new QStandardItemModel(this);
     model->setColumnCount(4);
     model->setHeaderData(0,Qt::Horizontal,"年份");
     model->setHeaderData(1,Qt::Horizontal,"分类名称");
     model->setHeaderData(2,Qt::Horizontal,"种植面积");
     model->setHeaderData(3,Qt::Horizontal,"收获重量");
     for(int j = 0; j < i;j++){
         model->setItem(j,0,new QStandardItem(yearr));
         model->setItem(j,1,new QStandardItem(data[j].ca->name));
         char buf[20] = {0};
         sprintf(buf,"%d",data[j].plantA);
         model->setItem(j,2,new QStandardItem(buf));
         memset(buf,0,sizeof(buf));
         sprintf(buf,"%.2f",data[j].plantW);
         model->setItem(j,3,new QStandardItem(buf));
     }
     ui->tableView->setModel(model);
     ui->label->setText("保存成功！");

}
