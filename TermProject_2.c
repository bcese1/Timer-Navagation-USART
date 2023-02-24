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
// Global Varibales & Includes
#include "Global_Defines.h"
// Function Declarations
void mystate();
void InitializeUSART1();
void U_up();
void U_dn();
void U_lt();
void U_rt();
void U_ck();
void U_q();
void convert_up_to_bcd(int val);
void convert_dn_to_bcd(int val);
void convert_lt_to_bcd(int val);
void convert_rt_to_bcd(int val);
void convert_ck_to_bcd(int val);
void data_in(void);

//*****************************************************************************

void main()
{
  InitializeUSART1();
  RCC_APB2ENR |= 1 << 5;      // GPIOD Clock
  RCC_APB2ENR |= 1 << 3;      // GPIOB Clock
  RCC_APB2ENR |= 1 << 6;      // GPIOE Clock
  RCC_APB2ENR |= 1 << 4;      // GLIOC Clock
  RCC_APB2ENR |= 1 << 2;      // GPIOA Clock
  GPIOE_CRL = 0x33333333;     // Load lower half of GPIOE to output
  GPIOE_CRH = 0x33333333;     // Load higher half of GPIOE to output
  GPIOA_CRL = 0x44444444;     // Load lower half of GPIOA to input
  GPIOB_CRL = 0x44444444;     // Load lower half of GPIOB to input
  GPIOB_CRH = 0x44444444;     // Load higher half of GPIOB to input
  GPIOC_CRL = 0x44444444;     // Load lower half of GPIOC to input
  GPIOC_CRH = 0x44444444;     // Load higher half of GPIOC to input
  GPIOD_CRL = 0x44444444;     // Load lower half of GPIOD to input
  GPIOD_CRH = 0x44444444;     // Load higher half of GPIOD to input
  mystate_t = _idle;          // Set my state to _idle
  // Initialize _Up, _Down, Right, Left, Click flags
  _up.flag = 0;
  _up.usartflag_s = 0;
  _up.usartflag = 0;
  _up.state0 = 0;
  _up.state1 = 1;
  _up.state2 = 2;
  _up.state3 = 3;
  _up.idleflag = 0;
  
  _down.flag = 0;
  _down.usartflag_s = 0;
  _down.usartflag = 0;
  _down.state0 = 0;
  _down.state1 = 1;
  _down.state2 = 2;
  _down.state3 = 3;
  _down.idleflag = 0;
  
  _left.flag = 0;
  _left.usartflag_s = 0;
  _left.usartflag = 0;
  _left.state0 = 0;
  _left.state1 = 1;
  _left.state2 = 2;
  _left.state3 = 3;
  _left.idleflag = 0;
  
  _right.flag = 0;
  _right.usartflag_s = 0;
  _right.usartflag = 0;
  _right.state0 = 0;
  _right.state1 = 1;
  _right.state2 = 2;
  _right.state3 = 3;
  _right.idleflag = 0;
  
  _click.flag = 0;
  _click.usartflag_s = 0;
  _click.usartflag = 0;
  _click.state0 = 0;
  _click.state1 = 1;
  _click.state2 = 2;
  _click.state3 = 3;
  _click.idleflag = 0;

for(;;) // infinite for loop
      {
         // calls the declared function and executes them
         data_in();
         U_up();
         U_dn();
         U_lt();
         U_rt();
         U_ck();
         U_q();
         convert_up_to_bcd(up_count);
         convert_dn_to_bcd(dn_count);
         convert_lt_to_bcd(lt_count);
         convert_rt_to_bcd(rt_count);
         convert_ck_to_bcd(ck_count);

        if(GPIOD_IDR.B4 == 0 && upp == 0)    // if B4 on port d or upp is equal to 0 proceed
         {
          mystate_t = up;                    // set my mystate_t to enum up
         }
         if(GPIOB_IDR.B5 == 0 && dnn == 0)   // if B5 on port b or dnn is equal to 0 proceed
         {
          mystate_t = dn;                    // set my mystate_t to enum dn
         }
         if(GPIOD_IDR.B2 == 0 && ltt == 0)   // if B2 on port d or ltt is equal to 0 proceed
         {
          mystate_t = lt;                    // set my mystate_t to enum lt
         }
         if(GPIOA_IDR.B6 == 0 && rtt == 0)   // if B6 on port a or rt is eqaul to 0 proceed
         {
          mystate_t = rt;                    // set my mystate_t to enum rt
         }
         if(GPIOC_IDR.B13 == 0 && ckk == 0)  // if B13 on port c or ckk is equal to 0 proceed
         {
          mystate_t = ck;                    // set mystate_t to enum ck
         }
         mystate();                 // calls mystate
       }
}

