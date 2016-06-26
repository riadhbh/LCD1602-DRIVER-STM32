/* Includes ------------------------------------------------------------------*/  
#include "LCD1602.h"  
#include "discover_board.h" 
#include "stm32l1xx_rcc.h"
#include "core_cm3.h"
#include <stdlib.h>
#define LCD1602_GPIO_PORT   GPIOB
#define LCD1602_RS_PIN      GPIO_Pin_5  //P2^6; 
#define LCD1602_RW_PIN      GPIO_Pin_6  //P2^5;   
#define LCD1602_EN_PIN      GPIO_Pin_7  //P2^7;  
  
#define LCD1602_DATA_PIN    GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
#define LCD1602_GPIO_CLK RCC_AHBPeriph_GPIOB  
  

#define RS_CLR LCD1602_GPIO_PORT->BSRRH = LCD1602_RS_PIN  
#define RS_SET LCD1602_GPIO_PORT->BSRRL = LCD1602_RS_PIN  
  
#define RW_CLR LCD1602_GPIO_PORT->BSRRH = LCD1602_RW_PIN  
#define RW_SET LCD1602_GPIO_PORT->BSRRL = LCD1602_RW_PIN  
  
#define EN_CLR LCD1602_GPIO_PORT->BSRRH = LCD1602_EN_PIN  
#define EN_SET LCD1602_GPIO_PORT->BSRRL = LCD1602_EN_PIN  
  
#define LCD1602_DATA_READ  ((GPIO_ReadInputData(LCD1602_GPIO_PORT) & 0xFF00)>>8)  
#define LCD1602_DATA_WRITE(data)  LCD1602_GPIO_PORT->BSRRL = ( data << 8 ); LCD1602_GPIO_PORT->BSRRH = ( ( 0xFF & (~data) ) << 8 );  
//#define LCD1602_DATA_WRITE(data) (LCD1602_GPIO_PORT->BSRR = (data<<8)); (LCD1602_GPIO_PORT->BRR = ((~data)<<8));  

void delay(__IO uint32_t nCount)  
{  
  while(nCount--);
   
}  

void SZ_STM32_LCD1602Init(void)  
{  
  GPIO_InitTypeDef  GPIO_InitStructure;  

  RCC_AHBPeriphClockCmd(LCD1602_GPIO_CLK, ENABLE);  
  
  /* Configure the RS,RW and EN pins */  
  GPIO_InitStructure.GPIO_Pin   = LCD1602_RS_PIN | LCD1602_RW_PIN | LCD1602_EN_PIN;  
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;  
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;  
  GPIO_Init(LCD1602_GPIO_PORT, &GPIO_InitStructure);  
      
  /* Configure the LCD DATA pins */  
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;  
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;  
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;  
  
  GPIO_Init(LCD1602_GPIO_PORT, &GPIO_InitStructure);  

}
void _nop_(void)  
{  
    delay(2000);  
}  
/*------------------------------------------------------ 

------------------------------------------------------*/  
void DelayMs(double t)  
{  
    while(t--)  
    {  
        
        delay(100000);  
    }  
}  
  
/*------------------------------------------------------ 
                    
------------------------------------------------------*/  
void LCD1602_Write_Com(u_c com)   
{      
        _nop_();  
    
    RS_CLR;   
    RW_CLR;   
    EN_SET;   
    LCD1602_DATA_WRITE(com);   
    _nop_();   
    EN_CLR;  
}  
  
/*------------------------------------------------------ 
                  
------------------------------------------------------*/  
void LCD1602_Write_Data(u_c Data)   
{   
     
        _nop_();  
   
    RS_SET;   
    RW_CLR;   
    EN_SET;   
    LCD1602_DATA_WRITE(Data);   
      _nop_();  
    EN_CLR;  
}  
  
/*------------------------------------------------------ 
                
------------------------------------------------------*/  
void LCD1602_Clear(void)   
{   
    LCD1602_Write_Com(0x01);   
    DelayMs(5);  
}  
  
/*------------------------------------------------------ 
                  
------------------------------------------------------*/  
void LCD1602_Write_String(u_int x,u_int y,u_c *s)   
{       
    if (y == 0)   
    {       
        LCD1602_Write_Com(0x80 + x);       
    }  
    else   
    {        
        LCD1602_Write_Com(0xC0 + x);      
    }   
  
    while (*s)   
    {       
        LCD1602_Write_Data( *s);       
        s ++;       
    }  
}  
  
/*------------------------------------------------------ 
               
------------------------------------------------------*/  
void LCD1602_Write_Char(u_int x,u_int y,u_c Data)   
{       
    if (y == 0)   
    {       
        LCD1602_Write_Com(0x80 + x);       
    }      
    else   
    {       
        LCD1602_Write_Com(0xC0 + x);       
    }  
      
    LCD1602_Write_Data( Data);    
}  
  
