#ifndef ADMINI_H
#define ADMINI_H
#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include "database_dao.h"
#include "globalvarible.h"

namespace Ui {
class admini;
}

class admini : public QMainWindow
{
    Q_OBJECT
public:
    explicit admini(QWidget *parent = 0);
    ~admini();

private slots:
    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_45_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_66_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_67_clicked();

private:
    Ui::admini *ui;
    database_dao *dao = new database_dao; //数据库查询模块实例化
};

#endif // ADMINI_H
