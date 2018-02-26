#ifndef THREAEDS_H__
#define THREAEDS_H__

#include "Message.h"

//メッセージキューIDを定義
enum MsgQueueID : int32_t {
    MSG_QUEUE_ID_THREAD_A = 0,
    MSG_QUEUE_ID_THREAD_B,
    MSG_QUEUE_ID_THREAD_C,
};

void InputThread(void);
void ThreadA( void );
void ThreadB(void);

#endif //THREAEDS_H__
