# CppDynamicLoad —— Linux下cpp动态加载so库

**主要文件**
dload.hpp			主要的实现文件
interface.h			定义统一的接口

example:
文件1:main.cpp
编译指令:    g++ main.cpp -std=c++11 -ldl -o dl 
其中只加了-ldl，表明使用了系统dlfcn.h相关的库
```C++
#include <iostream>
#include <dlfcn.h>     //动态加载so所需的头文件
#include "dLoad.hpp" //获取so所继承的基类
using namespace std;
int main()
{
    dynamicLoader loader("./"); //so文件在根目录下
    loader.load("so1.so");      //加载so1.so
    interface *p=loader.getInstance("so1.so");  //获取so1.so中的实例，获得对象
    p->run();   //调用函数
    delete p;   //删除对象
    loader.unload("so1.so");    //卸载动态库
}
```

文件2-n...:soMaker[n].cpp
编译指令: g++ -fPIC -shared soMaker[n].cpp -o so1.so
期中-fPIC：使得编译器产生位置无关的代码,PIC就是position independent code
PIC使.so文件的代码段变为真正意义上的共享
-shared 表示告诉编译器生成so文件

```C++
#include<iostream>
#include"interface.h"
class job1:public interface{		//继承自interface接口
public:
    virtual void run(){			//重写run（）接口
        std::cout<<"this is job131"<<std::endl;
    }
    ~job1(){
        std::cout<<"job1 descontruct"<<std::endl;
    }
};
extern "C"{
    interface* getInstance(){    //导出符号，必须要有的extern "C"
        return new job1;
    }    
}
```