void mystate()
     {
      switch(mystate_t)           // switch case for state machine
         {
          case _idle:       // case _idle
                
                if (upp == 0)
               {
                    GPIOE_ODR.B11 = 0;        // shifts bit into port 11
                    GPIOE_ODR.B15 = 0;        // shifts bit into port 15
               }

                if (dnn == 0)
               {
                    GPIOE_ODR.B8  = 0;        // shifts bit into port 8
                    GPIOE_ODR.B12 = 0;        // shifts bit into port 12
               }
               
               if (ltt == 0)
               {
                    GPIOE_ODR.B13  = 0;          // shifts bit into port 13
                    GPIOE_ODR.B14 = 0;           // shifts bit into port 14
               }
               
               if (rtt == 0)
               {
                    GPIOE_ODR.B9  = 0;         // shifts bit into port 9
                    GPIOE_ODR.B10 = 0;         // shifts bit into port 10
               }
               
               if (ckk == 1)
               {
                    GPIOE_ODR |= 1 <<   9;      // shifts bit into port 9
                    GPIOE_ODR |= 1 <<   14;     // shifts bit into port 14
               }
               else
               {
                  if (ltt == 0 || rtt == 0)
                  {
                   GPIOE_ODR.B9  = 0;         // shifts bit into port 9
                   GPIOE_ODR.B14 = 0;         // shifts bit into port 14
                  }
               }

               OneTime = 0;                  // sets flag OneTime to 0
               break;
          case up:
               // turning on PE11 & PE15
               GPIOE_ODR |= 0x8800;

               while (! (USART1_SR & (1<<7)) == 0x80) {} // check if SR is not empty
               if ( OneTime == 0)
               {
                  Delay_ms(30);                          // debounce
                  for(i = 0; i < upindex; i++)           // for loop to display up in terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = r_up[i];
                  }
                  for(i = 0; i < pressindex; i++)        // for loop to display pressed in terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = pressed[i];
                  }
                  OneTime = 1;                          // set OneTime to 1
                  mystate_t = _idle;                    // go to idle
                  up_count++;                           // add to the count
               }
               break;
          case dn:
               // turning on PE8 & PE12
               GPIOE_ODR |= 0x1100;
               while (! (USART1_SR & (1<<7)) == 0x80) {}  // check if SR is not empty
               if ( OneTime == 0)
               {
                  Delay_ms(30);                         // debounce
                  for(i = 0; i < dnindex; i++)          // for loop to display dn in terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = r_dn[i];
                  }
                  for(i = 0; i < pressindex; i++)       // for loop to display pressed in terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = pressed[i];
                  }
                  OneTime = 1;                         // set OneTime to 1
                  mystate_t = _idle;                   // go to idle
                  dn_count++;                          // add to the count
               }
               break;
          case lt:
               // turning on PE13 & PE14
               GPIOE_ODR |= 0x6000;
               while (! (USART1_SR & (1<<7)) == 0x80) {}  // check if SR is not empty
               if ( OneTime == 0)
               {
                  Delay_ms(30);                          // debounce
                  for(i = 0; i < ltindex; i++)           // for loop to display lt in terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = r_lt[i];
                  }
                  for(i = 0; i < pressindex; i++)       // for loop to display pressed in terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = pressed[i];
                  }
                  OneTime = 1;                         // set OneTime to 1
                  mystate_t = _idle;                   // go to idle
                  lt_count++;                          // add to the count
               }
               break;
          case rt:
               // turning on PE9 & PE10
               GPIOE_ODR |= 0x0600;
               while (! (USART1_SR & (1<<7)) == 0x80) {}   // check if SR is not empty
               if ( OneTime == 0)
               {
                  Delay_ms(30);                            // debounce
                  for(i = 0; i < rtindex; i++)             // for loop to display rt in terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = r_rt[i];
                  }
                  for(i = 0; i < pressindex; i++)         // for loop to display pressed in terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = pressed[i];
                  }
                  OneTime = 1;                            // set OneTime to 1
                  mystate_t = _idle;                      // go to idle
                  rt_count++;                             // add to the count
               }
               break;
          case ck:
               // turning on PE9 & PE14
               GPIOE_ODR |= 0x4200;
               while (! (USART1_SR & (1<<7)) == 0x80) {}     // check if SR is not empty
               if ( OneTime == 0)
               {
                  Delay_ms(30);                              // debounce
                  for(i = 0; i < ckindex; i++)               // for loop to display ck in terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = r_ck[i];
                  }
                  for(i = 0; i < pressindex; i++)            // for loop to display pressed in terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = pressed[i];
                  }
                  OneTime = 1;                               // set OneTime to 1
                  mystate_t = _idle;                         // go to idle
                  ck_count++;                                // add to the count
               }
               break;
          default:
                  lsb[0] = 0x00;
                  lsb[1] = 0x00;
                  rcvrdcount = 0;
                  mystate_t = _idle;
               break;
         }



     }
