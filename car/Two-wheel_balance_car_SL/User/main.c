//------------头文件-------------------------
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "freertos.h"
#include "task.h"
#include "encoder.h"
//-------------------------------------------
uint8_t Number = 0;
//-------------------------------------------
//------------创建任务句柄-------------------
TaskHandle_t LEDTaskHandle;
TaskHandle_t OLEDTaskHandle;
//-------------------------------------------
//-----------任务的回调函数------------------
void LED_TaskFunction(void *pream)
{
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		vTaskDelay(1000);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		vTaskDelay(1000);
	}
}
void OLED_TaskFunction(void *pream)
{
	while(1)
	{
		OLED_ShowNum(0,0,Number,5,OLED_8X16);
		vTaskDelay(1000);
		Number++;
	}
}
//-------------------------------------------
//-----------------主函数--------------------
int main(void)
{
	OLED_Init();
	Encoder_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	//---------------------------------------
	//-------------创建任务(动态调度)--------
	xTaskCreate(LED_TaskFunction,"LED_TASK",512,NULL,1,&LEDTaskHandle);
	xTaskCreate(OLED_TaskFunction,"OLED_TASK",512,NULL,1,&OLEDTaskHandle);
	//---------------------------------------
	//--------------开启任务调度-------------
	vTaskStartScheduler();
}
