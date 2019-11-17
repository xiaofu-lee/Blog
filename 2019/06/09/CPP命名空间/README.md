<!--
{
	"author": "lxf",
	"title": "CPP命名空间",
	"date": "2019-06-09 04:12:28",
	"category": "C++程序设计"
}
-->

CPP命名空间
------------------------------------------------------------
- 有两种形式的命名空间 有名的和无名的。  
1. 有名的命名空间：
```
namespace 命名空间名 {
    声明序列可选
}
eg:
namespace mynamespace {
    void fun() {
        function body
    }
}

namespace mynamespace {
    void fun() {
        function body
    }

    namespace submynamespace {
        void fun() {
            function body
        }
    }
}

```
1. 无名的命名空间：
```
namespace {
    声明序列可选
}
eg:
namespace {
    void fun() {
        function body
    }
}

```

- 使用命名空间  
  using namespace \<namespace name\>;  
  namespace \<name::namespace member\>  

- 使用命名空间别名  
namespace alias = \<namespace name\>;  
- 使用类别名  
using class alias = \<class name\>;  
eg: using String = std::string;  
------------------------------------------------------------
[返回上级目录](./../../../../categories/C++程序设计/README.md)  |
[返回首页](./../../../../README.md)