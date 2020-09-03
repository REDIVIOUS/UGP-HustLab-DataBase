# UGP-HustLab-DataBase
[undergraduate project in hust] a staff salary management system.
## 数据库系统大作业
* 文件夹中由三个文件/文件夹组成：qt项目源码、sql文件（用于创建基本表和视图）、readme。
* qt源码在DataBase_System文件夹中
* 可执行文件也在DataBase_System文件夹中，但是注意若在非我方主机上执行，需要重新配置数据库连接的参数。
* 对于上述所提到的可执行文件，若不在我方主机上运行，需重新配置数据库参数并配置（因为其连接的是我电脑上的数据库），具体配置见源码的main.cpp。更改过源码之后，需要重新编译qt项目并运行。我们需要连接到的新数据库的构造和数据的录入见DatabaseSystem.sql文件。