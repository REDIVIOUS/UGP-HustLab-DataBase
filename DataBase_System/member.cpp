#include "member.h"
#include "ui_member.h"
#include <Qtsql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QAction>

member::member(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::member)
{
    ui->setupUi(this);
    this->setWindowTitle("普通员工界面"); //设置页面标题
    // 设置抬头
    ui->label_5->setText(MID); //ID
    ui->label_8->setText(MName);  //姓名
    ui->label_10->setText(ifadmi);  //管理员
    ui->spinBox->setRange(0,3000); //设置搜寻年龄的上限
}

member::~member()
{
    delete ui;
}


//界面选择按钮槽函数
void member::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void member::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void member::on_pushButton_7_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void member::on_pushButton_8_clicked()
{
    QMessageBox::information(NULL,"exit","已退出系统");
    this->close();
}


// 出勤信息查询
void member::on_pushButton_clicked()
{
    ui->infoshow->setRowCount(0); //设置行数为0
    ui->infoshow->clear(); //清空内容
    QDate dateEdit1 = ui->dateEdit->date();
    QString dateinfo1 = dateEdit1.toString("yyyy-MM-dd"); //起始日期
    QDate dateEdit2 = ui->dateEdit_6->date();
    QString dateinfo2 = dateEdit2.toString("yyyy-MM-dd"); //结束日期
    QSqlQuery query = dao->RecordSelectDM(dateinfo1,dateinfo2,MID);

    // 在表格中显示查询结果（根据查询种类的不同来显示）
    if(ui->comboBox->currentIndex() == 0){ //查询全部
        ui->infoshow->setColumnCount(4); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"日期"<<"是否出勤"<<"是否加班";
        ui->infoshow->setHorizontalHeaderLabels(list);
    }
    else if(ui->comboBox->currentIndex() == 1){ //查询出勤信息
        ui->infoshow->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"日期"<<"是否出勤";
        ui->infoshow->setHorizontalHeaderLabels(list);
    }
    else if(ui->comboBox->currentIndex() == 2){ //查询加班信息
        ui->infoshow->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"日期"<<"是否加班";
        ui->infoshow->setHorizontalHeaderLabels(list);
    }
    while(query.next())
    {
        ui->infoshow->insertRow(ui->infoshow->rowCount());//插入一行
        int rowIndex = ui->infoshow->rowCount();
        QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
        ui->infoshow->setItem(rowIndex-1,0,item1);
        ui->infoshow->setItem(rowIndex-1,1,item2);
        if(ui->comboBox->currentIndex() == 0)
        {
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(2).toString());
            QTableWidgetItem *item4=new QTableWidgetItem(query.value(3).toString());
            ui->infoshow->setItem(rowIndex-1,2,item3);
            ui->infoshow->setItem(rowIndex-1,3,item4);
        }
        else if(ui->comboBox->currentIndex() == 1)
        {
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(2).toString());
            ui->infoshow->setItem(rowIndex-1,2,item3);
        }
        else if(ui->comboBox->currentIndex() == 2)
        {
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(3).toString());
            ui->infoshow->setItem(rowIndex-1,2,item3);
        }
    }

}


//出勤查询界面撤销表内操作
void member::on_pushButton_2_clicked()
{
    ui->infoshow->setRowCount(0); //设置行数为0
    ui->infoshow->clear(); //清空内容
}