void U_up()
{

               if(lsb[0] == 'U')                       // checks lsb for U
               {
                if(lsb[1] == 'P')                      // check lsb for P
                {
                 rcvrdcount = 0;                       // puts rcvrdcount back to 0 for next msg
                 lsb[0] = 0x00;                        // resets array
                 lsb[1] = 0x00;                        // resets array
                 mystate_t = up;                       // go to state up

                 // keeps it in state up
                 if(_up.usartflag == _up.state0)
                 {
                  _up.usartflag = _up.state1;
                  upp = 1;
                 }
                 // breaks from state up
                 if(_up.usartflag == _up.state2)
                 {
                 _up.usartflag = _up.state3;
                 upp = 0;
                 }
                }
               }
          // sets flag and usartflag_s to 1 for button pressed
          if(_up.usartflag_s == Low && GPIOD_IDR.B4 == Low && upp == 0)
               {
                _up.usartflag_s = 1;
                _up.flag = 1;
               }
          // sets flag to 2 and usartflag_s to 0 for button released
          if(_up.usartflag_s == High && GPIOD_IDR.B4 == High && upp ==0)
               {
                _up.usartflag_s = 0;
                _up.flag = 2;
               }
          // go to state button pressed
          if(_up.flag == 1 || _up.usartflag == _up.state1)
          {
           _up.flag = 0;
           _up.usartflag = _up.state2;
           _up.idleflag = 1;
          }
          // button is released
          if(_up.flag == 2 || _up.usartflag == _up.state3)
          {
           _up.flag = 0;
           _up.usartflag = _up.state0;
           _up.idleflag = 0;

           for(i = 0; i < upindex; i++)
           {
           while(USART1_SR.TC == 0) {}
           USART1_DR = r_up[i];
           }
           for(i = 0; i < releaseindex; i++)
           {
           while(USART1_SR.TC == 0){}
           USART1_DR = r_upr[i];
           }
           mystate_t = _idle;
          }
}

