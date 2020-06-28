#ifndef EDITVEGDIALOG_H
#define EDITVEGDIALOG_H

#include <QDialog>

namespace Ui {
class editVegDialog;
}

class editVegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editVegDialog(QWidget *parent = 0);
    ~editVegDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::editVegDialog *ui;
};

#endif // EDITVEGDIALOG_H
