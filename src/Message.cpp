#include "Message.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int32_t queue_num;
    nonsugar::MessageQueue<thread_msg>* queue[MSG_QUEUE_MAX_NUM];
}MessageManage;
MessageManage message_;

#define DEBUG_PRINT(...)  printf(__VA_ARGS__)
//#define DEBUG_PRINT(...) (void)(__VA_ARGS__)

void CreateMessageQueue(const MessageConfig* config, int32_t num)
{
    //最大数以上を指定
    if(num >= MSG_QUEUE_MAX_NUM){
        DEBUG_PRINT( "[CreateMessageQueue]Parameter error\n" );
    }

    //バッファを初期化
    message_.queue_num = 0;
    for(int i = 0; i<MSG_QUEUE_MAX_NUM; ++i){
        message_.queue[i] = NULL;
    }

    //メッセージキューを生成
    for(int i = 0; i<num; ++i){
        if(config[i].use == USE){
            if(config[i].msg_queue_id < MSG_QUEUE_MAX_NUM){
                message_.queue[config[i].msg_queue_id] = new(nonsugar::MessageQueue<thread_msg>);
                ++message_.queue_num;
            }else{
                //0～MSG_QUEUE_MAX_NUM-1以上のIDは無効
                DEBUG_PRINT( "[CreateMessageQueue]BAD Queue ID\n" );
            }
        }
    }
}

void DeleteMessageQueue(void)
{
    for (int i = 0; i<MSG_QUEUE_MAX_NUM; ++i) {
        if(message_.queue != NULL){
            delete message_.queue[i];
        }
    }
}

void ReceiveMsg( MsgQueueID queue_id, thread_msg& msg)
{
    message_.queue[queue_id]->Receive(msg);
}

void SendMsg( MsgQueueID queue_id, const thread_msg& msg)
{
    message_.queue[queue_id]->Send( msg );
}
