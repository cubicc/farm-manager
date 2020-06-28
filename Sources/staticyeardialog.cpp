#include "staticyeardialog.h"
#include "ui_staticyeardialog.h"
#include "Load.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include "QtCharts/QBarSet"
#include "QtCharts/QBarSeries"
#include "QtCharts/QBarCategoryAxis"
#include "QChart"
#include "QBarSet"
#include "QBarSeries"
#include "QChartView"
QT_CHARTS_USE_NAMESPACE

staticYearDialog::staticYearDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::staticYearDialog)
{
    ui->setupUi(this);
}

staticYearDialog::~staticYearDialog()
{
    delete ui;
}

void staticYearDialog::on_buttonBox_accepted()
{
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

    //统计某年各类蔬菜柱状图
    if(endYearr[0] == '\0'){
         struct totaldata{
            int plantASUm = 0;
            float plantWSum = 0;
            category *ca = NULL;
        };
       struct totaldata data[cateNumber];
        category *p = totalHead->next;
        int i = 0;
        int flag = 0;

        //统计某年各类蔬菜的面积，重量
        while(p != NULL){
            data[i].ca = p;
            vegetable *vege = p->vegenext;
            while(vege != NULL){
                plant *pla = vege->plantnext;
                while(pla != NULL){

                    if(year == atoi(pla->month)){
                        flag = 1;
                        data[i].plantASUm += pla->plantArea;
                        data[i].plantWSum += pla->weight;
                    }
                    pla = pla->next;
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

        //按照重量排序
        for(int j = 0; j < i - 1; j++){
            for(int k = 1; k < i - j; k++){
                if(data[k - 1].plantWSum < data[k].plantWSum){//交换
                    totaldata tmp = data[k - 1];
                    data[k - 1] = data[k];
                    data[k] = tmp;
                }
            }
        }

        //输出
        QStandardItemModel *model = new QStandardItemModel(this);
        model->setColumnCount(3);
        model->setHeaderData(0,Qt::Horizontal,"分类名称");
        model->setHeaderData(1,Qt::Horizontal,"种植面积");
        model->setHeaderData(2,Qt::Horizontal,"收获总重量");

        for(int j = 0; j < i; j++){
            model->setItem(j,0,new QStandardItem((*data[j].ca).name));
            model->setItem(j,1,new QStandardItem(QString::number(data[j].plantASUm,10)));
            char buffer[50];
            memset(buffer,0,sizeof(buffer));
            sprintf(buffer,"%.2f",data[j].plantWSum);
            model->setItem(j,2,new QStandardItem(buffer));
        }
        ui->tableView->setModel(model);


        //画柱状图
        QBarSeries *series = new QBarSeries();
         QStringList categories;
         QBarSet *set = new QBarSet("蔬菜");
        for(int j = 0; j < i; j++){
            *set << data[j].plantWSum;
             series->append(set);
             categories.append(QString(data[j].ca->name));
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("各类蔬菜收获重量柱状图（单位：kg）");
        chart->setAnimationOptions(QChart::SeriesAnimations);



        QBarCategoryAxis *axis = new QBarCategoryAxis();
            axis->append(categories);
            chart->createDefaultAxes();//创建默认的左侧的坐标轴（根据 QBarSet 设置的值）
            chart->setAxisX(axis, series);
            chart->legend()->setVisible(true); //设置图例为显示状态
            chart->legend()->setAlignment(Qt::AlignBottom);//设置图例的显示位置在底部
            QChartView *chartView = new QChartView(chart);
            chartView->resize(800,600);
            chartView->show();
            return;

    }

    //结束年份不为空，则统计起止年份内的蔬菜总面积
    if(endYear < year){
        ui->label->setText("年份无效！");
        return;
    }

    category *p = totalHead->next;
    struct totaldata{
       int plantASUm = 0;
       float plantWSum = 0;
       vegetable *veg = NULL;
       category *ca = NULL;
   };
  struct totaldata data[vegNumber];
    int i = 0;
    while(p != NULL){
        vegetable * vege = p->vegenext;
        while(vege != NULL){
            plant *pla = vege->plantnext;
            data[i].veg = vege;
            data[i].ca = p;
            i++;
            while(pla != NULL){
                if(atoi(pla->month) >= year && atoi(pla->month) <= endYear){
                    data[i].plantASUm += pla->plantArea;
                    data[i].plantWSum += pla->weight;
                }
                pla = pla->next;
            }
            vege = vege->next;
        }
        p = p->next;
    }

    //按总重量排序
    for(int j = 0; j < i - 1; j++){
        for(int k = 1; k < i - j; k++){
            if(data[k - 1].plantWSum < data[k].plantWSum){//交换
                totaldata tmp = data[k - 1];
                data[k - 1] = data[k];
                data[k] = tmp;
            }
        }
    }

    //输出
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,"蔬菜名称");
    model->setHeaderData(1,Qt::Horizontal,"分类名称");
    model->setHeaderData(2,Qt::Horizontal,"种植面积");
    model->setHeaderData(3,Qt::Horizontal,"总重量");
    for(int j = 0; j < i; j++){
        if(data[j].plantWSum == 0)
            break;
        model->setItem(j,0,new QStandardItem(data[j].veg->name));
        model->setItem(j,1,new QStandardItem(data[j].ca->name));
        model->setItem(j,2,new QStandardItem(QString::number(data[j].plantASUm,10)));
        char buffer[50];
        memset(buffer,0,sizeof(buffer));
        sprintf(buffer,"%.2f",data[j].plantWSum);
        model->setItem(j,3,new QStandardItem(buffer));
    }
    ui->label->setText("统计见上表");
    ui->tableView->setModel(model);

}
