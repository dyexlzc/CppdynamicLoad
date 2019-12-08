#include<iostream>
#include<dlfcn.h>       //动态加载so所需的头文件
#include"interface.h"   //获取so所继承的基类
using namespace std;
int main(){
    interface* ptr;
    interface* (*func)(void);
    void *so1=dlopen("./so1.so",RTLD_LAZY);
    if(!so1){cout<<"open so1 err.";return 0;}
    func=(interface*(*)(void))dlsym(so1,"getInstance");
    ptr=(interface*)func();
    ptr->show();
    dlclose(so1);

    void *so2=dlopen("./so2.so",RTLD_LAZY);
    if(!so2){cout<<"open so2 err.";return 0;}
    func=(interface*(*)(void))dlsym(so2,"getInstance");
    ptr=(interface*)func();
    ptr->show();
    dlclose(so2);
    return 0;
}