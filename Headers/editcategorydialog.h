#ifndef EDITCATEGORYDIALOG_H
#define EDITCATEGORYDIALOG_H

#include <QDialog>

namespace Ui {
class editCategoryDialog;
}

class editCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editCategoryDialog(QWidget *parent = 0);
    ~editCategoryDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::editCategoryDialog *ui;
};

#endif // EDITCATEGORYDIALOG_H
