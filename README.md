# CppDynamicLoad —— Linux下cpp动态加载so库


**主要文件**
dload.hpp			主要的实现文件  
interface.h			定义统一的接口  

example:  
>可以clone下来后使用make so,make两条指令  
>分别生成so和可执行文件./dl，执行./dl即可   
>
文件1:main.cpp  
编译指令:    g++ main.cpp -std=c++11 -ldl -o dl  
其中只加了-ldl，表明使用了系统dlfcn.h相关的库  
```C++
#include <iostream>
#include <dlfcn.h>   //动态加载so所需的头文件
#include "dLoad.hpp" //获取so所继承的基类
using namespace std;
struct param_Add{
    int a,b;
};
int main()
{
    dynamicLoader loader("./");                  //so文件在根目录下
    loader.load("add.so");                       //加载so1.so
    interface *p = loader.getInstance("add.so"); //获取so1.so中的实例，获得对象
    struct param_Add pa;    //和服务端保持一致的参数格式
    pa.a=1;
    pa.b=2;
    int result;
    p->run((char*)&pa,(char*)&result);                                    //调用函数
    cout<<"调用函数add:"<<result<<endl;
    delete p;                                    //删除对象
    loader.unload("add.so");                     //卸载动态库
}
```

文件2-n...:soMaker[n].cpp  
编译指令: g++ -fPIC -shared add_so.cpp -o add.so  
期中-fPIC：使得编译器产生位置无关的代码,PIC就是position independent code  
PIC使.so文件的代码段变为真正意义上的共享  
-shared 表示告诉编译器生成so文件  

>add_so.cpp
```C++
#include <iostream>
#include "interface.h"
class Add : public interface
{
    struct param{           //参数和结果都要放在一个自定义的struct中
        int numa,numb;
    }t;
public:
    virtual void run(char* buffer,char* returns)
    {
        std::cout << "this is FuncAdd" << std::endl;
        memcpy(&t,buffer,sizeof(t));//用buffer初始化结构体，从中解出
        int result=t.numa+t.numb;     //计算结果
        memcpy(returns,&result,sizeof(result));//把结果保存
    }
    ~Add()
    {
        std::cout << "Add descontruct" << std::endl;
    }
};
extern "C"
{
    interface *getInstance()
    { //导出符号
        return new Add;
    }
}

```
