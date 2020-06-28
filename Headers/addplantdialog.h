#ifndef ADDPLANTDIALOG_H
#define ADDPLANTDIALOG_H

#include <QDialog>

namespace Ui {
class addPlantDialog;
}

class addPlantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addPlantDialog(QWidget *parent = 0);
    ~addPlantDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addPlantDialog *ui;
};

#endif // ADDPLANTDIALOG_H
