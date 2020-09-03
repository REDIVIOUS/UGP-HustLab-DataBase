#include "admini.h"
#include "ui_admini.h"
#include <Qtsql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QAction>

admini::admini(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admini)
{
    ui->setupUi(this);
    this->setWindowTitle("管理员界面"); //设置管理员页面
    ui->label_5->setText(MID); //ID
    ui->label_8->setText(MName);  //姓名
    ui->label_10->setText(ifadmi);  //管理员
    ui->spinBox_9->setRange(0,3000); //年份选择范围
    QSqlQuery query = dao->WTypeSelect(); // 加入工种选择栏
    while (query.next()) {
        ui->comboBox_19->addItem(query.value(1).toString());
    }
}

admini::~admini()
{
    delete ui;
}

//界面选择按钮槽函数
void admini::on_pushButton_34_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void admini::on_pushButton_35_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void admini::on_pushButton_36_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void admini::on_pushButton_33_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void admini::on_pushButton_37_clicked()
{
    QMessageBox::information(NULL,"exit","已退出系统");
    this->close();
}

//员工管理查询设置
void admini::on_pushButton_16_clicked()
{
    ui->infoshow_10->setRowCount(0); //设置行数为0
    ui->infoshow_10->clearContents(); //清空内容

    QString IDnum = ui->lineEdit_16->text();   // 员工ID
    QString IDName = ui->lineEdit_18->text();  // 员工姓名
    QString IDtype = ui->lineEdit_19->text();  // 员工种类
    QSqlQuery query1 = dao->MemberSelectID(IDnum);  //按照员工ID查询
    QSqlQuery query2 = dao->MemberSelectNA(IDName);  //按照员工姓名查询
    QSqlQuery query3 = dao->MemberSelectIT(IDtype);  //按照员工种类查询

    QSqlQuery query;
    if(ui->comboBox_9->currentIndex() == 0)
    {
        query = query1;
    }
    else if(ui->comboBox_9->currentIndex() == 1)
    {
        query = query2;
    }
    else if(ui->comboBox_9->currentIndex() == 2)
    {
        query = query3;
    }

    ui->infoshow_10->setColumnCount(7); //设置列数
    QStringList list; //设置信息栏的表头
    list<<"员工ID"<<"姓名"<<"性别"<<"年龄"<<"工种"<<"密码"<<"管理员权限";
    ui->infoshow_10->setHorizontalHeaderLabels(list);
    while(query.next())
    { //输出员工信息
        ui->infoshow_10->insertRow(ui->infoshow_10->rowCount());//插入一行
        int rowIndex = ui->infoshow_10->rowCount();
        QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *item3=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *item4=new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *item5=new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *item6=new QTableWidgetItem(query.value(5).toString());
        QTableWidgetItem *item7=new QTableWidgetItem(query.value(6).toString());
        ui->infoshow_10->setItem(rowIndex-1,0,item1);
        ui->infoshow_10->setItem(rowIndex-1,1,item2);
        ui->infoshow_10->setItem(rowIndex-1,2,item3);
        ui->infoshow_10->setItem(rowIndex-1,3,item4);
        ui->infoshow_10->setItem(rowIndex-1,4,item5);
        ui->infoshow_10->setItem(rowIndex-1,5,item6);
        ui->infoshow_10->setItem(rowIndex-1,6,item7);
    }
}

//员工管理删除设置
void admini::on_pushButton_42_clicked()
{
    ui->infoshow_10->setRowCount(0); //设置行数为0
    ui->infoshow_10->clearContents(); //清空内容

    QString IDnum = ui->lineEdit_16->text();   // 员工ID
    QString IDName = ui->lineEdit_18->text();  // 员工姓名
    QString IDtype = ui->lineEdit_19->text();  // 员工种类
    if(ui->comboBox_9->currentIndex()==0)
    {
        dao->MemberdeleteID(IDnum);
        QMessageBox::information(NULL,"delete","删除成功");
    }
    else if(ui->comboBox_9->currentIndex()==1)
    {
        dao->MemberdeleteNA(IDName);
        QMessageBox::information(NULL,"delete","删除成功");
    }
    else if(ui->comboBox_9->currentIndex()==2)
    {
        dao->MemberdeleteIT(IDtype);
        QMessageBox::information(NULL,"delete","删除成功");
    }
}

