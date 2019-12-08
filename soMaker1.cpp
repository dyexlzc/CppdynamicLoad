#include<iostream>
#include"interface.h"
class job1:public interface{
public:
    virtual void show(){
        std::cout<<"this is job131"<<std::endl;
    }
};
extern "C"{
    job1* getInstance(){    //导出符号
        return new job1;
    }    
}
