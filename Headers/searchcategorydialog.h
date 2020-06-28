#ifndef SEARCHCATEGORYDIALOG_H
#define SEARCHCATEGORYDIALOG_H

#include <QDialog>

namespace Ui {
class searchCategoryDialog;
}

class searchCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit searchCategoryDialog(QWidget *parent = 0);
    ~searchCategoryDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::searchCategoryDialog *ui;
};

#endif // SEARCHCATEGORYDIALOG_H
