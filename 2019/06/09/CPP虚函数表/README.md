<!--
{
	"author": "lxf",
	"title": "CPP虚函数表",
	"date": "2019-06-09 03:58:09",
	"category": "C++程序设计"
}
-->

CPP虚函数表
------------------------------------------------------------
源代码：
```
#define TYPE long long *

class Object
{
public:
	Object() {}
	virtual void foo1()
	{
		printf("%s\n", "i am foo one");
	}
	virtual void foo2() {
		printf("%s\n", "i am foo two");
	}
};


int main()
{
	typedef void (*fun)();
	Object object;
	void *vftable = *(void**)&object;
	fun foo[2] = {0};
	foo[0] = (fun) ((TYPE)vftable)[0];
	foo[1] = (fun) ((TYPE)vftable)[1];
	foo[0]();
	foo[1]();
	return 0;
}

```
------------------------------------------------------------
[返回上级目录](./../../../../categories/C++程序设计/README.md)  |
[返回首页](./../../../../README.md)