<!--
{
	"author": "lxf",
	"title": "Hexo搭建个人博客",
	"date": "2019-04-12 03:23:10",
	"category": "其他"
}
-->

Hexo搭建个人博客
------------------------------------------------------------
1. **安装Git**  
    ```
    yum -y install git
    git config --global user.name "ilixiaofu"// github用户名
    git config --global user.email  "ilixiaofu@qq.com"// github注册邮箱
    ```
2. **安装NVM**  
    ```
    git clone https://github.com/creationix/nvm.git
    source nvm/nvm.sh
    ```
3. **安装Nodejs**  
    ```
    nvm install stable
    添加Node环境变量
    vim /etc/profile
    在底部添加 PATH 变量
	export PATH=$PATH:/usr/local/node/bin
	source /etc/profile
    ```

4. **安装Hexo**  
    ```
    npm install -g hexo-cli
   ```
5. **Hexo常用命令**  
    ```
    hexo init <文件名>
    hexo g == hexo generate     
    hexo d == hexo deploy
    hexo s == hexo server
    hexo n == hexo new
    hexo clean
    ```
------------------------------------------------------------
[返回上级目录](./../../../../categories/other/README.md)  |
[返回首页](./../../../../README.md)