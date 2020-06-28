#ifndef SEARCHPLANTDIALOG_H
#define SEARCHPLANTDIALOG_H

#include <QDialog>

namespace Ui {
class searchPlantDialog;
}

class searchPlantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit searchPlantDialog(QWidget *parent = 0);
    ~searchPlantDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::searchPlantDialog *ui;
};

#endif // SEARCHPLANTDIALOG_H

bool Equal(char *vegYear,char* month);
