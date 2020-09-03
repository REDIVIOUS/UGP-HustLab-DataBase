IF EXISTS (SELECT * FROM sysdatabases WHERE name ='SalarySystem')
	BEGIN
		DECLARE @dbname SYSNAME    
		SET @dbname = 'SalarySystem' --这个是要删除的数据库库名 SalarySystem 
				 
		DECLARE @s NVARCHAR(1000)    
		DECLARE tb CURSOR LOCAL   
		FOR  
			SELECT s = 'kill   ' + CAST(spid AS VARCHAR)  
			FROM   MASTER..sysprocesses  
			WHERE  dbid = DB_ID(@dbname)    
				 
		OPEN   tb      
		FETCH   NEXT   FROM   tb   INTO   @s    
		WHILE @@fetch_status = 0  
		BEGIN  
			EXEC (@s)   
			FETCH NEXT FROM tb INTO @s  
		END    
		CLOSE   tb    
		DEALLOCATE   tb    
			
		EXEC ('drop   database   [' + @dbname + ']') 
		--DROP DATABASE TrainRecord 
	END
GO


create database SalarySystem;
go

use SalarySystem
go

-- 员工表
IF EXISTS(SELECT * FROM sys.objects where name = 'Member')
	Drop TABLE Member;
create table Member(
	MemID varchar(20) primary key,
	MemName varchar(20),
	Sex bit,
	Age int,
	TypeName varchar(20),
	Password varchar(20),
	Auth bit,
	foreign key (TypeName) references WType(TypeName))
/* 加入测试样例*/
insert into Member Values('100000000A','张三',1,30,'销售岗','19900101',0)
insert into Member Values('100000000D','李四',1,30,'管理岗','19800101',1)
insert into Member Values('100000000W','王五',1,30,'销售岗','19860101',0)
select * from Member

-- 工种表
IF EXISTS(SELECT * FROM sys.objects where name = 'WType')
	Drop TABLE WType;
create table WType(
	TypeID varchar(20) primary key,
	TypeName varchar(20) unique,
	Tlevel int,
	Fsal decimal(20,2))
insert into WType Values('A01','销售岗',1,10000.00)
insert into WType Values('F01','管理岗',10,30000.00)
select * from WType

-- 基本工资表
IF EXISTS(SELECT * FROM sys.objects where name = 'FunSal')
	Drop TABLE FunSal;
create table FunSal(
	MemID varchar(20),
	MonthDate date,
	Fsal decimal(20,2),
	primary key (MemID,MonthDate),
	foreign key (MemID) references Member(MemID))

-- 考勤记录表
IF EXISTS(SELECT * FROM sys.objects where name = 'Record')
	Drop TABLE Record;
create table Record(
	MemID varchar(20),
	RDate date,
	ifhere bit,
	ifdelay bit,
	primary key (MemID,RDate),
	foreign key (MemID) references Member(MemID))
insert into Record Values('100000000A','2020-05-01',1,1)
insert into Record Values('100000000D','2020-05-01',1,0)
insert into Record Values('100000000W','2020-05-01',1,0)
insert into Record Values('100000000A','2020-05-02',1,1)
insert into Record Values('100000000D','2020-05-02',1,0)
insert into Record Values('100000000W','2020-05-02',1,1)
insert into Record Values('100000000A','2020-05-03',1,0)
insert into Record Values('100000000D','2020-05-03',1,0)
insert into Record Values('100000000W','2020-05-03',1,0)
select * from Record

-- 出勤工资表
IF EXISTS(SELECT * FROM sys.objects where name = 'Heresal')
	Drop TABLE Heresal;
create table Heresal(
	MemID varchar(20),
	MonthDate date,
	heresal decimal(20,2),
	hereday int,
	primary key (MemID,MonthDate),
	foreign key (MemID) references Member(MemID))

-- 津贴工资表
IF EXISTS(SELECT * FROM sys.objects where name = 'Tipsal')
	Drop TABLE Tipsal;
create table Tipsal(
	MemID varchar(20),
	MonthDate date,
	tipsal decimal(20,2),
	tipday int,
	primary key (MemID,MonthDate),
	foreign key (MemID) references Member(MemID))

-- 年终奖
IF EXISTS(SELECT * FROM sys.objects where name = 'AnnualReward')
	Drop TABLE AnnualReward;
create table AnnualReward(
	MemID varchar(20),
	YearDate int,
	annualsal decimal(20,2),
	primary key (MemID,YearDate),
	foreign key (MemID) references Member(MemID))

