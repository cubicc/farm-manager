#ifndef DELETECATEGORYDIALOG_H
#define DELETECATEGORYDIALOG_H

#include <QDialog>

namespace Ui {
class deleteCategoryDialog;
}

class deleteCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit deleteCategoryDialog(QWidget *parent = 0);
    ~deleteCategoryDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::deleteCategoryDialog *ui;
};

#endif // DELETECATEGORYDIALOG_H
