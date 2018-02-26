#include <stdio.h>
#include <thread>

#include "threads.h"
#include "Message.h"

//メッセージキュー生成用テーブル
static const MessageConfig config_table[] = {
    {MSG_QUEUE_ID_THREAD_A, USE},
    {MSG_QUEUE_ID_THREAD_B, USE},
    {MSG_QUEUE_ID_THREAD_C, USE},
};

int main()
{
    //メッセージキュー生成
    CreateMessageQueue( config_table, sizeof(config_table)/sizeof(config_table[0]));

    std::thread input(InputThread);
    std::thread a(ThreadA);
    std::thread b(ThreadB);

    input.join();
    a.join();
    b.join();
    //メッセージキュー削除
    DeleteMessageQueue();
    printf("プログラム終了\n");

    return 0;
}
