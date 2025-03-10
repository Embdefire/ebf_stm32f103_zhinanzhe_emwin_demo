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
// USER END
/**************************************************************************************
*
*       Defines
*
***************************************************************************************
*/
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
// USER START (Optionally insert additional static data)
static uint8_t eepromflag=0;
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreateEEPROM[] = {
  { FRAMEWIN_CreateIndirect,"EEPROM", 			0, 				0,   0, 240, 320, 0, 0x0, 0 },
  { TEXT_CreateIndirect, 	"INIT", 			GUI_ID_TEXT0, 	140, 225, 55, 20, 0, 0x64, 0 },
  { TEXT_CreateIndirect, 	"AUTOTEST", 		GUI_ID_TEXT1, 	140, 255, 55, 20, 0, 0x64, 0 },
  { EDIT_CreateIndirect, 	"Edit", 			GUI_ID_EDIT0, 	120, 35, 40, 20, 0, 0x3, 0 },  
  { EDIT_CreateIndirect, 	"Edit", 			GUI_ID_EDIT1, 	120, 70, 40, 20, 0, 0x3, 0 },
  { BUTTON_CreateIndirect, 	"Write", 			GUI_ID_BUTTON0, 180, 40, 40, 40, 0, 0x0, 0 },
  { EDIT_CreateIndirect, 	"Edit", 			GUI_ID_EDIT2, 	120, 125, 40, 20, 0, 0x3, 0 },
  { TEXT_CreateIndirect, 	"Read", 			GUI_ID_TEXT2, 	120, 155, 40, 20, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, 	"Read", 			GUI_ID_BUTTON1, 180, 130, 40, 40, 0, 0x0, 0 },
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
static void _cbDialogEEPROM(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  uint8_t num[4]={0};
  static uint8_t writedata,writeadd,readadd,readdata;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
	  case WM_DELETE:
		OS_INFO("EEPROMapp delete\n");
		eepromflag=0;
		Flag_ICON103 = 0;
		UserApp_Flag = 0;
		WM_DeleteWindow(KEYBOARD);
		tpad_flag=0;
		break;
  case WM_INIT_DIALOG:
    //
    // Initialization of 'EEPROM TEST'
    //
    hItem = pMsg->hWin;
		FRAMEWIN_SetTextColor(hItem,GUI_DARKGRAY);
    FRAMEWIN_SetFont(hItem, GUI_FONT_16B_ASCII);
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		FRAMEWIN_AddCloseButton(hItem,FRAMEWIN_BUTTON_RIGHT,0);
    FRAMEWIN_SetTitleHeight(hItem, 20);
    //
    // Initialization of 'INIT'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT0);
    TEXT_SetFont(hItem, &XBF_Font);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    TEXT_SetText(hItem, "");
    //
    // Initialization of 'AUTOTEST'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT1);
    TEXT_SetFont(hItem, &XBF_Font);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
		TEXT_SetText(hItem, "");
    //
    // Initialization of 'Read'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT2);
    TEXT_SetFont(hItem, GUI_FONT_16_ASCII);
    TEXT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    TEXT_SetTextColor(hItem, GUI_RED);
		TEXT_SetText(hItem, "***");
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
    EDIT_SetText(hItem, "123");
    EDIT_SetTextColor(hItem, EDIT_CI_ENABLED, GUI_BLUE);
    EDIT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    EDIT_SetFont(hItem, GUI_FONT_16B_ASCII);
		EDIT_SetUlongMode(hItem,123,0,255);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_16B_ASCII);
    EDIT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    EDIT_SetTextColor(hItem, EDIT_CI_ENABLED, GUI_BLUE);
		EDIT_SetUlongMode(hItem,123,0,255);    
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2);
    EDIT_SetText(hItem, "123");
    EDIT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    EDIT_SetTextColor(hItem, EDIT_CI_ENABLED, GUI_BLUE);
    EDIT_SetFont(hItem, GUI_FONT_16B_ASCII);
		EDIT_SetUlongMode(hItem,123,0,255);
		//
    // Initialization of 'Write'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON0);
    BUTTON_SetFont(hItem, &XBF_Font);
		BUTTON_SetText(hItem, "写");
    //
    // Initialization of 'Read'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_BUTTON1);
    BUTTON_SetFont(hItem, &XBF_Font);
		BUTTON_SetText(hItem, "读");
    // USER START (Optionally insert additional code for further widget initialization)
		// USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case GUI_ID_EDIT0: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				if(!keypadflag) keypadapp(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0),1);
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
    case GUI_ID_EDIT1: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
			  // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				if(!keypadflag) keypadapp(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1),1);
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
    case GUI_ID_EDIT2: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)		
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				if(!keypadflag) keypadapp(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2),1);
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
	case GUI_ID_BUTTON0: // Notifications sent by 'Write'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				writeadd  = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0));
				writedata = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1));
				ee_WriteBytes(&writedata, writeadd, 1);
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case GUI_ID_BUTTON1: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				readadd = EDIT_GetValue(WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2));
				ee_ReadBytes(&readdata,readadd,1);
				num[0]=readdata/100+'0';
				num[1]=readdata%100/10+'0';
				num[2]=readdata%100%10+'0';
				num[3]='\0';
				//printf("readdata=%s\n",num);
				TEXT_SetText(WM_GetDialogItem(pMsg->hWin, GUI_ID_TEXT2),(const char *)num);
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
		GUI_DispStringHCenterAt("写数据",110,5);
		GUI_DispStringAt("地址(0-255):",20,35);
		GUI_DispStringAt("数据(0-255):",20,70);
		GUI_DispStringHCenterAt("读数据",110,100);
		GUI_DispStringAt("地址(0-255):",20,125);
		GUI_DispStringAt("数据(0-255):",20,155);
		GUI_DispStringAt("初始化结果：",20,230);
		GUI_DispStringAt("自动测试结果：",20,260); 
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
*       CreateEEPROM TEST
*/
void FUN_ICON103Clicked(void)
{
	WM_HWIN hWin;
	uint8_t flag=0;
	uint16_t i;
	uint8_t write_buf[macEE_SIZE],read_buf[macEE_SIZE];
	OS_INFO("EEPROMapp create\n");
	hWin = GUI_CreateDialogBox(_aDialogCreateEEPROM, GUI_COUNTOF(_aDialogCreateEEPROM), _cbDialogEEPROM, WM_HBKWIN, 0, 0);
	GUI_Delay(1); 
	
	i2c_ee_CheckDevice(macEE_DEV_ADDR);
	if (ee_CheckOk())
	{	eepromflag=1;
		TEXT_SetText(WM_GetDialogItem(hWin, GUI_ID_TEXT0),"成功");
	}
	else 
	{	
		TEXT_SetText(WM_GetDialogItem(hWin, GUI_ID_TEXT0),"出错");
		eepromflag=0;
	}
	
	if(eepromflag)
	{
		/*------------------------------------------------------------------------------------*/  
		/* 填充测试缓冲区 */
		for (i = 0; i < macEE_SIZE; i++)
		{		
			write_buf[i] = i;
		}
		/*------------------------------------------------------------------------------------*/  
		if (ee_WriteBytes(write_buf, 0, macEE_SIZE))//写数据
		{
			i=250;
			while(--i);//短延时
			if (ee_ReadBytes(read_buf, 0, macEE_SIZE))//读数据
			{	
				for (i = 0; i < macEE_SIZE; i++)//数据比较
				{
					if(read_buf[i] != read_buf[i])
					{
						flag++;
					}
				}
			}
		}
		if(flag)
			TEXT_SetText(WM_GetDialogItem(hWin, GUI_ID_TEXT1),"出错");
		else
			TEXT_SetText(WM_GetDialogItem(hWin, GUI_ID_TEXT1),"成功");
	}
	else
		TEXT_SetText(WM_GetDialogItem(hWin, GUI_ID_TEXT1),"出错");
	while(Flag_ICON103)
	{
		if(tpad_flag)WM_DeleteWindow(hWin);
		GUI_Delay(10); 
	}
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