// 员工管理更新设置
void admini::on_pushButton_45_clicked()
{
    ui->infoshow_10->setRowCount(0); //设置行数为0
    ui->infoshow_10->clearContents(); //清空内容

    QString IDnum = ui->lineEdit_13->text();   // 员工ID
    QString IDName = ui->lineEdit_15->text();  // 员工姓名
    QString IDtype = ui->comboBox_19->currentText();  // 员工种类
    QString pwd = ui->lineEdit_14->text();     // 员工密码
    QString age0 = ui->spinBox_4->text();
    int age = age0.toInt(); //年龄
    int flag=0; //更新成功标志
    // 按照不同类型更改
    if(IDName!="")
    {
        dao->MemberupdateName(IDnum,IDName);
        flag = 1;
    }
    if(IDtype!="")
    {
        dao->MemberupdateType(IDnum,IDName);
        flag = 1;
    }
    if(pwd!="")
    {
        dao->MemberupdatePWD(IDnum,pwd);
        flag = 1;
    }
    if(age!=0)
    {
        dao->MemberupdateAGE(IDnum,age);
        flag = 1;
    }
    if(ui->checkBox_24->isChecked())
    {
        dao->MemberupdateMAN(IDnum);
        flag = 1;
    }
    if(ui->checkBox_25->isChecked())
    {
        dao->MemberupdateWOMAN(IDnum);
        flag = 1;
    }

    if(flag == 1)
    {
        QMessageBox::information(NULL,"update","更新成功");
    }
}

// 员工管理插入设置
void admini::on_pushButton_44_clicked()
{
    ui->infoshow_10->setRowCount(0); //设置行数为0
    ui->infoshow_10->clearContents(); //清空内容

    QString IDnum = ui->lineEdit_13->text();   // 员工ID
    QString IDName = ui->lineEdit_15->text();  // 员工姓名
    QString IDtype = ui->comboBox_19->currentText();  // 员工种类
    QString pwd = ui->lineEdit_14->text();     // 员工密码
    QString age0 = ui->spinBox_4->text();
    int age = age0.toInt(); //年龄
    int sex = 0;
    if(ui->checkBox_24->isChecked())
    {
        sex = 1; //男性
    }
    if(ui->checkBox_25->isChecked())
    {
        sex = 0; //女性
    }
    dao->Memberinsert(IDnum,IDName,sex,age,IDtype,pwd);
    QMessageBox::information(NULL,"insert","插入成功");
}

//撤销操作
void admini::on_pushButton_46_clicked()
{
    ui->infoshow_10->setRowCount(0); //设置行数为0
    ui->infoshow_10->clearContents(); //清空内容
}

//管理员授权操作
void admini::on_pushButton_47_clicked()
{
    ui->infoshow_10->setRowCount(0); //设置行数为0
    ui->infoshow_10->clearContents(); //清空内容

    QString IDnum = ui->lineEdit_21->text();   // 员工ID
    QString pwd = ui->lineEdit_22->text();     // 员工密码
    int auth = 0;
    if(ui->checkBox_26->isChecked())
    {
        auth = 1;
    }
    else if(ui->checkBox_27->isChecked())
    {
        auth = 0;
    }
    dao->MemberupdateAuth(IDnum,pwd,auth);
    QMessageBox::information(NULL,"AuthUpdate","管理员权限赋予/删除成功");
}


//工种管理界面查询操作
void admini::on_pushButton_13_clicked()
{
    ui->infoshow_2->setRowCount(0); //设置行数为0
    ui->infoshow_2->clearContents(); //清空内容

    QString typeID = ui->lineEdit->text();  //工种ID
    QString typeName = ui->lineEdit_6->text();  //工种名称

    QSqlQuery query;  //工种查询语句
    if(ui->comboBox_11->currentIndex() == 0)
    {
        query = dao->WTypeSelectID(typeID);
    }
    else if(ui->comboBox_11->currentIndex() == 1)
    {
        query = dao->WTypeSelectNA(typeName);
    }

    ui->infoshow_2->setColumnCount(4); //设置列数
    QStringList list; //设置信息栏的表头
    list<<"工种ID"<<"工种名"<<"工种等级"<<"基本工资";
    ui->infoshow_2->setHorizontalHeaderLabels(list);

    while(query.next())
    { //输出工种信息
        ui->infoshow_2->insertRow(ui->infoshow_2->rowCount());//插入一行
        int rowIndex = ui->infoshow_2->rowCount();
        QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *item3=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *item4=new QTableWidgetItem(query.value(3).toString());
        ui->infoshow_2->setItem(rowIndex-1,0,item1);
        ui->infoshow_2->setItem(rowIndex-1,1,item2);
        ui->infoshow_2->setItem(rowIndex-1,2,item3);
        ui->infoshow_2->setItem(rowIndex-1,3,item4);
    }
}

