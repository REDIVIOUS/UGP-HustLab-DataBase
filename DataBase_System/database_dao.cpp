#include "database_dao.h"
#include "globalvarible.h"

QSqlQuery database_dao::MemberSelect()
{
    QSqlQuery query(db);
    query.exec("select * from Member");
    return query;
}

//查询出勤表（带有日期和ID）
QSqlQuery database_dao::RecordSelectDM(QString dateinfo1, QString dateinfo2, QString MID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString ("select * from Record where RDate >= '%1' and RDate <= '%2' and MemID = '%3'and ifhere = 1").arg(dateinfo1).arg(dateinfo2).arg(MID);
    query.exec(sqlsentence);
    return query;
}

//月份收入（带时间和ID）
QSqlQuery database_dao::MonthIncomeSelectDM(QString dateinfo1, QString dateinfo2, QString MID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from monthincome where MonthDate >= '%1' and MonthDate <= '%2' and  MemID = '%3'").arg(dateinfo1).arg(dateinfo2).arg(MID);
    query.exec(sqlsentence);
    return query;
}

//年收入（带时间和ID）
QSqlQuery database_dao::YearIncomeSelectDM(QString dateinfo1, QString dateinfo2, QString MID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from yearincome where YearTime >= Year('%1') and YearTime <= Year('%2') and MemID = '%2'").arg(dateinfo1).arg(dateinfo2).arg(MID);
    query.exec(sqlsentence);
    return query;
}

//月份收入（带ID）
QSqlQuery database_dao::MonthIncomeSelectM(QString MID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from monthincome where MemID = '%1'").arg(MID);
    query.exec(sqlsentence);
    return query;
}

//年收入（带ID）
QSqlQuery database_dao::YearIncomeSelectM(QString MID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from yearincome where MemID = '%1'").arg(MID);
    query.exec(sqlsentence);
    return query;
}

// 年收入（带年份和ID）
QSqlQuery database_dao::YearIncomeSelectYM(QString MID,int yeartime)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from yearincome where MemID = '%1'and YearTime = %2").arg(MID).arg(yeartime);
    query.exec(sqlsentence);
    return query;
}
// 员工查询（ID）
QSqlQuery database_dao::MemberSelectID(QString IDnum)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from Member where MemID = '%1'").arg(IDnum);
    query.exec(sqlsentence);
    return query;
}

// 员工查询（名字）
QSqlQuery database_dao::MemberSelectNA(QString IDName)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from Member where MemName = '%1'").arg(IDName);
    query.exec(sqlsentence);
    return query;
}

// 员工查询（工种）
QSqlQuery database_dao::MemberSelectIT(QString IDtype)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from Member where TypeName = '%1'").arg(IDtype);
    query.exec(sqlsentence);
    return query;
}

// 员工删除（ID）
void database_dao::MemberdeleteID(QString IDnum)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("delete from Member where MemID = '%1'").arg(IDnum);
    query.exec(sqlsentence);
}

// 员工删除（名字）
void database_dao::MemberdeleteNA(QString IDName)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("delete from Member where MemName = '%1'").arg(IDName);
    query.exec(sqlsentence);
}


// 员工删除（工种）
void database_dao::MemberdeleteIT(QString IDtype)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("delete from Member where TypeName = '%1'").arg(IDtype);
    query.exec(sqlsentence);
}

//更改员工（姓名）
void database_dao::MemberupdateName(QString IDnum,QString IDName)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Member set MemName = '%2' where MemID = '%1'").arg(IDnum).arg(IDName);
    query.exec(sqlsentence);
}

//更改员工（工种）
void database_dao::MemberupdateType(QString IDnum,QString IDtype)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Member set TypeName = '%2' where MemID = '%1'").arg(IDnum).arg(IDtype);
    query.exec(sqlsentence);
}

//更改员工（密码）
void database_dao::MemberupdatePWD(QString IDnum,QString pwd)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Member set Password = '%2' where MemID = '%1'").arg(IDnum).arg(pwd);
    query.exec(sqlsentence);
}

//更改员工（年龄）
void database_dao::MemberupdateAGE(QString IDnum,int age)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Member set age = %2 where MemID = '%1'").arg(IDnum).arg(age);
    query.exec(sqlsentence);
}

