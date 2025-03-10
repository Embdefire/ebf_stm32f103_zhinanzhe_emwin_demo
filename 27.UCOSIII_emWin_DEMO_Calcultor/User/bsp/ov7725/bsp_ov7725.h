#ifndef __OV7725_H
#define __OV7725_H 
	   
#include "stm32f10x.h"


/* 寄存器宏定义 */
#define GAIN      0x00

#if 0
#define BLUE      0x01
#define RED       0x02
#define RED       0x02
#define GREEN     0x03
#endif

#define BAVG      0x05
#define GAVG      0x06
#define RAVG      0x07
#define AECH      0x08
#define COM2      0x09
#define PID       0x0A
#define VER       0x0B
#define COM3      0x0C
#define COM4      0x0D
#define COM5      0x0E
#define COM6      0x0F
#define AEC       0x10
#define CLKRC     0x11
#define COM7      0x12
#define COM8      0x13
#define COM9      0x14
#define COM10     0x15
#define REG16     0x16
#define HSTART    0x17
#define HSIZE     0x18
#define VSTART    0x19
#define VSIZE     0x1A
#define PSHFT     0x1B
#define MIDH      0x1C
#define MIDL      0x1D
#define LAEC      0x1F
#define COM11     0x20
#define BDBase    0x22
#define BDMStep   0x23
#define AEW       0x24
#define AEB       0x25
#define VPT       0x26
#define REG28     0x28
#define HOutSize  0x29
#define EXHCH     0x2A
#define EXHCL     0x2B
#define VOutSize  0x2C
#define ADVFL     0x2D
#define ADVFH     0x2E
#define YAVE      0x2F
#define LumHTh    0x30
#define LumLTh    0x31
#define HREF      0x32
#define DM_LNL    0x33
#define DM_LNH    0x34
#define ADoff_B   0x35
#define ADoff_R   0x36
#define ADoff_Gb  0x37
#define ADoff_Gr  0x38
#define Off_B     0x39
#define Off_R     0x3A
#define Off_Gb    0x3B
#define Off_Gr    0x3C
#define COM12     0x3D
#define COM13     0x3E
#define COM14     0x3F
#define COM16     0x41
#define TGT_B     0x42
#define TGT_R     0x43
#define TGT_Gb    0x44
#define TGT_Gr    0x45
#define LC_CTR    0x46
#define LC_XC     0x47
#define LC_YC     0x48
#define LC_COEF   0x49
#define LC_RADI   0x4A
#define LC_COEFB  0x4B 
#define LC_COEFR  0x4C
#define FixGain   0x4D
#define AREF1     0x4F
#define AREF6     0x54
#define UFix      0x60
#define VFix      0x61
#define AWBb_blk  0x62
#define AWB_Ctrl0 0x63
#define DSP_Ctrl1 0x64
#define DSP_Ctrl2 0x65
#define DSP_Ctrl3 0x66
#define DSP_Ctrl4 0x67
#define AWB_bias  0x68
#define AWBCtrl1  0x69
#define AWBCtrl2  0x6A
#define AWBCtrl3  0x6B
#define AWBCtrl4  0x6C
#define AWBCtrl5  0x6D
#define AWBCtrl6  0x6E
#define AWBCtrl7  0x6F
#define AWBCtrl8  0x70
#define AWBCtrl9  0x71
#define AWBCtrl10 0x72
#define AWBCtrl11 0x73
#define AWBCtrl12 0x74
#define AWBCtrl13 0x75
#define AWBCtrl14 0x76
#define AWBCtrl15 0x77
#define AWBCtrl16 0x78
#define AWBCtrl17 0x79
#define AWBCtrl18 0x7A
#define AWBCtrl19 0x7B
#define AWBCtrl20 0x7C
#define AWBCtrl21 0x7D 
#define GAM1      0x7E
#define GAM2      0x7F
#define GAM3      0x80
#define GAM4      0x81
#define GAM5      0x82
#define GAM6      0x83
#define GAM7      0x84
#define GAM8      0x85
#define GAM9      0x86
#define GAM10     0x87
#define GAM11     0x88
#define GAM12     0x89
#define GAM13     0x8A
#define GAM14     0x8B
#define GAM15     0x8C
#define SLOP      0x8D
#define DNSTh     0x8E
#define EDGE0     0x8F
#define EDGE1     0x90
#define DNSOff    0x91
#define EDGE2     0x92
#define EDGE3     0x93
#define MTX1      0x94
#define MTX2      0x95
#define MTX3      0x96
#define MTX4      0x97
#define MTX5      0x98
#define MTX6      0x99
#define MTX_Ctrl  0x9A
#define BRIGHT    0x9B
#define CNST      0x9C
#define UVADJ0    0x9E
#define UVADJ1    0x9F
#define SCAL0     0xA0
#define SCAL1     0xA1
#define SCAL2     0xA2
#define SDE       0xA6
#define USAT      0xA7
#define VSAT      0xA8
#define HUECOS    0xA9
#define HUESIN    0xAA
#define SIGN      0xAB
#define DSPAuto   0xAC


