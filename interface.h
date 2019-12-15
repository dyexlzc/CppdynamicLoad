#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <cstring>
class interface
{ //任务所继承的任务接口
public:
    virtual void run(char* buffer,char* returns) = 0;
    virtual ~interface() {}
};
////////////////////////////////////////////////////////////////
//服务器消息枚举类型
enum MsgType{
    DonotExist,
    Success,
    OtherErr
};
/////////////////////////////////////////////////////////
struct NetMsg{                      //发送给服务器的请求格式
    char FuncName[20];              //函数名称
    char Param[1024];               //存放函数参数的缓冲区，至于函数参数将会被填充到什么样的结构体里需要动态加载so中的定义
};
struct RespondMsg{
    MsgType msgType;                //来自服务器的消息类型
    char data[1024];                //服务器发送的消息
};
#endif