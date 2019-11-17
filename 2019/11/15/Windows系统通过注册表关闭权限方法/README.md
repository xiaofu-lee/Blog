<!--
{
	"author": "lxf",
	"title": "Windows系统通过注册表关闭权限方法",
	"date": "2019-11-15 00:16:50",
	"category": "其他"
}
-->

Windows系统通过注册表关闭权限方法
------------------------------------------------------------
2019-11-15 00:16:50 &emsp;   

关闭权限方法  

    打开注册表: regedit
	找到路径：HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Policies\System
	修改键值：EnableLUA 为0

------------------------------------------------------------
[返回上级目录](./../../../../categories/其他/README.md)  |
[返回首页](./../../../../README.md)