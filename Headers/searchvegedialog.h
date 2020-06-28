#ifndef SEARCHVEGEDIALOG_H
#define SEARCHVEGEDIALOG_H

#include <QDialog>

void Next(char*T,int *next);
bool KMP(char* S,char* T);

namespace Ui {
class searchVegeDialog;
}

class searchVegeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit searchVegeDialog(QWidget *parent = 0);
    ~searchVegeDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::searchVegeDialog *ui;
};

#endif // SEARCHVEGEDIALOG_H
