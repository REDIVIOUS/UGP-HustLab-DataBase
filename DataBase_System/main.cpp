#include "login.h"
#include "globalvarible.h"
#include <QApplication>
#include <QSql>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include<QSqlError>
#include<QSqlDatabase>
#include<QSqlQuery>

QSqlDatabase db; //数据库全局变量

// 配置数据库参数
void ConnectDataBase()
{

    db = QSqlDatabase::addDatabase("QODBC"); //数据库驱动
    QString DataSource = QString::fromLocal8Bit("mydata");  //数据源
    db.setHostName("localhost");                     //hostname
    db.setDatabaseName(DataSource);                  //设置数据源名称
    db.setUserName("project");                       //数据库用户名用户
    db.setPassword("123456");                        //数据库密码
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login log;

    ConnectDataBase(); //配置数据库参数

    if(!db.open())     //打开数据库失败的情况
    {
        QMessageBox::warning(0,"fail","数据库打开失败");
        return 0;
    }

    log.show();
    return a.exec();
}


