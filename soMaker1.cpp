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
