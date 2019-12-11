#include <iostream>
#include "interface.h"
class job1 : public interface
{
public:
    virtual void run()
    {
        std::cout << "this is job131" << std::endl;
    }
    ~job1()
    {
        std::cout << "job1 descontruct" << std::endl;
    }
};
extern "C"
{
    interface *getInstance()
    { //导出符号
        return new job1;
    }
}