//工资查询
void member::on_pushButton_3_clicked()
{
    ui->infoshow_3->setRowCount(0); //设置行数为0
    ui->infoshow_3->clear(); //清空内容
    QDate dateEdit1 = ui->dateEdit_3->date();
    QString dateinfo1 = dateEdit1.toString("yyyy-MM-dd"); //日期
    QDate dateEdit2 = ui->dateEdit_7->date();
    QString dateinfo2 = dateEdit2.toString("yyyy-MM-dd"); //日期
    QSqlQuery query1; //查询月收入
    QSqlQuery query2; //查询年收入

    //根据不同的条件构造查询语句
    if(ui->checkBox_14->isChecked())
    {
        query1 = dao->MonthIncomeSelectDM(dateinfo1,dateinfo2,MID);
        query2 = dao->YearIncomeSelectDM(dateinfo1,dateinfo2,MID);
    }
    else
    {
        query1 = dao->MonthIncomeSelectM(MID);
        query2 = dao->YearIncomeSelectM(MID);
    }


    // 根据给定的条件，显示查询内容
    if(ui->comboBox_3->currentIndex()==0)
    {
        ui->infoshow_3->setColumnCount(5); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"月份"<<"基本工资"<<"出勤奖金"<<"加班津贴";
        ui->infoshow_3->setHorizontalHeaderLabels(list);
        while(query1.next())
        {
            ui->infoshow_3->insertRow(ui->infoshow_3->rowCount());//插入一行
            int rowIndex = ui->infoshow_3->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query1.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query1.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query1.value(2).toString());
            QTableWidgetItem *item4=new QTableWidgetItem(query1.value(3).toString());
            QTableWidgetItem *item5=new QTableWidgetItem(query1.value(4).toString());
            ui->infoshow_3->setItem(rowIndex-1,0,item1);
            ui->infoshow_3->setItem(rowIndex-1,1,item2);
            ui->infoshow_3->setItem(rowIndex-1,2,item3);
            ui->infoshow_3->setItem(rowIndex-1,3,item4);
            ui->infoshow_3->setItem(rowIndex-1,4,item5);
        }
    }
    else if(ui->comboBox_3->currentIndex()==1)
    {
        ui->infoshow_3->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"月份"<<"基本工资";
        ui->infoshow_3->setHorizontalHeaderLabels(list);
        while(query1.next())
        {
            ui->infoshow_3->insertRow(ui->infoshow_3->rowCount());//插入一行
            int rowIndex = ui->infoshow_3->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query1.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query1.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query1.value(2).toString());
            ui->infoshow_3->setItem(rowIndex-1,0,item1);
            ui->infoshow_3->setItem(rowIndex-1,1,item2);
            ui->infoshow_3->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_3->currentIndex()==2)
    {
        ui->infoshow_3->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"月份"<<"出勤奖金";
        ui->infoshow_3->setHorizontalHeaderLabels(list);

        while(query1.next())
        {
            ui->infoshow_3->insertRow(ui->infoshow_3->rowCount());//插入一行
            int rowIndex = ui->infoshow_3->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query1.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query1.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query1.value(3).toString());
            ui->infoshow_3->setItem(rowIndex-1,0,item1);
            ui->infoshow_3->setItem(rowIndex-1,1,item2);
            ui->infoshow_3->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_3->currentIndex()==3)
    {
        ui->infoshow_3->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"月份"<<"加班津贴";
        ui->infoshow_3->setHorizontalHeaderLabels(list);

        while(query1.next())
        {
            ui->infoshow_3->insertRow(ui->infoshow_3->rowCount());//插入一行
            int rowIndex = ui->infoshow_3->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query1.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query1.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query1.value(4).toString());
            ui->infoshow_3->setItem(rowIndex-1,0,item1);
            ui->infoshow_3->setItem(rowIndex-1,1,item2);
            ui->infoshow_3->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_3->currentIndex()==4)
    {
        ui->infoshow_3->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"年终奖";
        ui->infoshow_3->setHorizontalHeaderLabels(list);

        while(query2.next())
        {
            ui->infoshow_3->insertRow(ui->infoshow_3->rowCount());//插入一行
            int rowIndex = ui->infoshow_3->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query2.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query2.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query2.value(5).toString());
            ui->infoshow_3->setItem(rowIndex-1,0,item1);
            ui->infoshow_3->setItem(rowIndex-1,1,item2);
            ui->infoshow_3->setItem(rowIndex-1,2,item3);
        }
    }

}

//工资查询界面撤销表内操作
void member::on_pushButton_5_clicked()
{
    ui->infoshow_3->setRowCount(0); //设置行数为0
    ui->infoshow_3->clear(); //清空内容
}