/************************** OV7725 连接引脚定义********************************/
#define      macOV7725_CS_SCK_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define      macOV7725_CS_GPIO_CLK                       RCC_APB2Periph_GPIOA
#define      macOV7725_CS_GPIO_PORT                      GPIOA
#define      macOV7725_CS_GPIO_PIN                       GPIO_Pin_3

#define      macOV7725_WRST_SCK_APBxClock_FUN            RCC_APB2PeriphClockCmd
#define      macOV7725_WRST_GPIO_CLK                     RCC_APB2Periph_GPIOC
#define      macOV7725_WRST_GPIO_PORT                    GPIOC
#define      macOV7725_WRST_GPIO_PIN                     GPIO_Pin_4

#define      macOV7725_RRST_SCK_APBxClock_FUN            RCC_APB2PeriphClockCmd
#define      macOV7725_RRST_GPIO_CLK                     RCC_APB2Periph_GPIOA
#define      macOV7725_RRST_GPIO_PORT                    GPIOA
#define      macOV7725_RRST_GPIO_PIN                     GPIO_Pin_2

#define      macOV7725_RCLK_SCK_APBxClock_FUN            RCC_APB2PeriphClockCmd
#define      macOV7725_RCLK_GPIO_CLK                     RCC_APB2Periph_GPIOC
#define      macOV7725_RCLK_GPIO_PORT                    GPIOC
#define      macOV7725_RCLK_GPIO_PIN                     GPIO_Pin_5

#define      macOV7725_WE_SCK_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define      macOV7725_WE_GPIO_CLK                       RCC_APB2Periph_GPIOD
#define      macOV7725_WE_GPIO_PORT                      GPIOD
#define      macOV7725_WE_GPIO_PIN                       GPIO_Pin_3


#define      macOV7725_DATA_SCK_APBxClock_FUN            RCC_APB2PeriphClockCmd
#define      macOV7725_DATA_GPIO_CLK                     RCC_APB2Periph_GPIOB
#define      macOV7725_DATA_GPIO_PORT                    GPIOB
#define      macOV7725_DATA_0_GPIO_PIN                   GPIO_Pin_8
#define      macOV7725_DATA_1_GPIO_PIN                   GPIO_Pin_9
#define      macOV7725_DATA_2_GPIO_PIN                   GPIO_Pin_10
#define      macOV7725_DATA_3_GPIO_PIN                   GPIO_Pin_11
#define      macOV7725_DATA_4_GPIO_PIN                   GPIO_Pin_12
#define      macOV7725_DATA_5_GPIO_PIN                   GPIO_Pin_13
#define      macOV7725_DATA_6_GPIO_PIN                   GPIO_Pin_14
#define      macOV7725_DATA_7_GPIO_PIN                   GPIO_Pin_15

