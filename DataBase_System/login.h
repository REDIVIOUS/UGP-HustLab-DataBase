#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include "admini.h"
#include "member.h"
#include "database_dao.h"
#include "globalvarible.h"

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT
public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots: //这里一定要用槽函数
    void on_log_clicked();
    void on_cancel_clicked();

private:
    Ui::login *ui;
    database_dao *dao = new database_dao; //实例化数据库dao层
    member *mem;  //创建新窗口指针（普通员工登录）
    admini *adm;  //创建新窗口指针（管理员工登录）
};
#endif // LOGIN_H
