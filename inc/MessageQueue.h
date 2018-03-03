#ifndef MESSAGEQUEUE_H__
#define MESSAGEQUEUE_H__

#include <stdint.h>
#include <queue>
#include <mutex>
#include <condition_variable>

typedef struct {
    int32_t event_id;
    void* data;
}thread_msg;

namespace nonsugar {
class MessageQueue final{
private:
    std::mutex mutex_;
	std::condition_variable cond_;
    std::queue<thread_msg> msg_queue_;

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
    void Send(const thread_msg& send_msg);

    /**
    * メッセージ受信
    *
    * @param msg   --- メッセージの格納先
    *
    */
    void Receive(thread_msg& reseive_msg);
};

} //namespace nonsugar
#endif //MESSAGEQUEUE_H__
