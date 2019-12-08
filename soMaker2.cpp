#include<iostream>
#include"interface.h"
class job2:public interface{
public:
    virtual void show(){
        std::cout<<"this is job2"<<std::endl;
    }
};
extern "C"{
    interface* getInstance(){    //导出符号
        return new job2;
    }
}