// 工资统计查询
void member::on_pushButton_9_clicked()
{
    ui->infoshow_6->setRowCount(0); //设置行数为0
    ui->infoshow_6->clear(); //清空内容
    QString yeartime0 = ui->spinBox->text();
    int yeartime = yeartime0.toInt();
    QSqlQuery query = dao->YearIncomeSelectYM(MID,yeartime);

    if(ui->comboBox_6->currentIndex()==0)
    {
        ui->infoshow_6->setColumnCount(7); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"基本工资和"<<"出勤奖金和"<<"加班津贴和"<<"年终奖"<<"共计";
        ui->infoshow_6->setHorizontalHeaderLabels(list);
        while(query.next())
        {
            ui->infoshow_6->insertRow(ui->infoshow_6->rowCount());//插入一行
            int rowIndex = ui->infoshow_6->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(2).toString());
            QTableWidgetItem *item4=new QTableWidgetItem(query.value(3).toString());
            QTableWidgetItem *item5=new QTableWidgetItem(query.value(4).toString());
            QTableWidgetItem *item6=new QTableWidgetItem(query.value(5).toString());
            QTableWidgetItem *item7=new QTableWidgetItem(query.value(6).toString());
            ui->infoshow_6->setItem(rowIndex-1,0,item1);
            ui->infoshow_6->setItem(rowIndex-1,1,item2);
            ui->infoshow_6->setItem(rowIndex-1,2,item3);
            ui->infoshow_6->setItem(rowIndex-1,3,item4);
            ui->infoshow_6->setItem(rowIndex-1,4,item5);
            ui->infoshow_6->setItem(rowIndex-1,5,item6);
            ui->infoshow_6->setItem(rowIndex-1,6,item7);
        }
    }
    else if(ui->comboBox_6->currentIndex()==1)
    {
        ui->infoshow_6->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"基本工资和";
        ui->infoshow_6->setHorizontalHeaderLabels(list);
        while(query.next())
        {
            ui->infoshow_6->insertRow(ui->infoshow_6->rowCount());//插入一行
            int rowIndex = ui->infoshow_6->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(2).toString());
            ui->infoshow_6->setItem(rowIndex-1,0,item1);
            ui->infoshow_6->setItem(rowIndex-1,1,item2);
            ui->infoshow_6->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_6->currentIndex()==2)
    {
            ui->infoshow_6->setColumnCount(3); //设置列数
            QStringList list; //设置信息栏的表头
            list<<"员工ID"<<"年份"<<"出勤奖金和";
            ui->infoshow_6->setHorizontalHeaderLabels(list);
            while(query.next())
            {
                ui->infoshow_6->insertRow(ui->infoshow_6->rowCount());//插入一行
                int rowIndex = ui->infoshow_6->rowCount();
                QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
                QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
                QTableWidgetItem *item3=new QTableWidgetItem(query.value(3).toString());
                ui->infoshow_6->setItem(rowIndex-1,0,item1);
                ui->infoshow_6->setItem(rowIndex-1,1,item2);
                ui->infoshow_6->setItem(rowIndex-1,2,item3);
            }
    }
    else if(ui->comboBox_6->currentIndex()==3)
    {
        ui->infoshow_6->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"加班津贴和";
        ui->infoshow_6->setHorizontalHeaderLabels(list);
        while(query.next())
        {
            ui->infoshow_6->insertRow(ui->infoshow_6->rowCount());//插入一行
            int rowIndex = ui->infoshow_6->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(4).toString());
            ui->infoshow_6->setItem(rowIndex-1,0,item1);
            ui->infoshow_6->setItem(rowIndex-1,1,item2);
            ui->infoshow_6->setItem(rowIndex-1,2,item3);
            }
    }
    else if(ui->comboBox_6->currentIndex()==4)
    {
        ui->infoshow_6->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"年终奖";
        ui->infoshow_6->setHorizontalHeaderLabels(list);
        while(query.next())
        {
            ui->infoshow_6->insertRow(ui->infoshow_6->rowCount());//插入一行
            int rowIndex = ui->infoshow_6->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(5).toString());
            ui->infoshow_6->setItem(rowIndex-1,0,item1);
            ui->infoshow_6->setItem(rowIndex-1,1,item2);
            ui->infoshow_6->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_6->currentIndex()==5)
    {
        ui->infoshow_6->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"总计";
        ui->infoshow_6->setHorizontalHeaderLabels(list);
        while(query.next())
        {
            ui->infoshow_6->insertRow(ui->infoshow_6->rowCount());//插入一行
            int rowIndex = ui->infoshow_6->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(6).toString());
            ui->infoshow_6->setItem(rowIndex-1,0,item1);
            ui->infoshow_6->setItem(rowIndex-1,1,item2);
            ui->infoshow_6->setItem(rowIndex-1,2,item3);
        }
    }
}

//工资统计界面撤销表内操作
void member::on_pushButton_10_clicked()
{
    ui->infoshow_6->setRowCount(0); //设置行数为0
    ui->infoshow_6->clear(); //清空内容
}

