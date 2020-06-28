#ifndef DELETEPLANTDIALOG_H
#define DELETEPLANTDIALOG_H

#include <QDialog>

namespace Ui {
class deletePlantDialog;
}

class deletePlantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit deletePlantDialog(QWidget *parent = 0);
    ~deletePlantDialog();

private slots:
    void on_buttonBox_accepted();
    
private:
    Ui::deletePlantDialog *ui;
};

#endif // DELETEPLANTDIALOG_H