void U_dn()
{
               if(lsb[0] == 'D')      // Check for D
               {
                if(lsb[1] == 'N')     // Checks for N
                {
                 rcvrdcount = 0;      // puts rcvrdcount back to 0 for next msg
                 lsb[0] = 0x00;       // reset array
                 lsb[1] = 0x00;       // reset array
                 mystate_t = dn;      // go to down state
                 // keeps it in state dn
                 if(_down.usartflag == _down.state0)
                 {
                  _down.usartflag = _down.state1;
                  dnn = 1;
                 }
                 // breaks from state dn
                 if(_down.usartflag == _down.state2)
                 {
                 _down.usartflag = _down.state3;
                 dnn = 0;
                 }
                }
               }
          // sets flag and usartflag_s to 1 for button pressed
          if(_down.usartflag_s == Low && GPIOB_IDR.B5 == Low && dnn == 0)
               {
                _down.usartflag_s = 1;
                _down.flag = 1;
               }
          // sets flag to 2 and usartflag_s to 0 for button released
          if(_down.usartflag_s == High && GPIOB_IDR.B5 == High && dnn ==0)
               {
                _down.usartflag_s = 0;
                _down.flag = 2;
               }
          // go to state button pressed
          if(_down.flag == 1 || _down.usartflag == _down.state1)
          {
           _down.flag = 0;
           _down.usartflag = _down.state2;
           _down.idleflag = 1;
          }
          // button is released
          if(_down.flag == 2 || _down.usartflag == _down.state3)
          {
           _down.flag = 0;
           _down.usartflag = _down.state0;
           _down.idleflag = 0;
           for(i = 0; i < dnindex; i++)
           {
           while(USART1_SR.TC == 0) {}
           USART1_DR = r_dn[i];
           }
           for(i = 0; i < releaseindex; i++)
           {
           while(USART1_SR.TC == 0){}
           USART1_DR = r_upr[i];
           }
           mystate_t = _idle;
          }
}

void U_lt()
{
               if(lsb[0] == 'L')           // checks for L
               {
                if(lsb[1] == 'T')          // checks for T
                {
                 rcvrdcount = 0;          // puts rcvrdcount back to 0 for next msg
                 lsb[0] = 0x00;           // reset array
                 lsb[1] = 0x00;           // reset array
                 mystate_t = lt;          // go to left state
                 // keeps it in state lt
                 if(_left.usartflag == _left.state0)
                 {
                  _left.usartflag = _left.state1;
                  ltt = 1;
                 }
                 // breaks from state lt
                 if(_left.usartflag == _left.state2)
                 {
                 _left.usartflag = _left.state3;
                 ltt = 0;
                 }
                }
               }
          // sets flag and usartflag_s to 1 for button pressed
          if(_left.usartflag_s == Low && GPIOD_IDR.B2 == Low && ltt == 0)
               {
                _left.usartflag_s = 1;
                _left.flag = 1;
               }
          // sets flag to 2 and usartflag_s to 0 for button released
          if(_left.usartflag_s == High && GPIOD_IDR.B2 == High && ltt ==0)
               {
                _left.usartflag_s = 0;
                _left.flag = 2;
               }
          // go to state button pressed
          if(_left.flag == 1 || _left.usartflag == _left.state1)
          {
           _left.flag = 0;
           _left.usartflag = _left.state2;
           _left.idleflag = 1;
          }
          // button is released
          if(_left.flag == 2 || _left.usartflag == _left.state3)
          {
           _left.flag = 0;
           _left.usartflag = _left.state0;
           _left.idleflag = 0;
           for(i = 0; i < ltindex; i++)
           {
           while(USART1_SR.TC == 0) {}
           USART1_DR = r_lt[i];
           }
           for(i = 0; i < releaseindex; i++)
           {
           while(USART1_SR.TC == 0){}
           USART1_DR = r_upr[i];
           }
           mystate_t = _idle;
          }
}