//工种管理界面删除操作
void admini::on_pushButton_21_clicked()
{
    ui->infoshow_2->setRowCount(0); //设置行数为0
    ui->infoshow_2->clearContents(); //清空内容

    QString typeID = ui->lineEdit->text();  //工种ID
    QString typeName = ui->lineEdit_6->text();  //工种名称

    if(ui->comboBox_11->currentIndex() == 0)
    {
        dao->WTypedeleteID(typeID);
        QMessageBox::information(NULL,"delete","删除成功");
    }
    else if(ui->comboBox_11->currentIndex() == 1)
    {
        dao->WTypedeleteNA(typeName);
        QMessageBox::information(NULL,"delete","删除成功");
    }
}

//工种管理界面修改操作
void admini::on_pushButton_22_clicked()
{
    ui->infoshow_2->setRowCount(0); //设置行数为0
    ui->infoshow_2->clearContents(); //清空内容

    QString typeID = ui->lineEdit_2->text();  //工种ID
    QString typeName = ui->lineEdit_11->text();  //工种名称
    QString level0 = ui->spinBox_3->text();
    int level = level0.toInt(); //等级
    QString sal0 = ui->lineEdit_12->text();
    double sal = sal0.toDouble(); //基本工资

    int flag=0; //更改标志
    if(typeName != "")
    {
        dao->WTypeupdateNA(typeID,typeName);
        flag = 1;
    }
    if(level != 0)
    {
        dao->WTypeupdateL(typeID,level);
        flag = 1;
    }
    if(sal != 0)
    {
        dao->WTypeupdateS(typeID,sal);
        flag = 1;
    }

    if(flag == 1)
    {
        QMessageBox::information(NULL,"update","修改成功");
    }
}

//工种管理界面插入操作
void admini::on_pushButton_23_clicked()
{
    ui->infoshow_2->setRowCount(0); //设置行数为0
    ui->infoshow_2->clearContents(); //清空内容

    QString typeID = ui->lineEdit_2->text();  //工种ID
    QString typeName = ui->lineEdit_11->text();  //工种名称
    QString level0 = ui->spinBox_3->text();
    int level = level0.toInt(); //等级
    QString sal0 = ui->lineEdit_12->text();
    double sal = sal0.toDouble(); //基本工资

    dao->WTypeinsert(typeID,typeName,level,sal);
    ui->comboBox_19->addItem(typeName); //可供选择的工种加入
    QMessageBox::information(NULL,"insert","插入成功");
}

//工种管理界面统计总人数
void admini::on_pushButton_41_clicked()
{
    ui->infoshow_2->setRowCount(0); //设置行数为0
    ui->infoshow_2->clearContents(); //清空内容

    QString typeID = ui->lineEdit_24->text();  //工种ID
    QString typeName = ui->lineEdit_23->text();  //工种名称

    QSqlQuery query;
    if(ui->comboBox_12->currentIndex() == 0)
    {
        query = dao->WTypetotalID(typeID);
    }
    else if(ui->comboBox_12->currentIndex() == 1)
    {
        query = dao->WTypetotalNA(typeName);
    }

    ui->infoshow_2->setColumnCount(4); //设置列数
    QStringList list; //设置信息栏的表头
    list<<"工种ID"<<"工种名"<<"基本工资"<<"总人数";
    ui->infoshow_2->setHorizontalHeaderLabels(list);

    while(query.next())
    { //输出工种信息
        ui->infoshow_2->insertRow(ui->infoshow_2->rowCount());//插入一行
        int rowIndex = ui->infoshow_2->rowCount();
        QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *item3=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *item4=new QTableWidgetItem(query.value(3).toString());
        ui->infoshow_2->setItem(rowIndex-1,0,item1);
        ui->infoshow_2->setItem(rowIndex-1,1,item2);
        ui->infoshow_2->setItem(rowIndex-1,2,item3);
        ui->infoshow_2->setItem(rowIndex-1,3,item4);
    }
}

