#ifndef MESSAGE_H__
#define MESSAGE_H__

#include <stdint.h>
#include "MessageQueue.h"

//宣言のみ 定義は共通ヘッダ等で行う
enum MsgQueueID : int32_t;

enum MsgQueueStatus : int8_t{
    UNUSE = 0,
    USE,
};

typedef struct {
    MsgQueueID msg_queue_id; //キューIDの有効値は0～MSG_QUEUE_MAX_NUM - 1
    MsgQueueStatus use;
}MessageConfig; //メッセージキュー設定テーブル用


//キューの最大数 適当に変更しても問題なし
#define MSG_QUEUE_MAX_NUM 10

/**
* メッセージキュー設定テーブルを元にメッセージキューを生成する
*
* @param config   --- 設定テーブル
* @param num   --- 設定テーブルの要素数
*
* @attention MSG_QUEUE_MAX_NUMより大きい要素数を設定した場合失敗する
*/
void CreateMessageQueue( const MessageConfig* config, int32_t num );

/**
* CreateMessageQueueで生成したメッセージキューを全て削除する
*
* @attention この関数より前にCreateMessageQueueを呼んでいること
*/
void DeleteMessageQueue( void );

/**
* メッセージ受信
*
* @param queue_id   --- 受信先キューのID
* @param msg   --- メッセージの格納先アドレス
*
* @attention MSG_QUEUE_MAX_NUMより大きい要素数を設定した場合失敗する
*/
void ReceiveMsg(MsgQueueID queue_id, thread_msg& msg);

/**
* メッセージ送信
*
* @param queue_id   --- 送信先キューのID
* @param msg   --- 送信するメッセージ
*
* @attention MSG_QUEUE_MAX_NUMより大きい要素数を設定した場合失敗する
*/
void SendMsg(MsgQueueID queue_id, const thread_msg& msg);

#endif //MESSAGE_H__