-- 基本工资插入
insert into FunSal
	select MemID,'2020-01-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
insert into FunSal
	select MemID,'2020-02-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
insert into FunSal
	select MemID,'2020-03-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
insert into FunSal
	select MemID,'2020-04-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
insert into FunSal
	select MemID,'2020-05-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
insert into FunSal
	select MemID,'2020-06-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
insert into FunSal
	select MemID,'2020-07-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
insert into FunSal
	select MemID,'2020-08-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
insert into FunSal
	select MemID,'2020-09-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
insert into FunSal
	select MemID,'2020-10-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
insert into FunSal
	select MemID,'2020-11-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
insert into FunSal
	select MemID,'2020-12-01',Fsal
	from Member,WType
	where Member.TypeName = Wtype.TypeName
select * from FunSal

-- 出勤数据插入
insert into Heresal Values('100000000A','2020-01-01',330.00,25)
insert into Heresal Values('100000000A','2020-02-01',400.00,28)
insert into Heresal Values('100000000A','2020-03-01',330.00,25)
insert into Heresal Values('100000000A','2020-04-01',400.00,28)
insert into Heresal Values('100000000A','2020-05-01',380.00,27)
insert into Heresal Values('100000000A','2020-06-01',300.00,23)
insert into Heresal Values('100000000A','2020-07-01',360.00,29)
insert into Heresal Values('100000000A','2020-08-01',330.00,25)
insert into Heresal Values('100000000A','2020-09-01',330.00,25)
insert into Heresal Values('100000000A','2020-10-01',400.00,28)
insert into Heresal Values('100000000A','2020-11-01',400.00,28)
insert into Heresal Values('100000000A','2020-12-01',260.00,21)

insert into Heresal Values('100000000D','2020-01-01',680.00,25)
insert into Heresal Values('100000000D','2020-02-01',800.00,28)
insert into Heresal Values('100000000D','2020-03-01',680.00,25)
insert into Heresal Values('100000000D','2020-04-01',550.00,21)
insert into Heresal Values('100000000D','2020-05-01',580.00,23)
insert into Heresal Values('100000000D','2020-06-01',550.00,21)
insert into Heresal Values('100000000D','2020-07-01',650.00,24)
insert into Heresal Values('100000000D','2020-08-01',680.00,25)
insert into Heresal Values('100000000D','2020-09-01',680.00,25)
insert into Heresal Values('100000000D','2020-10-01',800.00,28)
insert into Heresal Values('100000000D','2020-11-01',800.00,28)
insert into Heresal Values('100000000D','2020-12-01',550.00,21)

insert into Heresal Values('100000000W','2020-01-01',400.00,28)
insert into Heresal Values('100000000W','2020-02-01',400.00,28)
insert into Heresal Values('100000000W','2020-03-01',330.00,25)
insert into Heresal Values('100000000W','2020-04-01',400.00,28)
insert into Heresal Values('100000000W','2020-05-01',400.00,28)
insert into Heresal Values('100000000W','2020-06-01',400.00,28)
insert into Heresal Values('100000000W','2020-07-01',330.00,25)
insert into Heresal Values('100000000W','2020-08-01',330.00,25)
insert into Heresal Values('100000000W','2020-09-01',260.00,21)
insert into Heresal Values('100000000W','2020-10-01',240.00,19)
insert into Heresal Values('100000000W','2020-11-01',400.00,28)
insert into Heresal Values('100000000W','2020-12-01',400.00,28)

-- 津贴插入
insert into Tipsal Values('100000000A','2020-01-01',600.00,5)
insert into Tipsal Values('100000000A','2020-02-01',960.00,8)
insert into Tipsal Values('100000000A','2020-03-01',1200.00,10)
insert into Tipsal Values('100000000A','2020-04-01',1800.00,15)
insert into Tipsal Values('100000000A','2020-05-01',600.00,5)
insert into Tipsal Values('100000000A','2020-06-01',600.00,5)
insert into Tipsal Values('100000000A','2020-07-01',240.00,2)
insert into Tipsal Values('100000000A','2020-08-01',360.00,3)
insert into Tipsal Values('100000000A','2020-09-01',1800.00,15)
insert into Tipsal Values('100000000A','2020-10-01',600.00,5)
insert into Tipsal Values('100000000A','2020-11-01',840.00,7)
insert into Tipsal Values('100000000A','2020-12-01',1320.00,11)

