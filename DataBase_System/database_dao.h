#ifndef DATABASE_DAO_H
#define DATABASE_DAO_H
#include<QSqlDatabase>
#include<QSqlQuery>
#include <Qtsql>

class database_dao
{
public:
    QSqlQuery MemberSelect(); //查询员工表
    QSqlQuery RecordSelectDM(QString dateinfo1, QString dateinfo2, QString MID); //查询出勤表（带有日期和ID）
    QSqlQuery MonthIncomeSelectDM(QString dateinfo1, QString dateinfo2, QString MID); //月份收入（带时间和ID）
    QSqlQuery YearIncomeSelectDM(QString dateinfo1, QString dateinfo2, QString MID); //年收入（带时间和ID）
    QSqlQuery MonthIncomeSelectM(QString MID); //月份收入（带ID）
    QSqlQuery YearIncomeSelectM(QString MID); //年收入（带ID）
    QSqlQuery YearIncomeSelectYM(QString MID,int yeartime); //年收入（带年份和ID）
    QSqlQuery MemberSelectID(QString IDnum); // 员工查询（ID）
    QSqlQuery MemberSelectNA(QString IDName); // 员工查询（名字）
    QSqlQuery MemberSelectIT(QString IDtype); // 员工查询（工种）
    void MemberdeleteID(QString IDnum); // 员工删除（ID）
    void MemberdeleteNA(QString IDName); // 员工删除（名字）
    void MemberdeleteIT(QString IDtype); // 员工删除（工种）
    void MemberupdateName(QString IDnum,QString IDName);
    void MemberupdateType(QString IDnum,QString IDtype); //更改员工（工种）
    void MemberupdatePWD(QString IDnum,QString pwd); //更改员工（密码）
    void MemberupdateAGE(QString IDnum,int age); //更改员工（年龄）
    void MemberupdateMAN(QString IDnum); //更改员工（性别男）
    void MemberupdateWOMAN(QString IDnum); //更改员工（性别女）
    void Memberinsert(QString IDnum, QString IDName, int sex, int age, QString IDtype, QString pwd); //插入员工信息
    void MemberupdateAuth(QString IDnum, QString pwd, int auth); // 更改员工表（管理员权限）
    QSqlQuery WTypeSelect(); // 查询工种表
    QSqlQuery WTypeSelectID(QString typeID); // 查询工种表（ID）
    QSqlQuery WTypeSelectNA(QString typeName); // 查询工种表（名字）
    void WTypedeleteID(QString typeID); // 删除工种表（ID）
    void WTypedeleteNA(QString typeName); // 删除工种表（名称）
    void WTypeupdateNA(QString typeID, QString typeName); // 修改工种表（名称）
    void WTypeupdateL(QString typeID, int level); // 修改工种表（等级）
    void WTypeupdateS(QString typeID, double sal); // 修改工种表（基本工资）
    void WTypeinsert(QString typeID, QString typeName, int level, double sal); // 插入工种
    QSqlQuery WTypetotalID(QString typeID); // 工种人数统计（ID统计）
    QSqlQuery WTypetotalNA(QString typeName); //工种人数统计（按照名字统计）
    void Recorddelete(QString memID, QString dateinfo); // 出勤记录删除
    void RecordupdateIH(QString memID, QString dateinfo); // 出勤记录更新（已出勤）
    void RecordupdateNH(QString memID, QString dateinfo); // 出勤记录更新（未出勤）
    void RecordupdateID(QString memID, QString dateinfo); // 出勤记录更新（已加班）
    void RecordupdateND(QString memID, QString dateinfo); // 出勤记录更新（未加班）
    void Recordinsert(QString memID, QString dateinfo, int here, int delay); // 出勤记录插入
    QSqlQuery Recordhereday(QString memID, QString dateinfo); //查询出勤天数
    QSqlQuery Recorddelayday(QString memID, QString dateinfo); //查询加班天数
    QSqlQuery Recordheredelayday(QString memID, QString dateinfo); //加班天数、出勤天数联合查询
    QSqlQuery monthincome0(QString memID, QString dateinfo1, QString dateinfo2); // 月工资总计（指定时间）
    QSqlQuery monthincome1(QString memID); // 月工资总计（不指定时间）
    QSqlQuery funincome0(QString memID, QString dateinfo1, QString dateinfo2); // 月基本工资（指定时间）
    QSqlQuery funincome1(QString memID); // 月基本工资（不指定时间）
    QSqlQuery hereincome0(QString memID, QString dateinfo1, QString dateinfo2); // 月出勤工资（指定时间）
    QSqlQuery hereincome1(QString memID); // 月出勤工资（不指定时间）
    QSqlQuery tipincome0(QString memID, QString dateinfo1, QString dateinfo2); // 月加班那津贴（指定时间）
    QSqlQuery tipincome1(QString memID); //月加班津贴（不指定时间）
    QSqlQuery annualincome0(QString memID, QString dateinfo1, QString dateinfo2); //年终奖（指定时间）
    QSqlQuery annualincome1(QString memID); //年终奖 （不指定时间）
    void hereincomedelete(QString memID, QString dateinfo); // 删除出勤工资
    void tipincomedelete(QString memID, QString dateinfo); // 删除加班津贴
    void annualincomedelete(QString memID, QString dateinfo); // 删除年终奖
    void hereincomeupdate(QString memID, QString dateinfo, double sal); // 修改出勤工资
    void heredayupdate(QString memID, QString dateinfo, int here); // 修改出勤天数
    void tipincomeupdate(QString memID, QString dateinfo, double sal); // 修改加班津贴
    void tipdayupdate(QString memID, QString dateinfo, int delay); // 修改加班天数
    void annualincomeupdate(QString memID, QString dateinfo, double sal); // 修改年终奖
    void hereinsert(QString memID, QString dateinfo, double sal, int here); // 插入出勤工资
    void tipinsert(QString memID, QString dateinfo, double sal, int delay); // 插入加班津贴
    void annualinsert(QString memID, QString dateinfo, double sal); // 插入年终奖
    QSqlQuery annualimcomeselect(QString memID, int yearinfo); // 查询年度总信息
};

#endif // DATABASE_DAO_H
