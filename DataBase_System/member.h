#ifndef MEMBER_H
#define MEMBER_H
#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include <QDateTime>
#include "database_dao.h"
#include "globalvarible.h"


namespace Ui {
class member;
}

class member : public QMainWindow
{
    Q_OBJECT
public:
    explicit member(QWidget *parent = 0);
    ~member();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::member *ui;
    database_dao *dao = new database_dao; //数据库访问类实例化
};

#endif // MEMBER_H
