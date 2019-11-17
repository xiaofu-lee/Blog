<!--
{
	"author": "lxf",
	"title": "Nginx安装",
	"date": "2019-04-12 03:19:48",
	"category": "其他"
}
-->

Nginx安装
------------------------------------------------------------
### 一、安装编译工具及库文件
    安装gcc
    yum  -y install gcc  
    安装g++  
    yum -y install gcc-c++  
    yum -y install libstdc++-devel
    安装其他依赖  
    yum -y install pcre-devel openssl openssl-devel make zlib zlib-devel libtool 

### 二、解压安装包
    tar zxvf nginx-x.x.x.tar.gz

### 三、进入安装包目录并编译安装
    cd nginx-x.x.x
    ./configure --prefix=/home/nginx/webserver/nginx --with-http_stub_status_module --with-http_ssl_module && make && make install

### 四、查看nginx安装位置
    whereis nginx

### 五、查看nginx版本
    nginx -v

### 六、启动nginx
    ./sbin/nginx

### 七、查看nginx进程
    ps -aus | grep nginx

### 八、nginx常用命令
    ./sbin/nginx -h # 命令帮助
    ./sbin/nginx -s <stop | quit | reload> # 停止、退出、重启
    ./sbin/nginx -t # 验证配置文件是否配置正确
------------------------------------------------------------
[返回上级目录](./../../../../categories/other/README.md)  |
[返回首页](./../../../../README.md)