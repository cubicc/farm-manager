#ifndef EXPORTCATEGORYDIALOG_H
#define EXPORTCATEGORYDIALOG_H

#include <QDialog>

namespace Ui {
class exportCategoryDialog;
}

class exportCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit exportCategoryDialog(QWidget *parent = 0);
    ~exportCategoryDialog();

private slots:
    void on_buttonBox_accepted();
    
private:
    Ui::exportCategoryDialog *ui;
};

#endif // EXPORTCATEGORYDIALOG_H
