#ifndef STATICYEARDIALOG_H
#define STATICYEARDIALOG_H

#include <QDialog>

namespace Ui {
class staticYearDialog;
}

class staticYearDialog : public QDialog
{
    Q_OBJECT

public:
    explicit staticYearDialog(QWidget *parent = 0);
    ~staticYearDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::staticYearDialog *ui;
};

#endif // STATICYEARDIALOG_H
