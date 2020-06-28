#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Load.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum searchType{
        CARETORY,VEGETABLE,PLANT
    };


    void showCategaryInfo(category *totalHead); //显示蔬菜种类
    void showVegetableInfo(category *totalHead);//显示蔬菜
    void showPlantInfo(category *totalHead);//显示种植情况

private slots:
   void on_actionCategoryDisplay_triggered();
   void on_actionVegetableDisplay_triggered();
   void on_actionPlantDisplay_triggered();

   void on_actionSave_triggered();

   void on_actionFindCategoey_triggered();
   void on_actionSearchVeg_triggered();
   void on_actionSearchPlant_triggered();

   void on_actionAddVeg_triggered();
   void on_actionAddCategory_triggered();
   void on_actionAddPlant_triggered();

   void on_actionDeleteVeg_triggered();
   void on_actionDeleteCategory_triggered();
   void on_actionDeletePlant_triggered();

   void on_actionEditPlant_triggered();
   void on_actionEditCategory_triggered();
   void on_actionEditVeg_triggered();

   void on_actionStaticVeg_triggered();
   void on_actionStaticArea_triggered();
   void on_actionLoad_triggered();

   void on_actionImport_triggered();
   void on_actionExport_triggered();

   void on_actionExportCategory_triggered();
   void on_actionExportYear_triggered();
   void on_actionExportCustom_triggered();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

