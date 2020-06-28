#ifndef EXPORTCUSTOMDIALOG_H
#define EXPORTCUSTOMDIALOG_H

#include <QDialog>

namespace Ui {
class ExportCustomDialog;
}

class ExportCustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportCustomDialog(QWidget *parent = 0);
    ~ExportCustomDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ExportCustomDialog *ui;
};

#endif // EXPORTCUSTOMDIALOG_H
