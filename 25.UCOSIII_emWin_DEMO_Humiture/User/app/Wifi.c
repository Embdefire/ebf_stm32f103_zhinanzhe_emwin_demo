﻿/**************************************************************************************
* 因为emWin显示只支持UTF-8编码格式的中文，如果希望直接显示在Keil直接输入的中文，      *
*            比如使用：GUI_DispStringHCenterAt("流水灯",110,120);                     *
* 该文件必须以UTF-8编码格式，不然中文无法正常显示。                                   *
*                                                                                     *
* 如果只是个别例程出现中文显示乱码（如果所有例程都无法显示中文可能是字库问题），      *
* 把对应的例程文件(比如LEDapp.c)用电脑的记事本软件打开，然后选择另存为，在弹出对      *
* 话框中“保存(S)"按钮的左边有个"编码(E)"选项，选择"UTF-8",然后同样保存为同名称的      *
* C语言文件(覆盖原来文件)，再编译。                                                   *
*                                                                                     *
* 如果编译工程时出现下面类似错误也是该文件编码格式问题,必须把文件保存为UTF-8格式      *
* 再编译                                                                              *
* ..\..\User\app\LEDapp.c(275): error:  #8: missing closing quote                     *
*        GUI_DispStringHCenterAt("娴?姘?鐏?",110,120);                                *
* ..\..\User\app\LEDapp.c(276): error:  #165: too few arguments in function call      *
*        GUI_DispStringHCenterAt("瑙?鎽?鍋?宸?澶?鎵?闇€瑕?瑙?鎽?鏍?鍑?",110,215);     *
* ..\..\User\app\LEDapp.c(276): error:  #18: expected a ")"                           *
*        GUI_DispStringHCenterAt("瑙?鎽?鍋?宸?澶?鎵?闇€瑕?瑙?鎽?鏍?鍑?",110,215);     *
*                                                                                     *
* 修改文件后编译就出错这是Keil5软件问题(Keil4没这问题)，推荐使用其他程序编辑工具，    *
* 只用Keil5完成编译和下载工作。                                                       *
***************************************************************************************
*                      实验平台: 野火STM32 ISO 开发板                                 *
*                      论    坛: http://www.chuxue123.com                             *
*                      淘    宝: http://firestm32.taobao.com                          *
*                      邮    箱: wildfireteam@163.com                                 *
***************************************************************************************
*/
/**************************************************************************************
*                                                                                     *
*                SEGGER Microcontroller GmbH & Co. KG                                 *
*        Solutions for real time microcontroller applications                         *
*                                                                                     *
***************************************************************************************
*                                                                                     *
* C-file generated by:                                                                *
*                                                                                     *
*        GUI_Builder for emWin version 5.22                                           *
*        Compiled Jul  4 2013, 15:16:01                                               *
*        (c) 2013 Segger Microcontroller GmbH & Co. KG                                *
*                                                                                     *
***************************************************************************************
*                                                                                     *
*        Internet: www.segger.com  Support: support@segger.com                        *
*                                                                                     *
***************************************************************************************
*/
// USER START (Optionally insert additional includes)
#include "includes.h"
#include  "app.h"
#include  "..\User\bsp\ESP8266\bsp_esp8266.h"
// USER END
/**************************************************************************************
*
*       Defines
*
***************************************************************************************
*/
// USER START (Optionally insert additional defines)
#define BUFFER_SIZE		1024
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
// USER START (Optionally insert additional static data)
extern uint8_t ucTcpClosedFlag;
static uint8_t IsConnect=0;
static WM_HWIN hPend;
static uint8_t IsChange=1;
static uint8_t ssid[21]={"wildfire"};
static uint8_t pwd[21]={"wildfire123"};
static uint8_t host_ip[16]={"192.168.1.125"};
static uint8_t host_port[6]={"5000"};
static uint8_t wifistat=0;
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreateWifi[] = {
  { FRAMEWIN_CreateIndirect, "Wifi_ESP8266", 0, 0, 0, 240, 320, 0, 0x0, 0 },  
  { EDIT_CreateIndirect, "Port", GUI_ID_EDIT0, 180, 52, 45, 20, 0, 5, 0 },
  { EDIT_CreateIndirect, "IP", GUI_ID_EDIT1, 30, 52, 105, 22, 0, 15, 0 },
	{ EDIT_CreateIndirect, "SSID", GUI_ID_EDIT2, 42, 2, 125, 20, 0, 20, 0 },
	{ EDIT_CreateIndirect, "PassWord", GUI_ID_EDIT3, 42, 27, 125, 20, 0, 20, 0 },
  { BUTTON_CreateIndirect, "Connect", GUI_ID_BUTTON0, 170, 5, 57, 40, 0, 0x0, 0 },
  { MULTIEDIT_CreateIndirect, "Post", GUI_ID_MULTIEDIT0, 5, 95, 160, 80, 0, 0x0, 0 },
  { MULTIEDIT_CreateIndirect, "Pend", GUI_ID_MULTIEDIT1, 5, 195, 220, 100, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Send", GUI_ID_BUTTON1, 170, 105, 55, 25, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Clear", GUI_ID_BUTTON2, 170, 140, 55, 25, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialogWifi(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
	OS_ERR      err;
	uint16_t messagesnetwork[2];
  // USER END

  switch (pMsg->MsgId) {
	case WM_DELETE:
		OS_INFO("Wifiapp delete\n");
		IsConnect=0;//关闭连接
		ESP8266_stop();
		Flag_ICON106 = 0;
		UserApp_Flag = 0;
		keypadflag=0;
		WM_DeleteWindow(KEYBOARD);
		tpad_flag=0;
	break;
  case WM_INIT_DIALOG:
    //
    // Initialization of 'wifi'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetTextColor(hItem,GUI_DARKGRAY);
    FRAMEWIN_SetFont(hItem, GUI_FONT_16B_ASCII);
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		hFrameClose=FRAMEWIN_AddCloseButton(hItem,FRAMEWIN_BUTTON_RIGHT,0);
    FRAMEWIN_SetTitleHeight(hItem, 20);
		WM_DisableWindow(hFrameClose);
    //
    // Initialization of 'Port'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
    EDIT_SetText(hItem, (const char*)host_port);
    EDIT_SetFont(hItem, GUI_FONT_16B_ASCII);
    EDIT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    //
    // Initialization of 'IP'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
    EDIT_SetText(hItem,(char *)host_ip);
    EDIT_SetFont(hItem, GUI_FONT_16B_ASCII);
    EDIT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		//
    // Initialization of 'ssid'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2);
    EDIT_SetText(hItem,(char *)ssid);
    EDIT_SetFont(hItem, GUI_FONT_16B_ASCII);
    EDIT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		//
    // Initialization of 'pwd'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
    EDIT_SetText(hItem,(char *)pwd);
    EDIT_SetFont(hItem, GUI_FONT_16B_ASCII);
    EDIT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    //
    // Initialization of 'Connect'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON0);
    BUTTON_SetFont(hItem, &XBF_Font);
    BUTTON_SetText(hItem, "未连接");
		WM_DisableWindow(hItem);
    //
    // Initialization of 'Post'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_MULTIEDIT0);
    MULTIEDIT_SetText(hItem, "Hello World");
    MULTIEDIT_SetFont(hItem, &XBF_Font);
    MULTIEDIT_SetTextColor(hItem, MULTIEDIT_CI_EDIT, GUI_BLUE);
		MULTIEDIT_EnableBlink(hItem,500,1);
		MULTIEDIT_SetAutoScrollV(hItem,1);
		MULTIEDIT_SetAutoScrollH(hItem,1);
    //
    // Initialization of 'Pend'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_MULTIEDIT1);
		hPend=hItem;
		MULTIEDIT_SetFont(hItem, &XBF_Font);
    MULTIEDIT_SetText(hItem, "");
		MULTIEDIT_SetAutoScrollV(hItem,1);
		MULTIEDIT_SetAutoScrollH(hItem,1);
		MULTIEDIT_SetReadOnly(hItem,1);
		MULTIEDIT_SetMaxNumChars(hItem,1024);
    //
    // Initialization of 'Send'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON1);
    BUTTON_SetFont(hItem, &XBF_Font);
    BUTTON_SetText(hItem, "send");
		WM_DisableWindow(hItem);
    //
    // Initialization of 'Clear'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON2);
    BUTTON_SetFont(hItem, GUI_FONT_16B_ASCII);
    BUTTON_SetText(hItem, "Clear");
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case GUI_ID_EDIT0: // Notifications sent by 'Port'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)				
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				messagesnetwork[0]=WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
				messagesnetwork[1]=GUI_ID_EDIT0;
				if(!keypadflag)OSTaskQPost(&AppTaskKeypadTCB,
																(void *)&messagesnetwork,
																2,
																OS_OPT_POST_FIFO,
																&err);
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
				com_data2null(host_port,5);
				EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0),(char *)host_port,5);
				host_port[5]='\0';
				IsChange=1;
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case GUI_ID_EDIT1: // Notifications sent by 'IP'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)				
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				messagesnetwork[0]=WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
				messagesnetwork[1]=GUI_ID_EDIT1;
				if(!keypadflag)OSTaskQPost(&AppTaskKeypadTCB,
																(void *)&messagesnetwork,
																2,
																OS_OPT_POST_FIFO,
																&err);
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
					com_data2null(host_ip,15);
					EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1),(char *)host_ip,15);
					host_ip[15]='\0';
					IsChange=2;
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
		case GUI_ID_EDIT2: // Notifications sent by 'ssid'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)				
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				messagesnetwork[0]=WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2);
				messagesnetwork[1]=GUI_ID_EDIT2;
				if(!keypadflag)OSTaskQPost(&AppTaskKeypadTCB,
																(void *)&messagesnetwork,
																2,
																OS_OPT_POST_FIFO,
																&err);
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)				
					com_data2null(ssid,20);
					EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2),(char *)ssid,20);
					ssid[20]='\0';
					IsChange=3;
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
		case GUI_ID_EDIT3: // Notifications sent by 'pwd'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)				
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				messagesnetwork[0]=WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
				messagesnetwork[1]=GUI_ID_EDIT3;
				if(!keypadflag)OSTaskQPost(&AppTaskKeypadTCB,
																(void *)&messagesnetwork,
																2,
																OS_OPT_POST_FIFO,
																&err);
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
					com_data2null(pwd,20);
					EDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3),(char *)pwd,20);
					pwd[20]='\0';
					IsChange=4;
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case GUI_ID_BUTTON0: // Notifications sent by 'Connect'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
				if(keypadflag)WM_DeleteWindow(KEYBOARD);
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				if(IsConnect==0)
				{
					WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3));
					WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2));
					WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1));
					WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0));					
					IsConnect=1;//启动连接
				}
				else
				{
					WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3));
					WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2));
					WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1));
					WM_EnableWindow(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0));
					WM_DisableWindow(WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON1));						
					BUTTON_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON0), "未连接");					
					IsConnect=0;//关闭连接
				}
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case GUI_ID_MULTIEDIT0: // Notifications sent by 'Post'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)				
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				messagesnetwork[0]=WM_GetDialogItem(pMsg->hWin, GUI_ID_MULTIEDIT0);
				messagesnetwork[1]=GUI_ID_MULTIEDIT0;
				if(!keypadflag)OSTaskQPost(&AppTaskKeypadTCB,
																(void *)&messagesnetwork,
																2,
																OS_OPT_POST_FIFO,
																&err);
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
//    case GUI_ID_MULTIEDIT1: // Notifications sent by 'Pend'
//      switch(NCode) {
//      case WM_NOTIFICATION_CLICKED:
//        // USER START (Optionally insert code for reacting on notification message)
//        // USER END
//        break;
//      case WM_NOTIFICATION_RELEASED:
//        // USER START (Optionally insert code for reacting on notification message)
//        // USER END
//        break;
//      case WM_NOTIFICATION_VALUE_CHANGED:
//        // USER START (Optionally insert code for reacting on notification message)
//        // USER END
//        break;
//      // USER START (Optionally insert additional code for further notification handling)
//      // USER END
//      }
//      break;
    case GUI_ID_BUTTON1: // Notifications sent by 'Send'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
				if(keypadflag)WM_DeleteWindow(KEYBOARD);
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				com_data2null(comdata,BUFFER_SIZE);
				MULTIEDIT_GetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_MULTIEDIT0),(char *)comdata,BUFFER_SIZE);
				com_utf82gbk((const char *)comdata,(char *)comdata);
				ESP8266_SendString(ENABLE,(char *)comdata,0, Single_ID_0 ); 
				MULTIEDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_MULTIEDIT0),"");
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case GUI_ID_BUTTON2: // Notifications sent by 'Clear'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				MULTIEDIT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_MULTIEDIT1),"");
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
	case WM_PAINT:                                           
    GUI_SetBkColor(APPBKCOLOR);
		GUI_SetColor(APPTEXTCOLOR);
		GUI_Clear();
		GUI_DispStringAt("账号:",2,2);
		GUI_DispStringAt("密码:",2,27);
		GUI_DispStringAt("IP:",5,52);
		GUI_DispStringAt("端口:",140,52);
		GUI_DispStringAt("发送内容:",5,77);
		GUI_DispStringAt("接收内容:",5,177);
  break;
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateWifi
*/
void FUN_ICON106Clicked(void)
{
	uint8_t ucStatus;
	uint8_t timecount=0;
	uint16_t i=0;
	char *receive;
	WM_HWIN hWin;
	OS_INFO("Wifiapp create\n");
	IsConnect=0;//默认不启动连接
	IsChange=1;
	wifistat=0;
	
	com_data2null(comdata,COMDATA_SIZE);
	ESP8266_Init();
	
	hWin=GUI_CreateDialogBox(_aDialogCreateWifi, GUI_COUNTOF(_aDialogCreateWifi), _cbDialogWifi, WM_HBKWIN, 0, 0);
	GUI_Delay(1); 

	macESP8266_CH_ENABLE();
	if(ESP8266_AT_Test()==0)
		wifistat|=0x01;
	if(ESP8266_Net_Mode_Choose(STA)==0)
		wifistat|=0x02;
	
	//printf("wifistat:%d\n",wifistat);
	WM_EnableWindow(hFrameClose);
	while(wifistat&0x03)
	{
		GUI_ExecCreatedDialog(MESSAGEBOX_Create("\r\n The Wifi drive cannot work! \r\n","error",GUI_MESSAGEBOX_CF_MODAL));
		while(1)
		{			
			if(tpad_flag)WM_DeleteWindow(hWin);
			if(!Flag_ICON106)return;
			GUI_Delay(10);
		}
	}
	WM_EnableWindow(WM_GetDialogItem(hWin, GUI_ID_BUTTON0));	
	while(Flag_ICON106)
	{		
		if((wifistat==0)&&IsConnect)
		{			
			if(IsChange)
			{
				WM_DisableWindow(hFrameClose);
				BUTTON_SetText(WM_GetDialogItem(hWin, GUI_ID_BUTTON0), "连接中");				
				if(!ESP8266_JoinAP((char *)ssid,(char*)pwd))
					wifistat|=0x04;
				if(!wifistat)ESP8266_Enable_MultipleId(DISABLE);	
				i=0;
				while(i<5&&!wifistat)
				{
					if((IsConnect==0)||ESP8266_Link_Server(enumTCP,(char*)host_ip,(char*)host_port,Single_ID_0))break;
					++i;					
				}
				if(i==5)
					wifistat|=0x08;
				i=0;
				while(i<5&&!wifistat)
				{
					if((IsConnect==0)||ESP8266_UnvarnishSend())break;					
					++i;					
				}
				if(i==5)
					wifistat|=0x10;
				strEsp8266_Fram_Record .InfBit .FramLength = 0;
				strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;			
				IsChange=0;
				WM_EnableWindow(hFrameClose);
			}
			else if(timecount>=20)
			{
				BUTTON_SetText(WM_GetDialogItem(hWin, GUI_ID_BUTTON0), "通信中");
				WM_EnableWindow(WM_GetDialogItem(hWin, GUI_ID_BUTTON1));
				if(strEsp8266_Fram_Record.InfBit.FramFinishFlag)
				{
					com_data2null(comdata,BUFFER_SIZE);
					receive=(char *)comdata;
					strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ] = '\0';
					receive=strEsp8266_Fram_Record .Data_RX_BUF;
					ESP8266_SendString(ENABLE, receive, 0, Single_ID_0 ); 
					com_gbk2utf8(receive,(char *)comdata);
					if(MULTIEDIT_GetTextSize(hPend)>=1000)
						MULTIEDIT_SetText(hPend,"");
					MULTIEDIT_AddText(hPend,(char *)comdata);				
				}
				if(ucTcpClosedFlag)                                           //检测是否失去连接    
				{
					ESP8266_ExitUnvarnishSend ();                               //退出透传模式      
					do ucStatus = ESP8266_Get_LinkStatus ();                    //获取连接状态      
					while(!ucStatus);
					if(ucStatus==4)                                             //确认失去连接后重连
					{	
						IsConnect=0;
						IsChange=0;
						WM_EnableWindow(WM_GetDialogItem(hWin, GUI_ID_EDIT3));
						WM_EnableWindow(WM_GetDialogItem(hWin, GUI_ID_EDIT2));
						WM_EnableWindow(WM_GetDialogItem(hWin, GUI_ID_EDIT1));
						WM_EnableWindow(WM_GetDialogItem(hWin, GUI_ID_EDIT0));
						WM_DisableWindow(WM_GetDialogItem(hWin, GUI_ID_BUTTON1));						
						BUTTON_SetText(WM_GetDialogItem(hWin, GUI_ID_BUTTON0), "未连接");					
					}				
				}
				strEsp8266_Fram_Record .InfBit .FramLength = 0;
				strEsp8266_Fram_Record .InfBit .FramFinishFlag = 0;
				timecount=0;
			}
			if(wifistat&&Flag_ICON106)
			{
				WM_EnableWindow(WM_GetDialogItem(hWin, GUI_ID_EDIT3));
				WM_EnableWindow(WM_GetDialogItem(hWin, GUI_ID_EDIT2));
				WM_EnableWindow(WM_GetDialogItem(hWin, GUI_ID_EDIT1));
				WM_EnableWindow(WM_GetDialogItem(hWin, GUI_ID_EDIT0));
				WM_DisableWindow(WM_GetDialogItem(hWin, GUI_ID_BUTTON1));						
				BUTTON_SetText(WM_GetDialogItem(hWin, GUI_ID_BUTTON0), "未连接");	
				IsConnect=0;
				IsChange=0;
				GUI_MessageBox("\r\n The Wifi drive cannot work! \r\n","error",GUI_MESSAGEBOX_CF_MOVEABLE);
			}
		}
		timecount++;
		if(tpad_flag)WM_DeleteWindow(hWin);
		GUI_Delay(10); 
	}
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
