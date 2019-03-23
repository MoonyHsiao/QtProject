#ifndef CHATCMD_H
#define CHATCMD_H

//服務器------->客戶端
#define Login_answer 0x0F01 //是否是註冊user
#define Left_answer 0x0F02 //發送字符串
#define AddGroup_answer 0x0F03 //添加聊天室
#define Msg_send 0x0F04 //發送的信息
#define FileName_send 0x0F05 //發送文件
#define Struct_send 0x0F06 //發送結構體
#define LoginNotifi_Broadcast 0x0F07 //上線廣播
#define UesrInfo_Broadcast 0x0F08 //廣播user資訊
#define LeftUesrInfo_Broadcast 0x0F09 //廣播user資訊
#define Refuse_send 0x0F10 //拒絕接收檔案


//客戶端------->服務器
#define Login 0x0D00 //客戶端上線
#define Left 0x0D01 //客戶端下線
#define AddGroup 0x0D02 //客戶端添加房間
#define Msg 0x0D03 //客戶端發送聊天信息
#define FileName 0x0D04 //檔案名稱
#define Connet_Success 0x0D05 //連接成功應答包
#define Refuse 0x0D06 //拒絕接收檔案
#define LoginNotifi 0x0D07 //聊天室登入廣播
#define UesrInfo 0x0D08 //拒絕接收檔案


#endif // CHATCMD_H
