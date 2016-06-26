/* Includes ------------------------------------------------------------------*/  

 #ifndef __LCD1602_H
#define __LCD1602_H
#define u_c unsigned char 
#define u_int unsigned int
void DelayMs(double t);  
void SZ_STM32_LCD1602Init(void);  
void LCD1602_Init(void);  
void LCD1602_Clear(void);  
void LCD1602_Write_String(u_int x,u_int y,u_c *s);  
void LCD1602_Write_Char(u_int x,u_int y,u_c Data); 
void LCD1602_ScrollSentence(u_c *s,u_int nbscroll,u_int scollspeed);
u_int strlength(u_c* ch);
u_c* substr(u_c *ch,u_int p,u_int n);
u_c*strcat(u_c*s1, u_c*s2);
u_c* Number_to_str(long double f, u_int vc);
u_c* str_dec_to_base(long int a, int base);
void LCD1602_Blink(u_int x1,u_c* msg1,u_int x2,u_c* msg2,
                    u_int blinknb,u_int blinkspeed);

//void delay(__IO uint32_t nCount) ;
void _nop_(void);
u_c LCD1602_Check_Busy(void);
void LCD1602_Write_Com(u_c com);
void LCD1602_Write_Data(u_c Data);
//void delay(__IO uint32_t nCount) ; 
#endif