void U_rt()
{
               if(lsb[0] == 'R')      // checks for R
               {
                if(lsb[1] == 'T')     // checks for T
                {
                 rcvrdcount = 0;     // puts rcvrdcount back to 0 for next msg
                 lsb[0] = 0x00;      // reset array
                 lsb[1] = 0x00;      // reset array
                 mystate_t = rt;     // go to right state
                 // keeps it in state rt
                 if(_right.usartflag == _right.state0)
                 {
                  _right.usartflag = _right.state1;
                  rtt = 1;
                 }
                 // breaks from state lt
                 if(_right.usartflag == _right.state2)
                 {
                 _right.usartflag = _right.state3;
                 rtt = 0;
                 }
                }
               }
          // sets flag and usartflag_s to 1 for button pressed
          if(_right.usartflag_s == Low && GPIOA_IDR.B6 == Low && rtt == 0)
               {
                _right.usartflag_s = 1;
                _right.flag = 1;
               }
          // sets flag to 2 and usartflag_s to 0 for button released
          if(_right.usartflag_s == High && GPIOA_IDR.B6 == High && rtt ==0)
               {
                _right.usartflag_s = 0;
                _right.flag = 2;
               }
          // go to state button pressed
          if(_right.flag == 1 || _right.usartflag == _right.state1)
          {
           _right.flag = 0;
           _right.usartflag = _right.state2;
           _right.idleflag = 1;
          }
          // button is released
          if(_right.flag == 2 || _right.usartflag == _right.state3)
          {
           _right.flag = 0;
           _right.usartflag = _right.state0;
           _right.idleflag = 0;
           for(i = 0; i < rtindex; i++)
           {
           while(USART1_SR.TC == 0) {}
           USART1_DR = r_rt[i];
           }
           for(i = 0; i < releaseindex; i++)
           {
           while(USART1_SR.TC == 0){}
           USART1_DR = r_upr[i];
           }
           mystate_t = _idle;
          }
}

void U_ck()
{
               if(lsb[0] == 'C')         // check for C
               {
                if(lsb[1] == 'K')       // check for K
                {
                 rcvrdcount = 0;       // puts rcvrdcount back to 0 for next msg
                 lsb[0] = 0x00;        // resets array
                 lsb[1] = 0x00;        // resets array
                 mystate_t = ck;       // go to click state
                 // keeps it in state rt
                 if(_click.usartflag == _click.state0)
                 {
                  _click.usartflag = _click.state1;
                  ckk = 1;
                 }
                 // breaks from state lt
                 if(_click.usartflag == _click.state2)
                 {
                 _click.usartflag = _click.state3;
                 ckk = 0;
                 }
                }
               }
          // sets flag and usartflag_s to 1 for button pressed
          if(_click.usartflag_s == Low && GPIOC_IDR.B13 == Low && ckk == 0)
               {
                _click.usartflag_s = 1;
                _click.flag = 1;
               }
          // sets flag to 2 and usartflag_s to 0 for button released
          if(_click.usartflag_s == High && GPIOC_IDR.B13 == High && ckk ==0)
               {
                _click.usartflag_s = 0;
                _click.flag = 2;
               }
          // go to state button pressed
          if(_click.flag == 1 || _click.usartflag == _click.state1)
          {
           _click.flag = 0;
           _click.usartflag = _click.state2;
           _click.idleflag = 1;
          }
          // button is released
          if(_click.flag == 2 || _click.usartflag == _click.state3)
          {
           _click.flag = 0;
           _click.usartflag = _click.state0;
           _click.idleflag = 0;
           for(i = 0; i < ckindex; i++)
           {
           while(USART1_SR.TC == 0) {}
           USART1_DR = r_ck[i];
           }
           for(i = 0; i < releaseindex; i++)
           {
           while(USART1_SR.TC == 0){}
           USART1_DR = r_upr[i];
           }
           mystate_t = _idle;
          }
}

