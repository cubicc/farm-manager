#ifndef STORE_H
#define STORE_H

#include <QDialog>
#include "Load.h"
int store(category *head,const char *file1,const char *file2,const char *file3);
namespace Ui {
class Store;
}

class Store : public QDialog
{
    Q_OBJECT
signals:
    void sendboolean(bool isChanged);


public:
    explicit Store(QWidget *parent = 0);
    ~Store();


private slots:
    void on_Store_accepted();

private:
    Ui::Store *ui;
};

#endif // STORE_H
