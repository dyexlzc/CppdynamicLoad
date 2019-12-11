#include <iostream>
#include <dlfcn.h>     //动态加载so所需的头文件
#include "dLoad.hpp" //获取so所继承的基类
using namespace std;
int main()
{
    dynamicLoader loader("./"); //so文件在根目录下
    loader.load("so1.so");      //加载so1.so
    interface *p=loader.getInstance("so1.so");  //获取so1.so中的实例，获得对象
    p->run();  //调用函数
    delete p;   //删除对象
    loader.unload("so1.so");    //卸载动态库
}