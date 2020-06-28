#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Load.h"
#include "Store.h"
#include <QStandardItemModel>
#include "searchcategorydialog.h"
#include "searchvegedialog.h"
#include "searchplantdialog.h"
#include "addvegdialog.h"
#include "addcategorydialog.h"
#include "addplantdialog.h"
#include "editcategorydialog.h"
#include "editvegdialog.h"
#include "editplantdialog.h"
#include "deletecategorydialog.h"
#include "deletevegdialog.h"
#include "deleteplantdialog.h"
#include "staticyeardialog.h"
#include "staticvegdialog.h"
#include "QFileDialog"
#include <QMessageBox>
#include "exportcategorydialog.h"
#include "exportyeardialog.h"
#include "exportcustomdialog.h"
#include "stdio.h"
#include <QTextCodec>
#include "string"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec *cate = QTextCodec::codecForName("GB2312");
    std::string cate1 = cate->fromUnicode("蔬菜种类信息表.dat").data();
    QTextCodec *veg = QTextCodec::codecForName("GB2312");
    std::string veg1 = veg->fromUnicode("蔬菜基本信息表.dat").data();
    QTextCodec *pla = QTextCodec::codecForName("GB2312");
    std::string pla1 = pla->fromUnicode("菜农种植信息表.dat").data();
    totalHead = load(cate1.c_str(),veg1.c_str(),pla1.c_str());
    connect(ui->actioncategory,SIGNAL(triggered(bool)),this,SLOT(on_actionCategoryDisplay_triggered()));
    connect(ui->actionvegetable,SIGNAL(triggered(bool)),this,SLOT(on_actionVegetableDisplay_triggered()));
    connect(ui->actionplant,SIGNAL(triggered(bool)),this,SLOT(on_actionPlantDisplay_triggered()));
    connect(ui->actionsave,SIGNAL(triggered(bool)),this,SLOT(on_actionSave_triggered()));

    connect(ui->actionFindCategory,SIGNAL(triggered(bool)),this,SLOT(on_actionFindCategoey_triggered()));
    connect(ui->actionSearchVeg,SIGNAL(triggered(bool)),this,SLOT(on_actionSearchVeg_triggered()));
    connect(ui->actionSearchPlant_2,SIGNAL(triggered(bool)),this,SLOT(on_actionSearchPlant_triggered()));

    connect(ui->actionAddVeg_2,SIGNAL(triggered(bool)),this,SLOT(on_actionAddVeg_triggered()));
    connect(ui->actionAddCategory,SIGNAL(triggered(bool)),this,SLOT(on_actionAddCategory_triggered()));
    connect(ui->actionAddPlant,SIGNAL(triggered(bool)),this,SLOT(on_actionAddPlant_triggered()));

    connect(ui->actionEditCategory,SIGNAL(triggered(bool)),this,SLOT(on_actionEditCategory_triggered()));
    connect(ui->actionEditVeg,SIGNAL(triggered(bool)),this,SLOT(on_actionEditVeg_triggered()));
    connect(ui->actionEditPlant,SIGNAL(triggered(bool)),this,SLOT(on_actionEditPlant_triggered()));

    connect(ui->actionDeleteCategory,SIGNAL(triggered(bool)),this,SLOT(on_actionDeleteCategory_triggered()));
    connect(ui->actionDeleteVeg,SIGNAL(triggered(bool)),this,SLOT(on_actionDeleteVeg_triggered()));
    connect(ui->actionDeletePlant,SIGNAL(triggered(bool)),this,SLOT(on_actionDeletePlant_triggered()));

    connect(ui->actionstaticVeg,SIGNAL(triggered(bool)),this,SLOT(on_actionStaticVeg_triggered()));
    connect(ui->actionstaticArea,SIGNAL(triggered(bool)),this,SLOT(on_actionStaticArea_triggered()));

     connect(ui->actionload,SIGNAL(triggered(bool)),this,SLOT(on_actionLoad_triggered()));
     connect(ui->actionImport,SIGNAL(triggered(bool)),this,SLOT(on_actionImport_triggered()));
     connect(ui->actionExport,SIGNAL(triggered(bool)),this,SLOT(on_actionExport_triggered()));

     connect(ui->actionExportCategory,SIGNAL(triggered(bool)),this,SLOT(on_actionExportCategory_triggered()));
     connect(ui->actionExportYear,SIGNAL(triggered(bool)),this,SLOT(on_actionExportYear_triggered()));
      connect(ui->actionExportCustom,SIGNAL(triggered(bool)),this,SLOT(on_actionExportCustom_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showCategaryInfo(category *totalHead){
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setRowCount(3);
    model->setHeaderData(0,Qt::Vertical,"分类编号");
    model->setHeaderData(1,Qt::Vertical,"分类名称");
    model->setHeaderData(2,Qt::Vertical,"蔬菜名称");
    category *p = totalHead->next;
    for(int i = 0;p != NULL;i++){
        char buf[2];
        buf[0] = p->code;
        buf[2] = '\0';
        model->setItem(0,i,new QStandardItem(buf));
        model->setItem(1,i,new QStandardItem(p->name));
        vegetable *vegepoint = p->vegenext;
        for(int j = 2;vegepoint != NULL;j++){
            model->setItem(j,i,new QStandardItem(vegepoint->name));
            model->setHeaderData(j,Qt::Vertical,"蔬菜名称");
            vegepoint = vegepoint->next;
        }
        p = p->next;
    }
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}

void MainWindow::showVegetableInfo(category *totalHead){
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,"蔬菜编号");
    model->setHeaderData(1,Qt::Horizontal,"蔬菜名称");
    model->setHeaderData(2,Qt::Horizontal,"分类码");
    model->setHeaderData(3,Qt::Horizontal,"营养成分");
    category *p = totalHead->next;
    int count = 0;
    for(int i = 0; p != NULL;i++){
        vegetable *vegepoint = p->vegenext;
        for(int j = 0;vegepoint != NULL;j++){
            model->setItem(count,0,new QStandardItem(QString::number(vegepoint->number,10)));
            model->setItem(count,1,new QStandardItem(vegepoint->name));
            char buf[2];
            buf[0] = p->code;
            buf[1] = '\0';
            model->setItem(count,2,new QStandardItem(buf));
            model->setItem(count,3,new QStandardItem(vegepoint->nutrientContent));
            count++;
            vegepoint = vegepoint->next;
        }
        p = p->next;
    }
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}


void MainWindow::showPlantInfo(category *totalHead){
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setColumnCount(5);
    model->setHeaderData(0,Qt::Horizontal,"编号");
    model->setHeaderData(1,Qt::Horizontal,"蔬菜编号");
    model->setHeaderData(2,Qt::Horizontal,"种植面积");
    model->setHeaderData(3,Qt::Horizontal,"收获重量");
    model->setHeaderData(4,Qt::Horizontal,"种植年份");
    category* p = totalHead->next;
    int count = 0;
    while(p != NULL){
        vegetable *vegepoint = p->vegenext;
        while(vegepoint != NULL){
            plant *plantpoint = vegepoint->plantnext;
            while(plantpoint != NULL){
                 model->setItem(count,0,new QStandardItem(QString::number(plantpoint->number,10)));
                 model->setItem(count,1,new QStandardItem(QString::number(vegepoint->number,10)));
                 model->setItem(count,2,new QStandardItem(QString::number(plantpoint->plantArea,10)));
                 char buffer[50];
                 memset(buffer,0,sizeof(buffer));
                 sprintf(buffer,"%.2f",plantpoint->weight);
                 model->setItem(count,3,new QStandardItem(buffer));
                 model->setItem(count,4,new QStandardItem(plantpoint->month));
                 count++;
                 plantpoint = plantpoint->next;
            }
            vegepoint = vegepoint->next;
        }
        p = p->next;
    }
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}


 void MainWindow::on_actionCategoryDisplay_triggered(){

    showCategaryInfo(totalHead);
 }
void MainWindow:: on_actionVegetableDisplay_triggered(){
    showVegetableInfo(totalHead);
}
void MainWindow:: on_actionPlantDisplay_triggered(){
    showPlantInfo(totalHead);
}

void MainWindow::on_actionSave_triggered(){
    Store *store = new Store(this);

    store->show();
}

void MainWindow::on_actionFindCategoey_triggered(){
    searchCategoryDialog * dlg = new searchCategoryDialog(this);
    dlg->show();
}
void MainWindow::on_actionSearchVeg_triggered(){
    searchVegeDialog * dlg = new searchVegeDialog(this);
    dlg->show();
}

void MainWindow::on_actionSearchPlant_triggered(){
    searchPlantDialog * dlg = new searchPlantDialog(this);
    dlg->show();
}
void MainWindow::on_actionAddVeg_triggered(){
   addVegDialog * dlg = new addVegDialog(this);
    dlg->show();
}

void MainWindow::on_actionAddCategory_triggered(){
    addCategoryDialog * dlg = new addCategoryDialog(this);
    dlg->show();
}

void MainWindow::on_actionAddPlant_triggered(){
    addPlantDialog * dlg = new addPlantDialog(this);
    dlg->show();
}

void MainWindow::on_actionDeleteCategory_triggered(){
    deleteCategoryDialog * dlg = new deleteCategoryDialog(this);
    dlg->show();
}

void MainWindow::on_actionDeleteVeg_triggered(){
    deleteVegDialog * dlg = new deleteVegDialog(this);
    dlg->show();
}

void MainWindow::on_actionDeletePlant_triggered(){
    deletePlantDialog * dlg = new deletePlantDialog(this);
    dlg->show();
}

void MainWindow::on_actionEditCategory_triggered(){
    editCategoryDialog * dlg = new editCategoryDialog(this);
    dlg->show();
}

void MainWindow::on_actionEditVeg_triggered(){
    editVegDialog * dlg = new editVegDialog(this);
    dlg->show();
}

void MainWindow::on_actionEditPlant_triggered(){
    editPlantDialog * dlg = new editPlantDialog(this);
    dlg->show();
}

void MainWindow::on_actionStaticVeg_triggered(){
    staticYearDialog * dlg =new staticYearDialog(this);
    dlg->show();
}

void MainWindow::on_actionStaticArea_triggered(){
    staticVegDialog * dlg =new staticVegDialog(this);
    dlg->show();
}

void MainWindow::on_actionLoad_triggered(){
    category *head = load("D:\\1.dak","D:\\2.dak","D:\\3.dak");
    if(head != NULL){
        totalHead = head;
        QMessageBox::information(this,"载入成功","载入成功！",QMessageBox::Yes);
    }
    else{
         QMessageBox::warning(this,"载入失败","载入失败！",QMessageBox::Yes);
    }
}

void MainWindow::on_actionImport_triggered(){
    QTextCodec *cate = QTextCodec::codecForName("GB2312");
    std::string cate1 = cate->fromUnicode("蔬菜种类信息表.csv").data();
    QTextCodec *veg = QTextCodec::codecForName("GB2312");
    std::string veg1 = veg->fromUnicode("蔬菜基本信息表.csv").data();
    QTextCodec *pla = QTextCodec::codecForName("GB2312");
    std::string pla1 = pla->fromUnicode("菜农种植信息表.csv").data();

       category *head = load(cate1.c_str(),veg1.c_str(),pla1.c_str());
    if(head != NULL){
        totalHead = head;
        QMessageBox::information(this,"导入成功","导入成功！",QMessageBox::Yes);
    }
    else{
         QMessageBox::warning(this,"导入失败","导入失败！",QMessageBox::Yes);
    }
}


void MainWindow::on_actionExport_triggered(){
    QTextCodec *cate = QTextCodec::codecForName("GB2312");
    std::string cate1 = cate->fromUnicode("蔬菜种类信息表.csv").data();
    QTextCodec *veg = QTextCodec::codecForName("GB2312");
    std::string veg1 = veg->fromUnicode("蔬菜基本信息表.csv").data();
    QTextCodec *pla = QTextCodec::codecForName("GB2312");
    std::string pla1 = pla->fromUnicode("菜农种植信息表.csv").data();
    if(store(totalHead,cate1.c_str(),veg1.c_str(),pla1.c_str()) == 1){
        QMessageBox::information(this,"导出成功","导出成功！",QMessageBox::Yes);
    }
    else{
         QMessageBox::warning(this,"导入失败","导入失败！",QMessageBox::Yes);
    }
}

void MainWindow::on_actionExportCategory_triggered(){

    exportCategoryDialog *dlg = new exportCategoryDialog(this);
    dlg->show();
}

void MainWindow::on_actionExportYear_triggered(){

   exportYearDialog *dlg = new exportYearDialog(this);
    dlg->show();
}

void MainWindow::on_actionExportCustom_triggered(){

   ExportCustomDialog *dlg = new ExportCustomDialog(this);
    dlg->show();
}

