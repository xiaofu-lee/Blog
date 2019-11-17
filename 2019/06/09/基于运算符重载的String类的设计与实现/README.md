<!--
{
	"author": "lxf",
	"title": "基于运算符重载的String类的设计与实现",
	"date": "2019-06-09 03:42:23",
	"category": "C++程序设计"
}
-->

基于运算符重载的String类的设计与实现
------------------------------------------------------------
```
#include <stdio.h>
#include <string.h>

namespace MyStirng
{
class String
{
public:
    String(const char *str = NULL)
    {
        if (NULL == str)
        {
            m_string = new char[1]{0x00};
        }
        else
        {
            int length = strlen(str);
            m_string = new char[length + 1];
            memcpy(m_string, str, length + 1);
        }
    }

    String(const String &str)
    {
        int length = strlen(str.m_string);
        m_string = new char[length + 1];
        memcpy(m_string, str.m_string, length + 1);
    }

    ~String()
    {
        delete[] m_string;
    }

    // String a; a = b;
    String &operator=(const String &str)
    {
        if (this == &str)
        {
            return *this;
        }
        delete[] m_string;
        int length = strlen(str.m_string);
        m_string = new char[length + 1];
        memcpy(m_string, str.m_string, length + 1);
        return *this;
    }

    // String a; a = "   ";
    String &operator=(const char *str)
    {
        delete[] m_string;
        if (NULL == str)
        {
            m_string = new char[1]{0x00};
        }
        else
        {
            int length = strlen(str);
            m_string = new char[length + 1];
            memcpy(m_string, &str, length + 1);
        }
        return *this;
    }

    // String a; a += b;
    String &operator+=(const String &str)
    {
        char *tmp = m_string;
        int length1 = strlen(tmp);
        int length2 = strlen(str.m_string);
        int length = length1 + length2;
        m_string = new char[length + 1];
        memcpy(m_string, tmp, length1 + 1);
        strncat(m_string, str.m_string, length2);
        delete[] tmp;
        return *this;
    }

    // String a; a += "";
    String &operator+=(const char* str)
    {
        String tmp(str);
        *this += tmp;
        return *this;
    }
    // String a; a + b;
    String operator+(const String &str) const
    {
        String result;
        result += *this;
        result += str;
        return result;
    }

    // String a; a + "";
    String operator+(const char* str) const
    {
        String result = *this;;
        result += str;
        return result;
    }

    inline const char *getString() const
    {
        return this->m_string;
    }

private:
    char *m_string;
};
} // namespace MyStirng

using namespace std;
using namespace MyStirng;

int main(int argc, char const *argv[])
{
    String a("hello");
    printf("%s\n", a.getString());
    String b(a);
    printf("%s\n", b.getString());
    String c = b;
    printf("%s\n", c.getString());
    String d = "world";
    printf("%s\n", d.getString());
    String e = c + d;
    printf("%s\n", e.getString());
    c += d;
    printf("%s\n", c.getString());
    e += "xxxx";
    printf("%s\n", e.getString());
    String f = e + "xxxx";
    printf("%s\n", f.getString());
    return 0;
}
```
------------------------------------------------------------
[返回上级目录](./../../../../categories/C++程序设计/README.md)  |
[返回首页](./../../../../README.md)