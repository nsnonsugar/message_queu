#include "MessageQueue.h"

namespace nonsugar{
MessageQueue::MessageQueue(void)
{
    //nop
}

MessageQueue::~MessageQueue(void)
{
    //nop
}

void MessageQueue::Send(const thread_msg& send_msg)
{
    std::lock_guard<std::mutex> lock(mutex_);

    msg_queue_.push(send_msg);

    cond_.notify_all();
}

void MessageQueue::Receive(thread_msg& reseive_msg)
{
    std::unique_lock<std::mutex> lock(mutex_);

    if(msg_queue_.empty()){
        cond_.wait(lock, [&]{ return msg_queue_.size(); });
    }

    reseive_msg = msg_queue_.front();
    msg_queue_.pop();
}

} //namespace nonsugar
