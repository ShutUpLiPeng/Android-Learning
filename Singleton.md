# 单例模式
项目中最常遇到的一种设计模式:
(1)  static 指针成员变量
(2) destory函数
(3) 
```C++
#ifndef _TEMPLATE_SINGLETON_H
#define _TEMPLATE_SINGLETON_H

#include <mutex>

template <typename T>
class Singleton {
public:
    static T* getInstance();
    
    static void destoryInstance();

private:
    Singleton();
    ~Singleton();

    Singleton(const Singleton & );
    Singleton& operator = (const Singleton &);

private:
    static std::mutex sMutex;
    static T*   sInstance; 
};

template <typename T>
std::mutex Singleton<T>::sMutex;

template <typename T>
T* Singleton<T>::sInstance =nullptr;

template <typename T>
T* Singleton<T>::getInstance() {
    if ( sInstance == nullptr) {
        std::lock_guard<std::mutex> gLock(sMutex);
        sInstance = new T();
    }
    return sInstance;
}

template<typename T>
void Singleton<T>::destoryInstance() {
    if (sInstance != nullptr) {
        delete sInstance;
        sInstance = nullptr;
    }
}

#endif // _TEMPLATE_SINGLETON_H
```
