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
#ifndef Global_Defines_h
#define Global_Defines_h
#define upindex 3
#define dnindex 5
#define ltindex 5
#define rtindex 6
#define ckindex 6
#define joystickindex 19
#define releaseindex 10
#define pressindex 9
#define High 1
#define Low 0
enum state{_idle, up, dn, lt, rt, ck}mystate_t; // Creates a group of elements
volatile int rcvrd; // unpacking data register
volatile int OneTime = 0;
// terminal out array
volatile int r_up[upindex] = {'U','P', 0x20};
volatile int r_dn[dnindex] = {'D','O','W','N', 0x20};
volatile int r_lt[ltindex] = {'L','E','F','T', 0x20};
volatile int r_rt[rtindex] = {'R','I','G','H','T', 0x20};
volatile int r_ck[ckindex] = {'C','L','I','C','K', 0x20};
volatile int r_upr[releaseindex] = {'R','E','L','E','A','S','E','D', 0x0D, 0x0A};
volatile int pressed[pressindex] = {'P','R','E','S','S','E','D', 0x0D, 0x0A};
volatile int joystick[joystickindex] = {'J','O','Y','S','T','I','C','K',0x20,'P','R','E','S','S','E','S',':',0x0D,0x0A};
//////////////////////////
volatile int i = 0;
volatile int rcvrdcount = 0;
volatile int lsb[2];      // array for incoming data
volatile int new = 0;
volatile int upp = 0;
volatile int dnn = 0;
volatile int ltt = 0;
volatile int rtt = 0;
volatile int ckk = 0;
// conversion for ascii
volatile int updigit100 = 0;
volatile int updigit10 = 0;
volatile int updigit1 = 0;
volatile int dndigit100 = 0;
volatile int dndigit10 = 0;
volatile int dndigit1 = 0;
volatile int ltdigit100 = 0;
volatile int ltdigit10 = 0;
volatile int ltdigit1 = 0;
volatile int rtdigit100 = 0;
volatile int rtdigit10 = 0;
volatile int rtdigit1 = 0;
volatile int ckdigit100 = 0;
volatile int ckdigit10 = 0;
volatile int ckdigit1 = 0;
volatile int temp = 0;
//////////////////////////////////
// keeps track of button count
volatile int up_count = 0;
volatile int dn_count = 0;
volatile int lt_count = 0;
volatile int rt_count = 0;
volatile int ck_count = 0;
/////////////////////////////////
//flags for the up logic
typedef volatile struct {
  usartflag    : 3;
  state0       : 3;
  state1       : 3;
  state2       : 3;
  state3       : 3;
  usartflag_s  : 3;
  flag         : 3;
  idleflag     : 3;} myunsigned_up;
myunsigned_up _up;
//flags for the dn logic
typedef volatile struct {
  usartflag    : 3;
  state0       : 3;
  state1       : 3;
  state2       : 3;
  state3       : 3;
  usartflag_s  : 3;
  flag         : 3;
  idleflag     : 3;} myunsigned_dn;
myunsigned_dn _down;
//flags for the lt logic
typedef volatile struct {
  usartflag    : 3;
  state0       : 3;
  state1       : 3;
  state2       : 3;
  state3       : 3;
  usartflag_s  : 3;
  flag         : 3;
  idleflag     : 3;} myunsigned_lt;
myunsigned_lt _left;
//flags for the rt logic
typedef volatile struct {
  usartflag    : 3;
  state0       : 3;
  state1       : 3;
  state2       : 3;
  state3       : 3;
  usartflag_s  : 3;
  flag         : 3;
  idleflag     : 3;} myunsigned_rt;
myunsigned_rt _right;
//flags for the ck logic
typedef volatile struct {
  usartflag    : 3;
  state0       : 3;
  state1       : 3;
  state2       : 3;
  state3       : 3;
  usartflag_s  : 3;
  flag         : 3;
  idleflag     : 3;} myunsigned_ck;
myunsigned_ck _click;
#endif