#ifndef EDITPLANTDIALOG_H
#define EDITPLANTDIALOG_H

#include <QDialog>

namespace Ui {
class editPlantDialog;
}

class editPlantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editPlantDialog(QWidget *parent = 0);
    ~editPlantDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::editPlantDialog *ui;
};

#endif // EDITPLANTDIALOG_H