// 出勤查询界面
void admini::on_pushButton_15_clicked()
{
    ui->infoshow_4->setRowCount(0); //设置行数为0
    ui->infoshow_4->clearContents(); //清空内容

    QString memID = ui->lineEdit_10->text();  //员工ID
    QDate dateEdit1 = ui->dateEdit_16->date();
    QString dateinfo1 = dateEdit1.toString("yyyy-MM-dd"); //开始日期
    QDate dateEdit2 = ui->dateEdit_17->date();
    QString dateinfo2 = dateEdit2.toString("yyyy-MM-dd"); //结束日期

    QSqlQuery query = dao->RecordSelectDM(dateinfo1,dateinfo2,memID); //查询

    ui->infoshow_4->setColumnCount(4); //设置列数
    QStringList list; //设置信息栏的表头
    list<<"员工ID"<<"日期"<<"是否出勤"<<"是否加班";
    ui->infoshow_4->setHorizontalHeaderLabels(list);

    while(query.next())
    { //输出工种信息
        ui->infoshow_4->insertRow(ui->infoshow_4->rowCount());//插入一行
        int rowIndex = ui->infoshow_4->rowCount();
        QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *item3=new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *item4=new QTableWidgetItem(query.value(3).toString());
        ui->infoshow_4->setItem(rowIndex-1,0,item1);
        ui->infoshow_4->setItem(rowIndex-1,1,item2);
        ui->infoshow_4->setItem(rowIndex-1,2,item3);
        ui->infoshow_4->setItem(rowIndex-1,3,item4);
    }
}

// 出勤界面删除功能
void admini::on_pushButton_38_clicked()
{
    ui->infoshow_4->setRowCount(0); //设置行数为0
    ui->infoshow_4->clearContents(); //清空内容

    QString memID = ui->lineEdit_10->text();  //员工ID
    QDate dateEdit = ui->dateEdit_4->date();
    QString dateinfo = dateEdit.toString("yyyy-MM-dd"); //日期
    dao->Recorddelete(memID,dateinfo);
    QMessageBox::information(NULL,"delete","删除成功");
}

// 出勤界面修改功能
void admini::on_pushButton_40_clicked()
{
    ui->infoshow_4->setRowCount(0); //设置行数为0
    ui->infoshow_4->clearContents(); //清空内容

    QString memID = ui->lineEdit_9->text();  //员工ID
    QDate dateEdit = ui->dateEdit_11->date();
    QString dateinfo = dateEdit.toString("yyyy-MM-dd"); //日期
    int flag = 0; // 修改标识

    if(ui->checkBox_14->isChecked())
    {
        dao->RecordupdateIH(memID,dateinfo);
        flag = 1;
    }
    else
    {
        dao->RecordupdateNH(memID,dateinfo);
        flag = 1;
    }
    if(ui->checkBox_20->isChecked())
    {
        dao->RecordupdateID(memID,dateinfo);
        flag = 1;
    }
    else
    {
        dao->RecordupdateND(memID,dateinfo);
        flag = 1;
    }

    if(flag == 1)
    {
        QMessageBox::information(NULL,"update","修改成功");
    }
}

// 出勤界面插入功能
void admini::on_pushButton_39_clicked()
{
    ui->infoshow_4->setRowCount(0); //设置行数为0
    ui->infoshow_4->clearContents(); //清空内容

    QString memID = ui->lineEdit_9->text();  //员工ID
    QDate dateEdit = ui->dateEdit_11->date();
    QString dateinfo = dateEdit.toString("yyyy-MM-dd"); //日期
    int here = 0; //出勤标识
    int delay = 0; //加班标识
    if(ui->checkBox_14->isChecked())
    {
        here = 1;
    }
    if(ui->checkBox_20->isChecked())
    {
        delay = 1;
    }

    dao->Recordinsert(memID,dateinfo,here,delay);
    QMessageBox::information(NULL,"insert","插入成功");
}

