#include <stdint.h>



int main(void)
{
	//BLUE LED - PB7
	//configure GPIOB AHB2ENR for blue led
	uint32_t RCC_AHB2ENR = 0x40021000;
	uint32_t RCC_AHB2ENR_OFFSET = 0x4C;

	uint32_t* AHB2ENR = (uint32_t*)(RCC_AHB2ENR + RCC_AHB2ENR_OFFSET);

	//want to ENABLE -- want to make bit 1, 1 or bit 2 if its the button
	*AHB2ENR |= (1U << 1) | (1U << 2);


	//configure the pin1
	uint32_t* GPIOB_MODER = (uint32_t*) 0x48000400;
	//bit 14 to 1 to make this an output
	*GPIOB_MODER |= (1U << 14);
	*GPIOB_MODER = *GPIOB_MODER & ~(1U << 15);


	//enable the button -- PC13
	uint32_t RCC_ADDR = 0x40021000;
	uint32_t RCC_APB2ENR_OFFSET = 0x60;
	uint32_t* APB2ENR = (uint32_t*)(RCC_ADDR + RCC_APB2ENR_OFFSET);
	//Want to set the last bit to 1
	*APB2ENR |= (1U << 0);


	//configure as an input pin--- MODE 13 change bit 27/26
	uint32_t* GPIOC_MODER = (uint32_t*)0x48000800;
	*GPIOC_MODER &= ~(3U << 26); // 3 is 0011 in binary


	// configure SYSCFG_EXTICR4, routing to PortC
	uint32_t SYSCFG_ADDR = 0x40010000;
	uint32_t SYSCFG_EXTICR4_OFFSET = 0x14;

	uint32_t* EXTICR4 = (uint32_t*) (SYSCFG_ADDR + SYSCFG_EXTICR4_OFFSET);

	//ENABLE 0010 on bits 7-4
	*EXTICR4 &= ~(0xFU << 4); //CLEAR THE BITS
	*EXTICR4 |= (2U << 4);


	// configure PUDR pin 13 == mode 13
	uint32_t GPIO_PUPDR = 0x48000800;
	uint32_t GPIO_PUPDR_OFFSET = 0x0C;

	uint32_t* PUPDR = (uint32_t*) (GPIO_PUPDR + GPIO_PUPDR_OFFSET);
	//for pull down the 27/26 bits have to be 1 0
	*PUPDR &= ~(3U << 26); // 3 is 0011 in binary


	//configure the rising trigger vs the falling trigger (using rising)
	uint32_t EXTI_RTSR1 = 0x40010400;
	uint32_t EXTI_RTSR1_OFFSET = 0x08;

	uint32_t* RTSR1 = (uint32_t*)(EXTI_RTSR1 + EXTI_RTSR1_OFFSET);
	*RTSR1 |= (1U << 13); //first bit needs to be 1



	//disable the falling trigger
	uint32_t EXTI_FTSR1 = 0x40010400;
	uint32_t EXTI_FTSR1_OFFSET = 0x0C;

	uint32_t* FTSR1 = (uint32_t*)(EXTI_FTSR1 + EXTI_FTSR1_OFFSET);
	*FTSR1 &= ~(1U << 13); //13TH bit needs to be 0, clear it to disable



	//unmask the interrupt mask register
	uint32_t* EXTI_IMR1 = (uint32_t*)0x40010400;
	*EXTI_IMR1 |= (1U << 13);


	//handle the NVIC and set the position bit
	uint32_t* NVIC_ISER1 = (uint32_t*)0xE000E104;
	//since its bit 40, there is no bit 40, so you take up the entirety of the first register and then shift by the remaining bits
	*NVIC_ISER1 |= (1U << 8); //set bit 40 to 1

	while(1)
	{

	};
}
//IRQ handler
void EXTI15_10_IRQHandler(void) {
	//reset the pending register
	uint32_t EXTI_PR1 = 0x40010400;
	uint32_t EXTI_PR1_OFFSET = 0x14;
	uint32_t* PR1 = (uint32_t*)(EXTI_PR1 + EXTI_PR1_OFFSET);
	//set the blue LED
	uint32_t* gpio_b = (uint32_t*)(0x48000400 + 0x14);
	//what to do when the interrupt happens
	//need to clear the pending flag
	if (*PR1 & (1U << 13) ) {
		//RESET THE PENDING REGISTER
		*PR1 = (1U << 13);
		//toggle the blue led
		*gpio_b ^= (1U << 7); // write

	}








}
