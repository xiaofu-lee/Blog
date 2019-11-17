<!--
{
	"author": "lxf",
	"title": "Linux安装JDK",
	"date": "2019-04-12 03:14:08",
	"category": "其他"
}
-->

Linux安装JDK
------------------------------------------------------------
### 一、查看是否已安装JDK  
    rpm -qa | grep java # java
    rpm -qa | grep jdk # jdk

### 二、卸载之前安装的JDK
    rpm -e --nodeps xxx
    rpm -qa | grep java | xargs rpm -e --nodeps # 批量卸载
    rpm -qa | grep jdk  | xargs rpm -e --nodeps # 批量卸载

### 三、下载JDK
    rpm: wget https://download.oracle.com/otn-pub/java/jdk/8u201-b09/42970487e3af4f5aa5bca3f542482c60/jdk-8u201-linux-x64.rpm?AuthParam=1550898243_3bb525af34ad3a3875d5c1e973be2925
	tar: wget https://download.oracle.com/otn-pub/java/jdk/8u201-b09/42970487e3af4f5aa5bca3f542482c60/jdk-8u201-linux-x64.tar.gz?AuthParam=1550898465_13e429d87528c534b97917bffbbf05e1
    以上地址可进入JDK官网查找

### 四、安装
    rpm:
    rpm -ivh package.rpm 
    yum -y install package.rpm
    tar:
    tar -zxvf jdk-xxxx-linux-x64.tar.gz

### 五、配置JDK环境变量  
    编辑 /etc/profile 文件
    vi /etc/profile
    在最后一行添加如下内容：
    # JDK 环境变量
    export JAVA_HOME=/home/jdk/jdk1.8
    export CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
    export PATH=$JAVA_HOME/bin:$PATH
    重新加载/etc/profile：
    source /etc/profile

### 六、检查JDK是否安装成功  
    java -version
------------------------------------------------------------
[返回上级目录](./../../../../categories/other/README.md)  |
[返回首页](./../../../../README.md)