//更改员工（性别男）
void database_dao::MemberupdateMAN(QString IDnum)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Member set Sex = 1 where MemID = '%1'").arg(IDnum);
    query.exec(sqlsentence);
}

//更改员工（性别女）
void database_dao::MemberupdateWOMAN(QString IDnum)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Member set Sex = 0 where MemID = '%1'").arg(IDnum);
    query.exec(sqlsentence);
}

//插入员工信息
void database_dao::Memberinsert(QString IDnum, QString IDName, int sex, int age, QString IDtype, QString pwd)
{
    QSqlQuery query(db);
    //插入时默认无管理员权限，除非手动添加
    QString sqlsentence = QString("insert into Member values('%1','%2',%3,%4,'%5','%6',0)").arg(IDnum).arg(IDName).arg(sex).arg(age).arg(IDtype).arg(pwd);
    query.exec(sqlsentence);
}

// 更改员工表（管理员权限）
void database_dao::MemberupdateAuth(QString IDnum, QString pwd, int auth)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Member set Auth = %3 where MemID = '%1' and Password = '%2'").arg(IDnum).arg(pwd).arg(auth);
    query.exec(sqlsentence);
}

// 查询工种表（ID）
QSqlQuery database_dao::WTypeSelectID(QString typeID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from WType where TypeID = '%1'").arg(typeID);
    query.exec(sqlsentence);
    return query;
}

// 查询工种表
QSqlQuery database_dao::WTypeSelect()
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from WType");
    query.exec(sqlsentence);
    return query;
}


// 查询工种表（名字）
QSqlQuery database_dao::WTypeSelectNA(QString typeName)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from WType where TypeName = '%1'").arg(typeName);
    query.exec(sqlsentence);
    return query;
}

// 删除工种表（ID）
void database_dao::WTypedeleteID(QString typeID)
{
    QSqlQuery query(db);
    QString sqlsentence =QString("delete from WType where TypeID = '%1'").arg(typeID);
    query.exec(sqlsentence);
}

// 删除工种表（名称）
void database_dao::WTypedeleteNA(QString typeName)
{
    QSqlQuery query(db);
    QString sqlsentence =QString("delete from WType where TypeName = '%1'").arg(typeName);
    query.exec(sqlsentence);
}

// 修改工种表（名称）
void database_dao::WTypeupdateNA(QString typeID, QString typeName)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update WType set TypeName = '%2' where TypeID = '%1'").arg(typeID).arg(typeName);
    query.exec(sqlsentence);
}

// 修改工种表（等级）
void database_dao::WTypeupdateL(QString typeID, int level)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update WType set Tlevel = %2 where TypeID = '%1'").arg(typeID).arg(level);
    query.exec(sqlsentence);
}

// 修改工种表（基本工资）
void database_dao::WTypeupdateS(QString typeID, double sal)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update WType set Fsal = %2 where TypeID = '%1'").arg(typeID).arg(sal);
    query.exec(sqlsentence);
}

// 插入工种
void database_dao::WTypeinsert(QString typeID, QString typeName, int level, double sal)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("insert into WType values('%1','%2',%3,%4)").arg(typeID).arg(typeName).arg(level).arg(sal);
    query.exec(sqlsentence);
}

// 工种人数统计（ID统计）
QSqlQuery database_dao::WTypetotalID(QString typeID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select TypeID,WType.TypeName,Fsal,count(MemID) from Member,WType where Member.TypeName = WType.TypeName and TypeID = '%1' group by TypeID,WType.TypeName,Fsal").arg(typeID);
    query.exec(sqlsentence);
    return query;
}

//工种人数统计（按照名字统计）
QSqlQuery database_dao::WTypetotalNA(QString typeName)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select TypeID,WType.TypeName,Fsal,count(MemID) from Member,WType where Member.TypeName = WType.TypeName and WType.TypeName = '%1' group by TypeID,WType.TypeName,Fsal").arg(typeName);
    query.exec(sqlsentence);
    return query;
}

// 出勤记录删除
void database_dao::Recorddelete(QString memID, QString dateinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("delete from Record where MemID = '%1' and RDate = '%2'").arg(memID).arg(dateinfo);
    query.exec(sqlsentence);
}

// 出勤记录更新（已出勤）
void database_dao::RecordupdateIH(QString memID, QString dateinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Record set ifhere = 1 where MemID = '%1' and RDate = '%2'").arg(memID).arg(dateinfo);
    query.exec(sqlsentence);
}

