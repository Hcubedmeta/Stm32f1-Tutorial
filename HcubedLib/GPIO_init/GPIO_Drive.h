 
#define RCC_APB2ENR   (*((volatile unsigned long *)0x40021018))

#define GPIO_A   (*((volatile unsigned long *)0x40010800))
#define GPIO_B   (*((volatile unsigned long *)0x40010C00))
#define GPIO_C   (*((volatile unsigned long *)0x40011000))
#define GPIO_D   (*((volatile unsigned long *)0x40011400))	
// list of port
#define PA 1
#define PB 2
#define PC 3
#define PD 4
// direction
#define IN 0
#define O_10MHz 1
#define O_2MHz  2
#define O_50MHz 3
// direction options for input
#define Input_Analog 			0
#define Input_Floating 		1
#define Input_pp					2
// direction options for output
//#define Output_pp 					0
//#define Output_drain				1
//#define Output_alternate_pp 2
//#define Output_alternate_op 3
#define O_GP_PP 0
#define O_GP_OD 1
#define O_AF_PP 2
#define O_AF_OD 3
// state 
#define LOW	 0
#define HIGH 1
void init_GPIO(unsigned short port,unsigned short pin,unsigned short dir,unsigned short opt);
int R_GPIO(unsigned short port,unsigned short pin);
void W_GPIO(unsigned short port,unsigned short pin,unsigned short state);
void Toggle_GPIO(unsigned short port,unsigned short pin);
