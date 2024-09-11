#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "encoder.h"

int main(void){
	
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(0,0,"Hello",OLED_8X16);
	OLED_Update();
	
	while(1)
	{
		
	}

}
