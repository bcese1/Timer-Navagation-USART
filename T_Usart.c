//*****************************************************************************
// Name: Benjamin Cesero
// Date Due: 11/22/22
// Course: ELEC3371
// Description:
// The program is used to turn on LEDs using the navigation switch.
// Pressing Up, Down, Left, Right, Click will turn on the correct LEDs
// The LEDs on Port E will only be used in this code.
// USART1 will be enabled to output and recieved through the terminal at 56000
// baud. Commands that are used are: UP, DN, LT, RT, CK, Q(check count).
// The terminal will also display when a button is pressed using the navigation
// switch or using the USART1. In the case of an error reset the board
//*****************************************************************************
void InitializeUSART1()             // Sub function which initializes the registers to enable USART1
{
      RCC_APB2ENR |= 1;             // Enable clock for Alt.
      AFIO_MAPR=0X0F000000;
      RCC_APB2ENR |= 1<<2;          // Enable clock for GPIOA
      GPIOA_CRH &= ~(0xFF << 4);    // Clear PA9, PA10
      GPIOA_CRH |= (0x0B << 4);     // USART1 Tx (PA9) output push-pull
      GPIOA_CRH |= (0x04 << 8);     // USART1 Rx (PA10) input floating
      RCC_APB2ENR |= 1<<14;         // enable clock for USART1
      USART1_BRR=0X00000506;        // Set baud rate to 56000
      USART1_CR1 &= ~(1<<12);       // Force 8 data bits. M bit is set to 0
      USART1_CR2 &= ~(3<<12);       // Force 1 stop bit
      USART1_CR3 &= ~(3<<8);        // Force no flow control and no DMA for USART1
      USART1_CR1 &= ~(3<<9);        // Force no parity and no parity control
      USART1_CR1 |= 3<<2;           // RX, TX enable
      USART1_CR1 |= 1<<13;          // USART1 enab
      Delay_ms(100);                // Wait for USART to complete configuration and enable

}