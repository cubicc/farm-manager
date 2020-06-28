#ifndef ADDVEGDIALOG_H
#define ADDVEGDIALOG_H

#include <QDialog>

namespace Ui {
class addVegDialog;
}

class addVegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addVegDialog(QWidget *parent = 0);
    ~addVegDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addVegDialog *ui;
};

#endif // ADDVEGDIALOG_H
