#include "login.h"
#include "ui_login.h"
#include <Qtsql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QAction>

QString MID; //员工ID
QString MName; //员工姓名
QString ifadmi; //是否为管理员

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("登陆界面");
}

login::~login()
{
    delete ui;
}

//点击登录后的操作
void login::on_log_clicked()
{
    QString userID,password;
    userID = ui->lineID->text();  //获取用户名
    password = ui->line_password->text(); //获取密码
    QSqlQuery query = dao->MemberSelect(); //查询员工表
    int flag = 0;
    while(query.next())
    {
        if(userID == query.value(0).toString() && password == query.value(5).toString()) //判断用户名和密码是否匹配
        {
            flag = 1;
            QMessageBox::information(NULL,"success","您已成功登录",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            MID = query.value(0).toString(); //员工ID
            MName = query.value(1).toString(); //员工姓名
            this->close();
            if(query.value(6).toInt() == 1)
            { //如果是管理员，显示管理员页面
                ifadmi = "是";
                adm = new admini(); //指针实例化（管理员）
                adm->show();
                break;
            }
            else if(query.value(6).toInt() == 0)
            { //不是管理员，显示普通用户界面
                ifadmi = "否";
                mem = new member(); //指针实例化（普通员工）
                mem->show();
                break;
            }
        }
    }
    if(flag == 0)
    {
        QMessageBox::warning(NULL,"fail","用户名或者密码错误，请重新登陆",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        ui->lineID->clear();
        ui->line_password->clear();
    }
}

//点击取消后的操作
void login::on_cancel_clicked()
{
    QMessageBox::information(NULL,"exit","已退出登录");
    this->close();
}
