#include "interface.h"
#include <string>
class UsrLogin : public interface{
    struct loginStruct{
        char usrname[10];
        char pwd[10];
    }usr;
public:
    virtual void run(char* buffer,char* returns){
        memcpy(&usr,buffer,sizeof(usr));
        std::string respond;
        if(std::string(usr.usrname)=="dyexlzc"&&std::string(usr.pwd)=="1998111"){
            respond="登录成功！欢迎使用系统";
        }
        else{
            respond="登录失败，检查用户名和密码";
        }
        strcpy(returns,respond.c_str());
    }

};
extern "C"
{
    interface *getInstance()
    { //导出符号
        return new UsrLogin;
    }
}