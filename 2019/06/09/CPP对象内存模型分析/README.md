<!--
{
	"author": "lxf",
	"title": "CPP对象内存模型分析",
	"date": "2019-06-09 04:07:04",
	"category": "C++程序设计"
}
-->

CPP对象内存模型分析
------------------------------------------------------------
```
类代码：
class D {
    public:
        D() {
            d = 4;
        }~D() {}
    virtual void fun4() {
        printf("%d:: d = %d\n", __LINE__, d);
    }
    public:
        int d;
};
实例对象内存数据分布：
0019 FF34 30 20 42 00-- -- > 00422030 2 D 10 40 00--fun4--虚函数表
0019 FF38 04 00 00 00-- -- > int d;
```

```
类代码：
class B {
    public:
        B() {
            b = 2;
        }~B() {}
    virtual void fun2() {
        printf("%d:: b = %d\n", __LINE__, b);
    }
    public:
        int b;
};
class D: public B {
    public: D() {
        d = 4;
    }~D() {}
    virtual void fun4() {
        printf("%d:: d = %d\n", __LINE__, d);
    }
    public: int d;
};
实例对象内存数据分布：
0019 FF14 CC 2 F 42 00-- -- > 00422 FCC 2 D 10 40 00--fun2--虚函数表
                              00422 FD0 46 10 40 00--fun4
0019 FF1C 02 00 00 00-- -- > int b;
0019 FF24 04 00 00 00-- -- > int d;
```

```
类代码：
class B {
    public:
        B() {
            b = 2;
        }~B() {}
    virtual void fun2() {
        printf("%d:: b = %d\n", __LINE__, b);
    }
    public:
        int b;
};

class C {
    public:
        C() {
            c = 3;
        }~C() {}
    virtual void fun3() {
        printf("%d:: c = %d\n", __LINE__, c);
    }
    public:
        int c;
};
class D: public B, public C {
    public: D() {
        d = 4;
    }~D() {}
    virtual void fun4() {
        printf("%d:: d = %d\n", __LINE__, d);
    }
    public: int d;
};
实例对象内存数据分布：
0019 FF20 64 60 42 00-- -- > 00426064 46 10 40 00--fun2--虚函数表
                             00426068 41 10 40 00--fun4
0019 FF24 02 00 00 00-- -- > int b;
0019 FF28 2 C 50 42 00-- -- > 0042502 C 3 C 10 40 00--fun3--虚函数表
0019 FF2C 03 00 00 00-- -- > int c;
0019 FF30 04 00 00 00-- -- > int d;
```

```
类代码：
class A {
    public:
        A() {
            a = 1;
        }~A() {}
    virtual void fun1() {
        printf("%d:: a = %d\n", __LINE__, a);
    }
    public:
        int a;
};

class B: public A {
    public: B() {
        b = 2;
    }~B() {}
    virtual void fun2() {
        printf("%d:: b = %d\n", __LINE__, b);
    }
    public: int b;
};

class C {
    public:
        C() {
            c = 3;
        }~C() {}
    virtual void fun3() {
        printf("%d:: c = %d\n", __LINE__, c);
    }
    public:
        int c;
};

class D: public B, public C {
    public: D() {
        d = 4;
    }~D() {}
    virtual void fun4() {
        printf("%d:: d = %d\n", __LINE__, d);
    }
    public: int d;
};
实例对象内存数据分布：
0019 FF1C 2 C 50 42 00-- -- > 0042502 C 55 10 40 00--fun1--虚函数表
                              00425030 46 10 40 00--fun2
                              00425034 41 10 40 00--fun4
0019 FF20 01 00 00 00-- -- > int a;
0019 FF24 02 00 00 00-- -- > int b;
0019 FF28 38 50 42 00-- -- > 00425038 3 C 10 40 00--fun3--虚函数表
0019 FF2C 03 00 00 00-- -- > int c;
0019 FF30 04 00 00 00-- -- > int d;
```

菱形继承

```
类代码：
class A {
    public:
        A() {
            a = 1;
        }~A() {}
    virtual void fun1() {
        printf("%d:: a = %d\n", __LINE__, a);
    }
    public:
        int a;
};

class B: public A {
    public: B() {
        b = 2;
    }~B() {}
    virtual void fun2() {
        printf("%d:: b = %d\n", __LINE__, b);
        fun1();
    }
    public: int b;
};

class C: public A {
    public: C() {
        c = 3;
    }~C() {}
    virtual void fun3() {
        printf("%d:: c = %d\n", __LINE__, c);
        fun1();
    }
    public: int c;
};

class D: public B, public C {
    public: D() {
        d = 4;
    }~D() {}
    virtual void fun4() {
        printf("%d:: d = %d\n", __LINE__, d);
    }
    public: int d;
};
实例对象内存数据分布：
0019 FF18 40 50 42 00-- -- > 00425040 55 10 40 00--fun1--虚函数表
                             00425044 46 10 40 00--fun2
                             00425048 41 10 40 00--fun4
                             0042504 C 55 10 40 00--fun1
                             00425050 46 10 40 00--fun2
                             00425054 55 10 40 00--fun1
                             00425058 3 C 10 40 00--fun3
0019 FF1C 01 00 00 00-- -- > int a;
0019 FF20 02 00 00 00-- -- > int b;
0019 FF24 8 C 60 42 00-- -- > 0042608 C 55 10 40 00--fun1--虚函数表
                              00426090 3 C 10 40 00--fun3
0019 FF28 01 00 00 00-- -- > int a;
0019 FF2C 03 00 00 00-- -- > int c;
0019 FF30 04 00 00 00-- -- > int d;
```

虚拟继承

```
类代码：
class A {
    public:
        A() {
            a = 1;
        }~A() {}
    virtual void fun1() {
        printf("%d:: a = %d\n", __LINE__, a);
    }
    public:
        int a;
};

class B: virtual public A {
    public: B() {
        b = 2;
    }~B() {}
    virtual void fun2() {
        printf("%d:: b = %d\n", __LINE__, b);
    }
    public: int b;
};

class C: virtual public A {
    public: C() {
        c = 3;
    }~C() {}
    virtual void fun3() {
        printf("%d:: c = %d\n", __LINE__, c);
    }
    public: int c;
};

class D: public B, public C {
    public: D() {
        d = 4;
    }~D() {}
    virtual void fun4() {
        printf("%d:: d = %d\n", __LINE__, d);
    }
    public: int d;
};
实例对象内存数据分布：
0019 FF10 30 50 42 00-- -- > 00425030 46 10 40 00--fun2--虚函数表
                             00425034 41 10 40 00--fun4
0019 FF14 54 50 42 00-- -- > 00425054 FC FF FF FF--虚基类表
0019 FF18 02 00 00 00-- -- > int b;
0019 FF1C A4 60 42 00-- -- > 004260 A4 3 C 10 40 00--fun3
0019 FF20 94 60 42 00-- -- > 00426094 FC FF FF FF--虚基类表
0019 FF24 03 00 00 00-- -- > int c;
0019 FF28 04 00 00 00-- -- > int d;
0019 FF2C 40 50 42 00-- -- > 00425040 55 10 40 00--fun1--虚函数表
0019 FF30 01 00 00 00-- -- > int a;
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/C++程序设计/README.md)  |
[返回首页](./../../../../README.md)