// 查询每月的加班/出勤天数
void admini::on_pushButton_66_clicked()
{
    ui->infoshow_4->setRowCount(0); //设置行数为0
    ui->infoshow_4->clearContents(); //清空内容

    QString memID = ui->lineEdit_47->text();  //员工ID
    QDate dateEdit = ui->dateEdit_15->date();
    QString dateinfo = dateEdit.toString("yyyy-MM-dd"); //日期

    QSqlQuery query1 = dao->Recordhereday(memID,dateinfo); //查询出勤天数
    QSqlQuery query2 = dao->Recorddelayday(memID,dateinfo); //查询加班天数
    QSqlQuery query3 = dao->Recordheredelayday(memID,dateinfo); //加班天数、出勤天数联合查询

    if(ui->checkBox_33->isChecked() && ui->checkBox_34->isChecked())
    {
        ui->infoshow_4->setColumnCount(4); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"月份"<<"出勤天数"<<"加班天数";
        ui->infoshow_4->setHorizontalHeaderLabels(list);

        while(query3.next())
        { //输出工种信息
            ui->infoshow_4->insertRow(ui->infoshow_4->rowCount());//插入一行
            int rowIndex = ui->infoshow_4->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query3.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query3.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query3.value(2).toString());
            QTableWidgetItem *item4=new QTableWidgetItem(query3.value(3).toString());
            ui->infoshow_4->setItem(rowIndex-1,0,item1);
            ui->infoshow_4->setItem(rowIndex-1,1,item2);
            ui->infoshow_4->setItem(rowIndex-1,2,item3);
            ui->infoshow_4->setItem(rowIndex-1,3,item4);
        }
    }
    else if(ui->checkBox_33->isChecked())
    {
        ui->infoshow_4->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"月份"<<"加班天数";
        ui->infoshow_4->setHorizontalHeaderLabels(list);

        while(query2.next())
        { //输出工种信息
            ui->infoshow_4->insertRow(ui->infoshow_4->rowCount());//插入一行
            int rowIndex = ui->infoshow_4->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query2.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query2.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query2.value(2).toString());
            ui->infoshow_4->setItem(rowIndex-1,0,item1);
            ui->infoshow_4->setItem(rowIndex-1,1,item2);
            ui->infoshow_4->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->checkBox_34->isChecked())
    {
        ui->infoshow_4->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"月份"<<"出勤天数";
        ui->infoshow_4->setHorizontalHeaderLabels(list);

        while(query1.next())
        { //输出工种信息
            ui->infoshow_4->insertRow(ui->infoshow_4->rowCount());//插入一行
            int rowIndex = ui->infoshow_4->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query1.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query1.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query1.value(2).toString());
            ui->infoshow_4->setItem(rowIndex-1,0,item1);
            ui->infoshow_4->setItem(rowIndex-1,1,item2);
            ui->infoshow_4->setItem(rowIndex-1,2,item3);
        }
     }
}