/*------------------------------------------------------ 
                   
------------------------------------------------------*/  
void LCD1602_Init(void)   
{  
    SZ_STM32_LCD1602Init();  
      
    LCD1602_Write_Com(0x38);  
    DelayMs(5);   
    LCD1602_Write_Com(0x38);   
    DelayMs(5);   
    LCD1602_Write_Com(0x38);   
    DelayMs(5);   
    LCD1602_Write_Com(0x38);    
    LCD1602_Write_Com(0x08);    
    LCD1602_Write_Com(0x01);     
    LCD1602_Write_Com(0x06);     
    DelayMs(5);   
    LCD1602_Write_Com(0x0C);    
}  
/*------------------------------------------------------ 
                   
------------------------------------------------------*/ 
u_int strlength(u_c* ch){
u_int i=0;
while((ch[i]!='\0')) i++;
return(i);
}
/*------------------------------------------------------ 
                   
------------------------------------------------------*/ 
u_c* substr(u_c *ch,u_int p,u_int n){
u_c* res=malloc((n+1)*sizeof(u_c));;
u_int i;
for(i=0;((i<n)&&(ch[i+p]!='\0'));i++)
res[i]=ch[i+p];
res[i]='\0';
return res;
}
/*------------------------------------------------------

------------------------------------------------------*/
u_c*strcat(u_c*s1, u_c*s2){
	u_int l1 = strlength(s1);
	u_int l2 = strlength(s2);
	u_int sz = l1 + l2 + 1;
	u_c *res= calloc(sz,sizeof(u_c));
	for (int i = 0; i < l1;i++)
		res[i] = s1[i];
	for (int i = 0; i < l2; i++)
		res[i + l1] = s2[i];
	res[sz - 1] = '\0';
	return substr(res, 0, 38);
}
/*------------------------------------------------------ 
                
------------------------------------------------------*/
u_c* Number_to_str(long double f,u_int nbc){
u_c*res=NULL;
u_int sz=0;
u_int vc;

if(nbc<=8)//The max digits number after the point is 8 
vc=nbc;
else
vc=8;

long int fn; 
if(f<0)
fn =(long int)(-f);
else
fn =(long int)f;

long double fd = (long double)(f-((long int)f));
if(fd<0) fd=-fd;
fd+=0.000000001;//The Error of miscalculation is 10^(-9)
u_int num_l=0,dec_l=0;
u_int p_num=1,p_dec=1;
while(((long int)(fn/p_num))) {p_num*=10;num_l++;}

long double cd=fd;
long int cn=fn;
//calculate the real number of digits into the decimal part 
while((cd>0.000000001)&&(dec_l<vc)){
p_dec*=10;
cd=fd*p_dec;
cn=(long int) cd;
cd-=cn;
dec_l++;
}

if(f<0){
      if(fn>0){
          if(fd>0 && dec_l!=0)
          sz=num_l+dec_l+3;
          else
           sz=num_l+2;
          
          res=(u_c*)calloc(sz,sizeof(u_c));
          res[0]='-';
          for(int i=1;i<=num_l;i++){
          p_num/=10;
          res[i]=(((int)(fn/p_num))%10)+0x30;
          }
          if(fd>0 && dec_l!=0){
          res[num_l+1]='.';
          for(int i=num_l+2;i<sz-1;i++){
            fd*=10;
            res[i]=(((int)fd)%10)+0x30;
          }
          }
      }else{
          if(fd>0 && dec_l!=0)
          sz=dec_l+4;
          else
            sz=3;
          res=(u_c*)calloc(sz,sizeof(u_c));
          res[0]='-';
          res[1]='0';
          if(fd>0 && dec_l!=0){
          res[2]='.';
          for(int i=3;i<sz-1;i++){
            fd*=10; 
            res[i]=(((int)fd)%10)+0x30;
      }
      }
      }
}else{//f>=0
          if(fn>0){
            if(fd>0 && dec_l!=0)
            sz=num_l+dec_l+2;
            else
              sz=num_l+1;
            
            res=(u_c*)calloc(sz,sizeof(u_c));
            for(int i=0;i<num_l;i++){
             p_num/=10;
            res[i]=(((int)(fn/p_num))%10)+0x30;
            }
            if(fd>0 && dec_l!=0){
            res[num_l]='.';
            for(int i=num_l+1;i<sz-1;i++){
            fd*=10; 
            res[i]=(((int)fd)%10)+0x30;
            }
            }
          }
          else{
            if(fd>0 && dec_l!=0)
            sz=dec_l+3;
            else
              sz=2;
            res=(u_c*)calloc(sz,sizeof(u_c));
            res[0]='0';
            if(fd>0 && dec_l!=0){
            res[1]='.';
            for(int i=2;i<sz-1;i++){
              fd*=10; 
              res[i]=(((int)fd)%10)+0x30;
          }
          }
          }
  }

 res[sz-1]='\0';
return substr(res,0,38);
}


/*------------------------------------------------------ 
str_dec_to_base Converts any long int a to any 1<base<=16
         and returns the result into a String
------------------------------------------------------*/