// 出勤记录更新（未出勤）
void database_dao::RecordupdateNH(QString memID, QString dateinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Record set ifhere = 0 where MemID = '%1' and RDate = '%2'").arg(memID).arg(dateinfo);
    query.exec(sqlsentence);
}

// 出勤记录更新（已加班）
void database_dao::RecordupdateID(QString memID, QString dateinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Record set ifdelay = 1 where MemID = '%1' and RDate = '%2'").arg(memID).arg(dateinfo);
    query.exec(sqlsentence);
}

// 出勤记录更新（未加班）
void database_dao::RecordupdateND(QString memID, QString dateinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Record set ifdelay = 0 where MemID = '%1' and RDate = '%2'").arg(memID).arg(dateinfo);
    query.exec(sqlsentence);
}

// 出勤记录插入
void database_dao::Recordinsert(QString memID, QString dateinfo, int here, int delay)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("insert into Record values('%1','%2',%3,%4)").arg(memID).arg(dateinfo).arg(here).arg(delay);
    query.exec(sqlsentence);
}

//查询出勤天数
QSqlQuery database_dao::Recordhereday(QString memID, QString dateinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select MemID,MonthDate,hereday from Heresal where MemID = '%1' and MonthDate = '%2'").arg(memID).arg(dateinfo);
    query.exec(sqlsentence);
    return query;
}

//查询加班天数
QSqlQuery database_dao::Recorddelayday(QString memID, QString dateinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select MemID,MonthDate,tipday from Tipsal where MemID = '%1' and MonthDate = '%2'").arg(memID).arg(dateinfo);
    query.exec(sqlsentence);
    return query;
}

//加班天数、出勤天数联合查询
QSqlQuery database_dao::Recordheredelayday(QString memID, QString dateinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select Heresal.MemID,Tipsal.MonthDate,hereday,tipday from Heresal,Tipsal where Heresal.MemID = '%1' and Heresal.MonthDate = '%2' and Heresal.MemID = Tipsal.MemID and Heresal.MonthDate = Tipsal.MonthDate").arg(memID).arg(dateinfo);
    query.exec(sqlsentence);
    return query;
}

// 月工资总计（指定时间）
QSqlQuery database_dao::monthincome0(QString memID, QString dateinfo1, QString dateinfo2)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from monthincome where MemID = '%1' and MonthDate >= '%2' and MonthDate <= '%3'").arg(memID).arg(dateinfo1).arg(dateinfo2);
    query.exec(sqlsentence);
    return query;
}

// 月工资总计（不指定时间）
QSqlQuery database_dao::monthincome1(QString memID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from monthincome where MemID = '%1'").arg(memID);
    query.exec(sqlsentence);
    return query;
}

// 月基本工资（指定时间）
QSqlQuery database_dao::funincome0(QString memID, QString dateinfo1, QString dateinfo2)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from Funsal where MemID = '%1' and MonthDate >= '%2' and MonthDate <= '%3'").arg(memID).arg(dateinfo1).arg(dateinfo2);
    query.exec(sqlsentence);
    return query;
}

// 月基本工资（不指定时间）
QSqlQuery database_dao::funincome1(QString memID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from Funsal where MemID = '%1'").arg(memID);
    query.exec(sqlsentence);
    return query;
}

// 月出勤工资（指定时间）
QSqlQuery database_dao::hereincome0(QString memID, QString dateinfo1, QString dateinfo2)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from Heresal where MemID = '%1' and MonthDate >= '%2' and MonthDate <= '%3'").arg(memID).arg(dateinfo1).arg(dateinfo2);
    query.exec(sqlsentence);
    return query;
}

// 月出勤工资（不指定时间）
QSqlQuery database_dao::hereincome1(QString memID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from Heresal where MemID = '%1'").arg(memID);
    query.exec(sqlsentence);
    return query;
}

// 月加班那津贴（指定时间）
QSqlQuery database_dao::tipincome0(QString memID, QString dateinfo1, QString dateinfo2)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from Tipsal where MemID = '%1' and MonthDate >= '%2' and MonthDate <= '%3'").arg(memID).arg(dateinfo1).arg(dateinfo2);
    query.exec(sqlsentence);
    return query;
}