void U_q()
{
               if(lsb[0] == 'Q')       // check for Q
               {
                rcvrdcount = 0;        // puts rcvrdcount back to 0 for next msg
                lsb[0] = 0x00;         // reset array
                lsb[1] = 0x00;         // reset array
                
                for(i = 0; i < joystickindex; i++) // sends up to the terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = joystick[i];
                  }
                  
                for(i = 0; i < upindex; i++) // sends up to the terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = r_up[i];
                  }
                  // sends : XX to the terminal
                  USART1_DR = ':';
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x20;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = updigit10;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = updigit1;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x0D;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x0A;
                  while(USART1_SR.TC == 0) {}

                 for(i = 0; i < dnindex; i++)  // sends dn to the terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = r_dn[i];
                  }
                  // sends : XX to the terminal
                  USART1_DR = ':';
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x20;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = dndigit10;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = dndigit1;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x0D;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x0A;
                  while(USART1_SR.TC == 0) {}

                  for(i = 0; i < ltindex; i++)  // sends lt to the terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = r_lt[i];
                  }
                  // sends : XX to the terminal
                  USART1_DR = ':';
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x20;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = ltdigit10;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = ltdigit1;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x0D;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x0A;
                  while(USART1_SR.TC == 0) {}

                  for(i = 0; i < rtindex; i++)  // sends lt to the terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = r_rt[i];
                  }
                  // sends : XX to the terminal
                  USART1_DR = ':';
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x20;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = rtdigit10;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = rtdigit1;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x0D;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x0A;
                  while(USART1_SR.TC == 0) {}
                  
                  for(i = 0; i < ckindex; i++)  // sends lt to the terminal
                  {
                    while(USART1_SR.TC == 0) {}
                    USART1_DR = r_ck[i];
                  }
                  // sends : XX to the terminal
                  USART1_DR = ':';
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x20;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = ckdigit10;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = ckdigit1;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x0D;
                  while(USART1_SR.TC == 0) {}
                  USART1_DR = 0x0A;
                  while(USART1_SR.TC == 0) {}

                }



}

void data_in(void) // checks for incoming terminal data
{

if(((USART1_SR & (1<<5))== 0x20))
{
   rcvrd = USART1_DR;           // upackages into the variable
   lsb[rcvrdcount] = rcvrd;     // adds it to the array based off count
   rcvrdcount++;                // adds to count
}

while (! (USART1_SR & (1<<7)) == 0x80) {}

}

// converts the up count to ascii
void convert_up_to_bcd(int val)
{
    updigit100 = (val / 100);
    temp = val - (updigit100 * 100);
    updigit10 = temp / 10;
    updigit1 = (val - (updigit100 * 100) - (updigit10 * 10)) + 48;
    updigit10 = updigit10 + 48;
    updigit100 = updigit100 + 48;

}
// converts the dn count to ascii
void convert_dn_to_bcd(int val)
{
    dndigit100 = (val / 100);
    temp = val - (dndigit100 * 100);
    dndigit10 = temp / 10;
    dndigit1 = (val - (dndigit100 * 100) - (dndigit10 * 10)) + 48;
    dndigit10 = dndigit10 + 48;
    dndigit100 = dndigit100 + 48;

}
// converts the lt count to ascii
void convert_lt_to_bcd(int val)
{
    ltdigit100 = (val / 100);
    temp = val - (ltdigit100 * 100);
    ltdigit10 = temp / 10;
    ltdigit1 = (val - (ltdigit100 * 100) - (ltdigit10 * 10)) + 48;
    ltdigit10 = ltdigit10 + 48;
    ltdigit100 = ltdigit100 + 48;

}
// converts the rt count to ascii
void convert_rt_to_bcd(int val)
{
    rtdigit100 = (val / 100);
    temp = val - (rtdigit100 * 100);
    rtdigit10 = temp / 10;
    rtdigit1 = (val - (rtdigit100 * 100) - (rtdigit10 * 10)) + 48;
    rtdigit10 = rtdigit10 + 48;
    rtdigit100 = rtdigit100 + 48;

}
// converts the ck count to ascii
void convert_ck_to_bcd(int val)
{
    ckdigit100 = (val / 100);
    temp = val - (ckdigit100 * 100);
    ckdigit10 = temp / 10;
    ckdigit1 = (val - (ckdigit100 * 100) - (ckdigit10 * 10)) + 48;
    ckdigit10 = ckdigit10 + 48;
    ckdigit100 = ckdigit100 + 48;

}