u_c* str_dec_to_base(long int a, int base) {
	u_c*res;
	u_int sz = 0;
	long int tmp, lim = 1;
	if (base > 1) {
		if (a == 0) {
			sz = 2;
			res = calloc(sz,sizeof(u_c));
			res[0] = '0';
			res[1] = '\0';
			return substr(res,0,38);;
		}
		else {
			u_int n, begin;
			if (a < 0) {
				tmp = -a;
				while (lim <= tmp) { lim *= base; sz++; }
				sz += 2;
				res = calloc(sz,sizeof(u_c));
				begin = 1;
				res[0] = 0x30;
			}
			else {
				tmp = a;
				while (lim <= tmp) { lim *= base; sz++; }
				sz+=1;
				res = calloc(sz,sizeof(u_c));
				begin = 0;
			}
			lim /= base;
			for (int i = begin; i < sz - 1; i++) {
				n = ((int)(tmp / lim));
				if (n < 10)
					res[i] = (u_c)(n + 0x30);
				else
					res[i] = (u_c)((n - 10) + 0x41);
				tmp -= (n*lim);
				lim /= base;
			}
			if (a < 0) {
				u_int notzero = 0;
				for (int i = sz - 2; i >= 0; i--) {
					if (res[i] != 0x30 && !notzero) {
						notzero = 1;
						if (base > 10) {
							if (res[i] > 0x40)
								res[i] = base - 10 + 0x41 - res[i] + 0x30;
							else {
								if ((base - 10 + 0x30) >= res[i])
									res[i] = base - 10 + 0x30 - res[i] + 0x41;
								else
									res[i] = base + 2 * 0x30 - res[i];
							}
						}
						else
							res[i] = base + 2 * 0x30 - res[i];
						continue;
					}
					if (notzero) {
						if (base > 10) {
							if (res[i] > 0x40)
								res[i] = base - 11 + 0x41 - res[i] + 0x30;
							else {
								if ((base - 11 + 0x30) >= res[i])
									res[i] = base - 11 + 0x30 - res[i] + 0x41;
								else
									res[i] = base - 1 + 2 * 0x30 - res[i];
							}
						}
						else
							res[i] = base - 1 + 2 * 0x30 - res[i];
					}
				}
			}
			res[sz - 1] = '\0';
			return substr(res,0,38);;
		}
	}else
          return "Incorrect Base";
}

/*------------------------------------------------------ 
                   
------------------------------------------------------*/
void LCD1602_Blink(u_int x1,u_c* msg1,u_int x2,u_c* msg2,
                    u_int blinknb,u_int blinkspeed){
u_int disp_t=(2000/blinkspeed)+1;
u_int clrs_t=disp_t/2;

u_int lm1=strlength(msg1);
u_int lm2=strlength(msg2);

LCD1602_Clear();
if(((lm1+x1)<40) && ((lm2+x2)<40)){
for (int i=0;i<blinknb;i++){  
LCD1602_Write_String(x1,0,msg1);
LCD1602_Write_String(x2,1,msg2); 
DelayMs(disp_t);
LCD1602_Clear();
DelayMs(clrs_t);
}
}else{
  if((lm1+x1)>=40&&(lm2+x2)<40){
      for (int i=0;i<blinknb;i++){  
      LCD1602_Write_String(x2,1,msg2); 
      DelayMs(disp_t);
      LCD1602_Clear();
      DelayMs(clrs_t);
}
  }else{
    if((lm2+x2)>=40&&(lm1+x1)<40){
      for (int i=0;i<blinknb;i++){  
      LCD1602_Write_String(x1,0,msg1); 
      DelayMs(disp_t);
      LCD1602_Clear();
      DelayMs(clrs_t);
  }
  }else
  LCD1602_ScrollSentence("Messages may overlap",1,300);
  }

}
}
/*------------------------------------------------------ 
                   
------------------------------------------------------*/ 
void LCD1602_ScrollSentence(u_c *s,
                            u_int nbscroll,u_int scrollspeed){
int end_str=strlength(s)-1;
int end_lcd=16-1;
int limit=end_lcd+end_str+2;
u_int sp=(400/scrollspeed)+5;
LCD1602_Clear();
if(end_str<24){//LCD memory max address
for (int i=0;i<nbscroll;i++){
  for(int j=0;j<limit;j++){
    if(j<end_lcd)
      LCD1602_Write_String(end_lcd-j,0,s);
    else
      LCD1602_Write_String(0,0,s+j-end_lcd);
    
    if(j<=end_str)
      LCD1602_Write_String(0,1,s+end_str-j);
      else
      LCD1602_Write_String(j-end_str,1,s);  
    DelayMs(sp);
    LCD1602_Write_Com(0x01);//clear
  }
}
}else{
for (int i=0;i<nbscroll;i++){
  for(int j=0;j<limit;j++){
    
    if(j<end_lcd)
      LCD1602_Write_String(end_lcd-j,0,s);
    else
      LCD1602_Write_String(0,0,s+j-end_lcd);
    DelayMs(sp);
    LCD1602_Write_Com(0x01);//clear
  }
}
}
}