insert into Tipsal Values('100000000D','2020-01-01',1000.00,5)
insert into Tipsal Values('100000000D','2020-02-01',3200.00,16)
insert into Tipsal Values('100000000D','2020-03-01',400.00,2)
insert into Tipsal Values('100000000D','2020-04-01',1000.00,5)
insert into Tipsal Values('100000000D','2020-05-01',1000.00,5)
insert into Tipsal Values('100000000D','2020-06-01',400.00,2)
insert into Tipsal Values('100000000D','2020-07-01',1000.00,5)
insert into Tipsal Values('100000000D','2020-08-01',200.00,1)
insert into Tipsal Values('100000000D','2020-09-01',200.00,1)
insert into Tipsal Values('100000000D','2020-10-01',1000.00,5)
insert into Tipsal Values('100000000D','2020-11-01',400.00,2)
insert into Tipsal Values('100000000D','2020-12-01',400.00,2)

insert into Tipsal Values('100000000W','2020-01-01',720.00,6)
insert into Tipsal Values('100000000W','2020-02-01',600.00,5)
insert into Tipsal Values('100000000W','2020-03-01',1800.00,15)
insert into Tipsal Values('100000000W','2020-04-01',720.00,6)
insert into Tipsal Values('100000000W','2020-05-01',600.00,5)
insert into Tipsal Values('100000000W','2020-06-01',840.00,7)
insert into Tipsal Values('100000000W','2020-07-01',240.00,2)
insert into Tipsal Values('100000000W','2020-08-01',360.00,3)
insert into Tipsal Values('100000000W','2020-09-01',1200.00,10)
insert into Tipsal Values('100000000W','2020-10-01',840.00,7)
insert into Tipsal Values('100000000W','2020-11-01',840.00,7)
insert into Tipsal Values('100000000W','2020-12-01',600.00,5)

select * from FunSal
select * from Heresal
select * from Tipsal

-- 年终奖的计算
insert into AnnualReward
	select FunSal.MemID,Year(FunSal.MonthDate) AS YearDate,SUM(FunSal.Fsal + Heresal.heresal + Tipsal.tipsal)/12 AS total
	from FunSal,Heresal,Tipsal
	where FunSal.MemID = Heresal.MemID AND FunSal.MemID = Tipsal.MemID
		AND FunSal.MonthDate = Heresal.MonthDate AND Funsal.MonthDate = Tipsal.MonthDate
	group by FunSal.MemID,Year(FunSal.MonthDate)

	select * from AnnualReward

IF (EXISTS(SELECT * FROM sysobjects WHERE id=object_id(N'cal_reward') AND OBJECTPROPERTY(id, N'IsTrigger') = 1))
	DROP TRIGGER cal_reward
GO
create trigger cal_reward on Funsal 
	after insert
as
	
	
GO

-- 月收入视图
IF EXISTS(SELECT * FROM dbo.sysobjects WHERE id = object_id('monthincome') AND OBJECTPROPERTY(id, N'IsView') = 1)
	DROP VIEW monthincome
GO
CREATE VIEW monthincome
AS
	select Funsal.MemID,Funsal.MonthDate,Funsal.Fsal,Heresal.heresal,Tipsal.tipsal,(Funsal.Fsal + Heresal.heresal + Tipsal.tipsal) AS Total
	from FunSal,Heresal,Tipsal
	where Funsal.MemID = Heresal.MemID and FunSal.MemID = Tipsal.MemID
		and Funsal.MonthDate = Heresal.MonthDate and Funsal.MonthDate = Tipsal.MonthDate
go

-- 年收入视图
IF EXISTS(SELECT * FROM dbo.sysobjects WHERE id = object_id('yearincome') AND OBJECTPROPERTY(id, N'IsView') = 1)
	DROP VIEW yearincome
GO
CREATE VIEW yearincome
AS
	select monthincome.MemID, Year(monthincome.MonthDate) as YearTime,
		sum(monthincome.Fsal) as YFsal, sum(monthincome.heresal) as YHeresal,sum(monthincome.tipsal) as YTipsal,AnnualReward.annualsal,
		(sum(monthincome.Fsal + monthincome.heresal + monthincome.tipsal) + AnnualReward.annualsal) as yeartotal
	from monthincome,AnnualReward
	where monthincome.MemID = AnnualReward.MemID and AnnualReward.YearDate = Year(monthincome.MonthDate)
	group by monthincome.MemID, Year(monthincome.MonthDate),AnnualReward.annualsal
go