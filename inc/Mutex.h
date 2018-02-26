#ifndef MUTEX_H__
#define MUTEX_H__

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <pthread.h>
#endif

namespace nonsugar{

class Mutex final{
private:
#ifdef WIN32
    HANDLE mutex_;
    HANDLE wait_;
#endif

#ifdef __linux__
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
#endif

public:
    Mutex(void);
    ~Mutex(void);

    //コピー禁止
    Mutex(const Mutex&) = delete;
    void operator=(const Mutex&) = delete;

public:
    /**
    * ミューテックスを取得する
    */
    void Lock(void);

    /**
    * ミューテックスを開放する
    */
    void Unlock(void);

    /**
    * UnBlockingが呼び出されるまでまでブロッキングする<br>
    * この関数を呼び出す前に必ずLockで<br>
    * ミューテックスを取得すること
    */
    void Blocking(void);

    /**
    * Waitのブロッキングを解除する
    */
    void Blocking(void);

};

}//namespace nonsugar
#endif //MUTEX_H__
