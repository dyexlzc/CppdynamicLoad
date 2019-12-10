#ifndef _DLOAD_HPP
#define _DLOAD_HPP
#include <list>
#include <unordered_map>
#include <string>
#include <dlfcn.h> //加载动态库所需要的头文件
#include "interface.h"
class dload
{
    class SoWrapper
    {
    public:
        interface *(*getInstanceFunc)(void);
        void *soPtr;
        SoWrapper(interface *(*fptr)(void), void *soptr)
        {
            getInstanceFunc = fptr;
            soPtr = soptr;
        }
    };
    std::string mSoPath;                                       //so库的根目录
    std::unordered_map<std::string, SoWrapper> libInstanceMap; //map储存so指针实现 o(n)的效率

public:
    dload(const std::string &soPath) : mSoPath(soPath) {}
    ~dload() {}

    bool load(const std::string &libName)
    { //加载库名，即so的全名，【libxxx】.so，成功或者已经加载，则返回true，失败返回false
        void *soPtr = dlopen((mSoPath + libName).c_str(), RTLD_LAZY);
        if (!soPtr)
            return false;
        if (libInstanceMap.count(libName) != 0)
            return true;                                                       //如果已经加载过
        interface *(*getInstanceFunc)(void);                                   //getInstance的函数指针
        getInstanceFunc = (interface * (*)(void)) dlsym(soPtr, "getInstance"); //从so中获取符号,因此必须导出getInstance函数
        SoWrapper sw(getInstanceFunc, soPtr);
        libInstanceMap[libName] = sw;
        return true; //存入instanceMap中，下次要再次使用时直接获取即可
    }
    bool unload(const std::string &libName)
    { //卸载类库
        if (isExists(libName))
        {
            dlclose(libInstanceMap[libName].soPtr);
            libInstanceMap.erase(libName);
        }
        return true;
    }
    interface *getInstance(const std::string &libName)
    { //获取实例,实例产生的方式取决于maker中的实现方式
        if (isExists(libName))
        {
            return (interface *)(libInstanceMap[libName].getInstanceFunc()); //返回实例执行的结果
        }
        return nullptr;
    }
    bool isExists(const std::string &libName)
    { //判断是否已经加载该so
        if (libInstanceMap.count(libName) == 0)
        {
            return false; //不存在
        }
        return true;
    }
};
#endif