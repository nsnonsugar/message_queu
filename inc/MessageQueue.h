#ifndef MESSAGEQUEUE_H__
#define MESSAGEQUEUE_H__

#include <stdint.h>
#include <queue>
#include "Mutex.h"

typedef struct {
    int32_t event_id;
    void* data;
}thread_msg;

namespace nonsugar {
class MessageQueue final{
private:
    Mutex mutex_;
    std::queue<thread_msg> msg_queue_;
    bool is_wait_;

public:
    MessageQueue(void);
    ~MessageQueue(void);

    //コピー禁止
    MessageQueue(const MessageQueue&) = delete;
    void operator=( const MessageQueue& ) = delete;

public:
    /**
    * メッセージ受信
    *
    * @param msg   --- 送信するメッセージ
    *
    */
    void MessageSend(const thread_msg& send_msg);

    /**
    * メッセージ受信
    *
    * @param msg   --- メッセージの格納先
    *
    */
    void MessageReceive(thread_msg& reseive_msg);
};

} //namespace nonsugar
#endif //MESSAGEQUEUE_H__