// 工资管理查询模块
void admini::on_pushButton_17_clicked()
{
    ui->infoshow_9->setRowCount(0); //设置行数为0
    ui->infoshow_9->clearContents(); //清空内容

    QString memID = ui->lineEdit_5->text();  //员工ID
    QDate dateEdit1 = ui->dateEdit_9->date();
    QString dateinfo1 = dateEdit1.toString("yyyy-MM-dd"); //开始日期
    QDate dateEdit2 = ui->dateEdit_18->date();
    QString dateinfo2 = dateEdit2.toString("yyyy-MM-dd"); //截至日期


    QSqlQuery query1(db); //查询总视图
    QSqlQuery query2(db); //查询基本工资
    QSqlQuery query3(db); //查询出勤工资
    QSqlQuery query4(db); //查询津贴
    QSqlQuery query5(db); //查询年终奖
    if(ui->checkBox_35->isChecked())
    {
        query1 = dao->monthincome0(memID,dateinfo1,dateinfo2);
        query2 = dao->funincome0(memID,dateinfo1,dateinfo2);
        query3 = dao->hereincome0(memID,dateinfo1,dateinfo2);
        query4 = dao->tipincome0(memID,dateinfo1,dateinfo2);
        query5 = dao->annualincome0(memID,dateinfo1,dateinfo2);
    }
    else
    {
        query1 = dao->monthincome1(memID);
        query2 = dao->funincome1(memID);
        query3 = dao->hereincome1(memID);
        query4 = dao->tipincome1(memID);
        query5 = dao->annualincome1(memID);
    }

    if(ui->comboBox_7->currentIndex() == 0)
    {
        ui->infoshow_9->setColumnCount(6); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"月份"<<"基本工资"<<"出勤工资"<<"加班津贴"<<"月共计";
        ui->infoshow_9->setHorizontalHeaderLabels(list);

        while(query1.next())
        {
            ui->infoshow_9->insertRow(ui->infoshow_9->rowCount());//插入一行
            int rowIndex = ui->infoshow_9->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query1.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query1.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query1.value(2).toString());
            QTableWidgetItem *item4=new QTableWidgetItem(query1.value(3).toString());
            QTableWidgetItem *item5=new QTableWidgetItem(query1.value(4).toString());
            QTableWidgetItem *item6=new QTableWidgetItem(query1.value(5).toString());
            ui->infoshow_9->setItem(rowIndex-1,0,item1);
            ui->infoshow_9->setItem(rowIndex-1,1,item2);
            ui->infoshow_9->setItem(rowIndex-1,2,item3);
            ui->infoshow_9->setItem(rowIndex-1,3,item4);
            ui->infoshow_9->setItem(rowIndex-1,4,item5);
            ui->infoshow_9->setItem(rowIndex-1,5,item6);
        }
    }
    else if(ui->comboBox_7->currentIndex() == 1)
    {
        ui->infoshow_9->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"月份"<<"基本工资";
        ui->infoshow_9->setHorizontalHeaderLabels(list);

        while(query2.next())
        { //输出工种信息
            ui->infoshow_9->insertRow(ui->infoshow_9->rowCount());//插入一行
            int rowIndex = ui->infoshow_9->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query2.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query2.value(3).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query2.value(4).toString());
            ui->infoshow_9->setItem(rowIndex-1,0,item1);
            ui->infoshow_9->setItem(rowIndex-1,1,item2);
            ui->infoshow_9->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_7->currentIndex() == 2)
    {
        ui->infoshow_9->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"月份"<<"出勤工资";
        ui->infoshow_9->setHorizontalHeaderLabels(list);

        while(query3.next())
        { //输出工种信息
            ui->infoshow_9->insertRow(ui->infoshow_9->rowCount());//插入一行
            int rowIndex = ui->infoshow_9->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query3.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query3.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query3.value(2).toString());
            ui->infoshow_9->setItem(rowIndex-1,0,item1);
            ui->infoshow_9->setItem(rowIndex-1,1,item2);
            ui->infoshow_9->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_7->currentIndex() == 3)
    {
        ui->infoshow_9->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"月份"<<"加班津贴";
        ui->infoshow_9->setHorizontalHeaderLabels(list);

        while(query4.next())
        { //输出工种信息
            ui->infoshow_9->insertRow(ui->infoshow_9->rowCount());//插入一行
            int rowIndex = ui->infoshow_9->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query4.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query4.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query4.value(2).toString());
            ui->infoshow_9->setItem(rowIndex-1,0,item1);
            ui->infoshow_9->setItem(rowIndex-1,1,item2);
            ui->infoshow_9->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_7->currentIndex() == 4)
    {
        ui->infoshow_9->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"年终奖";
        ui->infoshow_9->setHorizontalHeaderLabels(list);

        while(query5.next())
        { //输出工种信息
            ui->infoshow_9->insertRow(ui->infoshow_9->rowCount());//插入一行
            int rowIndex = ui->infoshow_9->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query5.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query5.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query5.value(2).toString());
            ui->infoshow_9->setItem(rowIndex-1,0,item1);
            ui->infoshow_9->setItem(rowIndex-1,1,item2);
            ui->infoshow_9->setItem(rowIndex-1,2,item3);
        }
    }
}

// 工资管理删除模块
void admini::on_pushButton_18_clicked()
{
    ui->infoshow_9->setRowCount(0); //设置行数为0
    ui->infoshow_9->clearContents(); //清空内容

    QString memID = ui->lineEdit_5->text();  //员工ID
    QDate dateEdit = ui->dateEdit_9->date();
    QString dateinfo = dateEdit.toString("yyyy-MM-dd"); //日期

    // 拒绝无类别删除
    if(ui->comboBox_7->currentIndex() == 0)
    {
        QMessageBox::warning(NULL,"wrong","请按照类别删除！");
    }
    // 基本工资的设定在工种管理
    else if(ui->comboBox_7->currentIndex() == 1)
    {
        QMessageBox::warning(NULL,"wrong","请在工种管理处改变基本工资！");
    }
    else if(ui->comboBox_7->currentIndex() == 2)
    {
        dao->hereincomedelete(memID,dateinfo);
        QMessageBox::information(NULL,"delete","删除成功");
    }
    else if(ui->comboBox_7->currentIndex() == 3)
    {
        dao->tipincomedelete(memID,dateinfo);
        QMessageBox::information(NULL,"delete","删除成功");
    }
    else if(ui->comboBox_7->currentIndex() == 4)
    {
        dao->annualincomedelete(memID,dateinfo);
        QMessageBox::information(NULL,"delete","删除成功");
    }
}

