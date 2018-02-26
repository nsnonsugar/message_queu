#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Message.h"
#include "threads.h"


//イベントID
enum EventID : int32_t {
    MessagefromInputThread = 0,
    MessagefromThreadA,
    MessagefromThreadB,
    Exit,
};

void InputThread( void )
{
    while (1) {
        int num;
        thread_msg msg = { 0, NULL };

        printf( "0～2の数字を入力してください\n" );
        printf( "0...スレッドAにメッセージを送信\n" );
        printf( "1...スレッドBにメッセージを送信\n" );
        printf( "2...終了\n" );
        scanf( "%d", &num );

        switch (num) {
            case 0:
                printf("[InputThread]スレッドAにメッセージを送信します\n");
                msg.event_id = MessagefromInputThread;
                msg.data = malloc(sizeof("InputThread Send to Thread A"));
                memset(msg.data, '\0', sizeof("InputThread Send to Thread A"));
                strcpy((char*)msg.data, "InputThread Send to Thread A");
                SendMsg(MSG_QUEUE_ID_THREAD_A, msg);
                break;

            case 1:
                printf( "[InputThread]スレッドBにメッセージを送信します\n" );
                msg.event_id = MessagefromInputThread;
                msg.data = malloc( sizeof( "InputThread Send to Thread B" ) );
                memset( msg.data, '\0', sizeof( "InputThread Send to Thread B" ) );
                strcpy( (char*)msg.data, "InputThread Send to Thread B" );
                SendMsg( MSG_QUEUE_ID_THREAD_B, msg );
                break;

            case 2:
                msg.event_id = Exit;
                SendMsg( MSG_QUEUE_ID_THREAD_A, msg );
                SendMsg( MSG_QUEUE_ID_THREAD_B, msg );
                printf("[InputThread]終了\n");
                return;

            default:
                printf( "0～2を入力してください" );
                break;
        }
    }
}

void ThreadA(void)
{
    while(1){
        thread_msg msg = {0, NULL};
        thread_msg snd = {0, NULL};
        ReceiveMsg(MSG_QUEUE_ID_THREAD_A, msg);

        switch(msg.event_id){
            case MessagefromInputThread:
                printf("[ThreadA]InputThreadからメッセージを受信\n");
                printf("[ThreadA]%s\n", (char*)msg.data);

                printf("[ThreadA]スレッドBにメッセージを送信します\n");
                snd.event_id = MessagefromThreadA;
                snd.data = malloc( sizeof( u8"Thread A Send to Thread B" ) );
                memset( snd.data, '\0', sizeof( u8"Thread A Send to Thread B" ) );
                strcpy( (char*)snd.data, u8"Thread A Send to Thread B" );
                SendMsg( MSG_QUEUE_ID_THREAD_B, snd );

                break;

            case MessagefromThreadB:
                printf("[ThreadA]スレッドBからメッセージを受信\n");
                printf("[ThreadA]%s\n", (char*)msg.data );
                break;

            case Exit:
                printf("[ThreadA]終了\n");
                return;

            default:
                printf("[ThreadA]無効なイベントを受信しました\n");
                break;
        }

        if(msg.data != NULL){
            free(msg.data);
        }
    }
}

void ThreadB(void)
{
    while (1) {
        thread_msg msg = { 0, NULL };
        thread_msg snd = { 0, NULL };
        ReceiveMsg( MSG_QUEUE_ID_THREAD_B, msg );

        switch (msg.event_id) {
            case MessagefromInputThread:
                printf( "[ThreadB]InputThreadからメッセージを受信\n" );
                printf( "[ThreadB]%s\n", (char*)msg.data );

                printf("[ThreadB]スレッドAにメッセージを送信します\n");
                snd.event_id = MessagefromThreadB;
                snd.data = malloc( sizeof( u8"Thread B Send to Thread A" ) );
                memset( msg.data, '\0', sizeof( u8"Thread B Send to Thread A" ) );
                strcpy( (char*)snd.data, u8"Thread B Send to Thread A" );
                SendMsg( MSG_QUEUE_ID_THREAD_A, snd );
                break;

            case MessagefromThreadA:
                printf( "[ThreadB]スレッドAからメッセージを受信\n" );
                printf( "[ThreadB]%s\n", (char*)msg.data );
                break;
        
            case Exit:
                printf( "[ThreadB]終了\n" );
                return;

            default:
                printf( "[ThreadB]無効なイベントを受信しました\n" );
                break;
        }

        if (msg.data != NULL) {
            free( msg.data );
        }
    }
}
