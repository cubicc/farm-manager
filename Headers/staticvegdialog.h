#ifndef STATICVEGDIALOG_H
#define STATICVEGDIALOG_H

#include <QDialog>

namespace Ui {
class staticVegDialog;
}

class staticVegDialog : public QDialog
{
    Q_OBJECT

public:
    explicit staticVegDialog(QWidget *parent = 0);
    ~staticVegDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::staticVegDialog *ui;
};

#endif // STATICVEGDIALOG_H
