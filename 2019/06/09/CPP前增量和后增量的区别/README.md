<!--
{
	"author": "lxf",
	"title": "CPP前增量和后增量的区别",
	"date": "2019-06-09 04:10:10",
	"category": "C++程序设计"
}
-->

CPP前增量和后增量的区别
------------------------------------------------------------
前增量：
```
Obj& operator ++(Obj& obj)
{
    obj.value++;
    return obj;
}
```
后增量：
```
Obj operator ++(Obj& obj, int)
{
    Obj temp(obj);
    obj.value++;
    return temp;
}
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/C++程序设计/README.md)  |
[返回首页](./../../../../README.md)