//月加班津贴（不指定时间）
QSqlQuery database_dao::tipincome1(QString memID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from Tipsal where MemID = '%1'").arg(memID);
    query.exec(sqlsentence);
    return query;
}

//年终奖（指定时间）
QSqlQuery database_dao::annualincome0(QString memID, QString dateinfo1, QString dateinfo2)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from AnnualReward where MemID = '%1' and YearDate >= Year('%2') and YearDate <= Year('%3')").arg(memID).arg(dateinfo1).arg(dateinfo2);
    query.exec(sqlsentence);
    return query;
}

//年终奖 （不指定时间）
QSqlQuery database_dao::annualincome1(QString memID)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from AnnualReward where MemID = '%1'").arg(memID);
    query.exec(sqlsentence);
    return query;
}

// 删除出勤工资
void database_dao::hereincomedelete(QString memID, QString dateinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("delete from Heresal where MemID = '%1' and MonthDate = '%2'").arg(memID).arg(dateinfo);
    query.exec(sqlsentence);
}

// 删除加班津贴
void database_dao::tipincomedelete(QString memID, QString dateinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("delete from Tipsal where MemID = '%1' and MonthDate = '%2'").arg(memID).arg(dateinfo);
    query.exec(sqlsentence);
}

// 删除年终奖
void database_dao::annualincomedelete(QString memID, QString dateinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("delete from AnnualReward where MemID = '%1' and YearDate = Year('%2')").arg(memID).arg(dateinfo);
    query.exec(sqlsentence);
}

// 修改出勤工资
void database_dao::hereincomeupdate(QString memID, QString dateinfo, double sal)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Heresal set heresal = %3 where MemID = '%1' and MonthDate = '%2'").arg(memID).arg(dateinfo).arg(sal);
    query.exec(sqlsentence);
}

// 修改出勤天数
void database_dao::heredayupdate(QString memID, QString dateinfo, int here)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Heresal set hereday = %3 where MemID = '%1' and MonthDate = '%2'").arg(memID).arg(dateinfo).arg(here);
    query.exec(sqlsentence);
}

// 修改加班津贴
void database_dao::tipincomeupdate(QString memID, QString dateinfo, double sal)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Tipsal set tipsal = %3 where MemID = '%1' and MonthDate = '%2'").arg(memID).arg(dateinfo).arg(sal);
    query.exec(sqlsentence);
}

// 修改加班天数
void database_dao::tipdayupdate(QString memID, QString dateinfo, int delay)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update Tipsal set tipday = %3 where MemID = '%1' and MonthDate = '%2'").arg(memID).arg(dateinfo).arg(delay);
    query.exec(sqlsentence);
}

// 修改年终奖
void database_dao::annualincomeupdate(QString memID, QString dateinfo, double sal)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("update AnnualReward set annualsal = %3 where MemID = '%1' and YearDate = Year('%2')").arg(memID).arg(dateinfo).arg(sal);
    query.exec(sqlsentence);
}

// 插入出勤工资
void database_dao::hereinsert(QString memID, QString dateinfo, double sal, int here)
{
    QSqlQuery query(db);
    QString sqlsentence;
    sqlsentence = QString("insert into Heresal values('%1','%2',%3,%4)").arg(memID).arg(dateinfo).arg(sal).arg(here);
    query.exec(sqlsentence);
}

// 插入加班津贴
void database_dao::tipinsert(QString memID, QString dateinfo, double sal, int delay)
{
    QSqlQuery query(db);
    QString sqlsentence;
    sqlsentence = QString("insert into Tipsal values('%1','%2',%3,%4)").arg(memID).arg(dateinfo).arg(sal).arg(delay);
    query.exec(sqlsentence);
}

// 插入年终奖
void database_dao::annualinsert(QString memID, QString dateinfo, double sal)
{
    QSqlQuery query(db);
    QString sqlsentence;
    sqlsentence = QString("insert into AnnualReward values('%1',Year('%2'),%3)").arg(memID).arg(dateinfo).arg(sal);
    query.exec(sqlsentence);
}

// 查询年度总信息
QSqlQuery database_dao::annualimcomeselect(QString memID, int yearinfo)
{
    QSqlQuery query(db);
    QString sqlsentence = QString("select * from yearincome where MemID = '%1' and YearTime = %2").arg(memID).arg(yearinfo);
    query.exec(sqlsentence);
    return query;
}

