//PWMSine.c
/* This program generates a PWM sinusoidal signal on PA6 using Timer 3.
    The signal has 12-bits of resolution. 
*/
#include "stm32f446.h"
#include "math.h"
const float PI = 3.14159;
int main()

{int tmp, i;
	 float incr, x;
   //Clock bits
   RCC_AHB1ENR |= 1;         //Bit 0 is GPIOA clock enable bit
   //RCC_AHB1ENR |= 4;         //Bit 2 is GPIOC clock enable bit 
   RCC_APB1ENR |= 2;         //Enable peripheral timer for timer 3 (bit 1)
   //I/O bits
   GPIOA_MODER |= 0x2000;    //Bits 13-12 = 10 for Alt Funct Mode on PA6
   //OTYPER register resets to 0 so it is push/pull by default
   GPIOA_OSPEEDER |= 0x3000;  //Bits 13-12 = 11 for high speed on PA6
   //PUPDR defaults to no pull up no pull down    
   //Timer 3 bits
   GPIOA_AFRL = 0x02000000; //Sets PA6 to Timer 3
   TIM3_CCMR1 |= 0x60;      //Timer 3 in PWM Mode bits 6,5,4 = 110
   TIM3_CCMR1 |= 0x0C;      //Timer 3 Preload enable and fast enable
   TIM3_CR1 |= (1 << 7);    //Auto reload is buffered 
   TIM3_PSC = 0;            //Don't use prescaling
   TIM3_ARR = 320000;         //(16 MHz)/320000 = 50 Hz
   TIM3_CCR1 = 0;           //Duty cycle starts at 0
   TIM3_CCER |= 1;          //Compare and capture output enable
   TIM3_EGR |= 1;           //Enable event
   TIM3_CR1 |= 1;           //Enable Timer 3
   //Main program loop
   tmp = 0;
	 incr = 2*PI/8192;
	 x = 0;
   
	 //MATH 
	 //TIMER= 50Hz
	 //1/50=.020sec
	 //900-2100 µs for the HS 311
	 // .0009sec for 0 degrees
		//.0009/.020=.045
		//320000*.045=14400
	 // .0021 sec for 180 degrees
		//.0021/.02=.105
		//320000 *.105=33600
		
	//THEREFOR, MY RANGE FOR TIM3_CCR1 IS 14400-33600
	 
	 
	 //HS 311 requires pulse cycle of 20ms
	 //I need to use prescaling to get it to 50 hz
	 
	 
	 
	 while(1)
     {TIM3_CCR1 = 2666;
      //for(i=0;i<100;i++); //Delay 
      x += incr;
			tmp = (int)((sin(x) + 1)*1500);
      if(x >= 2*PI)
         x = 0;
     }
  }
