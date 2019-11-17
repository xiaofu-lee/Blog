<!--
{
	"author": "lxf",
	"title": "Docker安装",
	"date": "2019-04-12 03:26:31",
	"category": "其他"
}
-->

Docker安装
------------------------------------------------------------
1. yum包更新
```
yum update
```
2. 安装需要的软件包， yum-util 提供yum-config-manager功能，另外两个是devicemapper驱动依赖的
```
yum install -y yum-utils device-mapper-persistent-data lvm2
```
3. 设置yum源
```
yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
```
4. 查看所有仓库中所有docker版本，并选择特定版本安装
```
yum list docker-ce --showduplicates | sort -r
```
5. 安装docker
```
yum install docker-ce -y
```
6. 验证安装是否成功
```
docker version
```
7. 启动并加入开机启动
```
systemctl start docker
systemctl enable docker
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/other/README.md)  |
[返回首页](./../../../../README.md)