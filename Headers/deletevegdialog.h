#ifndef DELETEVEGDIALOG_H
#define DELETEVEGDIALOG_H

#include <QDialog>

namespace Ui {
class deleteVegDialog;
}

class deleteVegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit deleteVegDialog(QWidget *parent = 0);
    ~deleteVegDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::deleteVegDialog *ui;
};

#endif // DELETEVEGDIALOG_H
