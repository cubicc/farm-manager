#include "searchvegedialog.h"
#include "ui_searchvegedialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>

void Next(char*T,int *next){
    int i=1;
    next[1]=0;
    int j=0;
    while (i<strlen(T)) {
        if (j==0||T[i-1]==T[j-1]) {
            i++;
            j++;
            next[i]=j;
        }else{
            j=next[j];
        }
    }
}
bool KMP(char* S,char* T){
    if(S == NULL|| S[0]== '\0') return false;
    int next[10];
        Next(T,next);//根据模式串T,初始化next数组
        int i=1;
        int j=1;
        while (i<=strlen(S)&&j<=strlen(T)) {
            //j==0:代表模式串的第一个字符就和当前测试的字符不相等；S[i-1]==T[j-1],如果对应位置字符相等，两种情况下，指向当前测试的两个指针下标i和j都向后移
            if (j==0 || S[i-1]==T[j-1]) {
                i++;
                j++;
            }
            else{
                j=next[j];//如果测试的两个字符不相等，i不动，j变为当前测试字符串的next值
            }
        }
        if (j>strlen(T)) {//如果条件为真，说明匹配成功
            return true;
        }
        return false;
}

searchVegeDialog::searchVegeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchVegeDialog)
{
    ui->setupUi(this);
}

searchVegeDialog::~searchVegeDialog()
{
    delete ui;
}

void searchVegeDialog::on_buttonBox_accepted()
{
    QString a = ui->vegCode->text();
    QByteArray b = a.toUtf8();
    char *vegCode = b.data();

    QString c = ui->vegName->text();
     QByteArray d = c.toUtf8();
    char *vegName = d.data();

    QString e = ui->vegN->text();
    QByteArray f = e.toUtf8();
    char *vegN = f.data();

    category* p = totalHead->next;
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,"蔬菜编号");
    model->setHeaderData(1,Qt::Horizontal,"蔬菜名称");
    model->setHeaderData(2,Qt::Horizontal,"分类码");
    model->setHeaderData(3,Qt::Horizontal,"营养成分");
    int count = 0;
    while(p != NULL){
        vegetable* vege = p->vegenext;

        if(vegCode != NULL && vegCode[0] != p->code){
            p = p->next;
            continue;
        }
        while(vege != NULL){
            if(vegName != NULL && KMP(vege->name,vegName) == false){
                vege = vege->next;
                continue;
            }
            if(vegN != NULL && KMP(vege->nutrientContent,vegN) == false){
                vege = vege->next;
                continue;
            }
            model->setItem(count,0,new QStandardItem(QString::number(vege->number,10)));
            model->setItem(count,1,new QStandardItem(vege->name));
            char buf[2];
            buf[0] = p->code;
            buf[1] = '\0';
            model->setItem(count,2,new QStandardItem(buf));
            model->setItem(count,3,new QStandardItem(vege->nutrientContent));
            count++;

            vege = vege->next;
        }
        p = p->next;
    }
    if(count) ui->label_2->setText("查找成功！");
    else ui->label_2->setText("查找失败！");
    ui->tableView->setModel(model);

}
