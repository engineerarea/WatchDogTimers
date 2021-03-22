#include "stm32f10x.h"                  // Device header
#include "stm32f10x_wwdg.h"             // Keil::Device:StdPeriph Drivers:WWDG
#include "stm32f10x_iwdg.h"             // Keil::Device:StdPeriph Drivers:IWDG

void GpioConfig(){

GPIO_InitTypeDef GpioInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GpioInitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GpioInitStructure.GPIO_Pin=GPIO_Pin_0;
	GpioInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GpioInitStructure);

}



void delayUs(uint32_t time){
	uint32_t Newtime=time*24;


	while(Newtime--);

}
void iwdgConfig(){

 RCC_LSICmd(ENABLE);
	///clock u AKTIF ETTIK
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET){
	}
	//low speed internal ready (lsirdy);
	///FLAG LOW SPEED INTERNAL RESET OLDUGUNDA BI SEY DÖNDÜRMICEK
	
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_4);
  IWDG_SetReload(0xFFF);
	IWDG_ReloadCounter();
	IWDG_Enable();

}

int main(){

GpioConfig();
	
GPIO_ResetBits(GPIOB,GPIO_Pin_0);
delayUs(3000);///micro saniye
GPIO_SetBits(GPIOB,GPIO_Pin_0);
iwdgConfig();

	
	
while(1){

///Çalisma prensibi ilk önce ledimiz resetdurumunda 3000 ms bekliyor daha sonra setleniyor.
//Setledikten sonra IwdgConfig e girdigi için çalisa bilecegi 100ms kaliyor 
//Daha sonra 100ms geçtikten sonra sistemi Sifirliyor.

}

}


//void WindowWDGConfig(){

//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
//	
//	WWDG_DeInit();
//	
//	WWDG_SetPrescaler(WWDG_Prescaler_8);
//	WWDG_SetWindowValue(120);
//	WWDG_Enable(100); ///counter value
//  WWDG_EnableIT();	////interrupt kismi
//	
//}

////void NvicConfig(){
////NVIC_InitTypeDef  NvicStructure;
//	
//NvicStructure.NVIC_IRQChannel=WWDG_IRQn;
//NvicStructure.NVIC_IRQChannelCmd=ENABLE;
//NvicStructure.NVIC_IRQChannelPreemptionPriority=1;
//NvicStructure.NVIC_IRQChannelSubPriority=0;

//NVIC_Init(&NvicStructure);

//}

//void WWDG_IRQHandler(){

//WWDG_ClearFlag();///intterptta girmesi için bayragi temziliyoruz
//	
//WWDG_SetCounter(100);///WWDG enable 100 ise buda 100 olur
//GPIOB->ODR ^=GPIO_Pin_0; /// degeri burda gpioB ODR regidterine atiyorum her bi intteruptan sonra Pin 0 in durumuun degistiriyor  

//}

//int main(){

//	
//	GpioConfig();
//	NvicConfig();
//	WindowWDGConfig();
//while(1){


//}

//}