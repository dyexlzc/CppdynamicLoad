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