#ifndef EXPORTYEARDIALOG_H
#define EXPORTYEARDIALOG_H

#include <QDialog>

namespace Ui {
class exportYearDialog;
}

class exportYearDialog : public QDialog
{
    Q_OBJECT

public:
    explicit exportYearDialog(QWidget *parent = 0);
    ~exportYearDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::exportYearDialog *ui;
};

#endif // EXPORTYEARDIALOG_H