// 工资管理修改模块
void admini::on_pushButton_20_clicked()
{
    ui->infoshow_9->setRowCount(0); //设置行数为0
    ui->infoshow_9->clearContents(); //清空内容

    QString memID = ui->lineEdit_17->text();  //员工ID
    QDate dateEdit = ui->dateEdit_12->date();
    QString dateinfo = dateEdit.toString("yyyy-MM-dd"); //日期
    QString sal0 = ui->lineEdit_7->text(); //金额
    QString here0 = ui->lineEdit_8->text();//月出勤数量
    QString delay0 = ui->lineEdit_49->text(); //月加班数量
    int flag = 0; //修改标志

    if(ui->comboBox_10->currentIndex() == 0)
    {
        if(sal0 != "")
        {
            int sal = sal0.toDouble();
            dao->hereincomeupdate(memID,dateinfo,sal);
            flag = 1;
        }
        if(here0 !="")
        {
            int here = here0.toInt();
            dao->heredayupdate(memID,dateinfo,here);
            flag = 1;

        }
        if(flag == 1)
        {
            QMessageBox::information(NULL,"update","修改成功");
        }
    }
    else if(ui->comboBox_10->currentIndex() == 1)
    {
        if(sal0 != "")
        {
            int sal = sal0.toDouble();
            dao->tipincomeupdate(memID,dateinfo,sal);
            flag = 1;
        }
        if(delay0 !="")
        {
            int delay = delay0.toInt();
            dao->tipdayupdate(memID,dateinfo,delay);
            flag = 1;

        }
        if(flag == 1)
        {
            QMessageBox::information(NULL,"update","修改成功");
        }
    }
    else if(ui->comboBox_10->currentIndex() == 2)
    {
        if(sal0 != "")
        {
            int sal = sal0.toDouble();
            dao->annualincomeupdate(memID,dateinfo,sal);
            flag = 1;
        }
        if(flag == 1)
        {
            QMessageBox::information(NULL,"update","修改成功");
        }
    }
}


// 工资管理插入模块
void admini::on_pushButton_19_clicked()
{
    ui->infoshow_9->setRowCount(0); //设置行数为0
    ui->infoshow_9->clearContents(); //清空内容

    QString memID = ui->lineEdit_17->text();  //员工ID
    QDate dateEdit = ui->dateEdit_12->date();
    QString dateinfo = dateEdit.toString("yyyy-MM-dd"); //日期
    QString sal0 = ui->lineEdit_7->text(); //金额
    int sal = sal0.toDouble();
    QString here0 = ui->lineEdit_8->text();//月出勤数量
    int here  = here0.toDouble();
    QString delay0 = ui->lineEdit_49->text(); //月加班数量
    int delay = delay0.toDouble();

    if(ui->comboBox_10->currentIndex() == 0)
    {
        dao->hereinsert(memID,dateinfo,sal,here);
        QMessageBox::information(NULL,"insert","插入成功");
    }
    else if(ui->comboBox_10->currentIndex() == 1)
    {
        dao->tipinsert(memID,dateinfo,sal,delay);
        QMessageBox::information(NULL,"insert","插入成功");
    }
    else if(ui->comboBox_10->currentIndex() == 2)
    {
        dao->annualinsert(memID,dateinfo,sal);
        QMessageBox::information(NULL,"insert","插入成功");
    }
}

