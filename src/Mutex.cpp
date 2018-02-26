#include "Mutex.h"

namespace nonsugar{
Mutex::Mutex(void)
{
#ifdef WIN32
    mutex_ = CreateSemaphore(NULL, 1, 1, NULL);
    wait_ = CreateEvent(NULL, FALSE, FALSE, NULL);
#endif

#ifdef __linux__
    int	ret_mutex;
    int ret_cond;

    ret_mutex = pthread_mutex_init(&mutex_, NULL);
    ret_cond = pthread_cond_init(&cond_, NULL);

    //初期化失敗
    if(ret_mutex || ret_cond){
        if(!ret_mutex){
            pthread_mutex_destroy(&mutex_);
        }

        if(!ret_cond){
            pthread_cond_destroy(&cond_);
        }
    }
#endif
}

Mutex::~Mutex(void)
{
#ifdef WIN32
    BOOL ret;
    ret = CloseHandle(mutex_);
#endif

#ifdef __linux__
    pthread_mutex_destroy(&mutex_);
    pthread_cond_destroy(&cond_);
#endif
}

void Mutex::Lock(void)
{
#ifdef WIN32
    DWORD ret;
    ret = WaitForSingleObject(mutex_, INFINITE);
    if (ret == WAIT_FAILED) {

    }
#endif

#ifdef __linux__
    pthread_mutex_lock(&mutex_);
#endif
}

void Mutex::Unlock(void)
{
#ifdef WIN32
    BOOL ret;
    //セマフォ返却
    ret = ReleaseSemaphore(mutex_, 1, NULL);
    if(ret == FALSE){

    }
#endif

#ifdef __linux__
    pthread_mutex_unlock(&mutex_);
#endif
}

void Mutex::Blocking(void)
{
#ifdef WIN32
    DWORD ret;
    Unlock();
    ret = WaitForSingleObject(wait_, INFINITE);
    if(ret == WAIT_FAILED){

    }
    Lock();
#endif

#ifdef __linux__
    pthread_cond_wait( &cond_, &mutex_ );
#endif
}

void Mutex::UnBlocking(void)
{
#ifdef WIN32
    BOOL ret;
    ret = SetEvent(wait_);

    if(ret == FALSE){

    }
#endif

#ifdef __linux__
    pthread_cond_signal(&cond_);
#endif
}

} //namespace nonsugar
