#include <iostream>
#include "interface.h"
class mul : public interface
{
    struct param{           //参数和结果都要放在一个自定义的struct中
        int numa,numb;
    }t;
public:
    virtual void run(char* buffer,char* returns)
    {
        std::cout << "this is FuncMUL" << std::endl;
        memcpy(&t,buffer,sizeof(t));
        int result=t.numa*t.numb;
        memcpy(returns,&result,sizeof(result));
    }
};
extern "C"
{
    interface *getInstance()
    { //导出符号
        return new mul;
    }
}