// 工资管理年度查询模块
void admini::on_pushButton_67_clicked()
{
    ui->infoshow_9->setRowCount(0); //设置行数为0
    ui->infoshow_9->clearContents(); //清空内容

    QString memID = ui->lineEdit_48->text();  //员工ID
    QString yearinfo0 = ui->spinBox_9->text();
    int yearinfo = yearinfo0.toInt(); //年份

    QSqlQuery query = dao->annualimcomeselect(memID,yearinfo);

    if(ui->comboBox_18->currentIndex() == 0)
    {
        ui->infoshow_9->setColumnCount(7); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"基本工资和"<<"出勤工资和"<<"加班津贴和"<<"年终奖"<<"年共计";
        ui->infoshow_9->setHorizontalHeaderLabels(list);

        while(query.next())
        {
            ui->infoshow_9->insertRow(ui->infoshow_9->rowCount());//插入一行
            int rowIndex = ui->infoshow_9->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(2).toString());
            QTableWidgetItem *item4=new QTableWidgetItem(query.value(3).toString());
            QTableWidgetItem *item5=new QTableWidgetItem(query.value(4).toString());
            QTableWidgetItem *item6=new QTableWidgetItem(query.value(5).toString());
            QTableWidgetItem *item7=new QTableWidgetItem(query.value(6).toString());
            ui->infoshow_9->setItem(rowIndex-1,0,item1);
            ui->infoshow_9->setItem(rowIndex-1,1,item2);
            ui->infoshow_9->setItem(rowIndex-1,2,item3);
            ui->infoshow_9->setItem(rowIndex-1,3,item4);
            ui->infoshow_9->setItem(rowIndex-1,4,item5);
            ui->infoshow_9->setItem(rowIndex-1,5,item6);
            ui->infoshow_9->setItem(rowIndex-1,6,item7);
        }
    }
    else if(ui->comboBox_18->currentIndex() == 1)
    {
        ui->infoshow_9->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"基本工资和";
        ui->infoshow_9->setHorizontalHeaderLabels(list);

        while(query.next())
        {
            ui->infoshow_9->insertRow(ui->infoshow_9->rowCount());//插入一行
            int rowIndex = ui->infoshow_9->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(2).toString());
            ui->infoshow_9->setItem(rowIndex-1,0,item1);
            ui->infoshow_9->setItem(rowIndex-1,1,item2);
            ui->infoshow_9->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_18->currentIndex() == 2)
    {
        ui->infoshow_9->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"出勤工资和";
        ui->infoshow_9->setHorizontalHeaderLabels(list);

        while(query.next())
        {
            ui->infoshow_9->insertRow(ui->infoshow_9->rowCount());//插入一行
            int rowIndex = ui->infoshow_9->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(3).toString());
            ui->infoshow_9->setItem(rowIndex-1,0,item1);
            ui->infoshow_9->setItem(rowIndex-1,1,item2);
            ui->infoshow_9->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_18->currentIndex() == 3)
    {
        ui->infoshow_9->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"加班津贴和";
        ui->infoshow_9->setHorizontalHeaderLabels(list);

        while(query.next())
        {
            ui->infoshow_9->insertRow(ui->infoshow_9->rowCount());//插入一行
            int rowIndex = ui->infoshow_9->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(4).toString());
            ui->infoshow_9->setItem(rowIndex-1,0,item1);
            ui->infoshow_9->setItem(rowIndex-1,1,item2);
            ui->infoshow_9->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_18->currentIndex() == 4)
    {
        ui->infoshow_9->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"年终奖";
        ui->infoshow_9->setHorizontalHeaderLabels(list);

        while(query.next())
        {
            ui->infoshow_9->insertRow(ui->infoshow_9->rowCount());//插入一行
            int rowIndex = ui->infoshow_9->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(5).toString());
            ui->infoshow_9->setItem(rowIndex-1,0,item1);
            ui->infoshow_9->setItem(rowIndex-1,1,item2);
            ui->infoshow_9->setItem(rowIndex-1,2,item3);
        }
    }
    else if(ui->comboBox_18->currentIndex() == 5)
    {
        ui->infoshow_9->setColumnCount(3); //设置列数
        QStringList list; //设置信息栏的表头
        list<<"员工ID"<<"年份"<<"年总计";
        ui->infoshow_9->setHorizontalHeaderLabels(list);

        while(query.next())
        {
            ui->infoshow_9->insertRow(ui->infoshow_9->rowCount());//插入一行
            int rowIndex = ui->infoshow_9->rowCount();
            QTableWidgetItem *item1=new QTableWidgetItem(query.value(0).toString());
            QTableWidgetItem *item2=new QTableWidgetItem(query.value(1).toString());
            QTableWidgetItem *item3=new QTableWidgetItem(query.value(6).toString());
            ui->infoshow_9->setItem(rowIndex-1,0,item1);
            ui->infoshow_9->setItem(rowIndex-1,1,item2);
            ui->infoshow_9->setItem(rowIndex-1,2,item3);
        }
    }
}
