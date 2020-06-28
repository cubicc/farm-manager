#ifndef ADDCATEGORYDIALOG_H
#define ADDCATEGORYDIALOG_H

#include <QDialog>

namespace Ui {
class addCategoryDialog;
}

class addCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addCategoryDialog(QWidget *parent = 0);
    ~addCategoryDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::addCategoryDialog *ui;
};

#endif // ADDCATEGORYDIALOG_H