#define      macOV7725_VSYNC_SCK_APBxClock_FUN           RCC_APB2PeriphClockCmd
#define      macOV7725_VSYNC_GPIO_CLK                    RCC_APB2Periph_GPIOC
#define      macOV7725_VSYNC_GPIO_PORT                   GPIOC
#define      macOV7725_VSYNC_GPIO_PIN                    GPIO_Pin_3
#define      macOV7725_VSYNC_EXTI_SOURCE_PORT            GPIO_PortSourceGPIOC
#define      macOV7725_VSYNC_EXTI_SOURCE_PIN             GPIO_PinSource3
#define      macOV7725_VSYNC_EXTI_LINE                   EXTI_Line3
#define      macOV7725_VSYNC_EXTI_IRQ                    EXTI3_IRQn
#define      macOV7725_VSYNC_EXTI_INT_FUNCTION           EXTI3_IRQHandler




#define FIFO_CS_H()     macOV7725_CS_GPIO_PORT->BSRR =macOV7725_CS_GPIO_PIN	  
#define FIFO_CS_L()     macOV7725_CS_GPIO_PORT->BRR  =macOV7725_CS_GPIO_PIN	  /*拉低使FIFO输出使能*/

#define FIFO_WRST_H()   macOV7725_WRST_GPIO_PORT->BSRR =macOV7725_WRST_GPIO_PIN	  /*拉高允许FIFO写(数据from摄像头)指针运动 */
#define FIFO_WRST_L()   macOV7725_WRST_GPIO_PORT->BRR  =macOV7725_WRST_GPIO_PIN	  /*拉低使FIFO写(数据from摄像头)指针复位*/

#define FIFO_RRST_H()   macOV7725_RRST_GPIO_PORT->BSRR =macOV7725_RRST_GPIO_PIN	  /*拉高允许FIFO读(数据从FIFO输出)指针运动 */
#define FIFO_RRST_L()   macOV7725_RRST_GPIO_PORT->BRR  =macOV7725_RRST_GPIO_PIN	  /*拉低使FIFO读(数据从FIFO输出)指针复位 */

#define FIFO_RCLK_H()   macOV7725_RCLK_GPIO_PORT->BSRR =macOV7725_RCLK_GPIO_PIN	  
#define FIFO_RCLK_L()   macOV7725_RCLK_GPIO_PORT->BRR  =macOV7725_RCLK_GPIO_PIN	  /*FIFO输出数据时钟*/

#define FIFO_WE_H()     macOV7725_WE_GPIO_PORT->BSRR =macOV7725_WE_GPIO_PIN	  /*拉高使FIFO写允许*/
#define FIFO_WE_L()     macOV7725_WE_GPIO_PORT->BRR  =macOV7725_WE_GPIO_PIN


#define READ_FIFO_PIXEL(RGB565)   	do{\
	                                  RGB565=0;\
	                                  FIFO_RCLK_L();\
	                                  RGB565 = (GPIOB->IDR) & 0xff00;\
	                                  FIFO_RCLK_H();\
                                    FIFO_RCLK_L();\
	                                  RGB565 |= (GPIOB->IDR >>8) & 0x00ff;\
	                                  FIFO_RCLK_H();\
                                    }while(0)

#define FIFO_PREPARE                do{\
	                                  FIFO_RRST_L();\
	                                  FIFO_RCLK_L();\
	                                  FIFO_RCLK_H();\
	                                  FIFO_RRST_H();\
	                                  FIFO_RCLK_L();\
	                                  FIFO_RCLK_H();\
                                    }while(0)

#define OV7725_ID       0x21

void Ov7725_GPIO_Config(void);
ErrorStatus Ov7725_Init(void);
void VSYNC_Init(void);
void DisableCamera(void);
#endif
