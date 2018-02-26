#include "MessageQueue.h"

namespace nonsugar{
MessageQueue::MessageQueue(void)
{
    is_wait_ = false;
}

MessageQueue::~MessageQueue(void)
{
    //nop
}

void MessageQueue::MessageSend(const thread_msg& send_msg)
{
    mutex_.Lock();

    msg_queue_.push(send_msg);
    
    //メッセージキューが待ち状態の時は解除する
    if (is_wait_) {
        mutex_.UnBlocking();
    }

    mutex_.Unlock();
}

void MessageQueue::MessageReceive(thread_msg& reseive_msg)
{
    mutex_.Lock();
    while(1){
        if(msg_queue_.empty()){
            //メッセージがない時はメッセージ受信までブロッキング
            is_wait_ = true;
            mutex_.Blocking();
            is_wait_ = false;
        }else{
            reseive_msg = msg_queue_.front();
            msg_queue_.pop();
            break;
        }
    }
    mutex_.Unlock();

}

} //namespace nonsugar
